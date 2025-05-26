
#ifndef IStateMapManager_hpp
	#define IStateMapManager_hpp

	#include "AppState.hpp"
	#include "ClassCount.hpp"
	#include "ArrayRawList.hpp"
	#include "UpdateManager.hpp"

	#if defined(pankey_Log) && (defined(IStateMapManager_Log) || defined(pankey_Global_Log) || defined(pankey_ApplicationSystem_Log))
		#include "Logger_status.hpp"
		#define IStateMapManagerLog(status,method,mns) pankey_Log(status,"IStateMapManager",method,mns)
	#else
		#define IStateMapManagerLog(status,method,mns)
	#endif

	namespace pankey{

		namespace ApplicationSystem{

			template<class A, class... Args>
			class IStateMapManager : virtual public Base::UpdateManager<A,Args...>{
				public:
					IStateMapManager(){
						IStateMapManagerLog(pankey_Log_StartMethod, "Constructor", "");
						IStateMapManagerLog(pankey_Log_EndMethod, "Constructor", "");
					}
					virtual ~IStateMapManager(){
						IStateMapManagerLog(pankey_Log_StartMethod, "Destructor", "");
						IStateMapManagerLog(pankey_Log_EndMethod, "Destructor", "");
					}

					template<class AS>
					AS& addIState(const Base::CharArray& a_name){
						IStateMapManagerLog(pankey_Log_StartMethod, "addState",  "");
						AS* i_state = new AS();
						m_initialize_state_map.addPointer(a_name, i_state);
						IStateMapManagerLog(pankey_Log_EndMethod, "addState", "");
						return *i_state;
					}

					virtual bool containIState(long a_type){
						IStateMapManagerLog(pankey_Log_StartMethod, "containState",  "");
						for(int x = 0; x < m_initialize_state_map.length(); x++){
							Base::iState<Args...>* f_state = m_initialize_state_map.getValuePointerByIndex(x);
							if(f_state == nullptr){
								continue;
							}
							if(f_state->getType() == a_type){
								return true;
							}
						}
						for(int x = 0; x < m_state_map.length(); x++){
							Base::iState<Args...>* f_state = m_state_map.getValuePointerByIndex(x);
							if(f_state == nullptr){
								continue;
							}
							if(f_state->getType() == a_type){
								return true;
							}
						}
						IStateMapManagerLog(pankey_Log_EndMethod, "containState", "");
						return false;
					}

					template<class AS>
					bool containIState(){
						IStateMapManagerLog(pankey_Log_StartMethod, "containState",  "");
						long i_type = Base::ClassCount<AS>::get();
						IStateMapManagerLog(pankey_Log_EndMethod, "containState", "");
						return this->containIState(i_type);
					}

					template<class AS>
					void putIState(const Base::CharArray& a_name){
						IStateMapManagerLog(pankey_Log_StartMethod, "putState",  "");
						if(this->containIState(Base::ClassCount<AS>::get())){
							return;
						}
						this->addIStatePointer(a_name, new AS());
						IStateMapManagerLog(pankey_Log_EndMethod, "putState", "");
					}

					virtual int IState_length(){
						return m_state_map.length() + m_initialize_state_map.length();
					}

					virtual int length(){
						return m_state_map.length() + m_initialize_state_map.length();
					}
					
					virtual void clearIState(){
						IStateMapManagerLog(pankey_Log_StartMethod, "clearState",  "");
						for(int x = 0; x < m_state_map.length(); x++){
							Base::iState<Args...>* f_state = m_state_map.getValuePointerByIndex(x);
							if(f_state == nullptr){
								continue;
							}
							f_state->onDisable();
						}
						for(int x = 0; x < m_initialize_state_map.length(); x++){
							Base::iState<Args...>* f_state = m_initialize_state_map.getValuePointerByIndex(x);
							if(f_state == nullptr){
								continue;
							}
							f_state->onDisable();
						}
						m_state_map.clear();
						m_initialize_state_map.clear();
						IStateMapManagerLog(pankey_Log_EndMethod, "clearState", "");
					}
					
					virtual void clear(){
						IStateMapManagerLog(pankey_Log_StartMethod, "clear",  "");
						for(int x = 0; x < m_state_map.length(); x++){
							Base::iState<Args...>* f_state = m_state_map.getValuePointerByIndex(x);
							if(f_state == nullptr){
								continue;
							}
							f_state->onDisable();
						}
						for(int x = 0; x < m_initialize_state_map.length(); x++){
							Base::iState<Args...>* f_state = m_initialize_state_map.getValuePointerByIndex(x);
							if(f_state == nullptr){
								continue;
							}
							f_state->onDisable();
						}
						m_state_map.clear();
						m_initialize_state_map.clear();
						IStateMapManagerLog(pankey_Log_EndMethod, "clear", "");
					}

					virtual void initialize(A& a_app){
						IStateMapManagerLog(pankey_Log_StartMethod, "initialize",  "");
						for(int x = 0; x < this->m_initialize_state_map.length(); x++){
							IStateMapManagerLog(pankey_Log_StartMethod, "initialize",  "iterating through initializing states");
							IStateMapManagerLog(pankey_Log_StartMethod, "initialize",  "iteration: ");
							IStateMapManagerLog(pankey_Log_StartMethod, "initialize",  x);
							Base::CharArray* f_name = this->m_initialize_state_map.getKeyPointerByIndex(x);
							Base::iState<Args...>* f_state = this->m_initialize_state_map.getValuePointerByIndex(x);
							if(f_state == nullptr || f_name == nullptr){
								IStateMapManagerLog(pankey_Log_StartMethod, "initialize",  "initializing state is null");
								continue;
							}
							f_state->initialize();
							f_state->onEnable();
							this->m_state_map.addPointers(f_name, f_state);
						}
						IStateMapManagerLog(pankey_Log_StartMethod, "initialize",  "m_initialize_state_map");
						this->m_initialize_state_map.reset();
						IStateMapManagerLog(pankey_Log_EndMethod, "initialize", "");
					}

					virtual void update(A& a_app, Args... a_values){
						IStateMapManagerLog(pankey_Log_StartMethod, "update",  "");
						
						if(!this->m_initialize_state_map.isEmpty()){
							this->initialize(a_app);
						}

						for(int x = 0; x < this->m_state_map.length(); x++){
							IStateMapManagerLog(pankey_Log_StartMethod, "update",  "iterating through all states");
							IStateMapManagerLog(pankey_Log_StartMethod, "update",  "iteration: ");
							IStateMapManagerLog(pankey_Log_StartMethod, "update",  x);
							Base::iState<Args...>* f_state = this->m_state_map.getValuePointerByIndex(x);
							if(f_state == nullptr){
								continue;
							}
							f_state->update(a_values...);
						}

						IStateMapManagerLog(pankey_Log_EndMethod, "update", "");
					}

					template<class AS, class... MArgs>
					void runIStateMethod(Base::InvokeClassMethod<AS,MArgs...> a_method, MArgs... a_args){
						IStateMapManagerLog(pankey_Log_StartMethod, "run",  "");
						Base::Type* f_state = this->getIStatePointerByType(Base::ClassCount<AS>::get());
						if(f_state == nullptr){
							IStateMapManagerLog(pankey_Log_EndMethod, "run", "f_state == nullptr");
							return;
						}
						AS& i_state = f_state->cast<AS>();
						Base::invoke<AS,MArgs...>(i_state, a_method, a_args...);
						IStateMapManagerLog(pankey_Log_EndMethod, "run", "");
					}

				protected:

					virtual Base::iState<Args...>* addIStatePointer(const Base::CharArray& a_name, Base::iState<Args...>* a_state){
						IStateMapManagerLog(pankey_Log_StartMethod, "addStatePointer",  "");
						m_initialize_state_map.addPointer(a_name, a_state);
						IStateMapManagerLog(pankey_Log_EndMethod, "addStatePointer", "");
						return a_state;
					}

					virtual bool containIStatePointer(Base::iState<Args...>* a_state){
						IStateMapManagerLog(pankey_Log_StartMethod, "containStatePointer",  "");
						if(a_state == nullptr){
							return false;
						}
						long i_type = a_state->getType();
						IStateMapManagerLog(pankey_Log_EndMethod, "containStatePointer", "");
						return this->containIState(i_type);
					}

					virtual Base::iState<Args...>* getIStatePointerByType(long a_type){
						IStateMapManagerLog(pankey_Log_StartMethod, "getStatePointerByType",  "");
						IStateMapManagerLog(pankey_Log_Statement, "getStatePointerByType",  "a_type");
						IStateMapManagerLog(pankey_Log_Statement, "getStatePointerByType",  a_type);
						IStateMapManagerLog(pankey_Log_Statement, "getStatePointerByType",  "m_initialize_state_map length");
						IStateMapManagerLog(pankey_Log_Statement, "getStatePointerByType",  m_initialize_state_map.length());
						IStateMapManagerLog(pankey_Log_Statement, "getStatePointerByType",  "m_state_map length");
						IStateMapManagerLog(pankey_Log_Statement, "getStatePointerByType",  m_state_map.length());
						for(int x = 0; x < m_initialize_state_map.length(); x++){
							Base::iState<Args...>* f_state = m_initialize_state_map.getValuePointerByIndex(x);
							if(f_state == nullptr){
								IStateMapManagerLog(pankey_Log_Statement, "getStatePointerByType",  "m_initialize_state_map f_state == nullptr");
								continue;
							}
							IStateMapManagerLog(pankey_Log_Statement, "getStatePointerByType",  "m_initialize_state_map state type:");
							IStateMapManagerLog(pankey_Log_Statement, "getStatePointerByType",  f_state->getType());
							if(f_state->getType() == a_type){
								IStateMapManagerLog(pankey_Log_EndMethod, "getStatePointerByType", " m_initialize_state_mapf_state->getType() == a_type");
								return f_state;
							}
						}
						for(int x = 0; x < m_state_map.length(); x++){
							Base::iState<Args...>* f_state = m_state_map.getValuePointerByIndex(x);
							if(f_state == nullptr){
								IStateMapManagerLog(pankey_Log_Statement, "getStatePointerByType",  "m_state_map f_state == nullptr");
								continue;
							}
							IStateMapManagerLog(pankey_Log_Statement, "getStatePointerByType",  "m_state_map state type:");
							IStateMapManagerLog(pankey_Log_Statement, "getStatePointerByType",  f_state->getType());
							if(f_state->getType() == a_type){
								IStateMapManagerLog(pankey_Log_EndMethod, "getStatePointerByType", "m_state_map f_state->getType() == a_type");
								return f_state;
							}
						}
						IStateMapManagerLog(pankey_Log_EndMethod, "getStatePointerByType", "return nullptr");
						return nullptr;
					}
					
					virtual Base::RawMapEntry<Base::CharArray,Base::iState<Args...>> removeIStatePointers(Base::iState<Args...>* a_state){
						IStateMapManagerLog(pankey_Log_StartMethod, "removeStatePointers",  "");
						Base::RawMapEntry<Base::CharArray,Base::iState<Args...>> i_entry = m_initialize_state_map.removePointersByValuePointer(a_state);
						if(i_entry.isNull()){
							return i_entry;
						}
						Base::iState<Args...>* i_state = i_entry.getValue();
						if(i_state == nullptr){
							return i_entry;
						}
						i_state->onDisable();
						IStateMapManagerLog(pankey_Log_EndMethod, "removeStatePointers", "");
						return i_entry;
					}

					Base::ArrayRawMap<Base::CharArray,Base::iState<Args...>> m_state_map;
					Base::ArrayRawMap<Base::CharArray,Base::iState<Args...>> m_initialize_state_map;
					
					
			};

		}

	}

#endif
