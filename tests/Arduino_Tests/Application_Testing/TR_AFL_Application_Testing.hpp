
#ifndef TR_AFL_Application_Testing_hpp
	#define TR_AFL_Application_Testing_hpp

	#include "TestResult.hpp"
	#include "TestRunner.hpp"

	#include "AFL_Application.hpp"

	namespace pankey{

		namespace ApplicationSystem{
			
			Base::TestResult TR_AFL_Application_Testing_1(){
				Base::TestResult i_result;

				AFL_Application i_app;
				
				auto& i_manager = i_app.getStateManager();
				auto& i_settings = i_app.getSettings();

				i_app.initialize();
				i_app.update(millis());
				
				return i_result;
			}

			void TR_AFL_Application_Testing(Base::TestRunner& a_test_runner){
				a_test_runner.add("AFL_Application", TR_AFL_Application_Testing_1);
			}

		}

	}

#endif
