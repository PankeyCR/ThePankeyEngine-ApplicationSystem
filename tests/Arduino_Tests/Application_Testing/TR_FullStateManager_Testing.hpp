
#ifndef TR_FullStateManager_Testing_hpp
	#define TR_FullStateManager_Testing_hpp

	#include "TestResult.hpp"
	#include "TestRunner.hpp"

	#include "FullStateManager.hpp"
	#include "BaseAppState.hpp"

	namespace pankey{

		namespace ApplicationSystem{

			Base::TestResult<String> g_fullstatemanager_result;

			class FullStateManagerExample{
				public:
				void loop(){
					g_fullstatemanager_result.expecting("FullStateManagerExample::loop");
				}

				void tpc_loop(long a_tpc){
					g_fullstatemanager_result.expecting("FullStateManagerExample::tpc_loop");
				}
			};

			void FullStateManagerMethod(){
				g_fullstatemanager_result.expecting("FullStateManagerMethod");
			}
			void TPCFullStateManagerMethod(long a_tpc){
				g_fullstatemanager_result.expecting("TPCFullStateManagerMethod");
			}
			void FullStateManagerExampleMethod(FullStateManagerExample& a_example){
				g_fullstatemanager_result.expecting("FullStateManagerExampleMethod");
			}
			void TPCFullStateManagerExampleMethod(FullStateManagerExample& a_example, long a_tpc){
				g_fullstatemanager_result.expecting("TPCFullStateManagerExampleMethod");
			}

			class FullStateManagerExampleAppState : public BaseAppState<FullStateManagerExample,long>{
				public:
				virtual void initializeState(FullStateManagerExample& app){
					g_fullstatemanager_result.expecting("FullStateManagerExampleAppState::initializeState");
				}
				virtual void updateState(FullStateManagerExample& app, long a_tpc){
					g_fullstatemanager_result.expecting("FullStateManagerExampleAppState::updateState");
				}
			};

			class FullStateManagerExampleState : public State<long>{
				public:
				virtual void initializeState(){
					g_fullstatemanager_result.expecting("FullStateManagerExampleState::initializeState");
				}
				virtual void updateState(long a_tpc){
					g_fullstatemanager_result.expecting("FullStateManagerExampleState::updateState");
				}
			};

			Base::TestResult<String> TR_FullStateManager_Testing_1(){
				g_fullstatemanager_result.clear();

				FullStateManager<FullStateManagerExample> i_manager;
				FullStateManagerExample i_example;

				i_manager.addInitialization(FullStateManagerMethod);

				i_manager.initialize(i_example);

				g_fullstatemanager_result.assertExpectation("FullStateManagerMethod");

				Base::TestResult<String> i_result = g_fullstatemanager_result;
				g_fullstatemanager_result.clear();

				return i_result;
			}

			Base::TestResult<String> TR_FullStateManager_Testing_2(){
				g_fullstatemanager_result.clear();

				FullStateManager<FullStateManagerExample> i_manager;
				FullStateManagerExample i_example;

				i_manager.putInitialization(FullStateManagerMethod);
				i_manager.putInitialization(FullStateManagerMethod);

				i_manager.initialize(i_example);

				g_fullstatemanager_result.assertExpectation("FullStateManagerExampleMethod");

				Base::TestResult<String> i_result = g_fullstatemanager_result;
				g_fullstatemanager_result.clear();

				return i_result;
			}

			// Base::TestResult<String> TR_FullStateManager_Testing_3(){
			// 	g_fullstatemanager_result.clear();

			// 	FullStateManager<FullStateManagerExample> i_manager;
			// 	FullStateManagerExample i_example;

			// 	i_manager.app_functions_list.add(FullStateManagerExampleMethod);

			// 	i_manager.update(i_example, 100l);

			// 	g_fullstatemanager_result.assertExpectation("FullStateManagerExampleMethod");

			// 	Base::TestResult<String> i_result = g_fullstatemanager_result;
			// 	g_fullstatemanager_result.clear();

			// 	return i_result;
			// }

			// Base::TestResult<String> TR_FullStateManager_Testing_4(){
			// 	g_fullstatemanager_result.clear();

			// 	FullStateManager<FullStateManagerExample> i_manager;
			// 	FullStateManagerExample i_example;

			// 	i_manager.app_timed_functions_list.add(TPCFullStateManagerExampleMethod);

			// 	i_manager.update(i_example, 100l);

			// 	g_fullstatemanager_result.assertExpectation("TPCFullStateManagerExampleMethod");

			// 	Base::TestResult<String> i_result = g_fullstatemanager_result;
			// 	g_fullstatemanager_result.clear();

			// 	return i_result;
			// }

			// Base::TestResult<String> TR_FullStateManager_Testing_5(){
			// 	g_fullstatemanager_result.clear();

			// 	FullStateManager<FullStateManagerExample> i_manager;
			// 	FullStateManagerExample i_example;

			// 	i_manager.class_functions_list.add(&FullStateManagerExample::loop);

			// 	i_manager.update(i_example, 100l);

			// 	g_fullstatemanager_result.assertExpectation("FullStateManagerExample::loop");

			// 	Base::TestResult<String> i_result = g_fullstatemanager_result;
			// 	g_fullstatemanager_result.clear();

			// 	return i_result;
			// }

			// Base::TestResult<String> TR_FullStateManager_Testing_6(){
			// 	g_fullstatemanager_result.clear();

			// 	FullStateManager<FullStateManagerExample> i_manager;
			// 	FullStateManagerExample i_example;

			// 	i_manager.class_timed_functions_list.add(&FullStateManagerExample::tpc_loop);

			// 	i_manager.update(i_example, 100l);

			// 	g_fullstatemanager_result.assertExpectation("FullStateManagerExample::tpc_loop");

			// 	Base::TestResult<String> i_result = g_fullstatemanager_result;
			// 	g_fullstatemanager_result.clear();

			// 	return i_result;
			// }

			// Base::TestResult<String> TR_FullStateManager_Testing_7(){
			// 	g_fullstatemanager_result.clear();

			// 	FullStateManager<FullStateManagerExample> i_manager;
			// 	FullStateManagerExample i_example;

			// 	i_manager.app_state_timed_functions_list.add(FullStateManagerExampleAppState());

			// 	i_manager.initialize(i_example);
			// 	i_manager.update(i_example, 100l);

			// 	g_fullstatemanager_result.assertExpectation("FullStateManagerExampleAppState::initializeState");
			// 	g_fullstatemanager_result.assertExpectation("FullStateManagerExampleAppState::updateState");

			// 	Base::TestResult<String> i_result = g_fullstatemanager_result;
			// 	g_fullstatemanager_result.clear();

			// 	return i_result;
			// }

			// Base::TestResult<String> TR_FullStateManager_Testing_8(){
			// 	g_fullstatemanager_result.clear();

			// 	FullStateManager<FullStateManagerExample> i_manager;
			// 	FullStateManagerExample i_example;

			// 	i_manager.functions_map.add("method", FullStateManagerMethod);

			// 	i_manager.update(i_example, 100l);

			// 	g_fullstatemanager_result.assertExpectation("FullStateManagerMethod");

			// 	Base::TestResult<String> i_result = g_fullstatemanager_result;
			// 	g_fullstatemanager_result.clear();

			// 	return i_result;
			// }

			// Base::TestResult<String> TR_FullStateManager_Testing_9(){
			// 	g_fullstatemanager_result.clear();

			// 	FullStateManager<FullStateManagerExample> i_manager;
			// 	FullStateManagerExample i_example;

			// 	i_manager.timed_functions_map.add("method", TPCFullStateManagerMethod);

			// 	i_manager.update(i_example, 100l);

			// 	g_fullstatemanager_result.assertExpectation("TPCFullStateManagerMethod");

			// 	Base::TestResult<String> i_result = g_fullstatemanager_result;
			// 	g_fullstatemanager_result.clear();

			// 	return i_result;
			// }

			// Base::TestResult<String> TR_FullStateManager_Testing_10(){
			// 	g_fullstatemanager_result.clear();

			// 	FullStateManager<FullStateManagerExample> i_manager;
			// 	FullStateManagerExample i_example;

			// 	i_manager.app_functions_map.add("method", FullStateManagerExampleMethod);

			// 	i_manager.update(i_example, 100l);

			// 	g_fullstatemanager_result.assertExpectation("FullStateManagerExampleMethod");

			// 	Base::TestResult<String> i_result = g_fullstatemanager_result;
			// 	g_fullstatemanager_result.clear();

			// 	return i_result;
			// }

			// Base::TestResult<String> TR_FullStateManager_Testing_11(){
			// 	g_fullstatemanager_result.clear();

			// 	FullStateManager<FullStateManagerExample> i_manager;
			// 	FullStateManagerExample i_example;

			// 	i_manager.app_timed_functions_map.add("method", TPCFullStateManagerExampleMethod);

			// 	i_manager.update(i_example, 100l);

			// 	g_fullstatemanager_result.assertExpectation("TPCFullStateManagerExampleMethod");

			// 	Base::TestResult<String> i_result = g_fullstatemanager_result;
			// 	g_fullstatemanager_result.clear();

			// 	return i_result;
			// }

			// Base::TestResult<String> TR_FullStateManager_Testing_12(){
			// 	g_fullstatemanager_result.clear();

			// 	FullStateManager<FullStateManagerExample> i_manager;
			// 	FullStateManagerExample i_example;

			// 	i_manager.class_functions_map.add("method", &FullStateManagerExample::loop);

			// 	i_manager.update(i_example, 100l);

			// 	g_fullstatemanager_result.assertExpectation("FullStateManagerExample::loop");

			// 	Base::TestResult<String> i_result = g_fullstatemanager_result;
			// 	g_fullstatemanager_result.clear();

			// 	return i_result;
			// }

			// Base::TestResult<String> TR_FullStateManager_Testing_13(){
			// 	g_fullstatemanager_result.clear();

			// 	FullStateManager<FullStateManagerExample> i_manager;
			// 	FullStateManagerExample i_example;

			// 	i_manager.class_timed_functions_map.add("method", &FullStateManagerExample::tpc_loop);

			// 	i_manager.update(i_example, 100l);

			// 	g_fullstatemanager_result.assertExpectation("FullStateManagerExample::tpc_loop");

			// 	Base::TestResult<String> i_result = g_fullstatemanager_result;
			// 	g_fullstatemanager_result.clear();

			// 	return i_result;
			// }

			// // Base::TestResult<String> TR_FullStateManager_Testing_14(){
			// // 	g_fullstatemanager_result.clear();

			// // 	FullStateManager<FullStateManagerExample> i_manager;
			// // 	FullStateManagerExample i_example;

			// // 	i_manager.app_state_functions_map.add("method", FullStateManagerExampleAppState());

			// // 	i_manager.update(i_example, 100l);

			// // 	Base::TestResult<String> i_result = g_fullstatemanager_result;
			// // 	g_fullstatemanager_result.clear();

			// // 	return i_result;
			// // }

			// Base::TestResult<String> TR_FullStateManager_Testing_15(){
			// 	g_fullstatemanager_result.clear();

			// 	FullStateManager<FullStateManagerExample> i_manager;
			// 	FullStateManagerExample i_example;

			// 	i_manager.state_timed_functions_list.add(FullStateManagerExampleState());

			// 	i_manager.initialize(i_example);
			// 	i_manager.update(i_example, 100l);

			// 	g_fullstatemanager_result.assertExpectation("FullStateManagerExampleState::initializeState");
			// 	g_fullstatemanager_result.assertExpectation("FullStateManagerExampleState::updateState");

			// 	Base::TestResult<String> i_result = g_fullstatemanager_result;
			// 	g_fullstatemanager_result.clear();

			// 	return i_result;
			// }

			void TR_FullStateManager_Testing(Base::TestRunner<String>& a_test_runner){
				a_test_runner.add("TR_FullStateManager_Testing add (single method) and update", TR_FullStateManager_Testing_1);
				// a_test_runner.add("TR_FullStateManager_Testing add (tpc method) and update", TR_FullStateManager_Testing_2);
				// a_test_runner.add("TR_FullStateManager_Testing add (loop example method) and update", TR_FullStateManager_Testing_3);
				// a_test_runner.add("TR_FullStateManager_Testing add (loop example, float method) and update", TR_FullStateManager_Testing_4);
				// a_test_runner.add("TR_FullStateManager_Testing add (class single method) and update", TR_FullStateManager_Testing_5);
				// a_test_runner.add("TR_FullStateManager_Testing 6 add (class tpc method) and update", TR_FullStateManager_Testing_6);
				// a_test_runner.add("TR_FullStateManager_Testing add (appstate) and update", TR_FullStateManager_Testing_7);

				// a_test_runner.add("TR_FullStateManager_Testing add (single method) and update", TR_FullStateManager_Testing_8);
				// a_test_runner.add("TR_FullStateManager_Testing add (tpc method) and update", TR_FullStateManager_Testing_9);
				// a_test_runner.add("TR_FullStateManager_Testing add (loop example method) and update", TR_FullStateManager_Testing_10);
				// a_test_runner.add("TR_FullStateManager_Testing add (loop example, float method) and update", TR_FullStateManager_Testing_11);
				// a_test_runner.add("TR_FullStateManager_Testing add (class single method) and update", TR_FullStateManager_Testing_12);
				// a_test_runner.add("TR_FullStateManager_Testing 13 add (class tpc method) and update", TR_FullStateManager_Testing_13);
				// // a_test_runner.add("TR_FullStateManager_Testing add (appstate) and update", TR_FullStateManager_Testing_14);
				
				// a_test_runner.add("TR_FullStateManager_Testing 15 add (class tpc method) and update", TR_FullStateManager_Testing_15);
			}

		}

	}

#endif
