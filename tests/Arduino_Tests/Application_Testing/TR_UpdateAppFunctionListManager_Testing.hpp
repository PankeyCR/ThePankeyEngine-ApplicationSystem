
#ifndef TR_UpdateAppFunctionListManager_Testing_hpp
	#define TR_UpdateAppFunctionListManager_Testing_hpp

	#include "TestResult.hpp"
	#include "TestRunner.hpp"

	#include "UpdateAppFunctionListManager.hpp"

	namespace pankey{

		namespace ApplicationSystem{

			void UpdateAppFunctionListManagerTest(Base::TestResult<String>& a_result, float a_tpc){
				a_result.expecting("executing method");
			}

			void UpdateAppFunctionListManagerTest_2(Base::TestResult<String>& a_result, float a_tpc){
				a_result.expecting("executing method 2");
			}

			void UpdateAppFunctionListManagerTest_3(Base::TestResult<String>& a_result, float a_tpc){
				a_result.expecting("executing method 3");
			}

			void UpdateAppFunctionListManagerTestWithError(Base::TestResult<String>& a_result, float a_tpc){
				a_result.expectingTrue("executing error method", false);
			}
			
			Base::TestResult<String> TR_UpdateAppFunctionListManager_Testing_1(){
				Base::TestResult<String> i_result;

				UpdateAppFunctionListManager<Base::TestResult<String>,float> i_manager;

				i_manager.putAppFunction(UpdateAppFunctionListManagerTest);
				i_manager.update(i_result, 0.1f);

				i_result.assertExpectation("executing method");
				
				return i_result;
			}
			
			Base::TestResult<String> TR_UpdateAppFunctionListManager_Testing_2(){
				Base::TestResult<String> i_result;

				UpdateAppFunctionListManager<Base::TestResult<String>,float> i_manager;

				i_manager.putAppFunction(UpdateAppFunctionListManagerTest);
				i_manager.putAppFunction(UpdateAppFunctionListManagerTestWithError);
				i_manager.destroyAppFunction(UpdateAppFunctionListManagerTestWithError);
				i_manager.update(i_result, 0.1f);

				i_result.assertExpectation("executing method");
				i_result.assertUnexpectation("executing error method");
				
				return i_result;
			}
			
			Base::TestResult<String> TR_UpdateAppFunctionListManager_Testing_3(){
				Base::TestResult<String> i_result;

				UpdateAppFunctionListManager<Base::TestResult<String>,float> i_manager;

				i_manager.putAppFunction(UpdateAppFunctionListManagerTest);
				i_manager.putAppFunction(UpdateAppFunctionListManagerTestWithError);

				i_manager.clearAppFunctions();

				i_manager.update(i_result, 0.1f);

				i_result.assertEqual("manager shouldnt have any methods", i_manager.AppFunction_length(), 0);
				i_result.assertUnexpectation("executing method");
				i_result.assertUnexpectation("executing error method");
				
				return i_result;
			}
			
			Base::TestResult<String> TR_UpdateAppFunctionListManager_Testing_4(){
				Base::TestResult<String> i_result;

				int i_app = 15;

				UpdateAppFunctionListManager<Base::TestResult<String>,float> i_manager;

				i_manager.putAppFunction(UpdateAppFunctionListManagerTest);
				i_manager.putAppFunction(UpdateAppFunctionListManagerTestWithError);

				i_manager.clear();

				i_manager.update(i_result, 0.1f);

				i_result.assertEqual("manager shouldnt have any methods", i_manager.length(), 0);
				i_result.assertUnexpectation("executing method");
				i_result.assertUnexpectation("executing error method");
				
				return i_result;
			}
			
			Base::TestResult<String> TR_UpdateAppFunctionListManager_Testing_5(){
				Base::TestResult<String> i_result;

				// UpdateAppFunctionListManager<Base::TestResult<String>,float> i_manager;

				// auto lambda = [](Base::TestResult<String>& a_result, float a_tpc){
				// 	a_result.expecting("executing lambda method");
				// };

				// i_manager.putAppFunction(lambda);

				// i_manager.update(i_result, 0.1f);

				// i_result.assertUnexpectation("executing lambda method");
				
				return i_result;
			}
			
			Base::TestResult<String> TR_UpdateAppFunctionListManager_Testing_6(){
				Base::TestResult<String> i_result;

				UpdateAppFunctionListManager<Base::TestResult<String>,float> i_manager;
				
				i_manager.putAppFunction(UpdateAppFunctionListManagerTest);
				i_manager.putAppFunction(UpdateAppFunctionListManagerTest_2);
				i_manager.putAppFunction(UpdateAppFunctionListManagerTest_3);

				i_manager.destroyAppFunction(UpdateAppFunctionListManagerTest_2);

				i_manager.update(i_result, 0.1f);

				i_result.assertExpectedSequence("executing method", "executing method 3");
				
				return i_result;
			}

			UpdateAppFunctionListManager<Base::TestResult<String>&,float> g_UpdateAppFunctionListManager;

			void DestroyUpdateAppFunctionListManagerTest(Base::TestResult<String>& a_result, float a_tpc){
				g_UpdateAppFunctionListManager.destroyAppFunction(DestroyUpdateAppFunctionListManagerTest);
			}

			void DestroyUpdateAppFunctionListManagerTest_2(Base::TestResult<String>& a_result, float a_tpc){
				g_UpdateAppFunctionListManager.destroyAppFunction(DestroyUpdateAppFunctionListManagerTest);
			}
			
			Base::TestResult<String> TR_UpdateAppFunctionListManager_Testing_7(){
				Base::TestResult<String> i_result;
				
				g_UpdateAppFunctionListManager.putAppFunction(UpdateAppFunctionListManagerTest);
				g_UpdateAppFunctionListManager.putAppFunction(DestroyUpdateAppFunctionListManagerTest);
				g_UpdateAppFunctionListManager.putAppFunction(UpdateAppFunctionListManagerTest_3);

				g_UpdateAppFunctionListManager.update(i_result, 0.1f);

				i_result.assertExpectedSequence("executing method", "executing method 3");
				i_result.assertEqual("length should be 2", g_UpdateAppFunctionListManager.length(), 2);

				g_UpdateAppFunctionListManager.clear();
				
				return i_result;
			}
			
			Base::TestResult<String> TR_UpdateAppFunctionListManager_Testing_8(){
				Base::TestResult<String> i_result;
				
				g_UpdateAppFunctionListManager.putAppFunction(DestroyUpdateAppFunctionListManagerTest_2);
				g_UpdateAppFunctionListManager.putAppFunction(DestroyUpdateAppFunctionListManagerTest);
				g_UpdateAppFunctionListManager.putAppFunction(UpdateFunctionListManagerTest_3);

				g_UpdateAppFunctionListManager.update(i_result, 0.1f);

				i_result.assertExpectation("executing method 3");
				i_result.assertUnexpectation("executing method");
				i_result.assertEqual("length should be 2", g_UpdateAppFunctionListManager.length(), 2);

				g_UpdateAppFunctionListManager.clear();
				
				return i_result;
			}

			void TR_UpdateAppFunctionListManager_Testing(Base::TestRunner<String>& a_test_runner){
				a_test_runner.add("UpdateAppFunctionListManager putAppFunction and update", TR_UpdateAppFunctionListManager_Testing_1);
				a_test_runner.add("UpdateAppFunctionListManager destroyAppFunction by value", TR_UpdateAppFunctionListManager_Testing_2);
				a_test_runner.add("UpdateAppFunctionListManager clearAppFunctions", TR_UpdateAppFunctionListManager_Testing_3);
				a_test_runner.add("UpdateAppFunctionListManager clear", TR_UpdateAppFunctionListManager_Testing_4);
				a_test_runner.add("UpdateAppFunctionListManager lambda", TR_UpdateAppFunctionListManager_Testing_5);
				a_test_runner.add("UpdateAppFunctionListManager update", TR_UpdateAppFunctionListManager_Testing_6);
				a_test_runner.add("UpdateAppFunctionListManager destroyFunctions", TR_UpdateAppFunctionListManager_Testing_7);
				a_test_runner.add("UpdateAppFunctionListManager destroyFunctions 2", TR_UpdateAppFunctionListManager_Testing_8);
			}

		}

	}

#endif
