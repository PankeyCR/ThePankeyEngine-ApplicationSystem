
#ifndef TR_StateListManager_Testing_hpp
	#define TR_StateListManager_Testing_hpp

	#include "TestResult.hpp"
	#include "TestRunner.hpp"

	#include "CharArray.hpp"
	#include "StateListManager.hpp"

	namespace pankey{

		namespace ApplicationSystem{

			class SLM_State : public Base::State<>{
				public:
					Base::TestResult m_result;
					virtual void initializeState(){
						m_result.expecting("initialize");
					}
					virtual void updateState(){
						m_result.expecting("update");
					}
					virtual void run(Base::TestResult& a_result){
						a_result.expecting("run");
					}

					TYPE_CLASS(SLM_State)
			};
			
			Base::TestResult TR_StateListManager_Testing_1(){
				Base::TestResult i_result;

				StateListManager<int> i_manager;
				i_manager.addState<SLM_State>();

				i_manager.runStateMethod<SLM_State,Base::TestResult&>(&SLM_State::run, i_result);

				i_result.assertExpectedSequence("run");
				
				return i_result;
			}
			
			Base::TestResult TR_StateListManager_Testing_2(){
				Base::TestResult i_result;

				StateListManager<int> i_manager;
				i_manager.addState<SLM_State>();

				i_result.assertTrue("manager should contain SLM_State", i_manager.containState(Base::ClassCount<SLM_State>::get()));
				
				return i_result;
			}
			
			Base::TestResult TR_StateListManager_Testing_3(){
				Base::TestResult i_result;

				StateListManager<int> i_manager;
				i_manager.addState<SLM_State>();

				i_result.assertTrue("manager should contain SLM_State", i_manager.containState<SLM_State>());
				
				return i_result;
			}
			
			Base::TestResult TR_StateListManager_Testing_4(){
				Base::TestResult i_result;

				StateListManager<int> i_manager;
				i_manager.putState<SLM_State>();
				i_manager.putState<SLM_State>();

				i_result.assertEqual("manager should contain SLM_State", i_manager.State_length(), 1);
				
				return i_result;
			}
			
			Base::TestResult TR_StateListManager_Testing_5(){
				Base::TestResult i_result;

				StateListManager<int> i_manager;
				i_manager.addState<SLM_State>();
				i_manager.clearState();

				i_result.assertEqual("manager should contain SLM_State", i_manager.length(), 0);
				
				return i_result;
			}
			
			Base::TestResult TR_StateListManager_Testing_6(){
				int i_app = 15;

				StateListManager<int> i_manager;
				SLM_State& i_state = i_manager.addState<SLM_State>();
				i_manager.initialize(i_app);
				i_manager.update(i_app);

				i_state.m_result.assertExpectedSequence("initialize", "update");

				return i_state.m_result;
			}

			void TR_StateListManager_Testing(Base::TestRunner& a_test_runner){
				a_test_runner.add("StateListManager addState, update", TR_StateListManager_Testing_1);
				a_test_runner.add("StateListManager addState, containState", TR_StateListManager_Testing_2);
				a_test_runner.add("StateListManager addState, containState", TR_StateListManager_Testing_3);
				a_test_runner.add("StateListManager putState, length", TR_StateListManager_Testing_4);
				a_test_runner.add("StateListManager addState, clearState, State_length", TR_StateListManager_Testing_5);
				a_test_runner.add("StateListManager addState, initialize, update", TR_StateListManager_Testing_6);
			}

		}

	}

#endif
