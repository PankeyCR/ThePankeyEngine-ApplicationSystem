
#ifndef TR_StateMapManager_Testing_hpp
	#define TR_StateMapManager_Testing_hpp

	#include "TestResult.hpp"
	#include "TestRunner.hpp"

	#include "CharArray.hpp"
	#include "StateMapManager.hpp"

	namespace pankey{

		namespace ApplicationSystem{

			class SMM_State : public Base::State<>{
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

					TYPE_CLASS(SMM_State)
			};
			
			Base::TestResult TR_StateMapManager_Testing_1(){
				Base::TestResult i_result;

				StateMapManager<int> i_manager;
				i_manager.addState<SMM_State>("state");

				i_manager.runStateMethod<SMM_State,Base::TestResult&>(&SMM_State::run, i_result);

				i_result.assertExpectedSequence("run");
				
				return i_result;
			}
			
			Base::TestResult TR_StateMapManager_Testing_2(){
				Base::TestResult i_result;

				StateMapManager<int> i_manager;
				i_manager.addState<SMM_State>("state");

				i_result.assertTrue("manager should contain SMM_State", i_manager.containState(Base::ClassCount<SMM_State>::get()));
				
				return i_result;
			}
			
			Base::TestResult TR_StateMapManager_Testing_3(){
				Base::TestResult i_result;

				StateMapManager<int> i_manager;
				i_manager.addState<SMM_State>("state");

				i_result.assertTrue("manager should contain SMM_State", i_manager.containState<SMM_State>());
				
				return i_result;
			}
			
			Base::TestResult TR_StateMapManager_Testing_4(){
				Base::TestResult i_result;

				StateMapManager<int> i_manager;
				i_manager.putState<SMM_State>("state");
				i_manager.putState<SMM_State>("state");

				i_result.assertEqual("manager should contain SMM_State", i_manager.length(), 1);
				
				return i_result;
			}
			
			Base::TestResult TR_StateMapManager_Testing_5(){
				Base::TestResult i_result;

				StateMapManager<int> i_manager;
				i_manager.addState<SMM_State>("state");
				i_manager.clearState();

				i_result.assertEqual("manager should contain SMM_State", i_manager.State_length(), 0);
				
				return i_result;
			}
			
			Base::TestResult TR_StateMapManager_Testing_6(){
				int i_app = 15;

				StateMapManager<int> i_manager;
				SMM_State& i_state = i_manager.addState<SMM_State>("state");
				i_manager.initialize(i_app);
				i_manager.update(i_app);

				i_state.m_result.assertExpectedSequence("initialize", "update");

				return i_state.m_result;
			}

			void TR_StateMapManager_Testing(Base::TestRunner& a_test_runner){
				a_test_runner.add("StateMapManager addState, update", TR_StateMapManager_Testing_1);
				a_test_runner.add("StateMapManager addState, containState", TR_StateMapManager_Testing_2);
				a_test_runner.add("StateMapManager addState, containState", TR_StateMapManager_Testing_3);
				a_test_runner.add("StateMapManager putState, length", TR_StateMapManager_Testing_4);
				a_test_runner.add("StateMapManager addState, clearState, State_length", TR_StateMapManager_Testing_5);
				a_test_runner.add("StateMapManager addState, initialize, update", TR_StateMapManager_Testing_6);
			}

		}

	}

#endif
