
#ifndef LoopManager_hpp
	#define LoopManager_hpp

	#include "UpdateManager.hpp"

	#include "CharArray.hpp"

	#include "UpdateFunctionListManager.hpp"
	#include "InitializeFunctionListManager.hpp"
	#include "UpdateClassFunctionListManager.hpp"
	#include "StateListManager.hpp"
	#include "AppStateListManager.hpp"

	#include "UpdateFunctionMapManager.hpp"
	#include "UpdateClassFunctionMapManager.hpp"
	#include "AppStateMapManager.hpp"

	#if defined(pankey_Log) && (defined(LoopManager_Log) || defined(pankey_Global_Log) || defined(pankey_ApplicationSystem_Log))
		#include "Logger_status.hpp"
		#define LoopManagerLog(status,method,mns) pankey_Log(status,"LoopManager",method,mns)
	#else
		#define LoopManagerLog(status,method,mns)
	#endif

	namespace pankey{

		namespace ApplicationSystem{

			template<class A>
			class LoopManager : public UpdateManager<A&,long>{
				public:
					LoopManager(){
						LoopManagerLog(pankey_Log_StartMethod, "Constructor", "");
						LoopManagerLog(pankey_Log_EndMethod, "Constructor", "");
					}
					virtual ~LoopManager(){
						LoopManagerLog(pankey_Log_StartMethod, "Destructor", "");
						LoopManagerLog(pankey_Log_EndMethod, "Destructor", "");
					}
					
					virtual void addInitialization(Base::InvokeMethod<> a_state){
						init_functions_list.add(a_state);
					}
					
					virtual void putInitialization(Base::InvokeMethod<> a_state){
						init_functions_list.put(a_state);
					}
					
					virtual void addInitialization(Base::InvokeMethod<A&> a_state){
						init_app_functions_list.add(a_state);
					}
					
					virtual void putInitialization(Base::InvokeMethod<A&> a_state){
						init_app_functions_list.put(a_state);
					}
					
					virtual void addInitialization(const Base::CharArray& a_name, Base::InvokeMethod<> a_state){
						init_functions_map.add(a_name, a_state);
					}
					
					virtual void putInitialization(const Base::CharArray& a_name, Base::InvokeMethod<> a_state){
						init_functions_map.put(a_name, a_state);
					}
					
					virtual void addInitialization(const Base::CharArray& a_name, Base::InvokeMethod<A&> a_state){
						init_app_functions_map.add(a_name, a_state);
					}
					
					virtual void putInitialization(const Base::CharArray& a_name, Base::InvokeMethod<A&> a_state){
						init_app_functions_map.put(a_name, a_state);
					}
					
					virtual void addLoop(Base::InvokeMethod<> a_state){
						functions_list.add(a_state);
					}
					
					virtual void putLoop(Base::InvokeMethod<> a_state){
						functions_list.put(a_state);
					}
					
					virtual void addLoop(Base::InvokeMethod<A&> a_state){
						app_functions_list.add(a_state);
					}
					
					virtual void putLoop(Base::InvokeMethod<A&> a_state){
						app_functions_list.put(a_state);
					}
					
					virtual void addLoop(Base::InvokeMethod<long> a_state){
						timed_functions_list.add(a_state);
					}
					
					virtual void putLoop(Base::InvokeMethod<long> a_state){
						timed_functions_list.put(a_state);
					}
					
					virtual void addLoop(Base::InvokeMethod<A&,long> a_state){
						app_timed_functions_list.add(a_state);
					}
					
					virtual void putLoop(Base::InvokeMethod<A&,long> a_state){
						app_timed_functions_list.put(a_state);
					}
					
					virtual void addLoop(const Base::CharArray& a_name, Base::InvokeMethod<> a_state){
						functions_map.add(a_name, a_state);
					}
					
					virtual void putLoop(const Base::CharArray& a_name, Base::InvokeMethod<> a_state){
						functions_map.put(a_name, a_state);
					}
					
					virtual void addLoop(const Base::CharArray& a_name, Base::InvokeMethod<A&> a_state){
						app_functions_map.add(a_name, a_state);
					}
					
					virtual void putLoop(const Base::CharArray& a_name, Base::InvokeMethod<A&> a_state){
						app_functions_map.put(a_name, a_state);
					}
					
					virtual void addLoop(const Base::CharArray& a_name, Base::InvokeMethod<long> a_state){
						timed_functions_map.add(a_name, a_state);
					}
					
					virtual void putLoop(const Base::CharArray& a_name, Base::InvokeMethod<long> a_state){
						timed_functions_map.put(a_name, a_state);
					}
					
					virtual void addLoop(const Base::CharArray& a_name, Base::InvokeMethod<A&,long> a_state){
						app_timed_functions_map.add(a_name, a_state);
					}
					
					virtual void putLoop(const Base::CharArray& a_name, Base::InvokeMethod<A&,long> a_state){
						app_timed_functions_map.put(a_name, a_state);
					}
					
					virtual void removeInitialization(Base::InvokeMethod<> a_state){
						LoopManagerLog(pankey_Log_StartMethod, "removeInitialization", "Base::InvokeMethod<>");
						init_functions_list.removeUpdateFunctionList(a_state);
						LoopManagerLog(pankey_Log_EndMethod, "removeInitialization", "");
					}
					
					virtual void removeInitialization(Base::InvokeMethod<A&> a_state){
						LoopManagerLog(pankey_Log_StartMethod, "removeInitialization", "Base::InvokeMethod<A&>");
						init_app_functions_list.removeUpdateFunctionList(a_state);
						LoopManagerLog(pankey_Log_EndMethod, "removeInitialization", "");
					}
					
					virtual void removeInitialization(const Base::CharArray& a_name){
						
					}
					
					virtual void clear(){
						init_functions_list.clear();
						init_app_functions_list.clear();
						
						init_class_functions_list.clear();

						functions_list.clear();
						app_functions_list.clear();
						timed_functions_list.clear();
						app_timed_functions_list.clear();
						
						class_functions_list.clear();
						class_timed_functions_list.clear();
						
						functions_map.clear();
						app_functions_map.clear();
						timed_functions_map.clear();
						app_timed_functions_map.clear();
						
						class_functions_map.clear();
						class_timed_functions_map.clear();
					}

					virtual void initialize(A& a_app){
						init_functions_list.initialize();
						init_app_functions_list.initialize(a_app);
						
						init_class_functions_list.update(a_app);

						state_functions_list.initialize();

						init_functions_map.update();
						init_app_functions_map.update(a_app);
					}

					virtual void update(A& a_app, long a_tpc){
						LoopManagerLog(pankey_Log_StartMethod, "update",  "");
						init_functions_list.initialize();
						init_app_functions_list.initialize(a_app);
						
						functions_list.update();
						app_functions_list.update(a_app);
						timed_functions_list.update(a_tpc);
						app_timed_functions_list.update(a_app, a_tpc);

						class_functions_list.update(a_app);
						class_timed_functions_list.update(a_app, a_tpc);
						
						state_functions_list.update();
						// state_timed_functions_list.update(a_tpc);
						
						// app_state_functions_list.update(a_app);
						// app_state_timed_functions_list.update(a_app, a_tpc);
						
						functions_map.update();
						app_functions_map.update(a_app);
						timed_functions_map.update(a_tpc);
						app_timed_functions_map.update(a_app, a_tpc);

						class_functions_map.update(a_app);
						class_timed_functions_map.update(a_app, a_tpc);
						
						// app_state_functions_map.update(a_app, a_tpc);
						LoopManagerLog(pankey_Log_EndMethod, "update",  "");
					}

				protected:
					//initialize
					InitializeFunctionListManager<> init_functions_list;
					InitializeFunctionListManager<A&> init_app_functions_list;

					UpdateClassFunctionListManager<A> init_class_functions_list;

					UpdateFunctionMapManager<Base::CharArray> init_functions_map;
					UpdateFunctionMapManager<Base::CharArray,A&> init_app_functions_map;

					//update
					UpdateFunctionListManager<> functions_list;
					UpdateFunctionListManager<A&> app_functions_list;
					UpdateFunctionListManager<long> timed_functions_list;
					UpdateFunctionListManager<A&,long> app_timed_functions_list;

					UpdateClassFunctionListManager<A> class_functions_list;
					UpdateClassFunctionListManager<A,long> class_timed_functions_list;

					UpdateFunctionMapManager<Base::CharArray> functions_map;
					UpdateFunctionMapManager<Base::CharArray,A&> app_functions_map;
					UpdateFunctionMapManager<Base::CharArray,long> timed_functions_map;
					UpdateFunctionMapManager<Base::CharArray,A&,long> app_timed_functions_map;

					UpdateClassFunctionMapManager<A,Base::CharArray> class_functions_map;
					UpdateClassFunctionMapManager<A,Base::CharArray,long> class_timed_functions_map;
			};

		}

	}

#endif