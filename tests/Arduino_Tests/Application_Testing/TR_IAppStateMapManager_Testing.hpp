
#ifndef TR_IAppStateMapManager_Testing_hpp
	#define TR_IAppStateMapManager_Testing_hpp

	#include "TestResult.hpp"
	#include "TestRunner.hpp"

	#include "CharArray.hpp"
	#include "IAppStateMapManager.hpp"

	namespace pankey{

		namespace ApplicationSystem{

			class IAppStateMapManager_App{public: Base::TestResult<String> m_result;};

			class ASMM_State : public Base::iAppState<IAppStateMapManager_App>{
				public:
					virtual void initializeState(IAppStateMapManager_App& a_app){
						a_app.m_result.expecting("initialize");
					}
					virtual void updateState(IAppStateMapManager_App& a_app){
						a_app.m_result.expecting("update");
					}
					virtual void run(Base::TestResult<String>& a_result){
						a_result.expecting("run");
					}

					TYPE_CLASS(ASMM_State)
			};
			
			Base::TestResult<String> TR_IAppStateMapManager_Testing_1(){
				Base::TestResult<String> i_result;

				IAppStateMapManager<IAppStateMapManager_App> i_manager;
				i_manager.addIAppState<ASMM_State>("state");

				i_manager.runIAppStateMethod<ASMM_State,Base::TestResult<String>&>(&ASMM_State::run, i_result);

				i_result.assertExpectedSequence("run");
				
				return i_result;
			}
			
			Base::TestResult<String> TR_IAppStateMapManager_Testing_2(){
				Base::TestResult<String> i_result;

				IAppStateMapManager<IAppStateMapManager_App> i_manager;
				i_manager.addIAppState<ASMM_State>("state");

				i_result.assertTrue("manager should contain ASMM_State", i_manager.containIAppState(Base::ClassCount<ASMM_State>::get()));
				
				return i_result;
			}
			
			Base::TestResult<String> TR_IAppStateMapManager_Testing_3(){
				Base::TestResult<String> i_result;

				IAppStateMapManager<IAppStateMapManager_App> i_manager;
				i_manager.addIAppState<ASMM_State>("state");

				i_result.assertTrue("manager should contain ASMM_State", i_manager.containIAppState<ASMM_State>());
				
				return i_result;
			}
			
			Base::TestResult<String> TR_IAppStateMapManager_Testing_4(){
				Base::TestResult<String> i_result;

				IAppStateMapManager<IAppStateMapManager_App> i_manager;
				i_manager.putIAppState<ASMM_State>("state");
				i_manager.putIAppState<ASMM_State>("state");

				i_result.assertEqual("manager should contain ASMM_State", i_manager.length(), 1);
				
				return i_result;
			}
			
			Base::TestResult<String> TR_IAppStateMapManager_Testing_5(){
				Base::TestResult<String> i_result;

				IAppStateMapManager<IAppStateMapManager_App> i_manager;
				i_manager.addIAppState<ASMM_State>("state");
				i_manager.clearIAppState();

				i_result.assertEqual("manager should contain ASMM_State", i_manager.IAppState_length(), 0);
				
				return i_result;
			}
			
			Base::TestResult<String> TR_IAppStateMapManager_Testing_6(){
				IAppStateMapManager_App i_app;

				IAppStateMapManager<IAppStateMapManager_App> i_manager;
				i_manager.addIAppState<ASMM_State>("state");
				i_manager.initialize(i_app);
				i_manager.update(i_app);

				i_app.m_result.assertExpectedSequence("initialize", "update");

				return i_app.m_result;
			}

			void TR_IAppStateMapManager_Testing(Base::TestRunner<String>& a_test_runner){
				a_test_runner.add("IAppStateMapManager addIAppState, update", TR_IAppStateMapManager_Testing_1);
				a_test_runner.add("IAppStateMapManager addIAppState, containIAppState", TR_IAppStateMapManager_Testing_2);
				a_test_runner.add("IAppStateMapManager addIAppState, containIAppState", TR_IAppStateMapManager_Testing_3);
				a_test_runner.add("IAppStateMapManager putIAppState, length", TR_IAppStateMapManager_Testing_4);
				a_test_runner.add("IAppStateMapManager addIAppState, clearIAppState, IAppState_length", TR_IAppStateMapManager_Testing_5);
				a_test_runner.add("IAppStateMapManager addIAppState, initialize, update", TR_IAppStateMapManager_Testing_6);
			}

		}

	}

#endif
