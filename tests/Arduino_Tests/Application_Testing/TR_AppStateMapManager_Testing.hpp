
#ifndef TR_AppStateMapManager_Testing_hpp
	#define TR_AppStateMapManager_Testing_hpp

	#include "TestResult.hpp"
	#include "TestRunner.hpp"

	#include "CharArray.hpp"
	#include "AppStateMapManager.hpp"

	namespace pankey{

		namespace ApplicationSystem{

			class AppStateMapManager_App{public: Base::TestResult m_result;};

			class ASMM_State : public Base::AppState<AppStateMapManager_App>{
				public:
					virtual void initializeState(AppStateMapManager_App& a_app){
						a_app.m_result.expecting("initialize");
					}
					virtual void updateState(AppStateMapManager_App& a_app){
						a_app.m_result.expecting("update");
					}
					virtual void run(Base::TestResult& a_result){
						a_result.expecting("run");
					}

					TYPE_CLASS(ASMM_State)
			};
			
			Base::TestResult TR_AppStateMapManager_Testing_1(){
				Base::TestResult i_result;

				AppStateMapManager<AppStateMapManager_App> i_manager;
				i_manager.addAppState<ASMM_State>("state");

				i_manager.runAppStateMethod<ASMM_State,Base::TestResult&>(&ASMM_State::run, i_result);

				i_result.assertExpectedSequence("run");
				
				return i_result;
			}
			
			Base::TestResult TR_AppStateMapManager_Testing_2(){
				Base::TestResult i_result;

				AppStateMapManager<AppStateMapManager_App> i_manager;
				i_manager.addAppState<ASMM_State>("state");

				i_result.assertTrue("manager should contain ASMM_State", i_manager.containAppState(Base::ClassCount<ASMM_State>::get()));
				
				return i_result;
			}
			
			Base::TestResult TR_AppStateMapManager_Testing_3(){
				Base::TestResult i_result;

				AppStateMapManager<AppStateMapManager_App> i_manager;
				i_manager.addAppState<ASMM_State>("state");

				i_result.assertTrue("manager should contain ASMM_State", i_manager.containAppState<ASMM_State>());
				
				return i_result;
			}
			
			Base::TestResult TR_AppStateMapManager_Testing_4(){
				Base::TestResult i_result;

				AppStateMapManager<AppStateMapManager_App> i_manager;
				i_manager.putAppState<ASMM_State>("state");
				i_manager.putAppState<ASMM_State>("state");

				i_result.assertEqual("manager should contain ASMM_State", i_manager.length(), 1);
				
				return i_result;
			}
			
			Base::TestResult TR_AppStateMapManager_Testing_5(){
				Base::TestResult i_result;

				AppStateMapManager<AppStateMapManager_App> i_manager;
				i_manager.addAppState<ASMM_State>("state");
				i_manager.clearAppState();

				i_result.assertEqual("manager should contain ASMM_State", i_manager.AppState_length(), 0);
				
				return i_result;
			}
			
			Base::TestResult TR_AppStateMapManager_Testing_6(){
				AppStateMapManager_App i_app;

				AppStateMapManager<AppStateMapManager_App> i_manager;
				i_manager.addAppState<ASMM_State>("state");
				i_manager.initialize(i_app);
				i_manager.update(i_app);

				i_app.m_result.assertExpectedSequence("initialize", "update");

				return i_app.m_result;
			}

			void TR_AppStateMapManager_Testing(Base::TestRunner& a_test_runner){
				a_test_runner.add("AppStateMapManager addAppState, update", TR_AppStateMapManager_Testing_1);
				a_test_runner.add("AppStateMapManager addAppState, containAppState", TR_AppStateMapManager_Testing_2);
				a_test_runner.add("AppStateMapManager addAppState, containAppState", TR_AppStateMapManager_Testing_3);
				a_test_runner.add("AppStateMapManager putAppState, length", TR_AppStateMapManager_Testing_4);
				a_test_runner.add("AppStateMapManager addAppState, clearAppState, AppState_length", TR_AppStateMapManager_Testing_5);
				a_test_runner.add("AppStateMapManager addAppState, initialize, update", TR_AppStateMapManager_Testing_6);
			}

		}

	}

#endif
