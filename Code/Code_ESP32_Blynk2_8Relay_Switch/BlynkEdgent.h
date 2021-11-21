
extern "C" {
  void app_loop();
  void eraseMcuConfig();
  void restartMCU();
}

#include "Settings.h"
#include <BlynkSimpleEsp32_SSL.h>

#ifndef BLYNK_NEW_LIBRARY
#error "Old version of Blynk library is in use. Please replace it with the new one."
#endif

#if !defined(BLYNK_TEMPLATE_ID) || !defined(BLYNK_DEVICE_NAME)
#error "Please specify your BLYNK_TEMPLATE_ID and BLYNK_DEVICE_NAME"
#endif

#include "BlynkState.h"
#include "ConfigStore.h"
#include "ResetButton.h"
#include "ConfigMode.h"
#include "Indicator.h"
#include "OTA.h"
#include "Console.h"
void manual_control();
inline
void BlynkState::set(State m) {
  if (state != m && m < MODE_MAX_VALUE) {
    DEBUG_PRINT(String(StateStr[state]) + " => " + StateStr[m]);
    state = m;

    // You can put your state handling here,
    // i.e. implement custom indication
  }
}

void printDeviceBanner()
{
  Blynk.printBanner();
  DEBUG_PRINT("--------------------------");
  DEBUG_PRINT(String("Product:  ") + BLYNK_DEVICE_NAME);
  DEBUG_PRINT(String("Hardware: ") + BOARD_HARDWARE_VERSION);
  DEBUG_PRINT(String("Firmware: ") + BLYNK_FIRMWARE_VERSION " (build " __DATE__ " " __TIME__ ")");
  if (configStore.getFlag(CONFIG_FLAG_VALID)) {
    DEBUG_PRINT(String("Token:    ...") + (configStore.cloudToken+28));
  }
  DEBUG_PRINT(String("Device:   ") + BLYNK_INFO_DEVICE + " @ " + ESP.getCpuFreqMHz() + "MHz");
  DEBUG_PRINT(String("MAC:      ") + WiFi.macAddress());
  DEBUG_PRINT(String("Flash:    ") + ESP.getFlashChipSize() / 1024 + "K");
  DEBUG_PRINT(String("ESP sdk:  ") + ESP.getSdkVersion());
  DEBUG_PRINT(String("Chip rev: ") + ESP.getChipRevision());
  DEBUG_PRINT(String("Free mem: ") + ESP.getFreeHeap());
  DEBUG_PRINT("--------------------------");
}

void runBlynkWithChecks() {
  Blynk.run();
  if (BlynkState::get() == MODE_RUNNING) {
    if (!Blynk.connected()) {
      if (WiFi.status() == WL_CONNECTED) {
        BlynkState::set(MODE_CONNECTING_CLOUD);
      } else {
        BlynkState::set(MODE_CONNECTING_NET);
      }
    }
  }
}

class Edgent {

public:
  void begin()
  {
    indicator_init();
    button_init();
    config_init();

    WiFi.persistent(false);
    WiFi.enableSTA(true);   // Needed to get MAC

    printDeviceBanner();

    if (configStore.getFlag(CONFIG_FLAG_VALID)) {
      BlynkState::set(MODE_CONNECTING_NET);
    } else if (config_load_blnkopt()) {
      DEBUG_PRINT("Firmware is preprovisioned");
      BlynkState::set(MODE_CONNECTING_NET);
    } else {
      BlynkState::set(MODE_WAIT_CONFIG);
    }
  }

  void run() {
    app_loop();
    switch (BlynkState::get()) {
    case MODE_WAIT_CONFIG:       
    case MODE_CONFIGURING:       enterConfigMode();    break;
    case MODE_CONNECTING_NET:    enterConnectNet();    break;
    case MODE_CONNECTING_CLOUD:  enterConnectCloud();  break;
    case MODE_RUNNING:           runBlynkWithChecks(); break;
    case MODE_OTA_UPGRADE:       enterOTA();           break;
    case MODE_SWITCH_TO_STA:     enterSwitchToSTA();   break;
    case MODE_RESET_CONFIG:      enterResetConfig();   break;
    default:                     enterError();         break;
    }
  }
};

Edgent BlynkEdgent;
BlynkTimer edgentTimer;

void app_loop() {
    edgentTimer.run();
    edgentConsole.run();
    manual_control();
}

