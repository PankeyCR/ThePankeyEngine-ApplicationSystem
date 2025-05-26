
#ifndef UpdateClassFunctionListManager_hpp
	#define UpdateClassFunctionListManager_hpp

	#include "InvokeRawList.hpp"
	#include "UpdateManager.hpp"

	#if defined(pankey_Log) && (defined(UpdateClassFunctionListManager_Log) || defined(pankey_Global_Log) || defined(pankey_ApplicationSystem_Log))
		#include "Logger_status.hpp"
		#define UpdateClassFunctionListManagerLog(status,method,mns) pankey_Log(status,"UpdateClassFunctionListManager",method,mns)
	#else
		#define UpdateClassFunctionListManagerLog(status,method,mns)
	#endif

	namespace pankey{

		namespace ApplicationSystem{

			template<class A, class... Args>
			class UpdateClassFunctionListManager : virtual public Base::UpdateManager<A&,Args...>{
				public:

					UpdateClassFunctionListManager(){}
					
					virtual ~UpdateClassFunctionListManager(){}

					virtual void putClassFunction(Base::InvokeClassMethod<A,Args...> a_state){
						this->m_app_methods.put(a_state);
					}
					
					virtual void destroyClassFunction(Base::InvokeClassMethod<A,Args...> a_state){
						UpdateClassFunctionListManagerLog(pankey_Log_StartMethod, "destroyFunction", "Base::InvokeMethod<Args...>");
						Base::InvokeClassMethod<A,Args...>* i_pointer = this->m_app_methods.getPointer(a_state);
						if(i_pointer == nullptr){
							UpdateClassFunctionListManagerLog(pankey_Log_EndMethod, "destroyFunction", "i_pointer == nullptr");
							return;
						}
						UpdateClassFunctionListManagerLog(pankey_Log_Statement, "destroyFunction", "m_invoking_ucf_list: ");
						UpdateClassFunctionListManagerLog(pankey_Log_Statement, "destroyFunction", this->m_invoking_ucf_list);
						if(this->m_invoking_ucf_list){
							UpdateClassFunctionListManagerLog(pankey_Log_Statement, "destroyFunction", "invoking");
							this->m_deletes_ucf_list.putPointer(i_pointer);
						}else{
							UpdateClassFunctionListManagerLog(pankey_Log_Statement, "destroyFunction", "not invoking");
							this->m_app_methods.destroyByPointer(i_pointer);
						}
						UpdateClassFunctionListManagerLog(pankey_Log_EndMethod, "destroyFunction", "");
					}
					
					virtual void removeUpdateClassFunctionList(int a_index){
						this->m_app_methods.destroyByIndex(a_index);
					}
					
					virtual void removeAllUpdateClassFunctionList(){
						this->m_app_methods.clear();
					}
					
					virtual void clear(){
						this->m_app_methods.clear();
					}
					
					virtual int getUpdateClassFunctionListSize(){
						return this->m_app_methods.length();
					}
					
					virtual void update(A& a_app, Args... a_values){
						Base::invokeAll<A,Args...>(this->m_app_methods, a_app, a_values...);
					}

				protected:
					Base::MethodList<Args...> m_ucf_list;
					Base::MethodList<Args...> m_deletes_ucf_list;
					bool m_invoking_ucf_list = false;
					
					virtual void destroyFunctions(){
						UpdateFunctionListManagerLog(pankey_Log_StartMethod, "destroyFunctions", "Base::InvokeMethod<Args...>");
						for(int x = 0; x < m_deletes_ucf_list.length(); x++){
							UpdateFunctionListManagerLog(pankey_Log_StartMethod, "destroyFunctions", "iteration:");
							UpdateFunctionListManagerLog(pankey_Log_StartMethod, "destroyFunctions", x);
							Base::InvokeMethod<Args...>* f_state = m_deletes_ucf_list.getPointerByIndex(x);
							if(f_state == nullptr){
								UpdateFunctionListManagerLog(pankey_Log_StartMethod, "destroyFunctions", "f_state == nullptr");
								continue;
							}
							UpdateFunctionListManagerLog(pankey_Log_StartMethod, "destroyFunctions", "destroy");
							this->m_update_function_list.removePointerByPointer(f_state);
						}
						m_deletes_ucf_list.clear();
						UpdateFunctionListManagerLog(pankey_Log_EndMethod, "destroyFunctions", "");
					}
			};

		}

	}

#endif
