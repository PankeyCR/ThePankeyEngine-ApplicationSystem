
#ifndef TR_UpdateFunctionMapManager_Testing_hpp
	#define TR_UpdateFunctionMapManager_Testing_hpp

	#include "TestResult.hpp"
	#include "TestRunner.hpp"

	#include "CharArray.hpp"
	#include "UpdateFunctionMapManager.hpp"

	namespace pankey{

		namespace ApplicationSystem{

			void UpdateFunctionMapManagerTest(Base::TestResult& a_result, float a_tpc){
				a_result.assertTrue("executing method", true);
			}

			void UpdateFunctionMapManagerTestWithError(Base::TestResult& a_result, float a_tpc){
				a_result.assertTrue("executing method", false);
			}
			
			Base::TestResult TR_UpdateFunctionMapManager_Testing_1(){
				Base::TestResult i_result;

				UpdateFunctionMapManager<Base::CharArray,Base::TestResult&,float> i_manager;

				i_manager.add("key", UpdateFunctionMapManagerTest);
				i_manager.update(i_result, 0.1f);
				
				return i_result;
			}
			
			Base::TestResult TR_UpdateFunctionMapManager_Testing_2(){
				Base::TestResult i_result;

				UpdateFunctionMapManager<Base::CharArray,Base::TestResult&,float> i_manager;

				i_manager.add("function", UpdateFunctionMapManagerTest);
				i_manager.add("error_function", UpdateFunctionMapManagerTestWithError);
				i_manager.removeUpdateFunctionMap("error_function");
				i_manager.update(i_result, 0.1f);
				
				return i_result;
			}
			
			Base::TestResult TR_UpdateFunctionMapManager_Testing_3(){
				Base::TestResult i_result;

				UpdateFunctionMapManager<Base::CharArray,Base::TestResult&,float> i_manager;

				i_manager.add("function", UpdateFunctionMapManagerTest);
				i_manager.add("error_function", UpdateFunctionMapManagerTestWithError);
				i_manager.removeUpdateFunctionMap(1);
				i_manager.update(i_result, 0.1f);
				
				return i_result;
			}
			
			Base::TestResult TR_UpdateFunctionMapManager_Testing_4(){
				Base::TestResult i_result;

				UpdateFunctionMapManager<Base::CharArray,Base::TestResult&,float> i_manager;

				i_manager.add("function", UpdateFunctionMapManagerTest);
				i_manager.add("error_function", UpdateFunctionMapManagerTestWithError);

				i_manager.removeAllUpdateFunctionMap();

				i_manager.update(i_result, 0.1f);

				i_result.assertEqual("manager shouldnt have any methods", i_manager.getUpdateFunctionMapSize(), 0);
				
				return i_result;
			}
			
			Base::TestResult TR_UpdateFunctionMapManager_Testing_5(){
				Base::TestResult i_result;

				UpdateFunctionMapManager<Base::CharArray,Base::TestResult&,float> i_manager;

				i_manager.add("function", UpdateFunctionMapManagerTest);
				i_manager.add("error_function", UpdateFunctionMapManagerTestWithError);

				i_manager.clear();

				i_manager.update(i_result, 0.1f);

				i_result.assertEqual("manager shouldnt have any methods", i_manager.getUpdateFunctionMapSize(), 0);
				
				return i_result;
			}
			
			Base::TestResult TR_UpdateFunctionMapManager_Testing_6(){
				Base::TestResult i_result;

				UpdateFunctionMapManager<Base::CharArray,Base::TestResult&,float> i_manager;

				auto lambda = [](Base::TestResult& a_result, float a_tpc){
					a_result.assertTrue("executing method", true);
				};

				i_manager.add("method", lambda);

				i_manager.update(i_result, 0.1f);
				
				return i_result;
			}

			void TR_UpdateFunctionMapManager_Testing(Base::TestRunner& a_test_runner){
				a_test_runner.add("UpdateFunctionMapManager add and update", TR_UpdateFunctionMapManager_Testing_1);
				a_test_runner.add("UpdateFunctionMapManager removeUpdate by lvalue", TR_UpdateFunctionMapManager_Testing_2);
				a_test_runner.add("UpdateFunctionMapManager removeUpdate by index", TR_UpdateFunctionMapManager_Testing_3);
				a_test_runner.add("UpdateFunctionMapManager removeAllUpdateFunctionMap", TR_UpdateFunctionMapManager_Testing_4);
				a_test_runner.add("UpdateFunctionMapManager clear", TR_UpdateFunctionMapManager_Testing_5);
				a_test_runner.add("UpdateFunctionMapManager lambda", TR_UpdateFunctionMapManager_Testing_6);
			}

		}

	}

#endif
