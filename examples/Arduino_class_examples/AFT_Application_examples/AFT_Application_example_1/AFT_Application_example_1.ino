

#define AFT_Application_Log

#include "MethodLogger.hpp"
#include "AFT_Application.hpp"

using namespace pankey::Base;
using namespace pankey::ApplicationSystem;

void Log(int a_status, const CharArray& a_name, const CharArray& a_method, const CharArray& a_log){
  Serial.print("Status: ");Serial.print(a_status);Serial.print(" Class: ");Serial.print(a_name.pointer());Serial.print(" Method: ");Serial.print(a_method.pointer());Serial.print(" Log: ");Serial.println(a_log.pointer());
}

AFT_Application app;
long g_time = 0;

void setup() {
  Serial.begin(9600);
  
  pankey_Log_set(Log);
       
  auto& i_manager = app.getStateManager();

  app.initialize();
}

void loop() {
  g_time += app.update(millis());
  Serial.print("time: ");
  Serial.println(g_time);
}
