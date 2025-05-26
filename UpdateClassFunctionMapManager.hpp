
#ifndef UpdateClassFunctionMapManager_hpp
	#define UpdateClassFunctionMapManager_hpp

	#include "InvokeRawMap.hpp"
	#include "UpdateManager.hpp"

	namespace pankey{

		namespace ApplicationSystem{

			template<class A, class K, class... Args>
			class UpdateClassFunctionMapManager : virtual public Base::UpdateManager<A&,Args...>{
				public:

					UpdateClassFunctionMapManager(){}
					
					virtual ~UpdateClassFunctionMapManager(){}

					virtual void add(K a_key, Base::InvokeClassMethod<A,Args...> a_state){
						this->m_app_methods.add(a_key, a_state);
					}
					
					virtual void removeUpdateClassFunctionMap(K a_key){
						this->m_app_methods.destroyByKey(a_key);
					}
					
					virtual void removeUpdateClassFunctionMap(int a_index){
						this->m_app_methods.destroyByIndex(a_index);
					}
					
					virtual void removeAllUpdateClassFunctionMap(){
						this->m_app_methods.clear();
					}
					
					virtual void clear(){
						this->m_app_methods.clear();
					}
					
					virtual int getUpdateClassFunctionMapSize(){
						return this->m_app_methods.length();
					}
					
					virtual void update(A& a_app, Args... a_values){
						Base::invokeAll<A,K,Args...>(this->m_app_methods, a_app, a_values...);
					}

				protected:
					Base::ClassMethodMap<A,K,Args...> m_app_methods;
			};

		}

	}

#endif
