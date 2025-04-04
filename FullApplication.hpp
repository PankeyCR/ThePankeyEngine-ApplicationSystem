
#ifndef FullApplication_hpp
	#define FullApplication_hpp

	#include "DefaultEventManager.hpp"
	#include "LoopManager.hpp"
	#include "DefaultAppSettings.hpp"

	#if defined(pankey_Log) && (defined(FullApplication_Log) || defined(pankey_Global_Log) || defined(pankey_ApplicationSystem_Log))
		#include "Logger_status.hpp"
		#define FullApplicationLog(status,method,mns) pankey_Log(status,"FullApplication",method,mns)
	#else
		#define FullApplicationLog(status,method,mns)
	#endif

	namespace pankey{

		namespace ApplicationSystem{
		
			class FullApplication{
				public:
					FullApplication(){
						createEngineManager();
					}
					virtual ~FullApplication(){}

					virtual DefaultEventManager<FullApplication>& getEventManager(){
						return this->m_events;
					}

					virtual LoopManager<FullApplication>& getStateManager(){
						return this->m_states;
					}

					virtual DefaultAppSettings& getSettings(){
						return this->m_settings;
					}

					// virtual Object<ThreadControl,O,H,A> getTimeControl(){
					// 	return this->m_timer;
					// }


					virtual void run(Note a_name){
						auto& i_events = this->getEventManager();
						i_events.run(a_name, *this);
					}

					virtual void run(Note a_name, Note a_message){
						auto& i_events = this->getEventManager();
						i_events.run(a_name, *this, a_message);
					}

					virtual void runMethod(Note a_name){
						auto& i_events = this->getEventManager();
						i_events.runMethod(a_name);
					}

					virtual void runAppMethod(Note a_name){
						auto& i_events = this->getEventManager();
						i_events.runAppMethod(a_name, *this);
					}

					virtual void runMessageMethod(Note a_name, Note a_message){
						auto& i_events = this->getEventManager();
						i_events.runMessageMethod(a_name, a_message);
					}

					virtual void runAppMessageMethod(Note a_name, Note a_message){
						auto& i_events = this->getEventManager();
						i_events.runAppMessageMethod(a_name, *this, a_message);
					}

					virtual void initialize(){
						this->m_states.initialize(*this);
					}

					virtual long update(){
						FullApplicationLog(pankey_Log_StartMethod, "update", "");
						long i_tpc = this->generateTpc();

						this->m_states.update(*this, i_tpc);

						FullApplicationLog(pankey_Log_EndMethod, "update", "");
						return i_tpc;
					}
					
					virtual long tpc(){
						return m_tpc;
					}

					virtual long generateTpc(){
						this->m_now = System::milliSeconds();

						this->m_tpc = this->m_now - this->m_prev;
						this->m_prev = this->m_now;

						return this->m_tpc;
					}

				protected:
					DefaultEventManager<FullApplication> m_events;
					LoopManager<FullApplication> m_states;
					DefaultAppSettings m_settings;
					// TimeControl* m_timer = nullptr;

					long m_now = 0;
					long m_prev = 0;
					long m_tpc = 0;
			};
			
			using AppManager = LoopManager<FullApplication>;
			using appstate = app_state<FullApplication,float>;

		}

	}

#endif
