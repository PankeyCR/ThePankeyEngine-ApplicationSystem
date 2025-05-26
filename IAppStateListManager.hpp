
#ifndef IAppStateListManager_hpp
	#define IAppStateListManager_hpp

	#include "iAppState.hpp"
	#include "ClassCount.hpp"
	#include "ArrayRawList.hpp"
	#include "UpdateManager.hpp"

	#if defined(pankey_Log) && (defined(IAppStateListManager_Log) || defined(pankey_Global_Log) || defined(pankey_ApplicationSystem_Log))
		#include "Logger_status.hpp"
		#define IAppStateListManagerLog(status,method,mns) pankey_Log(status,"IAppStateListManager",method,mns)
	#else
		#define IAppStateListManagerLog(status,method,mns)
	#endif

	namespace pankey{

		namespace ApplicationSystem{

			template<class A, class... Args>
			class IAppStateListManager : virtual public Base::UpdateManager<A,Args...>{
				public:
					IAppStateListManager(){
						IAppStateListManagerLog(pankey_Log_StartMethod, "Constructor", "");
						IAppStateListManagerLog(pankey_Log_EndMethod, "Constructor", "");
					}
					virtual ~IAppStateListManager(){
						IAppStateListManagerLog(pankey_Log_StartMethod, "Destructor", "");
						IAppStateListManagerLog(pankey_Log_EndMethod, "Destructor", "");
					}

					template<class AS>
					AS& addIAppState(){
						IAppStateListManagerLog(pankey_Log_StartMethod, "addAppState",  "");
						AS* i_state = new AS();
						m_initialize_appstate_list.addPointer(i_state);
						IAppStateListManagerLog(pankey_Log_EndMethod, "addAppState", "");
						return *i_state;
					}

					virtual bool containIAppState(long a_type){
						IAppStateListManagerLog(pankey_Log_StartMethod, "containAppState",  "");
						for(int x = 0; x < m_initialize_appstate_list.length(); x++){
							Base::iAppState<A,Args...>* f_state = m_initialize_appstate_list.getPointerByIndex(x);
							if(f_state == nullptr){
								continue;
							}
							if(f_state->getType() == a_type){
								return true;
							}
						}
						for(int x = 0; x < m_appstate_list.length(); x++){
							Base::iAppState<A,Args...>* f_state = m_appstate_list.getPointerByIndex(x);
							if(f_state == nullptr){
								continue;
							}
							if(f_state->getType() == a_type){
								return true;
							}
						}
						IAppStateListManagerLog(pankey_Log_EndMethod, "containAppState", "");
						return false;
					}

					template<class AS>
					bool containIAppState(){
						IAppStateListManagerLog(pankey_Log_StartMethod, "containAppState",  "");
						long i_type = Base::ClassCount<AS>::get();
						IAppStateListManagerLog(pankey_Log_EndMethod, "containAppState", "");
						return this->containIAppState(i_type);
					}

					template<class AS>
					void putIAppState(){
						IAppStateListManagerLog(pankey_Log_StartMethod, "putAppState",  "");
						if(this->containIAppState(Base::ClassCount<AS>::get())){
							return;
						}
						this->addIAppStatePointer(new AS());
						IAppStateListManagerLog(pankey_Log_EndMethod, "putAppState", "");
					}

					virtual int IAppState_length(){
						return m_appstate_list.length() + m_initialize_appstate_list.length();
					}

					virtual int length(){
						return m_appstate_list.length() + m_initialize_appstate_list.length();
					}
					
					virtual void clearIAppState(){
						IAppStateListManagerLog(pankey_Log_StartMethod, "clearAppState",  "");
						for(int x = 0; x < m_appstate_list.length(); x++){
							Base::iAppState<A,Args...>* f_state = m_appstate_list.getPointerByIndex(x);
							if(f_state == nullptr){
								continue;
							}
							f_state->onDisable();
						}
						for(int x = 0; x < m_initialize_appstate_list.length(); x++){
							Base::iAppState<A,Args...>* f_state = m_initialize_appstate_list.getPointerByIndex(x);
							if(f_state == nullptr){
								continue;
							}
							f_state->onDisable();
						}
						m_appstate_list.clear();
						m_initialize_appstate_list.clear();
						IAppStateListManagerLog(pankey_Log_EndMethod, "clearAppState", "");
					}
					
					virtual void clear(){
						IAppStateListManagerLog(pankey_Log_StartMethod, "clear",  "");
						for(int x = 0; x < m_appstate_list.length(); x++){
							Base::iAppState<A,Args...>* f_state = m_appstate_list.getPointerByIndex(x);
							if(f_state == nullptr){
								continue;
							}
							f_state->onDisable();
						}
						for(int x = 0; x < m_initialize_appstate_list.length(); x++){
							Base::iAppState<A,Args...>* f_state = m_initialize_appstate_list.getPointerByIndex(x);
							if(f_state == nullptr){
								continue;
							}
							f_state->onDisable();
						}
						m_appstate_list.clear();
						m_initialize_appstate_list.clear();
						IAppStateListManagerLog(pankey_Log_EndMethod, "clear", "");
					}

					virtual void initialize(A& a_app){
						IAppStateListManagerLog(pankey_Log_StartMethod, "initialize",  "");
						for(int x = 0; x < this->m_initialize_appstate_list.length(); x++){
							IAppStateListManagerLog(pankey_Log_StartMethod, "initialize",  "iterating through initializing states");
							IAppStateListManagerLog(pankey_Log_StartMethod, "initialize",  "iteration: ");
							IAppStateListManagerLog(pankey_Log_StartMethod, "initialize",  x);
							Base::iAppState<A,Args...>* f_state = this->m_initialize_appstate_list.getPointerByIndex(x);
							if(f_state == nullptr){
								IAppStateListManagerLog(pankey_Log_StartMethod, "initialize",  "initializing state is null");
								continue;
							}
							f_state->initialize(a_app);
							f_state->onEnable();
							this->m_appstate_list.addPointer(f_state);
						}
						IAppStateListManagerLog(pankey_Log_StartMethod, "initialize",  "m_initialize_appstate_list");
						this->m_initialize_appstate_list.reset();
						IAppStateListManagerLog(pankey_Log_EndMethod, "initialize", "");
					}

					virtual void update(A& a_app, Args... a_values){
						IAppStateListManagerLog(pankey_Log_StartMethod, "update",  "");
						
						if(!this->m_initialize_appstate_list.isEmpty()){
							this->initialize(a_app);
						}

						for(int x = 0; x < this->m_appstate_list.length(); x++){
							IAppStateListManagerLog(pankey_Log_StartMethod, "update",  "iterating through all states");
							IAppStateListManagerLog(pankey_Log_StartMethod, "update",  "iteration: ");
							IAppStateListManagerLog(pankey_Log_StartMethod, "update",  x);
							Base::iAppState<A,Args...>* f_state = this->m_appstate_list.getPointerByIndex(x);
							if(f_state == nullptr){
								continue;
							}
							f_state->update(a_app, a_values...);
						}

						IAppStateListManagerLog(pankey_Log_EndMethod, "update", "");
					}

					template<class AS, class... MArgs>
					void runIAppStateMethod(Base::InvokeClassMethod<AS,MArgs...> a_method, MArgs... a_args){
						IAppStateListManagerLog(pankey_Log_StartMethod, "run",  "");
						Base::Type* f_state = this->getIAppStatePointerByType(Base::ClassCount<AS>::get());
						if(f_state == nullptr){
							IAppStateListManagerLog(pankey_Log_EndMethod, "run", "f_state == nullptr");
							return;
						}
						AS& i_state = f_state->cast<AS>();
						Base::invoke<AS,MArgs...>(i_state, a_method, a_args...);
						IAppStateListManagerLog(pankey_Log_EndMethod, "run", "");
					}

				protected:

					virtual Base::iAppState<A,Args...>* addIAppStatePointer(Base::iAppState<A,Args...>* a_state){
						IAppStateListManagerLog(pankey_Log_StartMethod, "addAppStatePointer",  "");
						m_initialize_appstate_list.addPointer(a_state);
						IAppStateListManagerLog(pankey_Log_EndMethod, "addAppStatePointer", "");
						return a_state;
					}

					virtual bool containIAppStatePointer(Base::iAppState<A,Args...>* a_state){
						IAppStateListManagerLog(pankey_Log_StartMethod, "containAppStatePointer",  "");
						if(a_state == nullptr){
							return false;
						}
						long i_type = a_state->getType();
						IAppStateListManagerLog(pankey_Log_EndMethod, "containAppStatePointer", "");
						return this->containIAppState(i_type);
					}

					virtual Base::iAppState<A,Args...>* getIAppStatePointerByType(long a_type){
						IAppStateListManagerLog(pankey_Log_StartMethod, "getAppStatePointerByType",  "");
						IAppStateListManagerLog(pankey_Log_Statement, "getAppStatePointerByType",  "a_type");
						IAppStateListManagerLog(pankey_Log_Statement, "getAppStatePointerByType",  a_type);
						IAppStateListManagerLog(pankey_Log_Statement, "getAppStatePointerByType",  "m_initialize_appstate_list length");
						IAppStateListManagerLog(pankey_Log_Statement, "getAppStatePointerByType",  m_initialize_appstate_list.length());
						IAppStateListManagerLog(pankey_Log_Statement, "getAppStatePointerByType",  "m_appstate_list length");
						IAppStateListManagerLog(pankey_Log_Statement, "getAppStatePointerByType",  m_appstate_list.length());
						for(int x = 0; x < m_initialize_appstate_list.length(); x++){
							Base::iAppState<A,Args...>* f_state = m_initialize_appstate_list.getPointerByIndex(x);
							if(f_state == nullptr){
								IAppStateListManagerLog(pankey_Log_Statement, "getAppStatePointerByType",  "m_initialize_appstate_list f_state == nullptr");
								continue;
							}
							IAppStateListManagerLog(pankey_Log_Statement, "getAppStatePointerByType",  "m_initialize_appstate_list state type:");
							IAppStateListManagerLog(pankey_Log_Statement, "getAppStatePointerByType",  f_state->getType());
							if(f_state->getType() == a_type){
								IAppStateListManagerLog(pankey_Log_EndMethod, "getAppStatePointerByType", " m_initialize_appstate_listf_state->getType() == a_type");
								return f_state;
							}
						}
						for(int x = 0; x < m_appstate_list.length(); x++){
							Base::iAppState<A,Args...>* f_state = m_appstate_list.getPointerByIndex(x);
							if(f_state == nullptr){
								IAppStateListManagerLog(pankey_Log_Statement, "getAppStatePointerByType",  "m_appstate_list f_state == nullptr");
								continue;
							}
							IAppStateListManagerLog(pankey_Log_Statement, "getAppStatePointerByType",  "m_appstate_list state type:");
							IAppStateListManagerLog(pankey_Log_Statement, "getAppStatePointerByType",  f_state->getType());
							if(f_state->getType() == a_type){
								IAppStateListManagerLog(pankey_Log_EndMethod, "getAppStatePointerByType", "m_appstate_list f_state->getType() == a_type");
								return f_state;
							}
						}
						IAppStateListManagerLog(pankey_Log_EndMethod, "getAppStatePointerByType", "return nullptr");
						return nullptr;
					}
					
					virtual Base::iAppState<A,Args...>* removeIAppStatePointer(Base::iAppState<A,Args...>* a_state){
						IAppStateListManagerLog(pankey_Log_StartMethod, "removeAppStatePointer",  "");
						Base::iAppState<A,Args...>* i_state = m_initialize_appstate_list.removePointerByPointer(a_state);
						if(i_state == nullptr){
							return nullptr;
						}
						i_state->onDisable();
						IAppStateListManagerLog(pankey_Log_EndMethod, "removeAppStatePointer", "");
						return i_state;
					}

					Base::ArrayRawList<Base::iAppState<A,Args...>> m_appstate_list;
					Base::ArrayRawList<Base::iAppState<A,Args...>> m_initialize_appstate_list;
					
					
			};

		}

	}

#endif
