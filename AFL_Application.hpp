
#ifndef AFL_Application_hpp
	#define AFL_Application_hpp

	#include "UpdateAppFunctionListManager.hpp"
	#include "DefaultAppSettings.hpp"
	#include "TPC.hpp"

	#if defined(pankey_Log) && (defined(AFL_Application_Log) || defined(pankey_Global_Log) || defined(pankey_ApplicationSystem_Log))
		#include "Logger_status.hpp"
		#define AFL_ApplicationLog(status,method,mns) pankey_Log(status,"AFL_Application",method,mns)
	#else
		#define AFL_ApplicationLog(status,method,mns)
	#endif

	namespace pankey{

		namespace ApplicationSystem{
		
			class AFL_Application{
				public:
					AFL_Application(){}
					virtual ~AFL_Application(){}

					virtual UpdateAppFunctionListManager<AFL_Application,long>& getStateManager(){
						return this->m_states;
					}

					virtual DefaultAppSettings& getSettings(){
						return this->m_settings;
					}

					virtual void initialize(){
						this->m_states.initialize(*this);
					}

					virtual long update(long a_time){
						AFL_ApplicationLog(pankey_Log_StartMethod, "update", "");
						AFL_ApplicationLog(pankey_Log_StartMethod, "update", "time: ");
						AFL_ApplicationLog(pankey_Log_StartMethod, "update", a_time);
						long i_tpc = m_tpc.generateTpc(a_time);
						AFL_ApplicationLog(pankey_Log_StartMethod, "update", "i_tpc: ");
						AFL_ApplicationLog(pankey_Log_StartMethod, "update", i_tpc);

						this->m_states.update(*this, i_tpc);

						AFL_ApplicationLog(pankey_Log_EndMethod, "update", "");
						return i_tpc;
					}

				protected:
					UpdateAppFunctionListManager<AFL_Application,long> m_states;
					DefaultAppSettings m_settings;
					
					Base::TPC m_tpc;
			};

		}

	}

#endif
