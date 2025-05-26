
#ifndef TR_IStateMapManager_Testing_hpp
	#define TR_IStateMapManager_Testing_hpp

	#include "TestResult.hpp"
	#include "TestRunner.hpp"

	#include "CharArray.hpp"
	#include "IStateMapManager.hpp"

	namespace pankey{

		namespace ApplicationSystem{

			class SMM_State : public Base::iState<>{
				public:
					Base::TestResult<String> m_result;
					virtual void initializeState(){
						m_result.expecting("initialize");
					}
					virtual void updateState(){
						m_result.expecting("update");
					}
					virtual void run(Base::TestResult<String>& a_result){
						a_result.expecting("run");
					}

					TYPE_CLASS(SMM_State)
			};
			
			Base::TestResult<String> TR_IStateMapManager_Testing_1(){
				Base::TestResult<String> i_result;

				IStateMapManager<int> i_manager;
				i_manager.addIState<SMM_State>("state");

				i_manager.runIStateMethod<SMM_State,Base::TestResult<String>&>(&SMM_State::run, i_result);

				i_result.assertExpectedSequence("run");
				
				return i_result;
			}
			
			Base::TestResult<String> TR_IStateMapManager_Testing_2(){
				Base::TestResult<String> i_result;

				IStateMapManager<int> i_manager;
				i_manager.addIState<SMM_State>("state");

				i_result.assertTrue("manager should contain SMM_State", i_manager.containIState(Base::ClassCount<SMM_State>::get()));
				
				return i_result;
			}
			
			Base::TestResult<String> TR_IStateMapManager_Testing_3(){
				Base::TestResult<String> i_result;

				IStateMapManager<int> i_manager;
				i_manager.addIState<SMM_State>("state");

				i_result.assertTrue("manager should contain SMM_State", i_manager.containIState<SMM_State>());
				
				return i_result;
			}
			
			Base::TestResult<String> TR_IStateMapManager_Testing_4(){
				Base::TestResult<String> i_result;

				IStateMapManager<int> i_manager;
				i_manager.putIState<SMM_State>("state");
				i_manager.putIState<SMM_State>("state");

				i_result.assertEqual("manager should contain SMM_State", i_manager.length(), 1);
				
				return i_result;
			}
			
			Base::TestResult<String> TR_IStateMapManager_Testing_5(){
				Base::TestResult<String> i_result;

				IStateMapManager<int> i_manager;
				i_manager.addIState<SMM_State>("state");
				i_manager.clearIState();

				i_result.assertEqual("manager should contain SMM_State", i_manager.IState_length(), 0);
				
				return i_result;
			}
			
			Base::TestResult<String> TR_IStateMapManager_Testing_6(){
				int i_app = 15;

				IStateMapManager<int> i_manager;
				SMM_State& i_state = i_manager.addIState<SMM_State>("state");
				i_manager.initialize(i_app);
				i_manager.update(i_app);

				i_state.m_result.assertExpectedSequence("initialize", "update");

				return i_state.m_result;
			}

			void TR_IStateMapManager_Testing(Base::TestRunner<String>& a_test_runner){
				a_test_runner.add("IStateMapManager addIState, update", TR_IStateMapManager_Testing_1);
				a_test_runner.add("IStateMapManager addIState, containIState", TR_IStateMapManager_Testing_2);
				a_test_runner.add("IStateMapManager addIState, containIState", TR_IStateMapManager_Testing_3);
				a_test_runner.add("IStateMapManager putIState, length", TR_IStateMapManager_Testing_4);
				a_test_runner.add("IStateMapManager addIState, clearIState, IState_length", TR_IStateMapManager_Testing_5);
				a_test_runner.add("IStateMapManager addIState, initialize, update", TR_IStateMapManager_Testing_6);
			}

		}

	}

#endif
