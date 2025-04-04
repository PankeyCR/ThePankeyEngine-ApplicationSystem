
#ifndef AppStateMapManager_hpp
	#define AppStateMapManager_hpp

	#include "AppState.hpp"
	#include "ClassCount.hpp"
	#include "ArrayRawList.hpp"
	#include "UpdateManager.hpp"

	#if defined(pankey_Log) && (defined(AppStateMapManager_Log) || defined(pankey_Global_Log) || defined(pankey_ApplicationSystem_Log))
		#include "Logger_status.hpp"
		#define AppStateMapManagerLog(status,method,mns) pankey_Log(status,"AppStateMapManager",method,mns)
	#else
		#define AppStateMapManagerLog(status,method,mns)
	#endif

	namespace pankey{

		namespace ApplicationSystem{

			template<class A, class... Args>
			class AppStateMapManager : virtual public UpdateManager<A,Args...>{
				public:
					AppStateMapManager(){
						AppStateMapManagerLog(pankey_Log_StartMethod, "Constructor", "");
						AppStateMapManagerLog(pankey_Log_EndMethod, "Constructor", "");
					}
					virtual ~AppStateMapManager(){
						AppStateMapManagerLog(pankey_Log_StartMethod, "Destructor", "");
						AppStateMapManagerLog(pankey_Log_EndMethod, "Destructor", "");
					}

					template<class AS>
					AS& addAppState(const Base::CharArray& a_name){
						AppStateMapManagerLog(pankey_Log_StartMethod, "addAppState",  "");
						AS* i_state = new AS();
						m_initialize_appstate_map.addPointer(a_name, i_state);
						AppStateMapManagerLog(pankey_Log_EndMethod, "addAppState", "");
						return *i_state;
					}

					virtual bool containAppState(long a_type){
						AppStateMapManagerLog(pankey_Log_StartMethod, "containAppState",  "");
						for(int x = 0; x < m_initialize_appstate_map.length(); x++){
							Base::AppState<A,Args...>* f_state = m_initialize_appstate_map.getValuePointerByIndex(x);
							if(f_state == nullptr){
								continue;
							}
							if(f_state->getType() == a_type){
								return true;
							}
						}
						for(int x = 0; x < m_appstate_map.length(); x++){
							Base::AppState<A,Args...>* f_state = m_appstate_map.getValuePointerByIndex(x);
							if(f_state == nullptr){
								continue;
							}
							if(f_state->getType() == a_type){
								return true;
							}
						}
						AppStateMapManagerLog(pankey_Log_EndMethod, "containAppState", "");
						return false;
					}

					template<class AS>
					bool containAppState(){
						AppStateMapManagerLog(pankey_Log_StartMethod, "containAppState",  "");
						long i_type = Base::ClassCount<AS>::get();
						AppStateMapManagerLog(pankey_Log_EndMethod, "containAppState", "");
						return this->containAppState(i_type);
					}

					template<class AS>
					void putAppState(const Base::CharArray& a_name){
						AppStateMapManagerLog(pankey_Log_StartMethod, "putAppState",  "");
						if(this->containAppState(Base::ClassCount<AS>::get())){
							return;
						}
						this->addAppStatePointer(a_name, new AS());
						AppStateMapManagerLog(pankey_Log_EndMethod, "putAppState", "");
					}

					virtual int AppState_length(){
						return m_appstate_map.length() + m_initialize_appstate_map.length();
					}

					virtual int length(){
						return m_appstate_map.length() + m_initialize_appstate_map.length();
					}
					
					virtual void clearAppState(){
						AppStateMapManagerLog(pankey_Log_StartMethod, "clearAppState",  "");
						for(int x = 0; x < m_appstate_map.length(); x++){
							Base::AppState<A,Args...>* f_state = m_appstate_map.getValuePointerByIndex(x);
							if(f_state == nullptr){
								continue;
							}
							f_state->onDisable();
						}
						for(int x = 0; x < m_initialize_appstate_map.length(); x++){
							Base::AppState<A,Args...>* f_state = m_initialize_appstate_map.getValuePointerByIndex(x);
							if(f_state == nullptr){
								continue;
							}
							f_state->onDisable();
						}
						m_appstate_map.clear();
						m_initialize_appstate_map.clear();
						AppStateMapManagerLog(pankey_Log_EndMethod, "clearAppState", "");
					}
					
					virtual void clear(){
						AppStateMapManagerLog(pankey_Log_StartMethod, "clear",  "");
						for(int x = 0; x < m_appstate_map.length(); x++){
							Base::AppState<A,Args...>* f_state = m_appstate_map.getValuePointerByIndex(x);
							if(f_state == nullptr){
								continue;
							}
							f_state->onDisable();
						}
						for(int x = 0; x < m_initialize_appstate_map.length(); x++){
							Base::AppState<A,Args...>* f_state = m_initialize_appstate_map.getValuePointerByIndex(x);
							if(f_state == nullptr){
								continue;
							}
							f_state->onDisable();
						}
						m_appstate_map.clear();
						m_initialize_appstate_map.clear();
						AppStateMapManagerLog(pankey_Log_EndMethod, "clear", "");
					}

					virtual void initialize(A& a_app){
						AppStateMapManagerLog(pankey_Log_StartMethod, "initialize",  "");
						for(int x = 0; x < this->m_initialize_appstate_map.length(); x++){
							AppStateMapManagerLog(pankey_Log_StartMethod, "initialize",  "iterating through initializing states");
							AppStateMapManagerLog(pankey_Log_StartMethod, "initialize",  "iteration: ");
							AppStateMapManagerLog(pankey_Log_StartMethod, "initialize",  x);
							Base::CharArray* f_name = this->m_initialize_appstate_map.getKeyPointerByIndex(x);
							Base::AppState<A,Args...>* f_state = this->m_initialize_appstate_map.getValuePointerByIndex(x);
							if(f_state == nullptr || f_name == nullptr){
								AppStateMapManagerLog(pankey_Log_StartMethod, "initialize",  "initializing state is null");
								continue;
							}
							f_state->initialize(a_app);
							f_state->onEnable();
							this->m_appstate_map.addPointers(f_name, f_state);
						}
						AppStateMapManagerLog(pankey_Log_StartMethod, "initialize",  "m_initialize_appstate_map");
						this->m_initialize_appstate_map.reset();
						AppStateMapManagerLog(pankey_Log_EndMethod, "initialize", "");
					}

					virtual void update(A& a_app, Args... a_values){
						AppStateMapManagerLog(pankey_Log_StartMethod, "update",  "");
						
						if(!this->m_initialize_appstate_map.isEmpty()){
							this->initialize(a_app);
						}

						for(int x = 0; x < this->m_appstate_map.length(); x++){
							AppStateMapManagerLog(pankey_Log_StartMethod, "update",  "iterating through all states");
							AppStateMapManagerLog(pankey_Log_StartMethod, "update",  "iteration: ");
							AppStateMapManagerLog(pankey_Log_StartMethod, "update",  x);
							Base::AppState<A,Args...>* f_state = this->m_appstate_map.getValuePointerByIndex(x);
							if(f_state == nullptr){
								continue;
							}
							f_state->update(a_app, a_values...);
						}

						AppStateMapManagerLog(pankey_Log_EndMethod, "update", "");
					}

					template<class AS, class... MArgs>
					void runAppStateMethod(Base::InvokeClassMethod<AS,MArgs...> a_method, MArgs... a_args){
						AppStateMapManagerLog(pankey_Log_StartMethod, "runAppStateMethod",  "");
						Base::Type* f_state = this->getAppStatePointerByType(Base::ClassCount<AS>::get());
						if(f_state == nullptr){
							AppStateMapManagerLog(pankey_Log_EndMethod, "runAppStateMethod", "f_state == nullptr");
							return;
						}
						AS& i_state = f_state->cast<AS>();
						Base::invoke<AS,MArgs...>(i_state, a_method, a_args...);
						AppStateMapManagerLog(pankey_Log_EndMethod, "runAppStateMethod", "");
					}

				protected:

					virtual Base::AppState<A,Args...>* addAppStatePointer(const Base::CharArray& a_name, Base::AppState<A,Args...>* a_state){
						AppStateMapManagerLog(pankey_Log_StartMethod, "addAppStatePointer",  "");
						m_initialize_appstate_map.addPointer(a_name, a_state);
						AppStateMapManagerLog(pankey_Log_EndMethod, "addAppStatePointer", "");
						return a_state;
					}

					virtual bool containAppStatePointer(Base::AppState<A,Args...>* a_state){
						AppStateMapManagerLog(pankey_Log_StartMethod, "containAppStatePointer",  "");
						if(a_state == nullptr){
							return false;
						}
						long i_type = a_state->getType();
						AppStateMapManagerLog(pankey_Log_EndMethod, "containAppStatePointer", "");
						return this->containAppState(i_type);
					}

					virtual Base::AppState<A,Args...>* getAppStatePointerByType(long a_type){
						AppStateMapManagerLog(pankey_Log_StartMethod, "getAppStatePointerByType",  "");
						AppStateMapManagerLog(pankey_Log_Statement, "getAppStatePointerByType",  "a_type");
						AppStateMapManagerLog(pankey_Log_Statement, "getAppStatePointerByType",  a_type);
						AppStateMapManagerLog(pankey_Log_Statement, "getAppStatePointerByType",  "m_initialize_appstate_map length");
						AppStateMapManagerLog(pankey_Log_Statement, "getAppStatePointerByType",  m_initialize_appstate_map.length());
						AppStateMapManagerLog(pankey_Log_Statement, "getAppStatePointerByType",  "m_appstate_map length");
						AppStateMapManagerLog(pankey_Log_Statement, "getAppStatePointerByType",  m_appstate_map.length());
						for(int x = 0; x < m_initialize_appstate_map.length(); x++){
							Base::AppState<A,Args...>* f_state = m_initialize_appstate_map.getValuePointerByIndex(x);
							if(f_state == nullptr){
								AppStateMapManagerLog(pankey_Log_Statement, "getAppStatePointerByType",  "m_initialize_appstate_map f_state == nullptr");
								continue;
							}
							AppStateMapManagerLog(pankey_Log_Statement, "getAppStatePointerByType",  "m_initialize_appstate_map state type:");
							AppStateMapManagerLog(pankey_Log_Statement, "getAppStatePointerByType",  f_state->getType());
							if(f_state->getType() == a_type){
								AppStateMapManagerLog(pankey_Log_EndMethod, "getAppStatePointerByType", " m_initialize_appstate_mapf_state->getType() == a_type");
								return f_state;
							}
						}
						for(int x = 0; x < m_appstate_map.length(); x++){
							Base::AppState<A,Args...>* f_state = m_appstate_map.getValuePointerByIndex(x);
							if(f_state == nullptr){
								AppStateMapManagerLog(pankey_Log_Statement, "getAppStatePointerByType",  "m_appstate_map f_state == nullptr");
								continue;
							}
							AppStateMapManagerLog(pankey_Log_Statement, "getAppStatePointerByType",  "m_appstate_map state type:");
							AppStateMapManagerLog(pankey_Log_Statement, "getAppStatePointerByType",  f_state->getType());
							if(f_state->getType() == a_type){
								AppStateMapManagerLog(pankey_Log_EndMethod, "getAppStatePointerByType", "m_appstate_map f_state->getType() == a_type");
								return f_state;
							}
						}
						AppStateMapManagerLog(pankey_Log_EndMethod, "getAppStatePointerByType", "return nullptr");
						return nullptr;
					}
					
					virtual Base::RawMapEntry<Base::CharArray,Base::AppState<A,Args...>> removeAppStatePointers(Base::AppState<A,Args...>* a_state){
						AppStateMapManagerLog(pankey_Log_StartMethod, "removeAppStatePointers",  "");
						Base::RawMapEntry<Base::CharArray,Base::AppState<A,Args...>> i_entry = m_initialize_appstate_map.removePointersByValuePointer(a_state);
						if(i_entry.isNull()){
							return i_entry;
						}
						Base::AppState<A,Args...>* i_state = i_entry.getValue();
						if(i_state == nullptr){
							return i_entry;
						}
						i_state->onDisable();
						AppStateMapManagerLog(pankey_Log_EndMethod, "removeAppStatePointers", "");
						return i_entry;
					}

					Base::ArrayRawMap<Base::CharArray,Base::AppState<A,Args...>> m_appstate_map;
					Base::ArrayRawMap<Base::CharArray,Base::AppState<A,Args...>> m_initialize_appstate_map;
					
					
			};

		}

	}

#endif
