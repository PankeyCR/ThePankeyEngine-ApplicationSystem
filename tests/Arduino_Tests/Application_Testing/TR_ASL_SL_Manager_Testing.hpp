
#ifndef TR_ASL_SL_Manager_Testing_hpp
	#define TR_ASL_SL_Manager_Testing_hpp

	#include "TestResult.hpp"
	#include "TestRunner.hpp"

	#include "ASL_SL_Manager.hpp"

	namespace pankey{

		namespace ApplicationSystem{

			class ASL_SL_Manager_App{public: Base::TestResult m_result;};

			class ASL_SL_AppState : public Base::AppState<ASL_SL_Manager_App>{
				public:
					virtual void initializeState(ASL_SL_Manager_App& a_app){
						a_app.m_result.expecting("initialize");
					}
					virtual void updateState(ASL_SL_Manager_App& a_app){
						a_app.m_result.expecting("update");
					}
					virtual void run(Base::TestResult& a_result){
						a_result.expecting("run");
					}

					TYPE_CLASS(ASLM_State)
			};

			class ASL_SL_State : public Base::State<>{
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
			
			Base::TestResult TR_ASL_SL_Manager_Testing_1(){
				Base::TestResult i_result;

				ASL_SL_Manager<int> i_manager;
				
				return i_result;
			}
			
			Base::TestResult TR_ASL_SL_Manager_Testing_2(){
				Base::TestResult i_result;

				ASL_SL_Manager<ASL_SL_Manager_App> i_manager;

				i_manager.addState<ASL_SL_State>();
				i_manager.addAppState<ASL_SL_AppState>();
				
				i_result.assertEqual("manager should contain 2 states", i_manager.length(), 2);

				return i_result;
			}

			void TR_ASL_SL_Manager_Testing(Base::TestRunner& a_test_runner){
				a_test_runner.add("AFL_Application", TR_ASL_SL_Manager_Testing_1);
				a_test_runner.add("AFL_Application, addState, addAppState", TR_ASL_SL_Manager_Testing_2);
			}

		}

	}

#endif
