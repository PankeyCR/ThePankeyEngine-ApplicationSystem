
#ifndef TR_DefaultAppSettings_Testing_hpp
	#define TR_DefaultAppSettings_Testing_hpp
	
	#include "TestResult.hpp"
	#include "TestRunner.hpp"

	#include "DefaultAppSettings.hpp"

	namespace pankey{

		namespace ApplicationSystem{
	
			Base::TestResult<String> TR_DefaultAppSettings_Testing_1(){
				Base::TestResult<String> i_result;

				DefaultAppSettings i_settings;
				
				return i_result;
			}
		
			Base::TestResult<String> TR_DefaultAppSettings_Testing_2(){
				Base::TestResult<String> i_result;

				DefaultAppSettings i_settings;

				i_settings.addInt("name", 15);

				int i_value = i_settings.getInt("name");
				
				i_result.assertTrue("settings should contain name", i_settings.containInt("name"));
				i_result.assertEqual("value should be 15", i_value, 15);

				return i_result;
			}
		
			Base::TestResult<String> TR_DefaultAppSettings_Testing_3(){
				Base::TestResult<String> i_result;

				DefaultAppSettings i_settings;

				i_settings.addLong("name", 1590l);

				long i_value = i_settings.getLong("name");
				
				i_result.assertTrue("settings should contain name", i_settings.containLong("name"));
				i_result.assertEqual("value should be 15", i_value, 1590l);

				return i_result;
			}
		
			Base::TestResult<String> TR_DefaultAppSettings_Testing_4(){
				Base::TestResult<String> i_result;

				DefaultAppSettings i_settings;

				i_settings.addFloat("name", 15.6f);

				float i_value = i_settings.getFloat("name");
				
				i_result.assertTrue("settings should contain name", i_settings.containFloat("name"));
				i_result.assertEqual("value should be 15.6f", i_value, 15.6f);

				return i_result;
			}
		
			Base::TestResult<String> TR_DefaultAppSettings_Testing_5(){
				Base::TestResult<String> i_result;

				DefaultAppSettings i_settings;

				i_settings.addCharArray("name", "Frank");

				Base::CharArray i_value = i_settings.getCharArray("name");
				
				i_result.assertTrue("settings should contain name", i_settings.containCharArray("name"));
				i_result.assertEqual("value should be 15.6f", i_value, Base::CharArray("Frank"));

				return i_result;
			}
		
			Base::TestResult<String> TR_DefaultAppSettings_Testing_6(){
				Base::TestResult<String> i_result;

				DefaultAppSettings i_settings;

				i_settings.addBoolean("name", true);

				bool i_value = i_settings.getBoolean("name");
				
				i_result.assertTrue("settings should contain name", i_settings.containBoolean("name"));
				i_result.assertEqual("value should be 15.6f", i_value, true);

				return i_result;
			}
		
			Base::TestResult<String> TR_DefaultAppSettings_Testing_8(){
				Base::TestResult<String> i_result;

				DefaultAppSettings i_settings;

				i_settings.addInt("name", 15);
				
				i_result.assertTrue("settings should contain name", i_settings.containInt("name"));

				i_settings.removeInt("name");
				
				i_result.assertTrue("settings shouldnt contain name", !i_settings.containInt("name"));

				return i_result;
			}
		
			Base::TestResult<String> TR_DefaultAppSettings_Testing_9(){
				Base::TestResult<String> i_result;

				DefaultAppSettings i_settings;

				i_settings.addLong("name", 1578l);
				
				i_result.assertTrue("settings should contain name", i_settings.containLong("name"));

				i_settings.removeLong("name");
				
				i_result.assertTrue("settings shouldnt contain name", !i_settings.containLong("name"));

				return i_result;
			}
		
			Base::TestResult<String> TR_DefaultAppSettings_Testing_10(){
				Base::TestResult<String> i_result;

				DefaultAppSettings i_settings;

				i_settings.addFloat("name", 15.6f);
				
				i_result.assertTrue("settings should contain name", i_settings.containFloat("name"));

				i_settings.removeFloat("name");
				
				i_result.assertTrue("settings shouldnt contain name", !i_settings.containFloat("name"));

				return i_result;
			}
		
			Base::TestResult<String> TR_DefaultAppSettings_Testing_11(){
				Base::TestResult<String> i_result;

				DefaultAppSettings i_settings;

				i_settings.addCharArray("name", "Frank");
				
				i_result.assertTrue("settings should contain name", i_settings.containCharArray("name"));

				i_settings.removeCharArray("name");
				
				i_result.assertTrue("settings shouldnt contain name", !i_settings.containCharArray("name"));

				return i_result;
			}
		
			Base::TestResult<String> TR_DefaultAppSettings_Testing_12(){
				Base::TestResult<String> i_result;

				DefaultAppSettings i_settings;

				i_settings.addBoolean("name", false);
				
				i_result.assertTrue("settings should contain name", i_settings.containBoolean("name"));

				i_settings.removeBoolean("name");
				
				i_result.assertTrue("settings shouldnt contain name", !i_settings.containBoolean("name"));

				return i_result;
			}
		
			Base::TestResult<String> TR_DefaultAppSettings_Testing_16(){
				Base::TestResult<String> i_result;

				DefaultAppSettings i_settings;

				i_settings.addInt("name", 15);
				i_settings.setInt("name", 6);

				int i_value = i_settings.getInt("name");
				
				i_result.assertTrue("settings should contain name", i_settings.containInt("name"));
				i_result.assertEqual("value should be 6", i_value, 6);

				return i_result;
			}
		
			Base::TestResult<String> TR_DefaultAppSettings_Testing_17(){
				Base::TestResult<String> i_result;

				DefaultAppSettings i_settings;

				i_settings.addLong("name", 1590l);
				i_settings.setLong("name", 543l);

				long i_value = i_settings.getLong("name");
				
				i_result.assertTrue("settings should contain name", i_settings.containLong("name"));
				i_result.assertEqual("value should be 543", i_value, 543l);

				return i_result;
			}
		
			Base::TestResult<String> TR_DefaultAppSettings_Testing_18(){
				Base::TestResult<String> i_result;

				DefaultAppSettings i_settings;

				i_settings.addFloat("name", 15.6f);
				i_settings.setFloat("name", 65.7f);

				float i_value = i_settings.getFloat("name");
				
				i_result.assertTrue("settings should contain name", i_settings.containFloat("name"));
				i_result.assertEqual("value should be 65.7f", i_value, 65.7f);

				return i_result;
			}
		
			Base::TestResult<String> TR_DefaultAppSettings_Testing_19(){
				Base::TestResult<String> i_result;

				DefaultAppSettings i_settings;

				i_settings.addCharArray("name", "Frank");
				i_settings.setCharArray("name", "Sam");

				Base::CharArray i_value = i_settings.getCharArray("name");
				
				i_result.assertTrue("settings should contain name", i_settings.containCharArray("name"));
				i_result.assertEqual("value should be Sam", i_value, Base::CharArray("Sam"));

				return i_result;
			}
		
			Base::TestResult<String> TR_DefaultAppSettings_Testing_20(){
				Base::TestResult<String> i_result;

				DefaultAppSettings i_settings;

				i_settings.addBoolean("name", true);
				i_settings.setBoolean("name", false);

				bool i_value = i_settings.getBoolean("name");
				
				i_result.assertTrue("settings should contain name", i_settings.containBoolean("name"));
				i_result.assertEqual("value should be false", i_value, false);

				return i_result;
			}
		
			Base::TestResult<String> TR_DefaultAppSettings_Testing_22(){
				Base::TestResult<String> i_result;

				DefaultAppSettings i_settings;

				i_settings.putInt("name", 15);
				i_settings.changeInt("name", 6);

				int i_value = i_settings.getInt("name");
				
				i_result.assertTrue("settings should contain name", i_settings.containInt("name"));
				i_result.assertEqual("value should be 6", i_value, 6);

				return i_result;
			}
		
			Base::TestResult<String> TR_DefaultAppSettings_Testing_23(){
				Base::TestResult<String> i_result;

				DefaultAppSettings i_settings;

				i_settings.putLong("name", 1590l);
				i_settings.changeLong("name", 543l);

				long i_value = i_settings.getLong("name");
				
				i_result.assertTrue("settings should contain name", i_settings.containLong("name"));
				i_result.assertEqual("value should be 543", i_value, 543l);

				return i_result;
			}
		
			Base::TestResult<String> TR_DefaultAppSettings_Testing_24(){
				Base::TestResult<String> i_result;

				DefaultAppSettings i_settings;

				i_settings.putFloat("name", 15.6f);
				i_settings.changeFloat("name", 65.7f);

				float i_value = i_settings.getFloat("name");
				
				i_result.assertTrue("settings should contain name", i_settings.containFloat("name"));
				i_result.assertEqual("value should be 65.7f", i_value, 65.7f);

				return i_result;
			}
		
			Base::TestResult<String> TR_DefaultAppSettings_Testing_25(){
				Base::TestResult<String> i_result;

				DefaultAppSettings i_settings;

				i_settings.putCharArray("name", "Frank");
				i_settings.changeCharArray("name", "Sam");

				Base::CharArray i_value = i_settings.getCharArray("name");
				
				i_result.assertTrue("settings should contain name", i_settings.containCharArray("name"));
				i_result.assertEqual("value should be Sam", i_value, Base::CharArray("Sam"));

				return i_result;
			}
		
			Base::TestResult<String> TR_DefaultAppSettings_Testing_26(){
				Base::TestResult<String> i_result;

				DefaultAppSettings i_settings;

				i_settings.putBoolean("name", true);
				i_settings.changeBoolean("name", false);

				bool i_value = i_settings.getBoolean("name");
				
				i_result.assertTrue("settings should contain name", i_settings.containBoolean("name"));
				i_result.assertEqual("value should be false", i_value, false);

				return i_result;
			}

			void TR_DefaultAppSettings_Testing(Base::TestRunner<String>& a_test_runner){
				a_test_runner.add("DefaultAppSettings Constructor", TR_DefaultAppSettings_Testing_1);
				a_test_runner.add("DefaultAppSettings addInt, containInt, getInt", TR_DefaultAppSettings_Testing_2);
				a_test_runner.add("DefaultAppSettings addLong, containLong, getLong", TR_DefaultAppSettings_Testing_3);
				a_test_runner.add("DefaultAppSettings addFloat, containFloat, getFloat", TR_DefaultAppSettings_Testing_4);
				a_test_runner.add("DefaultAppSettings addCharArray, containCharArray, getCharArray", TR_DefaultAppSettings_Testing_5);
				a_test_runner.add("DefaultAppSettings addBoolean, containBoolean, getBoolean", TR_DefaultAppSettings_Testing_6);
				a_test_runner.add("DefaultAppSettings removeInt", TR_DefaultAppSettings_Testing_8);
				a_test_runner.add("DefaultAppSettings removeLong", TR_DefaultAppSettings_Testing_9);
				a_test_runner.add("DefaultAppSettings removeFloat", TR_DefaultAppSettings_Testing_10);
				a_test_runner.add("DefaultAppSettings removeCharArray", TR_DefaultAppSettings_Testing_11);
				a_test_runner.add("DefaultAppSettings removeBoolean", TR_DefaultAppSettings_Testing_12);
				a_test_runner.add("DefaultAppSettings int set", TR_DefaultAppSettings_Testing_16);
				a_test_runner.add("DefaultAppSettings var set", TR_DefaultAppSettings_Testing_17);
				a_test_runner.add("DefaultAppSettings var set", TR_DefaultAppSettings_Testing_18);
				a_test_runner.add("DefaultAppSettings var set", TR_DefaultAppSettings_Testing_19);
				a_test_runner.add("DefaultAppSettings var set", TR_DefaultAppSettings_Testing_20);
				a_test_runner.add("DefaultAppSettings change int", TR_DefaultAppSettings_Testing_22);
				a_test_runner.add("DefaultAppSettings change long", TR_DefaultAppSettings_Testing_23);
				a_test_runner.add("DefaultAppSettings change CharArray", TR_DefaultAppSettings_Testing_24);
				a_test_runner.add("DefaultAppSettings change float", TR_DefaultAppSettings_Testing_25);
				a_test_runner.add("DefaultAppSettings change boolean", TR_DefaultAppSettings_Testing_26);
			}

		}

	}

#endif
