//#include <FreeRTOS.h>
//#include <task.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_BusIO_Register.h>
#include <Adafruit_TinyUSB.h>
//std::map<eTaskState, const char *> eTaskStateName { {eReady, "Ready"}, { eRunning, "Running" }, {eBlocked, "Blocked"}, {eSuspended, "Suspended"}, {eDeleted, "Deleted"} };
uint8_t pins[] = { D0, D1, D2, D3, D4, D5, D6, D7, D8, D9 };
uint8_t hidcode[] = {
 HID_KEY_A ,
 HID_KEY_B ,
 HID_KEY_C ,
 HID_KEY_D ,
 HID_KEY_E ,
 HID_KEY_F ,
 HID_KEY_G ,
 HID_KEY_H ,
 HID_KEY_I ,
 HID_KEY_J ,
 HID_KEY_K ,
 HID_KEY_L ,
 HID_KEY_M ,
 HID_KEY_N ,
 HID_KEY_O ,
 HID_KEY_P ,
 HID_KEY_Q ,
 HID_KEY_R ,
 HID_KEY_S ,
 HID_KEY_T ,
 HID_KEY_U ,
 HID_KEY_V ,
 HID_KEY_W ,
 HID_KEY_X ,
 HID_KEY_Y ,
 HID_KEY_Z ,
 HID_KEY_4 ,
 HID_KEY_5 ,
 HID_KEY_6 ,
 HID_KEY_7 ,
 HID_KEY_8 ,
 HID_KEY_9 ,
 HID_KEY_KEYPAD_1 ,
 HID_KEY_KEYPAD_2 ,
 HID_KEY_KEYPAD_3 ,
 HID_KEY_KEYPAD_4 ,
 HID_KEY_KEYPAD_5 ,
 HID_KEY_KEYPAD_6
};
uint8_t const desc_hid_report[] =
    {
        TUD_HID_REPORT_DESC_NKROKEYBOARD()
    };


Adafruit_USBD_HID usb_hid(desc_hid_report, sizeof(desc_hid_report), HID_ITF_PROTOCOL_NONE, 2, true);

hid_nkrokeyboard_report_t kb;

void setup() {
  // Manual begin() is required on core without built-in support e.g. mbed rp2040
  if (!TinyUSBDevice.isInitialized()) {
    TinyUSBDevice.begin(0);
  }

  // Setup HID
  usb_hid.setBootProtocol(HID_ITF_PROTOCOL_KEYBOARD);
  usb_hid.setPollInterval(1);
  usb_hid.setReportDescriptor(desc_hid_report, sizeof(desc_hid_report));
  usb_hid.setStringDescriptor("Ongeki Keyboard");

  // Set up output report (on control endpoint) for Capslock indicator
  usb_hid.setReportCallback(NULL, hid_report_callback);

  usb_hid.begin();

  // If already enumerated, additional class driverr begin() e.g msc, hid, midi won't take effect until re-enumeration
  if (TinyUSBDevice.mounted()) {
    TinyUSBDevice.detach();
    delay(10);
    TinyUSBDevice.attach();
  }
  Serial.begin(115200);
  Serial.println("Start Programm");
    pinMode(0,INPUT_PULLUP);
    pinMode(1,INPUT_PULLUP);
    pinMode(2,INPUT_PULLUP);
    pinMode(3,INPUT_PULLUP);
    pinMode(4,INPUT_PULLUP);
    pinMode(5,INPUT_PULLUP);
    pinMode(6,INPUT_PULLUP);
    pinMode(7,INPUT_PULLUP);
    pinMode(8,INPUT_PULLUP);
    pinMode(9,INPUT_PULLUP);
}
void hid_report_callback(uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer, uint16_t bufsize) {
  (void) report_id;
  (void) bufsize;

  if (report_type != HID_REPORT_TYPE_OUTPUT) return;

  uint8_t ledIndicator = buffer[0];
}

void send()
{
  usb_hid.sendReport(0, &kb, sizeof(kb));
}

void add(uint8_t key_value)
{
  kb.keys[key_value / 8] |= 1 << (key_value % 8);
}

void releaseall()
{
  kb.modifier = 0;
  kb.custom = 0;
  for (int i = 0; i < 13; i++)
  {
    kb.keys[i] = 0;
  }
}
/*
void setup1() {
  // put your setup code here, to run once:
    pinMode(D0,INPUT_PULLUP);
    pinMode(D1,INPUT_PULLUP);
    pinMode(D2,INPUT_PULLUP);
    pinMode(D3,INPUT_PULLUP);
    pinMode(D4,INPUT_PULLUP);
    pinMode(D5,INPUT_PULLUP);
    pinMode(D6,INPUT_PULLUP);
    pinMode(D7,INPUT_PULLUP);
    pinMode(D8,INPUT_PULLUP);
    pinMode(D9,INPUT_PULLUP);
}
*/
void readkeys(){
  // scan normal key and send report
  /*
      Serial.println(digitalRead(0));
      Serial.println(digitalRead(1));
      Serial.println(digitalRead(2));
      Serial.println(digitalRead(3));
      Serial.println(digitalRead(4));
      Serial.println(digitalRead(5));
      Serial.println(digitalRead(6));
      Serial.println(digitalRead(7));
      Serial.println(digitalRead(8));
      Serial.println(digitalRead(9));
      */
    if (digitalRead(0)==0){
      add(hidcode[0]);}
    if (digitalRead(1)==0){
      add(hidcode[1]);}
    if (digitalRead(2)==0){
      add(hidcode[2]);}
    if (digitalRead(3)==0){
      add(hidcode[3]);}
    if (digitalRead(4)==0){
      add(hidcode[4]);}
    if (digitalRead(5)==0){
      add(hidcode[5]);}
    if (digitalRead(6)==0){
      add(hidcode[6]);}
    if (digitalRead(7)==0){
      add(hidcode[7]);}
    if (digitalRead(8)==0){
      add(hidcode[8]);}
    if (digitalRead(9)==0){
      add(hidcode[9]);}
   //}
}

void loop() {
  // put your main code here, to run repeatedly:
  #ifdef TINYUSB_NEED_POLLING_TASK
  // Manual call tud_task since it isn't called by Core's background
  TinyUSBDevice.task();
  #endif
  if (!TinyUSBDevice.mounted()) {
    return;
  }
  readkeys();
  send();
  delay(1);
  releaseall();
}
/*
void loop1() {
  // put your main code here, to run repeatedly:
  readkeys();
}*/