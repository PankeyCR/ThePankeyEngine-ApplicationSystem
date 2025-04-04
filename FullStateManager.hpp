
#ifndef FullStateManager_hpp
	#define FullStateManager_hpp

	#include "UpdateManager.hpp"

	#include "Note.hpp"

	#include "AppStateListManager.hpp"
	// #include "MethodInitializeAppState.hpp"
	#include "MethodInitializeState.hpp"
	// #include "MethodLoopAppState.hpp"

	#ifdef FullStateManager_LogApp
		#include "pankey_Logger.hpp"
		#define FullStateManagerLog(location,method,type,mns) pankey_Log(this,location,"FullStateManager",method,type,mns)
	#else
		#define FullStateManagerLog(location,method,type,mns)
	#endif

	namespace pankey{

		template<class A>
		class FullStateManager : public UpdateManager<A&,long>{
			public:
				FullStateManager(){
					FullStateManagerLog(pankey_Log_StartMethod, "Constructor", "println", "");
					FullStateManagerLog(pankey_Log_EndMethod, "Constructor", "println", "");
				}
				virtual ~FullStateManager(){
					FullStateManagerLog(pankey_Log_StartMethod, "Destructor", "println", "");
					FullStateManagerLog(pankey_Log_EndMethod, "Destructor", "println", "");
				}
				
				virtual void addInitialization(InvokeMethod<> a_state){
					MethodInitializeState<A,long> i_state = a_state;
					m_app_state_list.add(i_state);
				}
				
				virtual void putInitialization(InvokeMethod<> a_state){
					// for(int x = 0; x < m_app_state_list.get){

					// }
				}
				
				// virtual void addInitialization(InvokeMethod<A&> a_state){
				// 	init_app_functions_list.add(a_state);
				// }
				
				// virtual void putInitialization(InvokeMethod<A&> a_state){
				// 	init_app_functions_list.put(a_state);
				// }
				
				// virtual void addInitialization(const Note& a_name, InvokeMethod<> a_state){
				// 	init_functions_map.add(a_name, a_state);
				// }
				
				// virtual void putInitialization(const Note& a_name, InvokeMethod<> a_state){
				// 	init_functions_map.put(a_name, a_state);
				// }
				
				// virtual void addInitialization(const Note& a_name, InvokeMethod<A&> a_state){
				// 	init_app_functions_map.add(a_name, a_state);
				// }
				
				// virtual void putInitialization(const Note& a_name, InvokeMethod<A&> a_state){
				// 	init_app_functions_map.put(a_name, a_state);
				// }
				
				// virtual void addLoop(InvokeMethod<> a_state){
				// 	functions_list.add(a_state);
				// }
				
				// virtual void putLoop(InvokeMethod<> a_state){
				// 	functions_list.put(a_state);
				// }
				
				// virtual void addLoop(InvokeMethod<A&> a_state){
				// 	app_functions_list.add(a_state);
				// }
				
				// virtual void putLoop(InvokeMethod<A&> a_state){
				// 	app_functions_list.put(a_state);
				// }
				
				// virtual void addLoop(InvokeMethod<long> a_state){
				// 	timed_functions_list.add(a_state);
				// }
				
				// virtual void putLoop(InvokeMethod<long> a_state){
				// 	timed_functions_list.put(a_state);
				// }
				
				// virtual void addLoop(InvokeMethod<A&,long> a_state){
				// 	app_timed_functions_list.add(a_state);
				// }
				
				// virtual void putLoop(InvokeMethod<A&,long> a_state){
				// 	app_timed_functions_list.put(a_state);
				// }
				
				// virtual void addLoop(const Note& a_name, InvokeMethod<> a_state){
				// 	functions_map.add(a_name, a_state);
				// }
				
				// virtual void putLoop(const Note& a_name, InvokeMethod<> a_state){
				// 	functions_map.put(a_name, a_state);
				// }
				
				// virtual void addLoop(const Note& a_name, InvokeMethod<A&> a_state){
				// 	app_functions_map.add(a_name, a_state);
				// }
				
				// virtual void putLoop(const Note& a_name, InvokeMethod<A&> a_state){
				// 	app_functions_map.put(a_name, a_state);
				// }
				
				// virtual void addLoop(const Note& a_name, InvokeMethod<long> a_state){
				// 	timed_functions_map.add(a_name, a_state);
				// }
				
				// virtual void putLoop(const Note& a_name, InvokeMethod<long> a_state){
				// 	timed_functions_map.put(a_name, a_state);
				// }
				
				// virtual void addLoop(const Note& a_name, InvokeMethod<A&,long> a_state){
				// 	app_timed_functions_map.add(a_name, a_state);
				// }
				
				// virtual void putLoop(const Note& a_name, InvokeMethod<A&,long> a_state){
				// 	app_timed_functions_map.put(a_name, a_state);
				// }
				
				// virtual void add(app_state<A,long> a_state){
				// 	app_state_timed_functions_list.add(a_state);
				// }
				
				// virtual void add(Note a_id, app_state<A,long> a_state){
				// 	app_state_timed_functions_list.add(a_id, a_state);
				// }
				
				// virtual void put(app_state<A,long> a_state){
				// 	app_state_timed_functions_list.put(a_state);
				// }
				
				// virtual void put(Note a_id, app_state<A,long> a_state){
				// 	app_state_timed_functions_list.put(a_id, a_state);
				// }
				
				// virtual app_state<A,long> getByID(Note a_id){
				// 	return app_state_timed_functions_list.getByID(a_id);
				// }
				
				// virtual void removeInitialization(InvokeMethod<> a_state){
				// 	FullStateManagerLog(pankey_Log_StartMethod, "removeInitialization", "println", "InvokeMethod<>");
				// 	init_functions_list.removeUpdateFunctionList(a_state);
				// 	FullStateManagerLog(pankey_Log_EndMethod, "removeInitialization", "println", "");
				// }
				
				// virtual void removeInitialization(InvokeMethod<A&> a_state){
				// 	FullStateManagerLog(pankey_Log_StartMethod, "removeInitialization", "println", "InvokeMethod<A&>");
				// 	init_app_functions_list.removeUpdateFunctionList(a_state);
				// 	FullStateManagerLog(pankey_Log_EndMethod, "removeInitialization", "println", "");
				// }
				
				// virtual void removeInitialization(const Note& a_name){
					
				// }
				
				virtual void removeAll(){
					m_app_state_list.removeAll();
				}

				virtual void initialize(A& a_app){
					FullStateManagerLog(pankey_Log_StartMethod, "initialize",  "println", "");
					m_app_state_list.initialize(a_app);
					FullStateManagerLog(pankey_Log_EndMethod, "initialize",  "println", "");
				}

				virtual void update(A& a_app, long a_tpc){
					FullStateManagerLog(pankey_Log_StartMethod, "update",  "println", "");
					m_app_state_list.update(a_app, a_tpc);
					FullStateManagerLog(pankey_Log_EndMethod, "update",  "println", "");
				}

			protected:
				AppStateListManager<A,long> m_app_state_list;
		};

	}

#endif