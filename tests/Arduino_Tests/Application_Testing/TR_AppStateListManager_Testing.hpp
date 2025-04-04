
#ifndef TR_AppStateListManager_Testing_hpp
	#define TR_AppStateListManager_Testing_hpp

	#include "TestResult.hpp"
	#include "TestRunner.hpp"

	#include "CharArray.hpp"
	#include "AppStateListManager.hpp"

	namespace pankey{

		namespace ApplicationSystem{

			class AppStateListManager_App{public: Base::TestResult m_result;};

			class ASLM_State : public Base::AppState<AppStateListManager_App>{
				public:
					virtual void initializeState(AppStateListManager_App& a_app){
						a_app.m_result.expecting("initialize");
					}
					virtual void updateState(AppStateListManager_App& a_app){
						a_app.m_result.expecting("update");
					}
					virtual void run(Base::TestResult& a_result){
						a_result.expecting("run");
					}

					TYPE_CLASS(ASLM_State)
			};
			
			Base::TestResult TR_AppStateListManager_Testing_1(){
				Base::TestResult i_result;

				AppStateListManager<AppStateListManager_App> i_manager;
				i_manager.addAppState<ASLM_State>();

				i_manager.runAppStateMethod<ASLM_State,Base::TestResult&>(&ASLM_State::run, i_result);

				i_result.assertExpectedSequence("run");
				
				return i_result;
			}
			
			Base::TestResult TR_AppStateListManager_Testing_2(){
				Base::TestResult i_result;

				AppStateListManager<AppStateListManager_App> i_manager;
				i_manager.addAppState<ASLM_State>();

				i_result.assertTrue("manager should contain ASLM_State", i_manager.containAppState(Base::ClassCount<ASLM_State>::get()));
				
				return i_result;
			}
			
			Base::TestResult TR_AppStateListManager_Testing_3(){
				Base::TestResult i_result;

				AppStateListManager<AppStateListManager_App> i_manager;
				i_manager.addAppState<ASLM_State>();

				i_result.assertTrue("manager should contain ASLM_State", i_manager.containAppState<ASLM_State>());
				
				return i_result;
			}
			
			Base::TestResult TR_AppStateListManager_Testing_4(){
				Base::TestResult i_result;

				AppStateListManager<AppStateListManager_App> i_manager;
				i_manager.putAppState<ASLM_State>();
				i_manager.putAppState<ASLM_State>();

				i_result.assertEqual("manager should contain ASLM_State", i_manager.length(), 1);
				
				return i_result;
			}
			
			Base::TestResult TR_AppStateListManager_Testing_5(){
				Base::TestResult i_result;

				AppStateListManager<AppStateListManager_App> i_manager;
				i_manager.addAppState<ASLM_State>();
				i_manager.clearAppState();

				i_result.assertEqual("manager should contain ASLM_State", i_manager.AppState_length(), 0);
				
				return i_result;
			}
			
			Base::TestResult TR_AppStateListManager_Testing_6(){
				AppStateListManager_App i_app;

				AppStateListManager<AppStateListManager_App> i_manager;
				i_manager.addAppState<ASLM_State>();
				i_manager.initialize(i_app);
				i_manager.update(i_app);

				i_app.m_result.assertExpectedSequence("initialize", "update");

				return i_app.m_result;
			}

			void TR_AppStateListManager_Testing(Base::TestRunner& a_test_runner){
				a_test_runner.add("AppStateListManager addAppState, update", TR_AppStateListManager_Testing_1);
				a_test_runner.add("AppStateListManager addAppState, containAppState", TR_AppStateListManager_Testing_2);
				a_test_runner.add("AppStateListManager addAppState, containAppState", TR_AppStateListManager_Testing_3);
				a_test_runner.add("AppStateListManager putAppState, length", TR_AppStateListManager_Testing_4);
				a_test_runner.add("AppStateListManager addAppState, clearAppState, AppState_length", TR_AppStateListManager_Testing_5);
				a_test_runner.add("AppStateListManager addAppState, initialize, update", TR_AppStateListManager_Testing_6);
			}

		}

	}

#endif
