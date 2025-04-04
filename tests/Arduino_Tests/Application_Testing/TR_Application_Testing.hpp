
#ifndef TR_Application_Testing_hpp
	#define TR_Application_Testing_hpp

	#include "TestResult.hpp"
	#include "TestRunner.hpp"

	namespace pankey{

		namespace ApplicationSystem{
	
			Base::TestResult TR_Application_Testing_1(){
				Base::TestResult i_result;

				Application i_app;
				
				return i_result;
			}
		
			Base::TestResult TR_Application_Testing_2(){
				Base::TestResult i_result;

				Application i_app;

				StateManager& i_manager = i_app.getStateManager();
				
				return i_result;
			}
		
			Base::TestResult TR_Application_Testing_3(){
				Base::TestResult i_result;

				Application i_app;

				StateManager& i_manager = i_app.getStateManager();
				
				return i_result;
			}
		
			Base::TestResult TR_Application_Testing_4(){
				Base::TestResult i_result;

				Application i_app;

				auto& i_manager = i_app.getStateManager();
				
				return i_result;
			}
		
			Base::TestResult TR_Application_Testing_5(){
				Base::TestResult i_result;

				Application i_app;

				Settings& i_settings = i_app.getSettings();
				
				return i_result;
			}
		
			Base::TestResult TR_Application_Testing_6(){
				Base::TestResult i_result;

				Application i_app;

				auto& i_settings = i_app.getSettings();
				
				return i_result;
			}
			void TR_Application_Testing(Base::TestRunner& a_test_runner){
				createEngineManager();

				a_test_runner.add("Application Constructor", TR_Application_Testing_1);
				a_test_runner.add("Application getStateManager", TR_Application_Testing_2);
				a_test_runner.add("Application AppManager", TR_Application_Testing_3);
				a_test_runner.add("Application auto getStateManager", TR_Application_Testing_4);
				a_test_runner.add("Application AppSettings getSettings", TR_Application_Testing_5);
				a_test_runner.add("Application auto getSettings", TR_Application_Testing_6);
			}

		}

	}

#endif