void manual_control()
{
  if (digitalRead(SwitchPin1) == LOW && SwitchState_1 == LOW) {
    digitalWrite(RelayPin1, LOW);
    Blynk.virtualWrite(VPIN_BUTTON_1, HIGH);
    toggleState_1 = HIGH;
    SwitchState_1 = HIGH;
    Serial.println("Switch-1 on");
  }
  if (digitalRead(SwitchPin1) == HIGH && SwitchState_1 == HIGH) {
    digitalWrite(RelayPin1, HIGH);
    Blynk.virtualWrite(VPIN_BUTTON_1, LOW);
    toggleState_1 = LOW;
    SwitchState_1 = 0;
    Serial.println("Switch-1 off");
  }
  if (digitalRead(SwitchPin2) == LOW && SwitchState_2 == LOW) {
    digitalWrite(RelayPin2, LOW);
    Blynk.virtualWrite(VPIN_BUTTON_2, HIGH);
    toggleState_2 = HIGH;
    SwitchState_2 = HIGH;
    Serial.println("Switch-2 on");
  }
  if (digitalRead(SwitchPin2) == HIGH && SwitchState_2 == HIGH) {
    digitalWrite(RelayPin2, HIGH);
    Blynk.virtualWrite(VPIN_BUTTON_2, LOW);
    toggleState_2 = LOW;
    SwitchState_2 = LOW;
    Serial.println("Switch-2 off");
  }
  if (digitalRead(SwitchPin3) == LOW && SwitchState_3 == LOW) {
    digitalWrite(RelayPin3, LOW);
    Blynk.virtualWrite(VPIN_BUTTON_3, HIGH);
    toggleState_3 = HIGH;
    SwitchState_3 = HIGH;
    Serial.println("Switch-3 on");
  }
  if (digitalRead(SwitchPin3) == HIGH && SwitchState_3 == HIGH) {
    digitalWrite(RelayPin3, HIGH);
    Blynk.virtualWrite(VPIN_BUTTON_3, LOW);
    toggleState_3 = LOW;
    SwitchState_3 = LOW;
    Serial.println("Switch-3 off");
  }
  if (digitalRead(SwitchPin4) == LOW && SwitchState_4 == LOW) {
    digitalWrite(RelayPin4, LOW);
    Blynk.virtualWrite(VPIN_BUTTON_4, HIGH);
    toggleState_4 = HIGH;
    SwitchState_4 = HIGH;
    Serial.println("Switch-4 on");
  }
  if (digitalRead(SwitchPin4) == HIGH && SwitchState_4 == HIGH) {
    digitalWrite(RelayPin4, HIGH);
    Blynk.virtualWrite(VPIN_BUTTON_4, LOW);
    toggleState_4 = LOW;
    SwitchState_4 = LOW;
    Serial.println("Switch-4 off");
  }
  if (digitalRead(SwitchPin5) == LOW && SwitchState_5 == LOW) {
    digitalWrite(RelayPin5, LOW);
    Blynk.virtualWrite(VPIN_BUTTON_5, HIGH);
    toggleState_5 = HIGH;
    SwitchState_5 = HIGH;
    Serial.println("Switch-5 on");
  }
  if (digitalRead(SwitchPin5) == HIGH && SwitchState_5 == HIGH) {
    digitalWrite(RelayPin5, HIGH);
    Blynk.virtualWrite(VPIN_BUTTON_5, LOW);
    toggleState_5 = LOW;
    SwitchState_5 = LOW;
    Serial.println("Switch-5 off");
  }
  if (digitalRead(SwitchPin6) == LOW && SwitchState_6 == LOW) {
    digitalWrite(RelayPin6, LOW);
    Blynk.virtualWrite(VPIN_BUTTON_6, HIGH);
    toggleState_6 = HIGH;
    SwitchState_6 = HIGH;
    Serial.println("Switch-6 on");
  }
  if (digitalRead(SwitchPin6) == HIGH && SwitchState_6 == HIGH) {
    digitalWrite(RelayPin6, HIGH);
    Blynk.virtualWrite(VPIN_BUTTON_6, LOW);
    toggleState_6 = LOW;
    SwitchState_6 = LOW;
    Serial.println("Switch-6 off");
  }
  if (digitalRead(SwitchPin7) == LOW && SwitchState_7 == LOW) {
    digitalWrite(RelayPin7, LOW);
    Blynk.virtualWrite(VPIN_BUTTON_7, HIGH);
    toggleState_7 = HIGH;
    SwitchState_7 = HIGH;
    Serial.println("Switch-7 on");
  }
  if (digitalRead(SwitchPin7) == HIGH && SwitchState_7 == HIGH) {
    digitalWrite(RelayPin7, HIGH);
    Blynk.virtualWrite(VPIN_BUTTON_7, LOW);
    toggleState_7 = LOW;
    SwitchState_7 = LOW;
    Serial.println("Switch-7 off");
  }
  if (digitalRead(SwitchPin8) == LOW && SwitchState_8 == LOW) {
    digitalWrite(RelayPin8, LOW);
    Blynk.virtualWrite(VPIN_BUTTON_8, HIGH);
    toggleState_8 = HIGH;
    SwitchState_8 = HIGH;
    Serial.println("Switch-8 on");
  }
  if (digitalRead(SwitchPin8) == HIGH && SwitchState_8 == HIGH) {
    digitalWrite(RelayPin8, HIGH);
    Blynk.virtualWrite(VPIN_BUTTON_8, LOW);
    toggleState_8 = LOW;
    SwitchState_8 = LOW;
    Serial.println("Switch-8 off");
  }
}
