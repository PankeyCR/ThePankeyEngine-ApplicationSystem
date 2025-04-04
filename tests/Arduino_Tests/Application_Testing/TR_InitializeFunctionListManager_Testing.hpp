
#ifndef TR_InitializeFunctionListManager_Testing_hpp
	#define TR_InitializeFunctionListManager_Testing_hpp

	#include "TestResult.hpp"
	#include "TestRunner.hpp"

	#include "InitializeFunctionListManager.hpp"

	namespace pankey{

		namespace ApplicationSystem{

			void InitializeFunctionListManagerTest(Base::TestResult& a_result, float a_tpc){
				a_result.expecting("executing method");
			}

			void InitializeFunctionListManagerTest_2(Base::TestResult& a_result, float a_tpc){
				a_result.expecting("executing method 2");
			}

			void InitializeFunctionListManagerTest_3(Base::TestResult& a_result, float a_tpc){
				a_result.expecting("executing method 3");
			}

			void InitializeFunctionListManagerTestWithError(Base::TestResult& a_result, float a_tpc){
				a_result.expectingTrue("executing error method", false);
			}
			
			Base::TestResult TR_InitializeFunctionListManager_Testing_1(){
				Base::TestResult i_result;

				InitializeFunctionListManager<Base::TestResult&,float> i_manager;

				i_manager.add(InitializeFunctionListManagerTest);
				i_manager.initialize(i_result, 0.1f);

				i_result.assertExpectation("executing method");
				
				return i_result;
			}

			void TR_InitializeFunctionListManager_Testing(Base::TestRunner& a_test_runner){
				a_test_runner.add("InitializeFunctionListManager add and initialize", TR_InitializeFunctionListManager_Testing_1);
			}

		}

	}

#endif
