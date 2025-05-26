
#ifndef IStateListManager_hpp
	#define IStateListManager_hpp

	#include "iState.hpp"
	#include "ClassCount.hpp"
	#include "ArrayRawList.hpp"
	#include "UpdateManager.hpp"

	#if defined(pankey_Log) && (defined(IStateListManager_Log) || defined(pankey_Global_Log) || defined(pankey_ApplicationSystem_Log))
		#include "Logger_status.hpp"
		#define IStateListManagerLog(status,method,mns) pankey_Log(status,"IStateListManager",method,mns)
	#else
		#define IStateListManagerLog(status,method,mns)
	#endif

	namespace pankey{

		namespace ApplicationSystem{

			template<class A, class... Args>
			class IStateListManager : virtual public Base::UpdateManager<A,Args...>{
				public:
					IStateListManager(){
						IStateListManagerLog(pankey_Log_StartMethod, "Constructor", "");
						IStateListManagerLog(pankey_Log_EndMethod, "Constructor", "");
					}
					virtual ~IStateListManager(){
						IStateListManagerLog(pankey_Log_StartMethod, "Destructor", "");
						IStateListManagerLog(pankey_Log_EndMethod, "Destructor", "");
					}

					template<class AS>
					AS& addIState(){
						IStateListManagerLog(pankey_Log_StartMethod, "addState",  "");
						AS* i_state = new AS();
						m_initialize_state_list.addPointer(i_state);
						IStateListManagerLog(pankey_Log_EndMethod, "addState", "");
						return *i_state;
					}

					virtual bool containIState(long a_type){
						IStateListManagerLog(pankey_Log_StartMethod, "containState",  "");
						for(int x = 0; x < m_initialize_state_list.length(); x++){
							Base::iState<Args...>* f_state = m_initialize_state_list.getPointerByIndex(x);
							if(f_state == nullptr){
								continue;
							}
							if(f_state->getType() == a_type){
								return true;
							}
						}
						for(int x = 0; x < m_state_list.length(); x++){
							Base::iState<Args...>* f_state = m_state_list.getPointerByIndex(x);
							if(f_state == nullptr){
								continue;
							}
							if(f_state->getType() == a_type){
								return true;
							}
						}
						IStateListManagerLog(pankey_Log_EndMethod, "containState", "");
						return false;
					}

					template<class AS>
					bool containIState(){
						IStateListManagerLog(pankey_Log_StartMethod, "containState",  "");
						long i_type = Base::ClassCount<AS>::get();
						IStateListManagerLog(pankey_Log_EndMethod, "containState", "");
						return this->containIState(i_type);
					}

					template<class AS>
					void putIState(){
						IStateListManagerLog(pankey_Log_StartMethod, "putState",  "");
						if(this->containIState(Base::ClassCount<AS>::get())){
							return;
						}
						this->addIStatePointer(new AS());
						IStateListManagerLog(pankey_Log_EndMethod, "putState", "");
					}

					virtual int IState_length(){
						return m_state_list.length() + m_initialize_state_list.length();
					}

					virtual int length(){
						return m_state_list.length() + m_initialize_state_list.length();
					}
					
					virtual void clearIState(){
						IStateListManagerLog(pankey_Log_StartMethod, "clearState",  "");
						for(int x = 0; x < m_state_list.length(); x++){
							Base::iState<Args...>* f_state = m_state_list.getPointerByIndex(x);
							if(f_state == nullptr){
								continue;
							}
							f_state->onDisable();
						}
						for(int x = 0; x < m_initialize_state_list.length(); x++){
							Base::iState<Args...>* f_state = m_initialize_state_list.getPointerByIndex(x);
							if(f_state == nullptr){
								continue;
							}
							f_state->onDisable();
						}
						m_state_list.clear();
						m_initialize_state_list.clear();
						IStateListManagerLog(pankey_Log_EndMethod, "clearState", "");
					}
					
					virtual void clear(){
						IStateListManagerLog(pankey_Log_StartMethod, "clear",  "");
						for(int x = 0; x < m_state_list.length(); x++){
							Base::iState<Args...>* f_state = m_state_list.getPointerByIndex(x);
							if(f_state == nullptr){
								continue;
							}
							f_state->onDisable();
						}
						for(int x = 0; x < m_initialize_state_list.length(); x++){
							Base::iState<Args...>* f_state = m_initialize_state_list.getPointerByIndex(x);
							if(f_state == nullptr){
								continue;
							}
							f_state->onDisable();
						}
						m_state_list.clear();
						m_initialize_state_list.clear();
						IStateListManagerLog(pankey_Log_EndMethod, "clear", "");
					}

					virtual void initialize(A& a_app){
						IStateListManagerLog(pankey_Log_StartMethod, "initialize",  "");
						for(int x = 0; x < this->m_initialize_state_list.length(); x++){
							IStateListManagerLog(pankey_Log_StartMethod, "initialize",  "iterating through initializing states");
							IStateListManagerLog(pankey_Log_StartMethod, "initialize",  "iteration: ");
							IStateListManagerLog(pankey_Log_StartMethod, "initialize",  x);
							Base::iState<Args...>* f_state = this->m_initialize_state_list.getPointerByIndex(x);
							if(f_state == nullptr){
								IStateListManagerLog(pankey_Log_StartMethod, "initialize",  "initializing state is null");
								continue;
							}
							f_state->initialize();
							f_state->onEnable();
							this->m_state_list.addPointer(f_state);
						}
						IStateListManagerLog(pankey_Log_StartMethod, "initialize",  "m_initialize_state_list");
						this->m_initialize_state_list.reset();
						IStateListManagerLog(pankey_Log_EndMethod, "initialize", "");
					}

					virtual void update(A& a_app, Args... a_values){
						IStateListManagerLog(pankey_Log_StartMethod, "update",  "");
						
						if(!this->m_initialize_state_list.isEmpty()){
							this->initialize(a_app);
						}

						for(int x = 0; x < this->m_state_list.length(); x++){
							IStateListManagerLog(pankey_Log_StartMethod, "update",  "iterating through all states");
							IStateListManagerLog(pankey_Log_StartMethod, "update",  "iteration: ");
							IStateListManagerLog(pankey_Log_StartMethod, "update",  x);
							Base::iState<Args...>* f_state = this->m_state_list.getPointerByIndex(x);
							if(f_state == nullptr){
								continue;
							}
							f_state->update(a_values...);
						}

						IStateListManagerLog(pankey_Log_EndMethod, "update", "");
					}

					template<class AS, class... MArgs>
					void runIStateMethod(Base::InvokeClassMethod<AS,MArgs...> a_method, MArgs... a_args){
						IStateListManagerLog(pankey_Log_StartMethod, "runStateMethod",  "");
						Base::Type* f_state = this->getIStatePointerByType(Base::ClassCount<AS>::get());
						if(f_state == nullptr){
							IStateListManagerLog(pankey_Log_EndMethod, "runStateMethod", "f_state == nullptr");
							return;
						}
						AS& i_state = f_state->cast<AS>();
						Base::invoke<AS,MArgs...>(i_state, a_method, a_args...);
						IStateListManagerLog(pankey_Log_EndMethod, "runStateMethod", "");
					}

				protected:

					virtual Base::iState<Args...>* addIStatePointer(Base::iState<Args...>* a_state){
						IStateListManagerLog(pankey_Log_StartMethod, "addStatePointer",  "");
						m_initialize_state_list.addPointer(a_state);
						IStateListManagerLog(pankey_Log_EndMethod, "addStatePointer", "");
						return a_state;
					}

					virtual bool containIStatePointer(Base::iState<Args...>* a_state){
						IStateListManagerLog(pankey_Log_StartMethod, "containStatePointer",  "");
						if(a_state == nullptr){
							return false;
						}
						long i_type = a_state->getType();
						IStateListManagerLog(pankey_Log_EndMethod, "containStatePointer", "");
						return this->containIState(i_type);
					}

					virtual Base::iState<Args...>* getIStatePointerByType(long a_type){
						IStateListManagerLog(pankey_Log_StartMethod, "getStatePointerByType",  "");
						IStateListManagerLog(pankey_Log_Statement, "getStatePointerByType",  "a_type");
						IStateListManagerLog(pankey_Log_Statement, "getStatePointerByType",  a_type);
						IStateListManagerLog(pankey_Log_Statement, "getStatePointerByType",  "m_initialize_state_list length");
						IStateListManagerLog(pankey_Log_Statement, "getStatePointerByType",  m_initialize_state_list.length());
						IStateListManagerLog(pankey_Log_Statement, "getStatePointerByType",  "m_state_list length");
						IStateListManagerLog(pankey_Log_Statement, "getStatePointerByType",  m_state_list.length());
						for(int x = 0; x < m_initialize_state_list.length(); x++){
							Base::iState<Args...>* f_state = m_initialize_state_list.getPointerByIndex(x);
							if(f_state == nullptr){
								IStateListManagerLog(pankey_Log_Statement, "getStatePointerByType",  "m_initialize_state_list f_state == nullptr");
								continue;
							}
							IStateListManagerLog(pankey_Log_Statement, "getStatePointerByType",  "m_initialize_state_list state type:");
							IStateListManagerLog(pankey_Log_Statement, "getStatePointerByType",  f_state->getType());
							if(f_state->getType() == a_type){
								IStateListManagerLog(pankey_Log_EndMethod, "getStatePointerByType", " m_initialize_state_listf_state->getType() == a_type");
								return f_state;
							}
						}
						for(int x = 0; x < m_state_list.length(); x++){
							Base::iState<Args...>* f_state = m_state_list.getPointerByIndex(x);
							if(f_state == nullptr){
								IStateListManagerLog(pankey_Log_Statement, "getStatePointerByType",  "m_state_list f_state == nullptr");
								continue;
							}
							IStateListManagerLog(pankey_Log_Statement, "getStatePointerByType",  "m_state_list state type:");
							IStateListManagerLog(pankey_Log_Statement, "getStatePointerByType",  f_state->getType());
							if(f_state->getType() == a_type){
								IStateListManagerLog(pankey_Log_EndMethod, "getStatePointerByType", "m_state_list f_state->getType() == a_type");
								return f_state;
							}
						}
						IStateListManagerLog(pankey_Log_EndMethod, "getStatePointerByType", "return nullptr");
						return nullptr;
					}
					
					virtual Base::iState<Args...>* removeIStatePointer(Base::iState<Args...>* a_state){
						IStateListManagerLog(pankey_Log_StartMethod, "removeStatePointer",  "");
						Base::iState<Args...>* i_state = m_initialize_state_list.removePointerByPointer(a_state);
						if(i_state == nullptr){
							return nullptr;
						}
						i_state->onDisable();
						IStateListManagerLog(pankey_Log_EndMethod, "removeStatePointer", "");
						return i_state;
					}

					Base::ArrayRawList<Base::iState<Args...>> m_state_list;
					Base::ArrayRawList<Base::iState<Args...>> m_initialize_state_list;
					
			};

		}

	}

#endif
