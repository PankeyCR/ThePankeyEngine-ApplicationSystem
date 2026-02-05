
#ifndef DefaultSettings_hpp
	#define DefaultSettings_hpp

	#include "Settings.hpp"
	#include "ArrayRawMap.hpp"

	namespace pankey{

		namespace ApplicationSystem{

			class DefaultSettings : public Settings{
				public:
					DefaultSettings(){}

					virtual ~DefaultSettings(){}
					
					virtual void addInt(const Base::CharArray& a_name, int a_var){
						m_int_map.add(a_name, a_var);
					}

					virtual void putInt(const Base::CharArray& a_name, int a_var){
						m_int_map.put(a_name, a_var);
					}

					virtual void setInt(const Base::CharArray& a_name, int a_var){
						m_int_map.set(a_name, a_var);
					}

					virtual void changeInt(const Base::CharArray& a_name, int a_var){
						if(m_int_map.containKey(a_name)){
							m_int_map.set(a_name, a_var);
						}else{
							m_int_map.add(a_name, a_var);
						}
					}

					virtual int getInt(const Base::CharArray& a_name){
						return m_int_map.get(a_name);
					}

					virtual void removeInt(const Base::CharArray& a_name){
						m_int_map.destroyByKey(a_name);
					}

					virtual bool containInt(const Base::CharArray& a_name){
						return m_int_map.containKey(a_name);
					}
					
					virtual void addLong(const Base::CharArray& a_name, long a_var){
						m_long_map.add(a_name, a_var);
					}

					virtual void putLong(const Base::CharArray& a_name, long a_var){
						m_long_map.put(a_name, a_var);
					}

					virtual void setLong(const Base::CharArray& a_name, long a_var){
						m_long_map.set(a_name, a_var);
					}

					virtual void changeLong(const Base::CharArray& a_name, long a_var){
						if(m_long_map.containKey(a_name)){
							m_long_map.set(a_name, a_var);
						}else{
							m_long_map.add(a_name, a_var);
						}
					}

					virtual long getLong(const Base::CharArray& a_name){
						return m_long_map.get(a_name);
					}

					virtual void removeLong(const Base::CharArray& a_name){
						m_long_map.destroyByKey(a_name);
					}

					virtual bool containLong(const Base::CharArray& a_name){
						return m_long_map.containKey(a_name);
					}
					
					virtual void addFloat(const Base::CharArray& a_name, float a_var){
						m_float_map.add(a_name, a_var);
					}

					virtual void putFloat(const Base::CharArray& a_name, float a_var){
						m_float_map.put(a_name, a_var);
					}

					virtual void setFloat(const Base::CharArray& a_name, float a_var){
						m_float_map.set(a_name, a_var);
					}

					virtual void changeFloat(const Base::CharArray& a_name, float a_var){
						if(m_float_map.containKey(a_name)){
							m_float_map.set(a_name, a_var);
						}else{
							m_float_map.add(a_name, a_var);
						}
					}

					virtual float getFloat(const Base::CharArray& a_name){
						return m_float_map.get(a_name);
					}

					virtual void removeFloat(const Base::CharArray& a_name){
						m_float_map.destroyByKey(a_name);
					}

					virtual bool containFloat(const Base::CharArray& a_name){
						return m_float_map.containKey(a_name);
					}
					
					virtual void addCharArray(const Base::CharArray& a_name, const Base::CharArray& a_var){
						m_chars_map.add(a_name, a_var);
					}

					virtual void putCharArray(const Base::CharArray& a_name, const Base::CharArray& a_var){
						m_chars_map.put(a_name, a_var);
					}

					virtual void setCharArray(const Base::CharArray& a_name, const Base::CharArray& a_var){
						m_chars_map.set(a_name, a_var);
					}

					virtual void changeCharArray(const Base::CharArray& a_name, const Base::CharArray& a_var){
						if(m_chars_map.containKey(a_name)){
							m_chars_map.set(a_name, a_var);
						}else{
							m_chars_map.add(a_name, a_var);
						}
					}

					virtual Base::CharArray getCharArray(const Base::CharArray& a_name){
						return m_chars_map.get(a_name);
					}

					virtual void removeCharArray(const Base::CharArray& a_name){
						m_chars_map.destroyByKey(a_name);
					}

					virtual bool containCharArray(const Base::CharArray& a_name){
						return m_chars_map.containKey(a_name);
					}
					
					virtual void addBoolean(const Base::CharArray& a_name, bool a_var){
						m_boolean_map.add(a_name, a_var);
					}

					virtual void putBoolean(const Base::CharArray& a_name, bool a_var){
						m_boolean_map.put(a_name, a_var);
					}

					virtual void setBoolean(const Base::CharArray& a_name, bool a_var){
						m_boolean_map.set(a_name, a_var);
					}

					virtual void changeBoolean(const Base::CharArray& a_name, bool a_var){
						if(m_boolean_map.containKey(a_name)){
							m_boolean_map.set(a_name, a_var);
						}else{
							m_boolean_map.add(a_name, a_var);
						}
					}

					virtual bool getBoolean(const Base::CharArray& a_name){
						return m_boolean_map.get(a_name);
					}

					virtual void removeBoolean(const Base::CharArray& a_name){
						m_boolean_map.destroyByKey(a_name);
					}

					virtual bool containBoolean(const Base::CharArray& a_name){
						return m_boolean_map.containKey(a_name);
					}
					
					
				protected:
					Base::ArrayRawMap<Base::CharArray,int> m_int_map;
					Base::ArrayRawMap<Base::CharArray,float> m_long_map;
					Base::ArrayRawMap<Base::CharArray,float> m_float_map;
					Base::ArrayRawMap<Base::CharArray,Base::CharArray> m_chars_map;
					Base::ArrayRawMap<Base::CharArray,bool> m_boolean_map;
			};

		}

	}

#endif