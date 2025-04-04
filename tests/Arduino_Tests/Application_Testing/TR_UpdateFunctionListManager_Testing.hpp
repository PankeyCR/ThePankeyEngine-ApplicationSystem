
#ifndef TR_UpdateFunctionListManager_Testing_hpp
	#define TR_UpdateFunctionListManager_Testing_hpp

	#include "TestResult.hpp"
	#include "TestRunner.hpp"

	#include "UpdateFunctionListManager.hpp"

	namespace pankey{

		namespace ApplicationSystem{

			void UpdateFunctionListManagerTest(Base::TestResult& a_result, float a_tpc){
				a_result.expecting("executing method");
			}

			void UpdateFunctionListManagerTest_2(Base::TestResult& a_result, float a_tpc){
				a_result.expecting("executing method 2");
			}

			void UpdateFunctionListManagerTest_3(Base::TestResult& a_result, float a_tpc){
				a_result.expecting("executing method 3");
			}

			void UpdateFunctionListManagerTestWithError(Base::TestResult& a_result, float a_tpc){
				a_result.expectingTrue("executing error method", false);
			}
			
			Base::TestResult TR_UpdateFunctionListManager_Testing_1(){
				Base::TestResult i_result;

				int i_app = 15;

				UpdateFunctionListManager<int,Base::TestResult&,float> i_manager;

				i_manager.putFunction(UpdateFunctionListManagerTest);
				i_manager.update(i_app, i_result, 0.1f);

				i_result.assertExpectation("executing method");
				
				return i_result;
			}
			
			Base::TestResult TR_UpdateFunctionListManager_Testing_2(){
				Base::TestResult i_result;

				int i_app = 15;

				UpdateFunctionListManager<int,Base::TestResult&,float> i_manager;

				i_manager.putFunction(UpdateFunctionListManagerTest);
				i_manager.putFunction(UpdateFunctionListManagerTestWithError);
				i_manager.destroyFunction(UpdateFunctionListManagerTestWithError);
				i_manager.update(i_app, i_result, 0.1f);

				i_result.assertExpectation("executing method");
				i_result.assertUnexpectation("executing error method");
				
				return i_result;
			}
			
			Base::TestResult TR_UpdateFunctionListManager_Testing_3(){
				Base::TestResult i_result;

				int i_app = 15;

				UpdateFunctionListManager<int,Base::TestResult&,float> i_manager;

				i_manager.putFunction(UpdateFunctionListManagerTest);
				i_manager.putFunction(UpdateFunctionListManagerTestWithError);

				i_manager.clearFunctions();

				i_manager.update(i_app, i_result, 0.1f);

				i_result.assertEqual("manager shouldnt have any methods", i_manager.Function_length(), 0);
				i_result.assertUnexpectation("executing method");
				i_result.assertUnexpectation("executing error method");
				
				return i_result;
			}
			
			Base::TestResult TR_UpdateFunctionListManager_Testing_4(){
				Base::TestResult i_result;

				int i_app = 15;

				UpdateFunctionListManager<int,Base::TestResult&,float> i_manager;

				i_manager.putFunction(UpdateFunctionListManagerTest);
				i_manager.putFunction(UpdateFunctionListManagerTestWithError);

				i_manager.clear();

				i_manager.update(i_app, i_result, 0.1f);

				i_result.assertEqual("manager shouldnt have any methods", i_manager.length(), 0);
				i_result.assertUnexpectation("executing method");
				i_result.assertUnexpectation("executing error method");
				
				return i_result;
			}
			
			Base::TestResult TR_UpdateFunctionListManager_Testing_5(){
				Base::TestResult i_result;

				int i_app = 15;

				UpdateFunctionListManager<int,Base::TestResult&,float> i_manager;

				auto lambda = [](Base::TestResult& a_result, float a_tpc){
					a_result.expecting("executing lambda method");
				};

				i_manager.putFunction(lambda);

				i_manager.update(i_app, i_result, 0.1f);

				i_result.assertUnexpectation("executing lambda method");
				
				return i_result;
			}
			
			Base::TestResult TR_UpdateFunctionListManager_Testing_6(){
				Base::TestResult i_result;

				int i_app = 15;

				UpdateFunctionListManager<int,Base::TestResult&,float> i_manager;
				
				i_manager.putFunction(UpdateFunctionListManagerTest);
				i_manager.putFunction(UpdateFunctionListManagerTest_2);
				i_manager.putFunction(UpdateFunctionListManagerTest_3);

				i_manager.destroyFunction(UpdateFunctionListManagerTest_2);

				i_manager.update(i_app, i_result, 0.1f);

				i_result.assertExpectedSequence("executing method", "executing method 3");
				
				return i_result;
			}

			UpdateFunctionListManager<int,Base::TestResult&,float> g_UpdateFunctionListManager;

			void DestroyUpdateFunctionListManagerTest(Base::TestResult& a_result, float a_tpc){
				g_UpdateFunctionListManager.destroyFunction(DestroyUpdateFunctionListManagerTest);
			}

			void DestroyUpdateFunctionListManagerTest_2(Base::TestResult& a_result, float a_tpc){
				g_UpdateFunctionListManager.destroyFunction(DestroyUpdateFunctionListManagerTest);
			}
			
			Base::TestResult TR_UpdateFunctionListManager_Testing_7(){
				Base::TestResult i_result;

				int i_app = 15;
				
				g_UpdateFunctionListManager.putFunction(UpdateFunctionListManagerTest);
				g_UpdateFunctionListManager.putFunction(DestroyUpdateFunctionListManagerTest);
				g_UpdateFunctionListManager.putFunction(UpdateFunctionListManagerTest_3);

				g_UpdateFunctionListManager.update(i_app, i_result, 0.1f);

				i_result.assertExpectedSequence("executing method", "executing method 3");
				i_result.assertEqual("length should be 2", g_UpdateFunctionListManager.length(), 2);

				g_UpdateFunctionListManager.clear();
				
				return i_result;
			}
			
			Base::TestResult TR_UpdateFunctionListManager_Testing_8(){
				Base::TestResult i_result;

				int i_app = 15;
				
				g_UpdateFunctionListManager.putFunction(DestroyUpdateFunctionListManagerTest_2);
				g_UpdateFunctionListManager.putFunction(DestroyUpdateFunctionListManagerTest);
				g_UpdateFunctionListManager.putFunction(UpdateFunctionListManagerTest_3);

				g_UpdateFunctionListManager.update(i_app, i_result, 0.1f);

				i_result.assertExpectedSequence("executing method", "executing method 3");
				i_result.assertEqual("length should be 2", g_UpdateFunctionListManager.length(), 2);

				g_UpdateFunctionListManager.clear();
				
				return i_result;
			}

			void TR_UpdateFunctionListManager_Testing(Base::TestRunner& a_test_runner){
				a_test_runner.add("UpdateFunctionListManager putFunction and update", TR_UpdateFunctionListManager_Testing_1);
				a_test_runner.add("UpdateFunctionListManager destroyFunction by value", TR_UpdateFunctionListManager_Testing_2);
				a_test_runner.add("UpdateFunctionListManager clearFunctions", TR_UpdateFunctionListManager_Testing_3);
				a_test_runner.add("UpdateFunctionListManager clear", TR_UpdateFunctionListManager_Testing_4);
				a_test_runner.add("UpdateFunctionListManager lambda", TR_UpdateFunctionListManager_Testing_5);
				a_test_runner.add("UpdateFunctionListManager update", TR_UpdateFunctionListManager_Testing_6);
				a_test_runner.add("UpdateFunctionListManager destroyFunctions", TR_UpdateFunctionListManager_Testing_7);
				a_test_runner.add("UpdateFunctionListManager destroyFunctions 2", TR_UpdateFunctionListManager_Testing_8);
			}

		}

	}

#endif
