
#ifndef StateListManager_hpp
	#define StateListManager_hpp

	#include "State.hpp"
	#include "ClassCount.hpp"
	#include "ArrayRawList.hpp"
	#include "UpdateManager.hpp"

	#if defined(pankey_Log) && (defined(StateListManager_Log) || defined(pankey_Global_Log) || defined(pankey_ApplicationSystem_Log))
		#include "Logger_status.hpp"
		#define StateListManagerLog(status,method,mns) pankey_Log(status,"StateListManager",method,mns)
	#else
		#define StateListManagerLog(status,method,mns)
	#endif

	namespace pankey{

		namespace ApplicationSystem{

			template<class A, class... Args>
			class StateListManager : virtual public UpdateManager<A,Args...>{
				public:
					StateListManager(){
						StateListManagerLog(pankey_Log_StartMethod, "Constructor", "");
						StateListManagerLog(pankey_Log_EndMethod, "Constructor", "");
					}
					virtual ~StateListManager(){
						StateListManagerLog(pankey_Log_StartMethod, "Destructor", "");
						StateListManagerLog(pankey_Log_EndMethod, "Destructor", "");
					}

					template<class AS>
					AS& addState(){
						StateListManagerLog(pankey_Log_StartMethod, "addState",  "");
						AS* i_state = new AS();
						m_initialize_state_list.addPointer(i_state);
						StateListManagerLog(pankey_Log_EndMethod, "addState", "");
						return *i_state;
					}

					virtual bool containState(long a_type){
						StateListManagerLog(pankey_Log_StartMethod, "containState",  "");
						for(int x = 0; x < m_initialize_state_list.length(); x++){
							Base::State<Args...>* f_state = m_initialize_state_list.getPointerByIndex(x);
							if(f_state == nullptr){
								continue;
							}
							if(f_state->getType() == a_type){
								return true;
							}
						}
						for(int x = 0; x < m_state_list.length(); x++){
							Base::State<Args...>* f_state = m_state_list.getPointerByIndex(x);
							if(f_state == nullptr){
								continue;
							}
							if(f_state->getType() == a_type){
								return true;
							}
						}
						StateListManagerLog(pankey_Log_EndMethod, "containState", "");
						return false;
					}

					template<class AS>
					bool containState(){
						StateListManagerLog(pankey_Log_StartMethod, "containState",  "");
						long i_type = Base::ClassCount<AS>::get();
						StateListManagerLog(pankey_Log_EndMethod, "containState", "");
						return this->containState(i_type);
					}

					template<class AS>
					void putState(){
						StateListManagerLog(pankey_Log_StartMethod, "putState",  "");
						if(this->containState(Base::ClassCount<AS>::get())){
							return;
						}
						this->addStatePointer(new AS());
						StateListManagerLog(pankey_Log_EndMethod, "putState", "");
					}

					virtual int State_length(){
						return m_state_list.length() + m_initialize_state_list.length();
					}

					virtual int length(){
						return m_state_list.length() + m_initialize_state_list.length();
					}
					
					virtual void clearState(){
						StateListManagerLog(pankey_Log_StartMethod, "clearState",  "");
						for(int x = 0; x < m_state_list.length(); x++){
							Base::State<Args...>* f_state = m_state_list.getPointerByIndex(x);
							if(f_state == nullptr){
								continue;
							}
							f_state->onDisable();
						}
						for(int x = 0; x < m_initialize_state_list.length(); x++){
							Base::State<Args...>* f_state = m_initialize_state_list.getPointerByIndex(x);
							if(f_state == nullptr){
								continue;
							}
							f_state->onDisable();
						}
						m_state_list.clear();
						m_initialize_state_list.clear();
						StateListManagerLog(pankey_Log_EndMethod, "clearState", "");
					}
					
					virtual void clear(){
						StateListManagerLog(pankey_Log_StartMethod, "clear",  "");
						for(int x = 0; x < m_state_list.length(); x++){
							Base::State<Args...>* f_state = m_state_list.getPointerByIndex(x);
							if(f_state == nullptr){
								continue;
							}
							f_state->onDisable();
						}
						for(int x = 0; x < m_initialize_state_list.length(); x++){
							Base::State<Args...>* f_state = m_initialize_state_list.getPointerByIndex(x);
							if(f_state == nullptr){
								continue;
							}
							f_state->onDisable();
						}
						m_state_list.clear();
						m_initialize_state_list.clear();
						StateListManagerLog(pankey_Log_EndMethod, "clear", "");
					}

					virtual void initialize(A& a_app){
						StateListManagerLog(pankey_Log_StartMethod, "initialize",  "");
						for(int x = 0; x < this->m_initialize_state_list.length(); x++){
							StateListManagerLog(pankey_Log_StartMethod, "initialize",  "iterating through initializing states");
							StateListManagerLog(pankey_Log_StartMethod, "initialize",  "iteration: ");
							StateListManagerLog(pankey_Log_StartMethod, "initialize",  x);
							Base::State<Args...>* f_state = this->m_initialize_state_list.getPointerByIndex(x);
							if(f_state == nullptr){
								StateListManagerLog(pankey_Log_StartMethod, "initialize",  "initializing state is null");
								continue;
							}
							f_state->initialize();
							f_state->onEnable();
							this->m_state_list.addPointer(f_state);
						}
						StateListManagerLog(pankey_Log_StartMethod, "initialize",  "m_initialize_state_list");
						this->m_initialize_state_list.reset();
						StateListManagerLog(pankey_Log_EndMethod, "initialize", "");
					}

					virtual void update(A& a_app, Args... a_values){
						StateListManagerLog(pankey_Log_StartMethod, "update",  "");
						
						if(!this->m_initialize_state_list.isEmpty()){
							this->initialize(a_app);
						}

						for(int x = 0; x < this->m_state_list.length(); x++){
							StateListManagerLog(pankey_Log_StartMethod, "update",  "iterating through all states");
							StateListManagerLog(pankey_Log_StartMethod, "update",  "iteration: ");
							StateListManagerLog(pankey_Log_StartMethod, "update",  x);
							Base::State<Args...>* f_state = this->m_state_list.getPointerByIndex(x);
							if(f_state == nullptr){
								continue;
							}
							f_state->update(a_values...);
						}

						StateListManagerLog(pankey_Log_EndMethod, "update", "");
					}

					template<class AS, class... MArgs>
					void runStateMethod(Base::InvokeClassMethod<AS,MArgs...> a_method, MArgs... a_args){
						StateListManagerLog(pankey_Log_StartMethod, "runStateMethod",  "");
						Base::Type* f_state = this->getStatePointerByType(Base::ClassCount<AS>::get());
						if(f_state == nullptr){
							StateListManagerLog(pankey_Log_EndMethod, "runStateMethod", "f_state == nullptr");
							return;
						}
						AS& i_state = f_state->cast<AS>();
						Base::invoke<AS,MArgs...>(i_state, a_method, a_args...);
						StateListManagerLog(pankey_Log_EndMethod, "runStateMethod", "");
					}

				protected:

					virtual Base::State<Args...>* addStatePointer(Base::State<Args...>* a_state){
						StateListManagerLog(pankey_Log_StartMethod, "addStatePointer",  "");
						m_initialize_state_list.addPointer(a_state);
						StateListManagerLog(pankey_Log_EndMethod, "addStatePointer", "");
						return a_state;
					}

					virtual bool containStatePointer(Base::State<Args...>* a_state){
						StateListManagerLog(pankey_Log_StartMethod, "containStatePointer",  "");
						if(a_state == nullptr){
							return false;
						}
						long i_type = a_state->getType();
						StateListManagerLog(pankey_Log_EndMethod, "containStatePointer", "");
						return this->containState(i_type);
					}

					virtual Base::State<Args...>* getStatePointerByType(long a_type){
						StateListManagerLog(pankey_Log_StartMethod, "getStatePointerByType",  "");
						StateListManagerLog(pankey_Log_Statement, "getStatePointerByType",  "a_type");
						StateListManagerLog(pankey_Log_Statement, "getStatePointerByType",  a_type);
						StateListManagerLog(pankey_Log_Statement, "getStatePointerByType",  "m_initialize_state_list length");
						StateListManagerLog(pankey_Log_Statement, "getStatePointerByType",  m_initialize_state_list.length());
						StateListManagerLog(pankey_Log_Statement, "getStatePointerByType",  "m_state_list length");
						StateListManagerLog(pankey_Log_Statement, "getStatePointerByType",  m_state_list.length());
						for(int x = 0; x < m_initialize_state_list.length(); x++){
							Base::State<Args...>* f_state = m_initialize_state_list.getPointerByIndex(x);
							if(f_state == nullptr){
								StateListManagerLog(pankey_Log_Statement, "getStatePointerByType",  "m_initialize_state_list f_state == nullptr");
								continue;
							}
							StateListManagerLog(pankey_Log_Statement, "getStatePointerByType",  "m_initialize_state_list state type:");
							StateListManagerLog(pankey_Log_Statement, "getStatePointerByType",  f_state->getType());
							if(f_state->getType() == a_type){
								StateListManagerLog(pankey_Log_EndMethod, "getStatePointerByType", " m_initialize_state_listf_state->getType() == a_type");
								return f_state;
							}
						}
						for(int x = 0; x < m_state_list.length(); x++){
							Base::State<Args...>* f_state = m_state_list.getPointerByIndex(x);
							if(f_state == nullptr){
								StateListManagerLog(pankey_Log_Statement, "getStatePointerByType",  "m_state_list f_state == nullptr");
								continue;
							}
							StateListManagerLog(pankey_Log_Statement, "getStatePointerByType",  "m_state_list state type:");
							StateListManagerLog(pankey_Log_Statement, "getStatePointerByType",  f_state->getType());
							if(f_state->getType() == a_type){
								StateListManagerLog(pankey_Log_EndMethod, "getStatePointerByType", "m_state_list f_state->getType() == a_type");
								return f_state;
							}
						}
						StateListManagerLog(pankey_Log_EndMethod, "getStatePointerByType", "return nullptr");
						return nullptr;
					}
					
					virtual Base::State<Args...>* removeStatePointer(Base::State<Args...>* a_state){
						StateListManagerLog(pankey_Log_StartMethod, "removeStatePointer",  "");
						Base::State<Args...>* i_state = m_initialize_state_list.removePointerByPointer(a_state);
						if(i_state == nullptr){
							return nullptr;
						}
						i_state->onDisable();
						StateListManagerLog(pankey_Log_EndMethod, "removeStatePointer", "");
						return i_state;
					}

					Base::ArrayRawList<Base::State<Args...>> m_state_list;
					Base::ArrayRawList<Base::State<Args...>> m_initialize_state_list;
					
			};

		}

	}

#endif
