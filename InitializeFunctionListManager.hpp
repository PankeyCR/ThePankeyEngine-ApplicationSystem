
#ifndef InitializeFunctionListManager_hpp
	#define InitializeFunctionListManager_hpp

	#include "UpdateFunctionListManager.hpp"

	#if defined(pankey_Log) && (defined(InitializeFunctionListManager_Log) || defined(pankey_Global_Log) || defined(pankey_ApplicationSystem_Log))
		#include "Logger_status.hpp"
		#define InitializeFunctionListManagerLog(status,method,mns) pankey_Log(status,"InitializeFunctionListManager",method,mns)
	#else
		#define InitializeFunctionListManagerLog(status,method,mns)
	#endif

	namespace pankey{

		namespace ApplicationSystem{

			template<class... Args>
			class InitializeFunctionListManager : virtual public UpdateFunctionListManager<Args...>{
				public:

					InitializeFunctionListManager(){
						InitializeFunctionListManagerLog(pankey_Log_StartMethod, "Constructor", "");
						InitializeFunctionListManagerLog(pankey_Log_EndMethod, "Constructor", "");
					}
					virtual ~InitializeFunctionListManager(){
						InitializeFunctionListManagerLog(pankey_Log_StartMethod, "Destructor", "");
						InitializeFunctionListManagerLog(pankey_Log_EndMethod, "Destructor", "");
					}

					virtual void add(Base::InvokeMethod<Args...> a_state){
						this->m_initialize_function_list.add(a_state);
					}

					virtual void put(Base::InvokeMethod<Args...> a_state){
						this->m_initialize_function_list.put(a_state);
					}
					
					virtual void removeUpdateFunctionList(Base::InvokeMethod<Args...> a_state){
						InitializeFunctionListManagerLog(pankey_Log_StartMethod, "removeUpdateFunctionList", "Base::InvokeMethod<Args...>");
						if(this->m_initialize_function_list.destroy(a_state)){
							return;
						}
						UpdateFunctionListManager<Args...>::removeUpdateFunctionList(a_state);
						InitializeFunctionListManagerLog(pankey_Log_EndMethod, "removeUpdateFunctionList", "");
					}
					
					virtual void removeUpdateFunctionList(int a_index){
						InitializeFunctionListManagerLog(pankey_Log_StartMethod, "removeUpdateFunctionList", "int");
						
						InitializeFunctionListManagerLog(pankey_Log_EndMethod, "removeUpdateFunctionList", "");
					}
					
					virtual void removeAllUpdateFunctionList(){
						InitializeFunctionListManagerLog(pankey_Log_StartMethod, "removeAllUpdateFunctionList", "");
						
						InitializeFunctionListManagerLog(pankey_Log_EndMethod, "removeAllUpdateFunctionList", "");
					}
					
					virtual void clear(){
						InitializeFunctionListManagerLog(pankey_Log_StartMethod, "clear", "");
						
						InitializeFunctionListManagerLog(pankey_Log_EndMethod, "clear", "");
					}
					
					virtual int getUpdateFunctionListSize(){
						InitializeFunctionListManagerLog(pankey_Log_StartMethod, "getUpdateFunctionListSize", "");
						InitializeFunctionListManagerLog(pankey_Log_EndMethod, "getUpdateFunctionListSize", "");
						return this->m_initialize_function_list.length() + this->m_update_function_list.length();
					}
					
					virtual void initialize(Args... a_update){
						InitializeFunctionListManagerLog(pankey_Log_StartMethod, "initialize", "");
						Base::invokeAll<Args...>(this->m_initialize_function_list, a_update...);
						this->m_update_function_list.addMove(this->m_initialize_function_list);
						InitializeFunctionListManagerLog(pankey_Log_EndMethod, "initialize", "");
					}
					
					virtual void unInitialize(){
						InitializeFunctionListManagerLog(pankey_Log_StartMethod, "unInitialize", "");
						this->m_initialize_function_list.addMove(this->m_update_function_list);
						InitializeFunctionListManagerLog(pankey_Log_EndMethod, "unInitialize", "");
					}

				protected:
					Base::MethodList<Args...> m_initialize_function_list;
			};

		}

	}

#endif
