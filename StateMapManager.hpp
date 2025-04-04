
#ifndef StateMapManager_hpp
	#define StateMapManager_hpp

	#include "AppState.hpp"
	#include "ClassCount.hpp"
	#include "ArrayRawList.hpp"
	#include "UpdateManager.hpp"

	#if defined(pankey_Log) && (defined(StateMapManager_Log) || defined(pankey_Global_Log) || defined(pankey_ApplicationSystem_Log))
		#include "Logger_status.hpp"
		#define StateMapManagerLog(status,method,mns) pankey_Log(status,"StateMapManager",method,mns)
	#else
		#define StateMapManagerLog(status,method,mns)
	#endif

	namespace pankey{

		namespace ApplicationSystem{

			template<class A, class... Args>
			class StateMapManager : virtual public UpdateManager<A,Args...>{
				public:
					StateMapManager(){
						StateMapManagerLog(pankey_Log_StartMethod, "Constructor", "");
						StateMapManagerLog(pankey_Log_EndMethod, "Constructor", "");
					}
					virtual ~StateMapManager(){
						StateMapManagerLog(pankey_Log_StartMethod, "Destructor", "");
						StateMapManagerLog(pankey_Log_EndMethod, "Destructor", "");
					}

					template<class AS>
					AS& addState(const Base::CharArray& a_name){
						StateMapManagerLog(pankey_Log_StartMethod, "addState",  "");
						AS* i_state = new AS();
						m_initialize_state_map.addPointer(a_name, i_state);
						StateMapManagerLog(pankey_Log_EndMethod, "addState", "");
						return *i_state;
					}

					virtual bool containState(long a_type){
						StateMapManagerLog(pankey_Log_StartMethod, "containState",  "");
						for(int x = 0; x < m_initialize_state_map.length(); x++){
							Base::State<Args...>* f_state = m_initialize_state_map.getValuePointerByIndex(x);
							if(f_state == nullptr){
								continue;
							}
							if(f_state->getType() == a_type){
								return true;
							}
						}
						for(int x = 0; x < m_state_map.length(); x++){
							Base::State<Args...>* f_state = m_state_map.getValuePointerByIndex(x);
							if(f_state == nullptr){
								continue;
							}
							if(f_state->getType() == a_type){
								return true;
							}
						}
						StateMapManagerLog(pankey_Log_EndMethod, "containState", "");
						return false;
					}

					template<class AS>
					bool containState(){
						StateMapManagerLog(pankey_Log_StartMethod, "containState",  "");
						long i_type = Base::ClassCount<AS>::get();
						StateMapManagerLog(pankey_Log_EndMethod, "containState", "");
						return this->containState(i_type);
					}

					template<class AS>
					void putState(const Base::CharArray& a_name){
						StateMapManagerLog(pankey_Log_StartMethod, "putState",  "");
						if(this->containState(Base::ClassCount<AS>::get())){
							return;
						}
						this->addStatePointer(a_name, new AS());
						StateMapManagerLog(pankey_Log_EndMethod, "putState", "");
					}

					virtual int State_length(){
						return m_state_map.length() + m_initialize_state_map.length();
					}

					virtual int length(){
						return m_state_map.length() + m_initialize_state_map.length();
					}
					
					virtual void clearState(){
						StateMapManagerLog(pankey_Log_StartMethod, "clearState",  "");
						for(int x = 0; x < m_state_map.length(); x++){
							Base::State<Args...>* f_state = m_state_map.getValuePointerByIndex(x);
							if(f_state == nullptr){
								continue;
							}
							f_state->onDisable();
						}
						for(int x = 0; x < m_initialize_state_map.length(); x++){
							Base::State<Args...>* f_state = m_initialize_state_map.getValuePointerByIndex(x);
							if(f_state == nullptr){
								continue;
							}
							f_state->onDisable();
						}
						m_state_map.clear();
						m_initialize_state_map.clear();
						StateMapManagerLog(pankey_Log_EndMethod, "clearState", "");
					}
					
					virtual void clear(){
						StateMapManagerLog(pankey_Log_StartMethod, "clear",  "");
						for(int x = 0; x < m_state_map.length(); x++){
							Base::State<Args...>* f_state = m_state_map.getValuePointerByIndex(x);
							if(f_state == nullptr){
								continue;
							}
							f_state->onDisable();
						}
						for(int x = 0; x < m_initialize_state_map.length(); x++){
							Base::State<Args...>* f_state = m_initialize_state_map.getValuePointerByIndex(x);
							if(f_state == nullptr){
								continue;
							}
							f_state->onDisable();
						}
						m_state_map.clear();
						m_initialize_state_map.clear();
						StateMapManagerLog(pankey_Log_EndMethod, "clear", "");
					}

					virtual void initialize(A& a_app){
						StateMapManagerLog(pankey_Log_StartMethod, "initialize",  "");
						for(int x = 0; x < this->m_initialize_state_map.length(); x++){
							StateMapManagerLog(pankey_Log_StartMethod, "initialize",  "iterating through initializing states");
							StateMapManagerLog(pankey_Log_StartMethod, "initialize",  "iteration: ");
							StateMapManagerLog(pankey_Log_StartMethod, "initialize",  x);
							Base::CharArray* f_name = this->m_initialize_state_map.getKeyPointerByIndex(x);
							Base::State<Args...>* f_state = this->m_initialize_state_map.getValuePointerByIndex(x);
							if(f_state == nullptr || f_name == nullptr){
								StateMapManagerLog(pankey_Log_StartMethod, "initialize",  "initializing state is null");
								continue;
							}
							f_state->initialize();
							f_state->onEnable();
							this->m_state_map.addPointers(f_name, f_state);
						}
						StateMapManagerLog(pankey_Log_StartMethod, "initialize",  "m_initialize_state_map");
						this->m_initialize_state_map.reset();
						StateMapManagerLog(pankey_Log_EndMethod, "initialize", "");
					}

					virtual void update(A& a_app, Args... a_values){
						StateMapManagerLog(pankey_Log_StartMethod, "update",  "");
						
						if(!this->m_initialize_state_map.isEmpty()){
							this->initialize(a_app);
						}

						for(int x = 0; x < this->m_state_map.length(); x++){
							StateMapManagerLog(pankey_Log_StartMethod, "update",  "iterating through all states");
							StateMapManagerLog(pankey_Log_StartMethod, "update",  "iteration: ");
							StateMapManagerLog(pankey_Log_StartMethod, "update",  x);
							Base::State<Args...>* f_state = this->m_state_map.getValuePointerByIndex(x);
							if(f_state == nullptr){
								continue;
							}
							f_state->update(a_values...);
						}

						StateMapManagerLog(pankey_Log_EndMethod, "update", "");
					}

					template<class AS, class... MArgs>
					void runStateMethod(Base::InvokeClassMethod<AS,MArgs...> a_method, MArgs... a_args){
						StateMapManagerLog(pankey_Log_StartMethod, "run",  "");
						Base::Type* f_state = this->getStatePointerByType(Base::ClassCount<AS>::get());
						if(f_state == nullptr){
							StateMapManagerLog(pankey_Log_EndMethod, "run", "f_state == nullptr");
							return;
						}
						AS& i_state = f_state->cast<AS>();
						Base::invoke<AS,MArgs...>(i_state, a_method, a_args...);
						StateMapManagerLog(pankey_Log_EndMethod, "run", "");
					}

				protected:

					virtual Base::State<Args...>* addStatePointer(const Base::CharArray& a_name, Base::State<Args...>* a_state){
						StateMapManagerLog(pankey_Log_StartMethod, "addStatePointer",  "");
						m_initialize_state_map.addPointer(a_name, a_state);
						StateMapManagerLog(pankey_Log_EndMethod, "addStatePointer", "");
						return a_state;
					}

					virtual bool containStatePointer(Base::State<Args...>* a_state){
						StateMapManagerLog(pankey_Log_StartMethod, "containStatePointer",  "");
						if(a_state == nullptr){
							return false;
						}
						long i_type = a_state->getType();
						StateMapManagerLog(pankey_Log_EndMethod, "containStatePointer", "");
						return this->containState(i_type);
					}

					virtual Base::State<Args...>* getStatePointerByType(long a_type){
						StateMapManagerLog(pankey_Log_StartMethod, "getStatePointerByType",  "");
						StateMapManagerLog(pankey_Log_Statement, "getStatePointerByType",  "a_type");
						StateMapManagerLog(pankey_Log_Statement, "getStatePointerByType",  a_type);
						StateMapManagerLog(pankey_Log_Statement, "getStatePointerByType",  "m_initialize_state_map length");
						StateMapManagerLog(pankey_Log_Statement, "getStatePointerByType",  m_initialize_state_map.length());
						StateMapManagerLog(pankey_Log_Statement, "getStatePointerByType",  "m_state_map length");
						StateMapManagerLog(pankey_Log_Statement, "getStatePointerByType",  m_state_map.length());
						for(int x = 0; x < m_initialize_state_map.length(); x++){
							Base::State<Args...>* f_state = m_initialize_state_map.getValuePointerByIndex(x);
							if(f_state == nullptr){
								StateMapManagerLog(pankey_Log_Statement, "getStatePointerByType",  "m_initialize_state_map f_state == nullptr");
								continue;
							}
							StateMapManagerLog(pankey_Log_Statement, "getStatePointerByType",  "m_initialize_state_map state type:");
							StateMapManagerLog(pankey_Log_Statement, "getStatePointerByType",  f_state->getType());
							if(f_state->getType() == a_type){
								StateMapManagerLog(pankey_Log_EndMethod, "getStatePointerByType", " m_initialize_state_mapf_state->getType() == a_type");
								return f_state;
							}
						}
						for(int x = 0; x < m_state_map.length(); x++){
							Base::State<Args...>* f_state = m_state_map.getValuePointerByIndex(x);
							if(f_state == nullptr){
								StateMapManagerLog(pankey_Log_Statement, "getStatePointerByType",  "m_state_map f_state == nullptr");
								continue;
							}
							StateMapManagerLog(pankey_Log_Statement, "getStatePointerByType",  "m_state_map state type:");
							StateMapManagerLog(pankey_Log_Statement, "getStatePointerByType",  f_state->getType());
							if(f_state->getType() == a_type){
								StateMapManagerLog(pankey_Log_EndMethod, "getStatePointerByType", "m_state_map f_state->getType() == a_type");
								return f_state;
							}
						}
						StateMapManagerLog(pankey_Log_EndMethod, "getStatePointerByType", "return nullptr");
						return nullptr;
					}
					
					virtual Base::RawMapEntry<Base::CharArray,Base::State<Args...>> removeStatePointers(Base::State<Args...>* a_state){
						StateMapManagerLog(pankey_Log_StartMethod, "removeStatePointers",  "");
						Base::RawMapEntry<Base::CharArray,Base::State<Args...>> i_entry = m_initialize_state_map.removePointersByValuePointer(a_state);
						if(i_entry.isNull()){
							return i_entry;
						}
						Base::State<Args...>* i_state = i_entry.getValue();
						if(i_state == nullptr){
							return i_entry;
						}
						i_state->onDisable();
						StateMapManagerLog(pankey_Log_EndMethod, "removeStatePointers", "");
						return i_entry;
					}

					Base::ArrayRawMap<Base::CharArray,Base::State<Args...>> m_state_map;
					Base::ArrayRawMap<Base::CharArray,Base::State<Args...>> m_initialize_state_map;
					
					
			};

		}

	}

#endif
