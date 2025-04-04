
#ifndef TR_LoopManager_Testing_hpp
	#define TR_LoopManager_Testing_hpp

	#include "TestResult.hpp"
	#include "TestRunner.hpp"

	#include "LoopManager.hpp"
	#include "BaseAppState.hpp"

	namespace pankey{

		namespace ApplicationSystem{

			Base::TestResult g_loop_result;

			class LoopExample{
				public:
				void loop(){
					g_loop_result.expecting("LoopExample::loop");
				}

				void tpc_loop(long a_tpc){
					g_loop_result.expecting("LoopExample::tpc_loop");
				}
			};

			void LoopMethod(){
				g_loop_result.expecting("LoopMethod");
			}
			void TPCLoopMethod(long a_tpc){
				g_loop_result.expecting("TPCLoopMethod");
			}
			void LoopExampleMethod(LoopExample& a_example){
				g_loop_result.expecting("LoopExampleMethod");
			}
			void TPCLoopExampleMethod(LoopExample& a_example, long a_tpc){
				g_loop_result.expecting("TPCLoopExampleMethod");
			}

			// class LoopExampleAppState : public BaseAppState<LoopExample,long>{
			// 	public:
			// 	virtual void initializeState(LoopExample& app){
			// 		g_loop_result.expecting("LoopExampleAppState::initializeState");
			// 	}
			// 	virtual void updateState(LoopExample& app, long a_tpc){
			// 		g_loop_result.expecting("LoopExampleAppState::updateState");
			// 	}
			// };

			// class LoopExampleState : public State<long>{
			// 	public:
			// 	virtual void initializeState(){
			// 		g_loop_result.expecting("LoopExampleState::initializeState");
			// 	}
			// 	virtual void updateState(long a_tpc){
			// 		g_loop_result.expecting("LoopExampleState::updateState");
			// 	}
			// };

			Base::TestResult TR_LoopManager_Testing_1(){
				g_loop_result.clear();

				LoopManager<LoopExample> i_manager;
				LoopExample i_example;

				i_manager.addInitialization(LoopMethod);

				i_manager.initialize(i_example);

				g_loop_result.assertExpectation("LoopMethod");

				Base::TestResult i_result = g_loop_result;
				g_loop_result.clear();

				return i_result;
			}

			Base::TestResult TR_LoopManager_Testing_2(){
				g_loop_result.clear();

				LoopManager<LoopExample> i_manager;
				LoopExample i_example;

				i_manager.putInitialization(LoopMethod);
				i_manager.putInitialization(LoopMethod);

				i_manager.initialize(i_example);

				g_loop_result.assertExpectation("LoopMethod");

				Base::TestResult i_result = g_loop_result;
				g_loop_result.clear();

				return i_result;
			}

			Base::TestResult TR_LoopManager_Testing_3(){
				g_loop_result.clear();

				LoopManager<LoopExample> i_manager;
				LoopExample i_example;

				i_manager.addInitialization(LoopExampleMethod);

				i_manager.initialize(i_example);

				g_loop_result.assertExpectation("LoopExampleMethod");

				Base::TestResult i_result = g_loop_result;
				g_loop_result.clear();

				return i_result;
			}

			Base::TestResult TR_LoopManager_Testing_4(){
				g_loop_result.clear();

				LoopManager<LoopExample> i_manager;
				LoopExample i_example;

				i_manager.putInitialization(LoopExampleMethod);
				i_manager.putInitialization(LoopExampleMethod);

				i_manager.initialize(i_example);

				g_loop_result.assertExpectation("LoopExampleMethod");

				Base::TestResult i_result = g_loop_result;
				g_loop_result.clear();

				return i_result;
			}

			Base::TestResult TR_LoopManager_Testing_5(){
				g_loop_result.clear();

				LoopManager<LoopExample> i_manager;
				LoopExample i_example;

				i_manager.addInitialization("state", LoopMethod);

				i_manager.initialize(i_example);

				g_loop_result.assertExpectation("LoopMethod");

				Base::TestResult i_result = g_loop_result;
				g_loop_result.clear();

				return i_result;
			}

			Base::TestResult TR_LoopManager_Testing_6(){
				g_loop_result.clear();

				LoopManager<LoopExample> i_manager;
				LoopExample i_example;

				i_manager.putInitialization("state", LoopMethod);
				i_manager.putInitialization("state", LoopMethod);

				i_manager.initialize(i_example);

				g_loop_result.assertExpectation("LoopMethod");

				Base::TestResult i_result = g_loop_result;
				g_loop_result.clear();

				return i_result;
			}

			Base::TestResult TR_LoopManager_Testing_7(){
				g_loop_result.clear();

				LoopManager<LoopExample> i_manager;
				LoopExample i_example;

				i_manager.addInitialization("state", LoopExampleMethod);

				i_manager.initialize(i_example);

				g_loop_result.assertExpectation("LoopExampleMethod");

				Base::TestResult i_result = g_loop_result;
				g_loop_result.clear();

				return i_result;
			}

			Base::TestResult TR_LoopManager_Testing_8(){
				g_loop_result.clear();

				LoopManager<LoopExample> i_manager;
				LoopExample i_example;

				i_manager.putInitialization("state", LoopExampleMethod);
				i_manager.putInitialization("state", LoopExampleMethod);

				i_manager.initialize(i_example);

				g_loop_result.assertExpectation("LoopExampleMethod");

				Base::TestResult i_result = g_loop_result;
				g_loop_result.clear();

				return i_result;
			}

			Base::TestResult TR_LoopManager_Testing_9(){
				g_loop_result.clear();

				LoopManager<LoopExample> i_manager;
				LoopExample i_example;

				i_manager.addLoop(LoopMethod);

				i_manager.update(i_example, 100l);

				g_loop_result.assertExpectation("LoopMethod");

				Base::TestResult i_result = g_loop_result;
				g_loop_result.clear();

				return i_result;
			}

			Base::TestResult TR_LoopManager_Testing_10(){
				g_loop_result.clear();

				LoopManager<LoopExample> i_manager;
				LoopExample i_example;

				i_manager.putLoop(LoopMethod);
				i_manager.putLoop(LoopMethod);

				i_manager.update(i_example, 100l);

				g_loop_result.assertExpectation("LoopMethod");

				Base::TestResult i_result = g_loop_result;
				g_loop_result.clear();

				return i_result;
			}

			Base::TestResult TR_LoopManager_Testing_11(){
				g_loop_result.clear();

				LoopManager<LoopExample> i_manager;
				LoopExample i_example;

				i_manager.addLoop(LoopExampleMethod);

				i_manager.update(i_example, 100l);

				g_loop_result.assertExpectation("LoopExampleMethod");

				Base::TestResult i_result = g_loop_result;
				g_loop_result.clear();

				return i_result;
			}

			Base::TestResult TR_LoopManager_Testing_12(){
				g_loop_result.clear();

				LoopManager<LoopExample> i_manager;
				LoopExample i_example;

				i_manager.putLoop(LoopExampleMethod);
				i_manager.putLoop(LoopExampleMethod);

				i_manager.update(i_example, 100l);

				g_loop_result.assertExpectation("LoopExampleMethod");

				Base::TestResult i_result = g_loop_result;
				g_loop_result.clear();

				return i_result;
			}

			Base::TestResult TR_LoopManager_Testing_13(){
				g_loop_result.clear();

				LoopManager<LoopExample> i_manager;
				LoopExample i_example;

				i_manager.addLoop(TPCLoopMethod);

				i_manager.update(i_example, 100l);

				g_loop_result.assertExpectation("TPCLoopMethod");

				Base::TestResult i_result = g_loop_result;
				g_loop_result.clear();

				return i_result;
			}

			Base::TestResult TR_LoopManager_Testing_14(){
				g_loop_result.clear();

				LoopManager<LoopExample> i_manager;
				LoopExample i_example;

				i_manager.putLoop(TPCLoopMethod);
				i_manager.putLoop(TPCLoopMethod);

				i_manager.update(i_example, 100l);

				g_loop_result.assertExpectation("TPCLoopMethod");

				Base::TestResult i_result = g_loop_result;
				g_loop_result.clear();

				return i_result;
			}

			Base::TestResult TR_LoopManager_Testing_15(){
				g_loop_result.clear();

				LoopManager<LoopExample> i_manager;
				LoopExample i_example;

				i_manager.addLoop(TPCLoopExampleMethod);

				i_manager.update(i_example, 100l);

				g_loop_result.assertExpectation("TPCLoopExampleMethod");

				Base::TestResult i_result = g_loop_result;
				g_loop_result.clear();

				return i_result;
			}

			Base::TestResult TR_LoopManager_Testing_16(){
				g_loop_result.clear();

				LoopManager<LoopExample> i_manager;
				LoopExample i_example;

				i_manager.putLoop(TPCLoopExampleMethod);
				i_manager.putLoop(TPCLoopExampleMethod);

				i_manager.update(i_example, 100l);

				g_loop_result.assertExpectation("TPCLoopExampleMethod");

				Base::TestResult i_result = g_loop_result;
				g_loop_result.clear();

				return i_result;
			}

			Base::TestResult TR_LoopManager_Testing_17(){
				g_loop_result.clear();

				LoopManager<LoopExample> i_manager;
				LoopExample i_example;

				i_manager.addLoop("state", LoopMethod);

				i_manager.update(i_example, 100l);

				g_loop_result.assertExpectation("LoopMethod");

				Base::TestResult i_result = g_loop_result;
				g_loop_result.clear();

				return i_result;
			}

			Base::TestResult TR_LoopManager_Testing_18(){
				g_loop_result.clear();

				LoopManager<LoopExample> i_manager;
				LoopExample i_example;

				i_manager.putLoop("state", LoopMethod);
				i_manager.putLoop("state", LoopMethod);

				i_manager.update(i_example, 100l);

				g_loop_result.assertExpectation("LoopMethod");

				Base::TestResult i_result = g_loop_result;
				g_loop_result.clear();

				return i_result;
			}

			Base::TestResult TR_LoopManager_Testing_19(){
				g_loop_result.clear();

				LoopManager<LoopExample> i_manager;
				LoopExample i_example;

				i_manager.addLoop("state", LoopExampleMethod);

				i_manager.update(i_example, 100l);

				g_loop_result.assertExpectation("LoopExampleMethod");

				Base::TestResult i_result = g_loop_result;
				g_loop_result.clear();

				return i_result;
			}

			Base::TestResult TR_LoopManager_Testing_20(){
				g_loop_result.clear();

				LoopManager<LoopExample> i_manager;
				LoopExample i_example;

				i_manager.putLoop("state", LoopExampleMethod);
				i_manager.putLoop("state", LoopExampleMethod);

				i_manager.update(i_example, 100l);

				g_loop_result.assertExpectation("LoopExampleMethod");

				Base::TestResult i_result = g_loop_result;
				g_loop_result.clear();

				return i_result;
			}

			Base::TestResult TR_LoopManager_Testing_21(){
				g_loop_result.clear();

				LoopManager<LoopExample> i_manager;
				LoopExample i_example;

				i_manager.addLoop("state", TPCLoopMethod);

				i_manager.update(i_example, 100l);

				g_loop_result.assertExpectation("TPCLoopMethod");

				Base::TestResult i_result = g_loop_result;
				g_loop_result.clear();

				return i_result;
			}

			Base::TestResult TR_LoopManager_Testing_22(){
				g_loop_result.clear();

				LoopManager<LoopExample> i_manager;
				LoopExample i_example;

				i_manager.putLoop("state", TPCLoopMethod);
				i_manager.putLoop("state", TPCLoopMethod);

				i_manager.update(i_example, 100l);

				g_loop_result.assertExpectation("TPCLoopMethod");

				Base::TestResult i_result = g_loop_result;
				g_loop_result.clear();

				return i_result;
			}

			Base::TestResult TR_LoopManager_Testing_23(){
				g_loop_result.clear();

				LoopManager<LoopExample> i_manager;
				LoopExample i_example;

				i_manager.addLoop("state", TPCLoopExampleMethod);

				i_manager.update(i_example, 100l);

				g_loop_result.assertExpectation("TPCLoopExampleMethod");

				Base::TestResult i_result = g_loop_result;
				g_loop_result.clear();

				return i_result;
			}

			Base::TestResult TR_LoopManager_Testing_24(){
				g_loop_result.clear();

				LoopManager<LoopExample> i_manager;
				LoopExample i_example;

				i_manager.putLoop("state", TPCLoopExampleMethod);
				i_manager.putLoop("state", TPCLoopExampleMethod);

				i_manager.update(i_example, 100l);

				g_loop_result.assertExpectation("TPCLoopExampleMethod");

				Base::TestResult i_result = g_loop_result;
				g_loop_result.clear();

				return i_result;
			}

			void TR_LoopManager_Testing(Base::TestRunner& a_test_runner){
				a_test_runner.add("TR_LoopManager_Testing addInitialization, initialize", TR_LoopManager_Testing_1);
				a_test_runner.add("TR_LoopManager_Testing putInitialization, initialize", TR_LoopManager_Testing_2);
				a_test_runner.add("TR_LoopManager_Testing addInitialization(App), initialize", TR_LoopManager_Testing_3);
				a_test_runner.add("TR_LoopManager_Testing putInitialization(App), initialize", TR_LoopManager_Testing_4);
				a_test_runner.add("TR_LoopManager_Testing addInitialization(Name), initialize", TR_LoopManager_Testing_5);
				a_test_runner.add("TR_LoopManager_Testing putInitialization(Name), initialize", TR_LoopManager_Testing_6);
				a_test_runner.add("TR_LoopManager_Testing addInitialization(Name,App), initialize", TR_LoopManager_Testing_7);
				a_test_runner.add("TR_LoopManager_Testing putInitialization(Name,App), initialize", TR_LoopManager_Testing_8);
				a_test_runner.add("TR_LoopManager_Testing addLoop, update", TR_LoopManager_Testing_9);
				a_test_runner.add("TR_LoopManager_Testing putLoop, update", TR_LoopManager_Testing_10);
				a_test_runner.add("TR_LoopManager_Testing addLoop(App), update", TR_LoopManager_Testing_11);
				a_test_runner.add("TR_LoopManager_Testing putLoop(App), update", TR_LoopManager_Testing_12);
				a_test_runner.add("TR_LoopManager_Testing addLoop(tcp), update", TR_LoopManager_Testing_13);
				a_test_runner.add("TR_LoopManager_Testing putLoop(tcp), update", TR_LoopManager_Testing_14);
				a_test_runner.add("TR_LoopManager_Testing addLoop(App,tcp), update", TR_LoopManager_Testing_15);
				a_test_runner.add("TR_LoopManager_Testing putLoop(App,tcp), update", TR_LoopManager_Testing_16);
				a_test_runner.add("TR_LoopManager_Testing addLoop(Name), update", TR_LoopManager_Testing_17);
				a_test_runner.add("TR_LoopManager_Testing putLoop(Name), update", TR_LoopManager_Testing_18);
				a_test_runner.add("TR_LoopManager_Testing addLoop(Name,App), update", TR_LoopManager_Testing_19);
				a_test_runner.add("TR_LoopManager_Testing putLoop(Name,App), update", TR_LoopManager_Testing_20);
				a_test_runner.add("TR_LoopManager_Testing addLoop(Name,tcp), update", TR_LoopManager_Testing_21);
				a_test_runner.add("TR_LoopManager_Testing putLoop(Name,tcp), update", TR_LoopManager_Testing_22);
				a_test_runner.add("TR_LoopManager_Testing addLoop(Name,App,tcp), update", TR_LoopManager_Testing_23);
				a_test_runner.add("TR_LoopManager_Testing putLoop(Name,App,tcp), update", TR_LoopManager_Testing_24);
			}

		}

	}

#endif
