
#ifndef ASL_SL_Manager_hpp
	#define ASL_SL_Manager_hpp
	
	#include "IAppStateListManager.hpp"
	#include "IStateListManager.hpp"

	#if defined(pankey_Log) && (defined(ASL_SL_Manager_Log) || defined(pankey_Global_Log) || defined(pankey_ApplicationSystem_Log))
		#include "Logger_status.hpp"
		#define ASL_SL_ManagerLog(status,method,mns) pankey_Log(status,"ASL_SL_Manager",method,mns)
	#else
		#define ASL_SL_ManagerLog(status,method,mns)
	#endif

	namespace pankey{

		namespace ApplicationSystem{

			template<class A, class... Args>
			class ASL_SL_Manager : virtual public IAppStateListManager<A,Args...>, virtual public IStateListManager<A,Args...>{
				public:
					ASL_SL_Manager(){
						ASL_SL_ManagerLog(pankey_Log_StartMethod, "Constructor", "");
						ASL_SL_ManagerLog(pankey_Log_EndMethod, "Constructor", "");
					}
					virtual ~ASL_SL_Manager(){
						ASL_SL_ManagerLog(pankey_Log_StartMethod, "Destructor", "");
						ASL_SL_ManagerLog(pankey_Log_EndMethod, "Destructor", "");
					}

					virtual int length(){
						return IAppStateListManager<A,Args...>::IAppState_length() + IStateListManager<A,Args...>::IState_length();
					}
					
					virtual void clear(){
						ASL_SL_ManagerLog(pankey_Log_StartMethod, "clear",  "");
						IStateListManager<A,Args...>::clear();
						IAppStateListManager<A,Args...>::clear();
						ASL_SL_ManagerLog(pankey_Log_EndMethod, "clear", "");
					}

					virtual void initialize(A& a_app){
						ASL_SL_ManagerLog(pankey_Log_StartMethod, "initialize",  "");
						IStateListManager<A,Args...>::initialize(a_app);
						IAppStateListManager<A,Args...>::initialize(a_app);
						ASL_SL_ManagerLog(pankey_Log_EndMethod, "initialize", "");
					}

					virtual void update(A& a_app, Args... a_values){
						ASL_SL_ManagerLog(pankey_Log_StartMethod, "update",  "");
						IStateListManager<A,Args...>::update(a_app, a_values...);
						IAppStateListManager<A,Args...>::update(a_app, a_values...);
						ASL_SL_ManagerLog(pankey_Log_EndMethod, "update", "");
					}
					
			};

		}

	}

#endif
