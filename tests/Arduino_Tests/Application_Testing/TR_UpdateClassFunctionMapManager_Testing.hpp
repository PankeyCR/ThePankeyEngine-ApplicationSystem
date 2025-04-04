
#ifndef TR_UpdateClassFunctionMapManager_Testing_hpp
	#define TR_UpdateClassFunctionMapManager_Testing_hpp

	#include "TestResult.hpp"
	#include "TestRunner.hpp"

	#include "UpdateClassFunctionMapManager.hpp"
	#include "CharArray.hpp"

	namespace pankey{

		namespace ApplicationSystem{
		
			class UpdateClassFunctionMapExample{
				public:
				void UpdateClassFunctionMapManagerTest(Base::TestResult& a_result, float a_tpc){
					a_result.assertTrue("executing class method", true);
				}

				void UpdateClassFunctionMapManagerTestWithError(Base::TestResult& a_result, float a_tpc){
					a_result.assertTrue("executing class method with error", false);
				}
			};
		
			Base::TestResult TR_UpdateClassFunctionMapManager_Testing_1(){
				Base::TestResult i_result;

				UpdateClassFunctionMapManager<UpdateClassFunctionMapExample,Base::CharArray,Base::TestResult&,float> i_manager;
				UpdateClassFunctionMapExample i_example;

				i_manager.add("class_function", &UpdateClassFunctionMapExample::UpdateClassFunctionMapManagerTest);

				i_manager.update(i_example, i_result, 0.1f);
				
				return i_result;
			}
			
			Base::TestResult TR_UpdateClassFunctionMapManager_Testing_2(){
				Base::TestResult i_result;

				UpdateClassFunctionMapManager<UpdateClassFunctionMapExample,Base::CharArray,Base::TestResult&,float> i_manager;
				UpdateClassFunctionMapExample i_example;

				i_manager.add("class_function", &UpdateClassFunctionMapExample::UpdateClassFunctionMapManagerTest);
				i_manager.add("class_error_function", &UpdateClassFunctionMapExample::UpdateClassFunctionMapManagerTestWithError);

				i_manager.removeUpdateClassFunctionMap("class_error_function");

				i_manager.update(i_example, i_result, 0.1f);
				
				return i_result;
			}
			
			Base::TestResult TR_UpdateClassFunctionMapManager_Testing_3(){
				Base::TestResult i_result;

				UpdateClassFunctionMapManager<UpdateClassFunctionMapExample,Base::CharArray,Base::TestResult&,float> i_manager;
				UpdateClassFunctionMapExample i_example;

				i_manager.add("class_function", &UpdateClassFunctionMapExample::UpdateClassFunctionMapManagerTest);
				i_manager.add("class_error_function", &UpdateClassFunctionMapExample::UpdateClassFunctionMapManagerTestWithError);

				i_manager.removeUpdateClassFunctionMap(1);
				
				i_manager.update(i_example, i_result, 0.1f);
				
				return i_result;
			}
			
			Base::TestResult TR_UpdateClassFunctionMapManager_Testing_4(){
				Base::TestResult i_result;

				UpdateClassFunctionMapManager<UpdateClassFunctionMapExample,Base::CharArray,Base::TestResult&,float> i_manager;
				UpdateClassFunctionMapExample i_example;

				i_manager.add("class_function", &UpdateClassFunctionMapExample::UpdateClassFunctionMapManagerTest);
				i_manager.add("class_error_function", &UpdateClassFunctionMapExample::UpdateClassFunctionMapManagerTestWithError);

				i_manager.clear();
				
				i_manager.update(i_example, i_result, 0.1f);
				
				i_result.assertEqual("manager shouldnt have any methods", i_manager.getUpdateClassFunctionMapSize(), 0);
				i_result.assertEqual("manager shouldnt have any methods", i_manager.getUpdateClassFunctionMapSize(), 0);
				
				return i_result;
			}

			void TR_UpdateClassFunctionMapManager_Testing(Base::TestRunner& a_test_runner){
				a_test_runner.add("UpdateClassFunctionMapManager add and update", TR_UpdateClassFunctionMapManager_Testing_1);
				a_test_runner.add("UpdateClassFunctionMapManager removeUpdate by lvalue", TR_UpdateClassFunctionMapManager_Testing_2);
				a_test_runner.add("UpdateClassFunctionMapManager removeUpdate by index", TR_UpdateClassFunctionMapManager_Testing_3);
				a_test_runner.add("UpdateClassFunctionMapManager removeAll", TR_UpdateClassFunctionMapManager_Testing_4);
			}

		}

	}

#endif
