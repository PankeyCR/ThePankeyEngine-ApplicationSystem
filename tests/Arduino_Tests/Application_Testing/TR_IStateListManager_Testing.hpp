
#ifndef TR_IStateListManager_Testing_hpp
	#define TR_IStateListManager_Testing_hpp

	#include "TestResult.hpp"
	#include "TestRunner.hpp"

	#include "CharArray.hpp"
	#include "IStateListManager.hpp"

	namespace pankey{

		namespace ApplicationSystem{

			class SLM_State : public Base::iState<>{
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

					TYPE_CLASS(SLM_State)
			};
			
			Base::TestResult<String> TR_IStateListManager_Testing_1(){
				Base::TestResult<String> i_result;

				IStateListManager<int> i_manager;
				i_manager.addIState<SLM_State>();

				i_manager.runIStateMethod<SLM_State,Base::TestResult<String>&>(&SLM_State::run, i_result);

				i_result.assertExpectedSequence("run");
				
				return i_result;
			}
			
			Base::TestResult<String> TR_IStateListManager_Testing_2(){
				Base::TestResult<String> i_result;

				IStateListManager<int> i_manager;
				i_manager.addIState<SLM_State>();

				i_result.assertTrue("manager should contain SLM_State", i_manager.containIState(Base::ClassCount<SLM_State>::get()));
				
				return i_result;
			}
			
			Base::TestResult<String> TR_IStateListManager_Testing_3(){
				Base::TestResult<String> i_result;

				IStateListManager<int> i_manager;
				i_manager.addIState<SLM_State>();

				i_result.assertTrue("manager should contain SLM_State", i_manager.containIState<SLM_State>());
				
				return i_result;
			}
			
			Base::TestResult<String> TR_IStateListManager_Testing_4(){
				Base::TestResult<String> i_result;

				IStateListManager<int> i_manager;
				i_manager.putIState<SLM_State>();
				i_manager.putIState<SLM_State>();

				i_result.assertEqual("manager should contain SLM_State", i_manager.IState_length(), 1);
				
				return i_result;
			}
			
			Base::TestResult<String> TR_IStateListManager_Testing_5(){
				Base::TestResult<String> i_result;

				IStateListManager<int> i_manager;
				i_manager.addIState<SLM_State>();
				i_manager.clearIState();

				i_result.assertEqual("manager should contain SLM_State", i_manager.length(), 0);
				
				return i_result;
			}
			
			Base::TestResult<String> TR_IStateListManager_Testing_6(){
				int i_app = 15;

				IStateListManager<int> i_manager;
				SLM_State& i_state = i_manager.addIState<SLM_State>();
				i_manager.initialize(i_app);
				i_manager.update(i_app);

				i_state.m_result.assertExpectedSequence("initialize", "update");

				return i_state.m_result;
			}

			void TR_IStateListManager_Testing(Base::TestRunner<String>& a_test_runner){
				a_test_runner.add("IStateListManager addIState, update", TR_IStateListManager_Testing_1);
				a_test_runner.add("IStateListManager addIState, containIState", TR_IStateListManager_Testing_2);
				a_test_runner.add("IStateListManager addIState, containIState", TR_IStateListManager_Testing_3);
				a_test_runner.add("IStateListManager putIState, length", TR_IStateListManager_Testing_4);
				a_test_runner.add("IStateListManager addIState, clearState, IState_length", TR_IStateListManager_Testing_5);
				a_test_runner.add("IStateListManager addIState, initialize, update", TR_IStateListManager_Testing_6);
			}

		}

	}

#endif
