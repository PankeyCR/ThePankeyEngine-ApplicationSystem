
#ifndef IAppStateMapManager_hpp
	#define IAppStateMapManager_hpp

	#include "iAppState.hpp"
	#include "ClassType.hpp"
	#include "ArrayRawList.hpp"
	#include "UpdateManager.hpp"

	#if defined(pankey_Log) && (defined(IAppStateMapManager_Log) || defined(pankey_Global_Log) || defined(pankey_ApplicationSystem_Log))
		#include "Logger_status.hpp"
		#define IAppStateMapManagerLog(status,method,mns) pankey_Log(status,"IAppStateMapManager",method,mns)
	#else
		#define IAppStateMapManagerLog(status,method,mns)
	#endif

	namespace pankey{

		namespace ApplicationSystem{

			template<class A, class... Args>
			class IAppStateMapManager : virtual public UpdateManager<A,Args...>{
				public:
					IAppStateMapManager(){
						IAppStateMapManagerLog(pankey_Log_StartMethod, "Constructor", "");
						IAppStateMapManagerLog(pankey_Log_EndMethod, "Constructor", "");
					}
					virtual ~IAppStateMapManager(){
						IAppStateMapManagerLog(pankey_Log_StartMethod, "Destructor", "");
						IAppStateMapManagerLog(pankey_Log_EndMethod, "Destructor", "");
					}

					template<class AS>
					AS& addIAppState(const Base::CharArray& a_name){
						IAppStateMapManagerLog(pankey_Log_StartMethod, "addAppState",  "");
						AS* i_state = new AS();
						m_initialize_appstate_map.addPointer(a_name, i_state);
						IAppStateMapManagerLog(pankey_Log_EndMethod, "addAppState", "");
						return *i_state;
					}

					virtual bool containIAppState(long a_type){
						IAppStateMapManagerLog(pankey_Log_StartMethod, "containAppState",  "");
						for(int x = 0; x < m_initialize_appstate_map.length(); x++){
							Base::iAppState<A,Args...>* f_state = m_initialize_appstate_map.getValuePointerByIndex(x);
							if(f_state == nullptr){
								continue;
							}
							if(f_state->getType() == a_type){
								return true;
							}
						}
						for(int x = 0; x < m_appstate_map.length(); x++){
							Base::iAppState<A,Args...>* f_state = m_appstate_map.getValuePointerByIndex(x);
							if(f_state == nullptr){
								continue;
							}
							if(f_state->getType() == a_type){
								return true;
							}
						}
						IAppStateMapManagerLog(pankey_Log_EndMethod, "containAppState", "");
						return false;
					}

					template<class AS>
					bool containIAppState(){
						IAppStateMapManagerLog(pankey_Log_StartMethod, "containAppState",  "");
						long i_type = Base::ClassType<AS>::getId();
						IAppStateMapManagerLog(pankey_Log_EndMethod, "containAppState", "");
						return this->containIAppState(i_type);
					}

					template<class AS>
					void putIAppState(const Base::CharArray& a_name){
						IAppStateMapManagerLog(pankey_Log_StartMethod, "putAppState",  "");
						if(this->containIAppState(Base::ClassType<AS>::getId())){
							return;
						}
						this->addIAppStatePointer(a_name, new AS());
						IAppStateMapManagerLog(pankey_Log_EndMethod, "putAppState", "");
					}

					virtual int IAppState_length(){
						return m_appstate_map.length() + m_initialize_appstate_map.length();
					}

					virtual int length()const{
						return m_appstate_map.length() + m_initialize_appstate_map.length();
					}
					
					virtual void clearIAppState(){
						IAppStateMapManagerLog(pankey_Log_StartMethod, "clearAppState",  "");
						for(int x = 0; x < m_appstate_map.length(); x++){
							Base::iAppState<A,Args...>* f_state = m_appstate_map.getValuePointerByIndex(x);
							if(f_state == nullptr){
								continue;
							}
							f_state->onDisable();
						}
						for(int x = 0; x < m_initialize_appstate_map.length(); x++){
							Base::iAppState<A,Args...>* f_state = m_initialize_appstate_map.getValuePointerByIndex(x);
							if(f_state == nullptr){
								continue;
							}
							f_state->onDisable();
						}
						m_appstate_map.clear();
						m_initialize_appstate_map.clear();
						IAppStateMapManagerLog(pankey_Log_EndMethod, "clearAppState", "");
					}
					
					virtual void clear(){
						IAppStateMapManagerLog(pankey_Log_StartMethod, "clear",  "");
						for(int x = 0; x < m_appstate_map.length(); x++){
							Base::iAppState<A,Args...>* f_state = m_appstate_map.getValuePointerByIndex(x);
							if(f_state == nullptr){
								continue;
							}
							f_state->onDisable();
						}
						for(int x = 0; x < m_initialize_appstate_map.length(); x++){
							Base::iAppState<A,Args...>* f_state = m_initialize_appstate_map.getValuePointerByIndex(x);
							if(f_state == nullptr){
								continue;
							}
							f_state->onDisable();
						}
						m_appstate_map.clear();
						m_initialize_appstate_map.clear();
						IAppStateMapManagerLog(pankey_Log_EndMethod, "clear", "");
					}

					virtual void initialize(A& a_app){
						IAppStateMapManagerLog(pankey_Log_StartMethod, "initialize",  "");
						for(int x = 0; x < this->m_initialize_appstate_map.length(); x++){
							IAppStateMapManagerLog(pankey_Log_StartMethod, "initialize",  "iterating through initializing states");
							IAppStateMapManagerLog(pankey_Log_StartMethod, "initialize",  "iteration: ");
							IAppStateMapManagerLog(pankey_Log_StartMethod, "initialize",  x);
							Base::CharArray* f_name = this->m_initialize_appstate_map.getKeyPointerByIndex(x);
							Base::iAppState<A,Args...>* f_state = this->m_initialize_appstate_map.getValuePointerByIndex(x);
							if(f_state == nullptr || f_name == nullptr){
								IAppStateMapManagerLog(pankey_Log_StartMethod, "initialize",  "initializing state is null");
								continue;
							}
							f_state->initialize(a_app);
							f_state->onEnable();
							this->m_appstate_map.addPointers(f_name, f_state);
						}
						IAppStateMapManagerLog(pankey_Log_StartMethod, "initialize",  "m_initialize_appstate_map");
						this->m_initialize_appstate_map.reset();
						IAppStateMapManagerLog(pankey_Log_EndMethod, "initialize", "");
					}

					virtual void update(A& a_app, Args... a_values){
						IAppStateMapManagerLog(pankey_Log_StartMethod, "update",  "");
						
						if(!this->m_initialize_appstate_map.isEmpty()){
							this->initialize(a_app);
						}

						for(int x = 0; x < this->m_appstate_map.length(); x++){
							IAppStateMapManagerLog(pankey_Log_StartMethod, "update",  "iterating through all states");
							IAppStateMapManagerLog(pankey_Log_StartMethod, "update",  "iteration: ");
							IAppStateMapManagerLog(pankey_Log_StartMethod, "update",  x);
							Base::iAppState<A,Args...>* f_state = this->m_appstate_map.getValuePointerByIndex(x);
							if(f_state == nullptr){
								continue;
							}
							f_state->update(a_app, a_values...);
						}

						IAppStateMapManagerLog(pankey_Log_EndMethod, "update", "");
					}

					template<class AS, class... MArgs>
					void runIAppStateMethod(Base::InvokeClassMethod<AS,MArgs...> a_method, MArgs... a_args){
						IAppStateMapManagerLog(pankey_Log_StartMethod, "runAppStateMethod",  "");
						Base::Type* f_state = this->getIAppStatePointerByType(Base::ClassType<AS>::getId());
						if(f_state == nullptr){
							IAppStateMapManagerLog(pankey_Log_EndMethod, "runAppStateMethod", "f_state == nullptr");
							return;
						}
						AS& i_state = f_state->cast<AS>();
						Base::invoke<AS,MArgs...>(i_state, a_method, a_args...);
						IAppStateMapManagerLog(pankey_Log_EndMethod, "runAppStateMethod", "");
					}

				protected:

					virtual Base::iAppState<A,Args...>* addIAppStatePointer(const Base::CharArray& a_name, Base::iAppState<A,Args...>* a_state){
						IAppStateMapManagerLog(pankey_Log_StartMethod, "addAppStatePointer",  "");
						m_initialize_appstate_map.addPointer(a_name, a_state);
						IAppStateMapManagerLog(pankey_Log_EndMethod, "addAppStatePointer", "");
						return a_state;
					}

					virtual bool containIAppStatePointer(Base::iAppState<A,Args...>* a_state){
						IAppStateMapManagerLog(pankey_Log_StartMethod, "containAppStatePointer",  "");
						if(a_state == nullptr){
							return false;
						}
						long i_type = a_state->getType();
						IAppStateMapManagerLog(pankey_Log_EndMethod, "containAppStatePointer", "");
						return this->containIAppState(i_type);
					}

					virtual Base::iAppState<A,Args...>* getIAppStatePointerByType(long a_type){
						IAppStateMapManagerLog(pankey_Log_StartMethod, "getAppStatePointerByType",  "");
						IAppStateMapManagerLog(pankey_Log_Statement, "getAppStatePointerByType",  "a_type");
						IAppStateMapManagerLog(pankey_Log_Statement, "getAppStatePointerByType",  a_type);
						IAppStateMapManagerLog(pankey_Log_Statement, "getAppStatePointerByType",  "m_initialize_appstate_map length");
						IAppStateMapManagerLog(pankey_Log_Statement, "getAppStatePointerByType",  m_initialize_appstate_map.length());
						IAppStateMapManagerLog(pankey_Log_Statement, "getAppStatePointerByType",  "m_appstate_map length");
						IAppStateMapManagerLog(pankey_Log_Statement, "getAppStatePointerByType",  m_appstate_map.length());
						for(int x = 0; x < m_initialize_appstate_map.length(); x++){
							Base::iAppState<A,Args...>* f_state = m_initialize_appstate_map.getValuePointerByIndex(x);
							if(f_state == nullptr){
								IAppStateMapManagerLog(pankey_Log_Statement, "getAppStatePointerByType",  "m_initialize_appstate_map f_state == nullptr");
								continue;
							}
							IAppStateMapManagerLog(pankey_Log_Statement, "getAppStatePointerByType",  "m_initialize_appstate_map state type:");
							IAppStateMapManagerLog(pankey_Log_Statement, "getAppStatePointerByType",  f_state->getType());
							if(f_state->getType() == a_type){
								IAppStateMapManagerLog(pankey_Log_EndMethod, "getAppStatePointerByType", " m_initialize_appstate_mapf_state->getType() == a_type");
								return f_state;
							}
						}
						for(int x = 0; x < m_appstate_map.length(); x++){
							Base::iAppState<A,Args...>* f_state = m_appstate_map.getValuePointerByIndex(x);
							if(f_state == nullptr){
								IAppStateMapManagerLog(pankey_Log_Statement, "getAppStatePointerByType",  "m_appstate_map f_state == nullptr");
								continue;
							}
							IAppStateMapManagerLog(pankey_Log_Statement, "getAppStatePointerByType",  "m_appstate_map state type:");
							IAppStateMapManagerLog(pankey_Log_Statement, "getAppStatePointerByType",  f_state->getType());
							if(f_state->getType() == a_type){
								IAppStateMapManagerLog(pankey_Log_EndMethod, "getAppStatePointerByType", "m_appstate_map f_state->getType() == a_type");
								return f_state;
							}
						}
						IAppStateMapManagerLog(pankey_Log_EndMethod, "getAppStatePointerByType", "return nullptr");
						return nullptr;
					}
					
					virtual Base::RawMapEntry<Base::CharArray,Base::iAppState<A,Args...>> removeIAppStatePointers(Base::iAppState<A,Args...>* a_state){
						IAppStateMapManagerLog(pankey_Log_StartMethod, "removeAppStatePointers",  "");
						Base::RawMapEntry<Base::CharArray,Base::iAppState<A,Args...>> i_entry = m_initialize_appstate_map.removePointersByValuePointer(a_state);
						if(i_entry.isNull()){
							return i_entry;
						}
						Base::iAppState<A,Args...>* i_state = i_entry.getValue();
						if(i_state == nullptr){
							return i_entry;
						}
						i_state->onDisable();
						IAppStateMapManagerLog(pankey_Log_EndMethod, "removeAppStatePointers", "");
						return i_entry;
					}

					Base::ArrayRawMap<Base::CharArray,Base::iAppState<A,Args...>> m_appstate_map;
					Base::ArrayRawMap<Base::CharArray,Base::iAppState<A,Args...>> m_initialize_appstate_map;
					
					
			};

		}

	}

#endif
