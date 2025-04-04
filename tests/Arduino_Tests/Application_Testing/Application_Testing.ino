
#include "TestRunner.hpp"

#include "TR_AFL_Application_Testing.hpp"
#include "TR_ASL_Application_Testing.hpp"
#include "TR_ASL_SL_Application_Testing.hpp"
//#include "TR_Application_Testing.hpp"
#include "TR_AppStateListManager_Testing.hpp"
#include "TR_AppStateMapManager_Testing.hpp"
#include "TR_StateListManager_Testing.hpp"
#include "TR_StateMapManager_Testing.hpp"
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

void Info(const pankey::Base::CharArray& a_test, const pankey::Base::CharArray& a_info) {
  Serial.print("Test: "); Serial.println(a_test.pointer());
  Serial.println(a_info.pointer());
}

void Error(const pankey::Base::CharArray& a_test, const pankey::Base::CharArray& a_error) {
  Serial.print("Test: "); Serial.println(a_test.pointer());
  Serial.println(a_error.pointer());
}

void Succes() {
  Serial.println("Test Complete with no errors");
}

TestRunner tester;

void setup() {
  Serial.begin(9600);
  delay(3000);

  TR_AFL_Application_Testing(tester);
  TR_ASL_Application_Testing(tester);
  TR_ASL_SL_Application_Testing(tester);
  //  TR_Application_Testing(tester);
    TR_AppStateListManager_Testing(tester);
    TR_AppStateMapManager_Testing(tester);
    TR_StateListManager_Testing(tester);
    TR_StateMapManager_Testing(tester);
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
  delay(3000);
}