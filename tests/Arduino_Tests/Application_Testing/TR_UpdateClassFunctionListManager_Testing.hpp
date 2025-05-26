
#ifndef TR_UpdateClassFunctionListManager_Testing_hpp
	#define TR_UpdateClassFunctionListManager_Testing_hpp

	#include "TestResult.hpp"
	#include "TestRunner.hpp"

	#include "UpdateClassFunctionListManager.hpp"

	namespace pankey{

		namespace ApplicationSystem{
		
			class UpdateClassFunctionListExample{
				public:
				void UpdateClassFunctionListManagerTest(Base::TestResult<String>& a_result, float a_tpc){
					a_result.assertTrue("executing class method", true);
				}

				void UpdateClassFunctionListManagerTestWithError(Base::TestResult<String>& a_result, float a_tpc){
					a_result.assertTrue("executing class method with error", false);
				}
			};
		
			Base::TestResult<String> TR_UpdateClassFunctionListManager_Testing_1(){
				Base::TestResult<String> i_result;

				UpdateClassFunctionListManager<UpdateClassFunctionListExample,Base::TestResult<String>&,float> i_manager;
				UpdateClassFunctionListExample i_example;

				i_manager.add(&UpdateClassFunctionListExample::UpdateClassFunctionListManagerTest);

				i_manager.update(i_example, i_result, 0.1f);
				
				return i_result;
			}
			
			Base::TestResult<String> TR_UpdateClassFunctionListManager_Testing_2(){
				Base::TestResult<String> i_result;

				UpdateClassFunctionListManager<UpdateClassFunctionListExample,Base::TestResult<String>&,float> i_manager;
				UpdateClassFunctionListExample i_example;

				i_manager.add(&UpdateClassFunctionListExample::UpdateClassFunctionListManagerTest);
				i_manager.add(&UpdateClassFunctionListExample::UpdateClassFunctionListManagerTestWithError);

				i_manager.removeUpdateClassFunctionList(&UpdateClassFunctionListExample::UpdateClassFunctionListManagerTestWithError);

				i_manager.update(i_example, i_result, 0.1f);
				
				return i_result;
			}
			
			Base::TestResult<String> TR_UpdateClassFunctionListManager_Testing_3(){
				Base::TestResult<String> i_result;

				UpdateClassFunctionListManager<UpdateClassFunctionListExample,Base::TestResult<String>&,float> i_manager;
				UpdateClassFunctionListExample i_example;

				i_manager.add(&UpdateClassFunctionListExample::UpdateClassFunctionListManagerTest);
				i_manager.add(&UpdateClassFunctionListExample::UpdateClassFunctionListManagerTestWithError);

				i_manager.removeUpdateClassFunctionList(1);
				i_manager.removeUpdateClassFunctionList(1);
				
				i_manager.update(i_example, i_result, 0.1f);
				
				return i_result;
			}
			
			Base::TestResult<String> TR_UpdateClassFunctionListManager_Testing_4(){
				Base::TestResult<String> i_result;

				UpdateClassFunctionListManager<UpdateClassFunctionListExample,Base::TestResult<String>&,float> i_manager;
				UpdateClassFunctionListExample i_example;

				i_manager.add(&UpdateClassFunctionListExample::UpdateClassFunctionListManagerTest);
				i_manager.add(&UpdateClassFunctionListExample::UpdateClassFunctionListManagerTestWithError);

				i_manager.clear();
				
				i_manager.update(i_example, i_result, 0.1f);
				
				i_result.assertEqual("manager shouldnt have any methods", i_manager.getUpdateClassFunctionListSize(), 0);
				i_result.assertEqual("manager shouldnt have any methods", i_manager.getUpdateClassFunctionListSize(), 0);
				
				return i_result;
			}

			void TR_UpdateClassFunctionListManager_Testing(Base::TestRunner<String>& a_test_runner){
				a_test_runner.add("UpdateClassFunctionListManager add and update", TR_UpdateClassFunctionListManager_Testing_1);
				a_test_runner.add("UpdateClassFunctionListManager removeUpdate by lvalue", TR_UpdateClassFunctionListManager_Testing_2);
				a_test_runner.add("UpdateClassFunctionListManager removeUpdate by index", TR_UpdateClassFunctionListManager_Testing_3);
				a_test_runner.add("UpdateClassFunctionListManager removeAll", TR_UpdateClassFunctionListManager_Testing_4);
			}

		}

	}

#endif
