
#ifndef AppSettings_hpp
	#define AppSettings_hpp

	#include "CharArray.hpp"

	namespace pankey{

		namespace ApplicationSystem{
		
			class AppSettings{
				public:
					virtual ~AppSettings(){}
					
					virtual void addInt(const Base::CharArray& a_name,int a_var)=0;
					virtual void putInt(const Base::CharArray& a_name, int a_var)=0;
					virtual void setInt(const Base::CharArray& a_name, int a_var)=0;
					virtual void changeInt(const Base::CharArray& a_name, int a_var)=0;
					virtual int getInt(const Base::CharArray& a_name)=0;
					virtual void removeInt(const Base::CharArray& a_name)=0;
					virtual bool containInt(const Base::CharArray& a_name)=0;
					
					virtual void addLong(const Base::CharArray& a_name, long a_var)=0;
					virtual void putLong(const Base::CharArray& a_name, long a_var)=0;
					virtual void setLong(const Base::CharArray& a_name, long a_var)=0;
					virtual void changeLong(const Base::CharArray& a_name, long a_var)=0;
					virtual long getLong(const Base::CharArray& a_name)=0;
					virtual void removeLong(const Base::CharArray& a_name)=0;
					virtual bool containLong(const Base::CharArray& a_name)=0;
					
					virtual void addFloat(const Base::CharArray& a_name, float a_var)=0;
					virtual void putFloat(const Base::CharArray& a_name, float a_var)=0;
					virtual void setFloat(const Base::CharArray& a_name, float a_var)=0;
					virtual void changeFloat(const Base::CharArray& a_name, float a_var)=0;
					virtual float getFloat(const Base::CharArray& a_name)=0;
					virtual void removeFloat(const Base::CharArray& a_name)=0;
					virtual bool containFloat(const Base::CharArray& a_name)=0;
					
					virtual void addCharArray(const Base::CharArray& a_name, const Base::CharArray& a_var)=0;
					virtual void putCharArray(const Base::CharArray& a_name, const Base::CharArray& a_var)=0;
					virtual void setCharArray(const Base::CharArray& a_name, const Base::CharArray& a_var)=0;
					virtual void changeCharArray(const Base::CharArray& a_name, const Base::CharArray& a_var)=0;
					virtual Base::CharArray getCharArray(const Base::CharArray& a_name)=0;
					virtual void removeCharArray(const Base::CharArray& a_name)=0;
					virtual bool containCharArray(const Base::CharArray& a_name)=0;
					
					virtual void addBoolean(const Base::CharArray& a_name, bool a_var)=0;
					virtual void putBoolean(const Base::CharArray& a_name, bool a_var)=0;
					virtual void setBoolean(const Base::CharArray& a_name, bool a_var)=0;
					virtual void changeBoolean(const Base::CharArray& a_name, bool a_var)=0;
					virtual bool getBoolean(const Base::CharArray& a_name)=0;
					virtual void removeBoolean(const Base::CharArray& a_name)=0;
					virtual bool containBoolean(const Base::CharArray& a_name)=0;
			};

		}

	}

#endif
