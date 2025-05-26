
namespace pankey{
  template<class T>
  String toString(const T& a_add){
    return String(a_add);
  }

  template<class T>
  String concat(const T& a_add){
    return String(a_add);
  }

  template<class T, class... Args>
  String concat(const T& a_string, const Args&... a_add){
    String i_string = String(a_string) + concat(a_add...);
    return i_string;
  }
}

#include "TestRunner.hpp"

#include "TR_AFL_Application_Testing.hpp"
#include "TR_ASL_Application_Testing.hpp"
#include "TR_ASL_SL_Application_Testing.hpp"
//#include "TR_Application_Testing.hpp"
#include "TR_IAppStateListManager_Testing.hpp"
#include "TR_IAppStateMapManager_Testing.hpp"
#include "TR_IStateListManager_Testing.hpp"
#include "TR_IStateMapManager_Testing.hpp"
#include "TR_ASL_SL_Manager_Testing.hpp"
#include "TR_DefaultAppSettings_Testing.hpp"
//#include "TR_FullStateManager_Testing.hpp"
//#include "TR_LoopManager_Testing.hpp"
//#include "TR_UpdateClassFunctionListManager_Testing.hpp"
//#include "TR_UpdateClassFunctionMapManager_Testing.hpp"
#include "TR_UpdateFunctionListManager_Testing.hpp"
#include "TR_UpdateAppFunctionListManager_Testing.hpp"
//#include "TR_UpdateFunctionMapManager_Testing.hpp"
//#include "TR_InitializeFunctionListManager_Testing.hpp"

#include "CharArray.hpp"

using namespace pankey::Base;
using namespace pankey::ApplicationSystem;

void Start() {
  Serial.println("Start Test");
}

void End() {
  Serial.println("End Test");
}

void Info(const String& a_test, const String& a_info) {
  Serial.print("Test: "); Serial.println(a_test);
  Serial.println(a_info);
}

void Error(const String& a_test, const String& a_error) {
  Serial.print("Test: "); Serial.println(a_test);
  Serial.println(a_error);
}

void Succes() {
  Serial.println("Test Complete with no errors");
}

TestRunner<String> tester;

void setup() {
  Serial.begin(9600);
  delay(3000);

  TR_AFL_Application_Testing(tester);
  TR_ASL_Application_Testing(tester);
  TR_ASL_SL_Application_Testing(tester);
  //  TR_Application_Testing(tester);
    TR_IAppStateListManager_Testing(tester);
    TR_IAppStateMapManager_Testing(tester);
    TR_IStateListManager_Testing(tester);
    TR_IStateMapManager_Testing(tester);
    TR_ASL_SL_Manager_Testing(tester);
    TR_DefaultAppSettings_Testing(tester);
  //  TR_FullStateManager_Testing(tester);
  //  TR_LoopManager_Testing(tester);
  //  TR_UpdateClassFunctionListManager_Testing(tester);
  //  TR_UpdateClassFunctionMapManager_Testing(tester);
  TR_UpdateFunctionListManager_Testing(tester);
  TR_UpdateAppFunctionListManager_Testing(tester);
  //  TR_UpdateFunctionMapManager_Testing(tester);
  //  TR_InitializeFunctionListManager_Testing(tester);

  tester.output(Start, End, Info, Error, Succes);
}

void loop() {
  tester.runTest();
  tester.run();
  // Serial.println(ESP.getFreeHeap());
  delay(3000);
}