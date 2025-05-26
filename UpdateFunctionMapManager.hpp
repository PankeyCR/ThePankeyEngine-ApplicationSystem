
#ifndef UpdateFunctionMapManager_hpp
	#define UpdateFunctionMapManager_hpp

	#include "InvokeRawMap.hpp"
	#include "UpdateManager.hpp"

	namespace pankey{

		namespace ApplicationSystem{

			template<class K, class... Args>
			class UpdateFunctionMapManager : virtual public Base::UpdateManager<Args...>{
				public:

					UpdateFunctionMapManager(){}
					virtual ~UpdateFunctionMapManager(){}

					virtual void addFunction(K a_key, Base::InvokeMethod<Args...> a_state){
						this->m_update_function_map.add(a_key, a_state);
					}

					virtual void putFunction(K a_key, Base::InvokeMethod<Args...> a_state){
						this->m_update_function_map.put(a_key, a_state);
					}

					virtual void changeFunction(K a_key, Base::InvokeMethod<Args...> a_state){
						this->m_update_function_map.destroy(a_key);
						this->m_update_function_map.add(a_key, a_state);
					}
					
					virtual void destroyFunction(K a_key){
						this->m_update_function_map.destroyByKey(a_key);
						int i_index = this->m_update_function_map.getKeyIndex(a_state);
						if(i_index < 0){
							return;
						}
						if(this->m_invoking){
							this->m_deletes.add(i_index);
						}else{
							this->m_update_function_map.destroyByIndex(i_index);
						}
					}
					
					virtual void clearFunctions(){
						this->m_update_function_map.clear();
					}
					
					virtual void clear(){
						this->m_update_function_map.clear();
					}
					
					virtual int Function_length(){
						return this->m_update_function_map.length();
					}
					
					virtual int length(){
						return this->m_update_function_map.length();
					}
					
					virtual void update(Args... a_update){
						this->m_invoking = true;
						Base::invokeAll<K,Args...>(this->m_update_function_map, a_update...);
						this->m_invoking = false;
					}

				protected:
					Base::MethodMap<K,Args...> m_update_function_map;
					Base::ArrayRawList<int> m_deletes;
					bool m_invoking = false;
			};

		}

	}

#endif
