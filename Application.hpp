
#ifndef Application_hpp
	#define Application_hpp

	#include "DefaultSettings.hpp"
	#include "IAppStateMapManager.hpp"
	#include "TPC.hpp"

	#if defined(pankey_Log) && (defined(Application_Log) || defined(pankey_Global_Log) || defined(pankey_ApplicationSystem_Log))
		#include "Logger_status.hpp"
		#define ApplicationLog(status,method,mns) pankey_Log(status,"Application",method,mns)
	#else
		#define ApplicationLog(status,method,mns)
	#endif

	namespace pankey{

		namespace ApplicationSystem{
			
			class Application{
				public:
					Application(){}
					virtual ~Application(){}

					DefaultSettings& getSettings(){
						return m_settings;
					}

					IAppStateMapManager<Application,float>& getStateManager(){
						return m_states;
					}

					virtual void initialize(){
						this->m_states.initialize(*this);
					}

					virtual long update(long a_time){
						ApplicationLog(pankey_Log_StartMethod, "update", "");
						ApplicationLog(pankey_Log_StartMethod, "update", "time: ");
						ApplicationLog(pankey_Log_StartMethod, "update", a_time);
						long i_tpc = m_tpc.generateTpc(a_time);
						ApplicationLog(pankey_Log_StartMethod, "update", "i_tpc: ");
						ApplicationLog(pankey_Log_StartMethod, "update", i_tpc);

						this->m_states.update(*this, i_tpc);

						ApplicationLog(pankey_Log_EndMethod, "update", "");
						return i_tpc;
					}

				protected:
					DefaultSettings m_settings;
					IAppStateMapManager<Application,float> m_states;
					
					Base::TPC m_tpc;
			};

		}

	}

#endif
