
#ifndef TR_IAppStateListManager_Testing_hpp
	#define TR_IAppStateListManager_Testing_hpp

	#include "TestResult.hpp"
	#include "TestRunner.hpp"

	#include "CharArray.hpp"
	#include "IAppStateListManager.hpp"

	namespace pankey{

		namespace ApplicationSystem{

			class IAppStateListManager_App{public: Base::TestResult<String> m_result;};

			class ASLM_State : public Base::iAppState<IAppStateListManager_App>{
				public:
					virtual void initializeState(IAppStateListManager_App& a_app){
						a_app.m_result.expecting("initialize");
					}
					virtual void updateState(IAppStateListManager_App& a_app){
						a_app.m_result.expecting("update");
					}
					virtual void run(Base::TestResult<String>& a_result){
						a_result.expecting("run");
					}

					TYPE_CLASS(ASLM_State)
			};
			
			Base::TestResult<String> TR_IAppStateListManager_Testing_1(){
				Base::TestResult<String> i_result;

				IAppStateListManager<IAppStateListManager_App> i_manager;
				i_manager.addIAppState<ASLM_State>();

				i_manager.runIAppStateMethod<ASLM_State,Base::TestResult<String>&>(&ASLM_State::run, i_result);

				i_result.assertExpectedSequence("run");
				
				return i_result;
			}
			
			Base::TestResult<String> TR_IAppStateListManager_Testing_2(){
				Base::TestResult<String> i_result;

				IAppStateListManager<IAppStateListManager_App> i_manager;
				i_manager.addIAppState<ASLM_State>();

				i_result.assertTrue("manager should contain ASLM_State", i_manager.containIAppState(Base::ClassCount<ASLM_State>::get()));
				
				return i_result;
			}
			
			Base::TestResult<String> TR_IAppStateListManager_Testing_3(){
				Base::TestResult<String> i_result;

				IAppStateListManager<IAppStateListManager_App> i_manager;
				i_manager.addIAppState<ASLM_State>();

				i_result.assertTrue("manager should contain ASLM_State", i_manager.containIAppState<ASLM_State>());
				
				return i_result;
			}
			
			Base::TestResult<String> TR_IAppStateListManager_Testing_4(){
				Base::TestResult<String> i_result;

				IAppStateListManager<IAppStateListManager_App> i_manager;
				i_manager.putIAppState<ASLM_State>();
				i_manager.putIAppState<ASLM_State>();

				i_result.assertEqual("manager should contain ASLM_State", i_manager.length(), 1);
				
				return i_result;
			}
			
			Base::TestResult<String> TR_IAppStateListManager_Testing_5(){
				Base::TestResult<String> i_result;

				IAppStateListManager<IAppStateListManager_App> i_manager;
				i_manager.addIAppState<ASLM_State>();
				i_manager.clearIAppState();

				i_result.assertEqual("manager should contain ASLM_State", i_manager.IAppState_length(), 0);
				
				return i_result;
			}
			
			Base::TestResult<String> TR_IAppStateListManager_Testing_6(){
				IAppStateListManager_App i_app;

				IAppStateListManager<IAppStateListManager_App> i_manager;
				i_manager.addIAppState<ASLM_State>();
				i_manager.initialize(i_app);
				i_manager.update(i_app);

				i_app.m_result.assertExpectedSequence("initialize", "update");

				return i_app.m_result;
			}

			void TR_IAppStateListManager_Testing(Base::TestRunner<String>& a_test_runner){
				a_test_runner.add("IAppStateListManager addIAppState, update", TR_IAppStateListManager_Testing_1);
				a_test_runner.add("IAppStateListManager addIAppState, containIAppState", TR_IAppStateListManager_Testing_2);
				a_test_runner.add("IAppStateListManager addIAppState, containIAppState", TR_IAppStateListManager_Testing_3);
				a_test_runner.add("IAppStateListManager putIAppState, length", TR_IAppStateListManager_Testing_4);
				a_test_runner.add("IAppStateListManager addIAppState, clearIAppState, IAppState_length", TR_IAppStateListManager_Testing_5);
				a_test_runner.add("IAppStateListManager addIAppState, initialize, update", TR_IAppStateListManager_Testing_6);
			}

		}

	}

#endif
