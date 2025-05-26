
#ifndef TR_ASL_Application_Testing_hpp
	#define TR_ASL_Application_Testing_hpp

	#include "TestResult.hpp"
	#include "TestRunner.hpp"

	#include "ASL_Application.hpp"

	namespace pankey{

		namespace ApplicationSystem{
			
			Base::TestResult<String> TR_ASL_Application_Testing_1(){
				Base::TestResult<String> i_result;

				ASL_Application i_app;
				
				auto& i_manager = i_app.getStateManager();
				auto& i_settings = i_app.getSettings();

				i_app.initialize();
				i_app.update(millis());
				
				return i_result;
			}

			void TR_ASL_Application_Testing(Base::TestRunner<String>& a_test_runner){
				a_test_runner.add("ASL_Application", TR_ASL_Application_Testing_1);
			}

		}

	}

#endif
