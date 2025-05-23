
#ifndef ASL_SL_Application_hpp
	#define ASL_SL_Application_hpp

	#include "ASL_SL_Manager.hpp"
	#include "DefaultAppSettings.hpp"
	#include "TPC.hpp"

	#if defined(pankey_Log) && (defined(ASL_SL_Application_Log) || defined(pankey_Global_Log) || defined(pankey_ApplicationSystem_Log))
		#include "Logger_status.hpp"
		#define ASL_SL_ApplicationLog(status,method,mns) pankey_Log(status,"ASL_SL_Application",method,mns)
	#else
		#define ASL_SL_ApplicationLog(status,method,mns)
	#endif

	namespace pankey{

		namespace ApplicationSystem{
		
			class ASL_SL_Application{
				public:
					ASL_SL_Application(){}
					virtual ~ASL_SL_Application(){}

					virtual ASL_SL_Manager<ASL_SL_Application,long>& getStateManager(){
						return this->m_states;
					}

					virtual DefaultAppSettings& getSettings(){
						return this->m_settings;
					}

					virtual void initialize(){
						this->m_states.initialize(*this);
					}

					virtual long update(long a_time){
						ASL_SL_ApplicationLog(pankey_Log_StartMethod, "update", "");
						ASL_SL_ApplicationLog(pankey_Log_StartMethod, "update", "time: ");
						ASL_SL_ApplicationLog(pankey_Log_StartMethod, "update", a_time);
						long i_tpc = m_tpc.generateTpc(a_time);
						ASL_SL_ApplicationLog(pankey_Log_StartMethod, "update", "i_tpc: ");
						ASL_SL_ApplicationLog(pankey_Log_StartMethod, "update", i_tpc);

						this->m_states.update(*this, i_tpc);

						ASL_SL_ApplicationLog(pankey_Log_EndMethod, "update", "");
						return i_tpc;
					}

				protected:
					ASL_SL_Manager<ASL_SL_Application,long> m_states;
					DefaultAppSettings m_settings;
					
					Base::TPC m_tpc;
			};

		}

	}

#endif
