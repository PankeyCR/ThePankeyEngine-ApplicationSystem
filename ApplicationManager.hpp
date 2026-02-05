
#ifndef ApplicationManager_hpp
	#define ApplicationManager_hpp

	#include "InvokeMethod.hpp"
	#include "CombinedUpdateManager.hpp"
	#include "TPC.hpp"

	#if defined(pankey_Log) && (defined(ApplicationManager_Log) || defined(pankey_Global_Log) || defined(pankey_ApplicationSystem_Log))
		#include "Logger_status.hpp"
		#define ApplicationManagerLog(status,method,mns) pankey_Log(status,"ApplicationManager",method,mns)
	#else
		#define ApplicationManagerLog(status,method,mns)
	#endif

	namespace pankey{

		namespace ApplicationSystem{
			
			template<class A, class... Managers>
			class ApplicationManager{
				public:
					ApplicationManager(){}
					virtual ~ApplicationManager(){}

					template<class IA>
					void mutateApplication(Base::InvokeMethod<IA&> a_mutate){
						Base::invoke<IA&>(a_mutate, this->m_app);
					}

					template<class IA>
					void mutateInApplication(Base::InvokeMethod<IA&> a_mutate){
						this->m_app.mutate(a_mutate);
					}

					template<class IM>
					void mutateUpdateManager(Base::InvokeMethod<IM&> a_mutate){
						Base::invoke<IM&>(a_mutate, this->m_states);
					}

					template<class IU, class IS>
					void put(IS a_mutate){
						this->m_states.IU::put(a_mutate);
					}

					template<class IS>
					void putMutate(Base::InvokeMethod<IS&> a_mutate){
						this->m_states.putMutate(a_mutate);
					}

					virtual void initialize(){
						this->m_states.initialize(this->m_app);
					}

					virtual long update(long a_time){
						ApplicationManagerLog(pankey_Log_StartMethod, "update", "");
						ApplicationManagerLog(pankey_Log_StartMethod, "update", "time: ");
						ApplicationManagerLog(pankey_Log_StartMethod, "update", a_time);
						long i_tpc = m_tpc.generateTpc(a_time);
						ApplicationManagerLog(pankey_Log_StartMethod, "update", "i_tpc: ");
						ApplicationManagerLog(pankey_Log_StartMethod, "update", i_tpc);

						this->m_states.update(this->m_app, i_tpc);

						ApplicationManagerLog(pankey_Log_EndMethod, "update", "");
						return i_tpc;
					}

				protected:
					A m_app;
					CombinedUpdateManager<A,Managers...> m_states;
					
					Base::TPC m_tpc;
			};

		}

	}

#endif
