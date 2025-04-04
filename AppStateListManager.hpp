
#ifndef AppStateListManager_hpp
	#define AppStateListManager_hpp

	#include "AppState.hpp"
	#include "ClassCount.hpp"
	#include "ArrayRawList.hpp"
	#include "UpdateManager.hpp"

	#if defined(pankey_Log) && (defined(AppStateListManager_Log) || defined(pankey_Global_Log) || defined(pankey_ApplicationSystem_Log))
		#include "Logger_status.hpp"
		#define AppStateListManagerLog(status,method,mns) pankey_Log(status,"AppStateListManager",method,mns)
	#else
		#define AppStateListManagerLog(status,method,mns)
	#endif

	namespace pankey{

		namespace ApplicationSystem{

			template<class A, class... Args>
			class AppStateListManager : virtual public UpdateManager<A,Args...>{
				public:
					AppStateListManager(){
						AppStateListManagerLog(pankey_Log_StartMethod, "Constructor", "");
						AppStateListManagerLog(pankey_Log_EndMethod, "Constructor", "");
					}
					virtual ~AppStateListManager(){
						AppStateListManagerLog(pankey_Log_StartMethod, "Destructor", "");
						AppStateListManagerLog(pankey_Log_EndMethod, "Destructor", "");
					}

					template<class AS>
					AS& addAppState(){
						AppStateListManagerLog(pankey_Log_StartMethod, "addAppState",  "");
						AS* i_state = new AS();
						m_initialize_appstate_list.addPointer(i_state);
						AppStateListManagerLog(pankey_Log_EndMethod, "addAppState", "");
						return *i_state;
					}

					virtual bool containAppState(long a_type){
						AppStateListManagerLog(pankey_Log_StartMethod, "containAppState",  "");
						for(int x = 0; x < m_initialize_appstate_list.length(); x++){
							Base::AppState<A,Args...>* f_state = m_initialize_appstate_list.getPointerByIndex(x);
							if(f_state == nullptr){
								continue;
							}
							if(f_state->getType() == a_type){
								return true;
							}
						}
						for(int x = 0; x < m_appstate_list.length(); x++){
							Base::AppState<A,Args...>* f_state = m_appstate_list.getPointerByIndex(x);
							if(f_state == nullptr){
								continue;
							}
							if(f_state->getType() == a_type){
								return true;
							}
						}
						AppStateListManagerLog(pankey_Log_EndMethod, "containAppState", "");
						return false;
					}

					template<class AS>
					bool containAppState(){
						AppStateListManagerLog(pankey_Log_StartMethod, "containAppState",  "");
						long i_type = Base::ClassCount<AS>::get();
						AppStateListManagerLog(pankey_Log_EndMethod, "containAppState", "");
						return this->containAppState(i_type);
					}

					template<class AS>
					void putAppState(){
						AppStateListManagerLog(pankey_Log_StartMethod, "putAppState",  "");
						if(this->containAppState(Base::ClassCount<AS>::get())){
							return;
						}
						this->addAppStatePointer(new AS());
						AppStateListManagerLog(pankey_Log_EndMethod, "putAppState", "");
					}

					virtual int AppState_length(){
						return m_appstate_list.length() + m_initialize_appstate_list.length();
					}

					virtual int length(){
						return m_appstate_list.length() + m_initialize_appstate_list.length();
					}
					
					virtual void clearAppState(){
						AppStateListManagerLog(pankey_Log_StartMethod, "clearAppState",  "");
						for(int x = 0; x < m_appstate_list.length(); x++){
							Base::AppState<A,Args...>* f_state = m_appstate_list.getPointerByIndex(x);
							if(f_state == nullptr){
								continue;
							}
							f_state->onDisable();
						}
						for(int x = 0; x < m_initialize_appstate_list.length(); x++){
							Base::AppState<A,Args...>* f_state = m_initialize_appstate_list.getPointerByIndex(x);
							if(f_state == nullptr){
								continue;
							}
							f_state->onDisable();
						}
						m_appstate_list.clear();
						m_initialize_appstate_list.clear();
						AppStateListManagerLog(pankey_Log_EndMethod, "clearAppState", "");
					}
					
					virtual void clear(){
						AppStateListManagerLog(pankey_Log_StartMethod, "clear",  "");
						for(int x = 0; x < m_appstate_list.length(); x++){
							Base::AppState<A,Args...>* f_state = m_appstate_list.getPointerByIndex(x);
							if(f_state == nullptr){
								continue;
							}
							f_state->onDisable();
						}
						for(int x = 0; x < m_initialize_appstate_list.length(); x++){
							Base::AppState<A,Args...>* f_state = m_initialize_appstate_list.getPointerByIndex(x);
							if(f_state == nullptr){
								continue;
							}
							f_state->onDisable();
						}
						m_appstate_list.clear();
						m_initialize_appstate_list.clear();
						AppStateListManagerLog(pankey_Log_EndMethod, "clear", "");
					}

					virtual void initialize(A& a_app){
						AppStateListManagerLog(pankey_Log_StartMethod, "initialize",  "");
						for(int x = 0; x < this->m_initialize_appstate_list.length(); x++){
							AppStateListManagerLog(pankey_Log_StartMethod, "initialize",  "iterating through initializing states");
							AppStateListManagerLog(pankey_Log_StartMethod, "initialize",  "iteration: ");
							AppStateListManagerLog(pankey_Log_StartMethod, "initialize",  x);
							Base::AppState<A,Args...>* f_state = this->m_initialize_appstate_list.getPointerByIndex(x);
							if(f_state == nullptr){
								AppStateListManagerLog(pankey_Log_StartMethod, "initialize",  "initializing state is null");
								continue;
							}
							f_state->initialize(a_app);
							f_state->onEnable();
							this->m_appstate_list.addPointer(f_state);
						}
						AppStateListManagerLog(pankey_Log_StartMethod, "initialize",  "m_initialize_appstate_list");
						this->m_initialize_appstate_list.reset();
						AppStateListManagerLog(pankey_Log_EndMethod, "initialize", "");
					}

					virtual void update(A& a_app, Args... a_values){
						AppStateListManagerLog(pankey_Log_StartMethod, "update",  "");
						
						if(!this->m_initialize_appstate_list.isEmpty()){
							this->initialize(a_app);
						}

						for(int x = 0; x < this->m_appstate_list.length(); x++){
							AppStateListManagerLog(pankey_Log_StartMethod, "update",  "iterating through all states");
							AppStateListManagerLog(pankey_Log_StartMethod, "update",  "iteration: ");
							AppStateListManagerLog(pankey_Log_StartMethod, "update",  x);
							Base::AppState<A,Args...>* f_state = this->m_appstate_list.getPointerByIndex(x);
							if(f_state == nullptr){
								continue;
							}
							f_state->update(a_app, a_values...);
						}

						AppStateListManagerLog(pankey_Log_EndMethod, "update", "");
					}

					template<class AS, class... MArgs>
					void runAppStateMethod(Base::InvokeClassMethod<AS,MArgs...> a_method, MArgs... a_args){
						AppStateListManagerLog(pankey_Log_StartMethod, "run",  "");
						Base::Type* f_state = this->getAppStatePointerByType(Base::ClassCount<AS>::get());
						if(f_state == nullptr){
							AppStateListManagerLog(pankey_Log_EndMethod, "run", "f_state == nullptr");
							return;
						}
						AS& i_state = f_state->cast<AS>();
						Base::invoke<AS,MArgs...>(i_state, a_method, a_args...);
						AppStateListManagerLog(pankey_Log_EndMethod, "run", "");
					}

				protected:

					virtual Base::AppState<A,Args...>* addAppStatePointer(Base::AppState<A,Args...>* a_state){
						AppStateListManagerLog(pankey_Log_StartMethod, "addAppStatePointer",  "");
						m_initialize_appstate_list.addPointer(a_state);
						AppStateListManagerLog(pankey_Log_EndMethod, "addAppStatePointer", "");
						return a_state;
					}

					virtual bool containAppStatePointer(Base::AppState<A,Args...>* a_state){
						AppStateListManagerLog(pankey_Log_StartMethod, "containAppStatePointer",  "");
						if(a_state == nullptr){
							return false;
						}
						long i_type = a_state->getType();
						AppStateListManagerLog(pankey_Log_EndMethod, "containAppStatePointer", "");
						return this->containAppState(i_type);
					}

					virtual Base::AppState<A,Args...>* getAppStatePointerByType(long a_type){
						AppStateListManagerLog(pankey_Log_StartMethod, "getAppStatePointerByType",  "");
						AppStateListManagerLog(pankey_Log_Statement, "getAppStatePointerByType",  "a_type");
						AppStateListManagerLog(pankey_Log_Statement, "getAppStatePointerByType",  a_type);
						AppStateListManagerLog(pankey_Log_Statement, "getAppStatePointerByType",  "m_initialize_appstate_list length");
						AppStateListManagerLog(pankey_Log_Statement, "getAppStatePointerByType",  m_initialize_appstate_list.length());
						AppStateListManagerLog(pankey_Log_Statement, "getAppStatePointerByType",  "m_appstate_list length");
						AppStateListManagerLog(pankey_Log_Statement, "getAppStatePointerByType",  m_appstate_list.length());
						for(int x = 0; x < m_initialize_appstate_list.length(); x++){
							Base::AppState<A,Args...>* f_state = m_initialize_appstate_list.getPointerByIndex(x);
							if(f_state == nullptr){
								AppStateListManagerLog(pankey_Log_Statement, "getAppStatePointerByType",  "m_initialize_appstate_list f_state == nullptr");
								continue;
							}
							AppStateListManagerLog(pankey_Log_Statement, "getAppStatePointerByType",  "m_initialize_appstate_list state type:");
							AppStateListManagerLog(pankey_Log_Statement, "getAppStatePointerByType",  f_state->getType());
							if(f_state->getType() == a_type){
								AppStateListManagerLog(pankey_Log_EndMethod, "getAppStatePointerByType", " m_initialize_appstate_listf_state->getType() == a_type");
								return f_state;
							}
						}
						for(int x = 0; x < m_appstate_list.length(); x++){
							Base::AppState<A,Args...>* f_state = m_appstate_list.getPointerByIndex(x);
							if(f_state == nullptr){
								AppStateListManagerLog(pankey_Log_Statement, "getAppStatePointerByType",  "m_appstate_list f_state == nullptr");
								continue;
							}
							AppStateListManagerLog(pankey_Log_Statement, "getAppStatePointerByType",  "m_appstate_list state type:");
							AppStateListManagerLog(pankey_Log_Statement, "getAppStatePointerByType",  f_state->getType());
							if(f_state->getType() == a_type){
								AppStateListManagerLog(pankey_Log_EndMethod, "getAppStatePointerByType", "m_appstate_list f_state->getType() == a_type");
								return f_state;
							}
						}
						AppStateListManagerLog(pankey_Log_EndMethod, "getAppStatePointerByType", "return nullptr");
						return nullptr;
					}
					
					virtual Base::AppState<A,Args...>* removeAppStatePointer(Base::AppState<A,Args...>* a_state){
						AppStateListManagerLog(pankey_Log_StartMethod, "removeAppStatePointer",  "");
						Base::AppState<A,Args...>* i_state = m_initialize_appstate_list.removePointerByPointer(a_state);
						if(i_state == nullptr){
							return nullptr;
						}
						i_state->onDisable();
						AppStateListManagerLog(pankey_Log_EndMethod, "removeAppStatePointer", "");
						return i_state;
					}

					Base::ArrayRawList<Base::AppState<A,Args...>> m_appstate_list;
					Base::ArrayRawList<Base::AppState<A,Args...>> m_initialize_appstate_list;
					
					
			};

		}

	}

#endif
