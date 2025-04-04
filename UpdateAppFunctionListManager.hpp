
#ifndef UpdateAppFunctionListManager_hpp
	#define UpdateAppFunctionListManager_hpp

	#include "InvokeRawList.hpp"
	#include "UpdateManager.hpp"

	#if defined(pankey_Log) && (defined(UpdateAppFunctionListManager_Log) || defined(pankey_Global_Log) || defined(pankey_ApplicationSystem_Log))
		#include "Logger_status.hpp"
		#define UpdateFunctionListManagerLog(status,method,mns) pankey_Log(status,"UpdateAppFunctionListManager",method,mns)
	#else
		#define UpdateFunctionListManagerLog(status,method,mns)
	#endif

	namespace pankey{

		namespace ApplicationSystem{

			template<class A, class... Args>
			class UpdateAppFunctionListManager : virtual public UpdateManager<A,Args...>{
				public:

					UpdateAppFunctionListManager(){
						UpdateFunctionListManagerLog(pankey_Log_StartMethod, "Constructor", "");
						UpdateFunctionListManagerLog(pankey_Log_EndMethod, "Constructor", "");
					}
					virtual ~UpdateAppFunctionListManager(){
						UpdateFunctionListManagerLog(pankey_Log_StartMethod, "Destructor", "");
						UpdateFunctionListManagerLog(pankey_Log_EndMethod, "Destructor", "");
					}

					virtual void addAppFunction(Base::InvokeMethod<A&,Args...> a_state){
						UpdateFunctionListManagerLog(pankey_Log_StartMethod, "add", "");
						this->m_auf_list.add(a_state);
						UpdateFunctionListManagerLog(pankey_Log_StartMethod, "add", "");
					}

					virtual void putAppFunction(Base::InvokeMethod<A&,Args...> a_state){
						this->m_auf_list.put(a_state);
					}
					
					virtual void destroyAppFunction(Base::InvokeMethod<A&,Args...> a_state){
						UpdateFunctionListManagerLog(pankey_Log_StartMethod, "destroyAppFunction", "Base::InvokeMethod<A&,Args...>");
						Base::InvokeMethod<A&,Args...>* i_pointer = this->m_auf_list.getPointer(a_state);
						if(i_pointer == nullptr){
							UpdateFunctionListManagerLog(pankey_Log_EndMethod, "destroyFunction", "i_pointer == nullptr");
							return;
						}
						UpdateFunctionListManagerLog(pankey_Log_Statement, "destroyFunction", "m_invoking_auf_list: ");
						UpdateFunctionListManagerLog(pankey_Log_Statement, "destroyFunction", this->m_invoking_auf_list);
						if(this->m_invoking_auf_list){
							UpdateFunctionListManagerLog(pankey_Log_Statement, "destroyFunction", "invoking");
							this->m_deletes_auf_list.putPointer(i_pointer);
						}else{
							UpdateFunctionListManagerLog(pankey_Log_Statement, "destroyFunction", "not invoking");
							this->m_auf_list.destroyByPointer(i_pointer);
						}
						UpdateFunctionListManagerLog(pankey_Log_EndMethod, "destroyAppFunction", "");
					}
					
					virtual void clearAppFunctions(){
						if(this->m_invoking_auf_list){
							for(int x = 0; x < this->m_auf_list.length(); x++){
								Base::InvokeMethod<A&,Args...>* f_state = m_auf_list.getPointerByIndex(x);
								if(f_state == nullptr){
									continue;
								}
								this->m_deletes_auf_list.addPointer(f_state);
							}
						}else{
							this->m_auf_list.clear();
						}
					}
					
					virtual void clear(){
						if(this->m_invoking_auf_list){
							for(int x = 0; x < this->m_auf_list.length(); x++){
								Base::InvokeMethod<A&,Args...>* f_state = m_auf_list.getPointerByIndex(x);
								if(f_state == nullptr){
									continue;
								}
								this->m_deletes_auf_list.addPointer(f_state);
							}
						}else{
							this->m_auf_list.clear();
						}
					}
					
					virtual int AppFunction_length(){
						return this->m_auf_list.length();
					}
					
					virtual int length(){
						return this->m_auf_list.length();
					}
					
					virtual void update(A& a_app, Args... a_update){
						UpdateFunctionListManagerLog(pankey_Log_StartMethod, "update", "");
						this->m_invoking_auf_list = true;
						Base::invokeAll<A&,Args...>(this->m_auf_list, a_app, a_update...);
						this->m_invoking_auf_list = false;
						this->destroyAppFunctions();
						UpdateFunctionListManagerLog(pankey_Log_EndMethod, "update", "");
					}

				protected:
					Base::MethodList<A&,Args...> m_auf_list;
					Base::MethodList<A&,Args...> m_deletes_auf_list;
					bool m_invoking_auf_list = false;
					
					virtual void destroyAppFunctions(){
						UpdateFunctionListManagerLog(pankey_Log_StartMethod, "destroyAppFunctions", "Base::InvokeMethod<A&,Args...>");
						for(int x = 0; x < m_deletes_auf_list.length(); x++){
							UpdateFunctionListManagerLog(pankey_Log_StartMethod, "destroyFunctions", "iteration:");
							UpdateFunctionListManagerLog(pankey_Log_StartMethod, "destroyFunctions", x);
							Base::InvokeMethod<A&,Args...>* f_state = m_deletes_auf_list.getPointerByIndex(x);
							if(f_state == nullptr){
								UpdateFunctionListManagerLog(pankey_Log_StartMethod, "destroyFunctions", "f_state == nullptr");
								continue;
							}
							UpdateFunctionListManagerLog(pankey_Log_StartMethod, "destroyFunctions", "destroy");
							this->m_auf_list.removePointerByPointer(f_state);
						}
						m_deletes_auf_list.clear();
						UpdateFunctionListManagerLog(pankey_Log_EndMethod, "destroyAppFunctions", "");
					}
			};

		}

	}

#endif
