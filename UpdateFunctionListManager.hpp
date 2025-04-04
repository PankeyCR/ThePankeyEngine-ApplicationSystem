
#ifndef UpdateFunctionListManager_hpp
	#define UpdateFunctionListManager_hpp

	#include "InvokeRawList.hpp"
	#include "UpdateManager.hpp"

	#if defined(pankey_Log) && (defined(UpdateFunctionListManager_Log) || defined(pankey_Global_Log) || defined(pankey_ApplicationSystem_Log))
		#include "Logger_status.hpp"
		#define UpdateFunctionListManagerLog(status,method,mns) pankey_Log(status,"UpdateFunctionListManager",method,mns)
	#else
		#define UpdateFunctionListManagerLog(status,method,mns)
	#endif

	namespace pankey{

		namespace ApplicationSystem{

			template<class A, class... Args>
			class UpdateFunctionListManager : virtual public UpdateManager<A,Args...>{
				public:

					UpdateFunctionListManager(){
						UpdateFunctionListManagerLog(pankey_Log_StartMethod, "Constructor", "");
						UpdateFunctionListManagerLog(pankey_Log_EndMethod, "Constructor", "");
					}
					virtual ~UpdateFunctionListManager(){
						UpdateFunctionListManagerLog(pankey_Log_StartMethod, "Destructor", "");
						UpdateFunctionListManagerLog(pankey_Log_EndMethod, "Destructor", "");
					}

					virtual void putFunction(Base::InvokeMethod<Args...> a_state){
						this->m_uf_list.put(a_state);
					}
					
					virtual void destroyFunction(Base::InvokeMethod<Args...> a_state){
						UpdateFunctionListManagerLog(pankey_Log_StartMethod, "destroyFunction", "Base::InvokeMethod<Args...>");
						Base::InvokeMethod<Args...>* i_pointer = this->m_uf_list.getPointer(a_state);
						if(i_pointer == nullptr){
							UpdateFunctionListManagerLog(pankey_Log_EndMethod, "destroyFunction", "i_pointer == nullptr");
							return;
						}
						UpdateFunctionListManagerLog(pankey_Log_Statement, "destroyFunction", "m_invoking_uf_list: ");
						UpdateFunctionListManagerLog(pankey_Log_Statement, "destroyFunction", this->m_invoking_uf_list);
						if(this->m_invoking_uf_list){
							UpdateFunctionListManagerLog(pankey_Log_Statement, "destroyFunction", "invoking");
							this->m_deletes_uf_list.putPointer(i_pointer);
						}else{
							UpdateFunctionListManagerLog(pankey_Log_Statement, "destroyFunction", "not invoking");
							this->m_uf_list.destroyByPointer(i_pointer);
						}
						UpdateFunctionListManagerLog(pankey_Log_EndMethod, "destroyFunction", "");
					}
					
					virtual void clearFunctions(){
						if(this->m_invoking_uf_list){
							for(int x = 0; x < this->m_uf_list.length(); x++){
								Base::InvokeMethod<Args...>* f_state = this->m_uf_list.getPointerByIndex(x);
								if(f_state == nullptr){
									continue;
								}
								this->m_deletes_uf_list.addPointer(f_state);
							}
						}else{
							this->m_uf_list.clear();
						}
					}
					
					virtual void clear(){
						if(this->m_invoking_uf_list){
							for(int x = 0; x < this->m_uf_list.length(); x++){
								Base::InvokeMethod<Args...>* f_state = this->m_uf_list.getPointerByIndex(x);
								if(f_state == nullptr){
									continue;
								}
								this->m_deletes_uf_list.addPointer(f_state);
							}
						}else{
							this->m_uf_list.clear();
						}
					}
					
					virtual int Function_length(){
						return this->m_uf_list.length();
					}
					
					virtual int length(){
						return this->m_uf_list.length();
					}
					
					virtual void update(A& a_app, Args... a_update){
						UpdateFunctionListManagerLog(pankey_Log_StartMethod, "update", "");
						this->m_invoking_uf_list = true;
						Base::invokeAll<Args...>(this->m_uf_list, a_update...);
						this->m_invoking_uf_list = false;
						this->destroyFunctions();
						UpdateFunctionListManagerLog(pankey_Log_EndMethod, "update", "");
					}

				protected:
					Base::MethodList<Args...> m_uf_list;
					Base::MethodList<Args...> m_deletes_uf_list;
					bool m_invoking_uf_list = false;
					
					virtual void destroyFunctions(){
						UpdateFunctionListManagerLog(pankey_Log_StartMethod, "destroyFunctions", "Base::InvokeMethod<Args...>");
						for(int x = 0; x < m_deletes_uf_list.length(); x++){
							UpdateFunctionListManagerLog(pankey_Log_StartMethod, "destroyFunctions", "iteration:");
							UpdateFunctionListManagerLog(pankey_Log_StartMethod, "destroyFunctions", x);
							Base::InvokeMethod<Args...>* f_state = m_deletes_uf_list.getPointerByIndex(x);
							if(f_state == nullptr){
								UpdateFunctionListManagerLog(pankey_Log_StartMethod, "destroyFunctions", "f_state == nullptr");
								continue;
							}
							UpdateFunctionListManagerLog(pankey_Log_StartMethod, "destroyFunctions", "destroy");
							this->m_uf_list.removePointerByPointer(f_state);
						}
						m_deletes_uf_list.clear();
						UpdateFunctionListManagerLog(pankey_Log_EndMethod, "destroyFunctions", "");
					}
			};

		}

	}

#endif
