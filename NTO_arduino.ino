#define REMOTEXY_MODE__HARDSERIAL

#define NEW_REPORT    0x01
#define NEW_FILL      0x02
#define CHECK_ENABLE  0x03
#define CHECK_WHICH   0x04
#define TECH_NOTIFY   0x05
#define ADD_BONUS     0x06

#include <Wire.h>
#include <SparkFun_VL6180X.h>
#include "Adafruit_TCS34725.h"
#include <TroykaOLED.h>
#include <Servo.h>
#include <SPI.h>
#include <Adafruit_PN532.h>

uint8_t SendReport(uint8_t * servo, uint8_t * rgb, uint8_t * level) {
  uint8_t cmd = NEW_REPORT;
  uint8_t ans = 0;
  Serial2.write(&cmd, 1);
  Serial2.write(servo, 3);
  Serial2.write(rgb, 3);
  Serial2.write(level, 3);

  if (Serial2.readBytes(&ans, 1) == 1) {
    return ans;
  }
  else return 0;
}

uint8_t SendFill(uint8_t * fill) {
  uint8_t cmd = NEW_FILL;
  uint8_t ans = 0;
  Serial2.write(&cmd, 1);
  Serial2.write(fill, 3);

  if (Serial2.readBytes(&ans, 1) == 1) {
    return ans;
  }
  else return 0;
}

uint8_t GetEnabled(void) {
  uint8_t cmd = CHECK_ENABLE;
  uint8_t ans = 0;
  Serial2.write(&cmd, 1);

  if (Serial2.readBytes(&ans, 1) == 1) {
    return ans;
  }
  else return 0;
}

uint8_t TechNotification(void) {
  uint8_t cmd = TECH_NOTIFY;
  uint8_t ans = 0;
  Serial2.write(&cmd, 1);

  if (Serial2.readBytes(&ans, 1) == 1) {
    return ans;
  }
  else return 0;
}

uint8_t AddBonus(uint8_t * card_id, int32_t bonus) {
  uint8_t cmd = ADD_BONUS;
  uint8_t ans = 0;
  Serial2.write(&cmd, 1);
  Serial2.write(card_id, 7);
  Serial2.write((uint8_t *)&bonus, 4);

  if (Serial2.readBytes(&ans, 1) == 1) {
    return ans;
  }
  else return 0;
}

#include <RemoteXY.h>

#define REMOTEXY_SERIAL Serial
#define REMOTEXY_SERIAL_SPEED 9600

#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =   // 669 bytes
{ 255, 17, 0, 9, 0, 150, 2, 16, 2, 1, 130, 0, 2, 29, 59, 9, 16, 130, 0, 2,
  20, 59, 9, 16, 130, 0, 2, 11, 59, 9, 16, 2, 1, 49, 13, 10, 5, 2, 26, 31,
  31, 79, 75, 0, 69, 82, 82, 0, 2, 1, 49, 22, 10, 5, 2, 26, 31, 31, 79, 75,
  0, 69, 82, 82, 0, 2, 1, 49, 31, 10, 5, 2, 26, 31, 31, 79, 75, 0, 69, 82,
  82, 0, 130, 2, 11, 13, 17, 5, 26, 129, 0, 12, 14, 15, 3, 2, 83, 69, 82, 86,
  79, 32, 49, 0, 130, 2, 11, 22, 17, 5, 26, 129, 0, 12, 23, 15, 3, 2, 83, 69,
  82, 86, 79, 32, 50, 0, 130, 2, 11, 31, 17, 5, 26, 129, 0, 12, 32, 15, 3, 2,
  83, 69, 82, 86, 79, 32, 51, 0, 130, 0, 2, 3, 59, 6, 16, 129, 0, 18, 4, 26,
  4, 26, 68, 105, 97, 103, 110, 111, 115, 116, 105, 99, 115, 0, 130, 0, 2, 59, 59, 9,
  16, 130, 0, 2, 50, 59, 9, 16, 130, 0, 2, 41, 59, 9, 16, 2, 1, 49, 43, 10,
  5, 2, 26, 31, 31, 79, 75, 0, 69, 82, 82, 0, 2, 1, 49, 52, 10, 5, 2, 26,
  31, 31, 79, 75, 0, 69, 82, 82, 0, 2, 1, 49, 61, 10, 5, 2, 26, 31, 31, 79,
  75, 0, 69, 82, 82, 0, 130, 2, 11, 43, 17, 5, 26, 129, 0, 14, 44, 10, 3, 2,
  82, 71, 66, 32, 49, 0, 130, 2, 11, 52, 17, 5, 26, 129, 0, 14, 53, 10, 3, 2,
  82, 71, 66, 32, 50, 0, 130, 2, 11, 61, 17, 5, 26, 129, 0, 14, 62, 10, 3, 2,
  82, 71, 66, 32, 51, 0, 70, 16, 39, 43, 5, 5, 26, 36, 0, 1, 0, 32, 43, 5,
  5, 2, 31, 76, 69, 68, 0, 1, 0, 32, 52, 5, 5, 2, 31, 76, 69, 68, 0, 1,
  0, 32, 61, 5, 5, 2, 31, 76, 69, 68, 0, 70, 16, 39, 52, 5, 5, 26, 36, 0,
  70, 16, 39, 61, 5, 5, 26, 36, 0, 130, 0, 42, 71, 19, 17, 16, 130, 0, 22, 71,
  20, 17, 16, 130, 0, 2, 71, 20, 17, 16, 2, 1, 10, 81, 10, 5, 2, 26, 31, 31,
  79, 75, 0, 69, 82, 82, 0, 2, 1, 30, 81, 10, 5, 2, 26, 31, 31, 79, 75, 0,
  69, 82, 82, 0, 2, 1, 50, 81, 10, 5, 2, 26, 31, 31, 79, 75, 0, 69, 82, 82,
  0, 130, 2, 4, 73, 16, 5, 26, 129, 0, 5, 74, 13, 3, 2, 76, 69, 86, 69, 76,
  32, 49, 0, 130, 2, 24, 73, 16, 5, 26, 129, 0, 25, 74, 13, 3, 2, 76, 69, 86,
  69, 76, 32, 50, 0, 130, 2, 44, 73, 15, 5, 26, 129, 0, 45, 74, 13, 3, 2, 76,
  69, 86, 69, 76, 32, 51, 0, 70, 16, 4, 43, 5, 5, 26, 119, 0, 70, 16, 4, 52,
  5, 5, 26, 119, 0, 70, 16, 4, 61, 5, 5, 26, 119, 0, 70, 16, 4, 81, 5, 5,
  26, 119, 0, 70, 16, 44, 81, 5, 5, 26, 119, 0, 70, 16, 24, 81, 5, 5, 26, 119,
  0, 1, 1, 8, 90, 20, 8, 27, 16, 83, 69, 78, 68, 32, 82, 69, 80, 79, 82, 84,
  0, 1, 1, 33, 90, 26, 8, 27, 31, 69, 88, 73, 84, 32, 68, 73, 65, 71, 78, 79,
  83, 84, 73, 67, 83, 0, 2, 1, 33, 22, 13, 5, 2, 26, 31, 31, 79, 80, 69, 78,
  0, 67, 76, 79, 83, 69, 0, 2, 1, 33, 13, 13, 5, 2, 26, 31, 31, 79, 80, 69,
  78, 0, 67, 76, 79, 83, 69, 0, 2, 1, 33, 31, 13, 5, 2, 26, 31, 31, 79, 80,
  69, 78, 0, 67, 76, 79, 83, 69, 0
};

struct {

  // input variables
  uint8_t servo_1_status; // =1 if switch ON and =0 if OFF
  uint8_t servo_2_status; // =1 if switch ON and =0 if OFF
  uint8_t servo_3_status; // =1 if switch ON and =0 if OFF
  uint8_t rgb_1_status; // =1 if switch ON and =0 if OFF
  uint8_t rgb_2_status; // =1 if switch ON and =0 if OFF
  uint8_t rgb_3_status; // =1 if switch ON and =0 if OFF
  uint8_t rgb_led_1_btn; // =1 if button pressed, else =0
  uint8_t rgb_led_2_btn; // =1 if button pressed, else =0
  uint8_t rgb_led_3_btn; // =1 if button pressed, else =0
  uint8_t level_1_status; // =1 if switch ON and =0 if OFF
  uint8_t level_2_status; // =1 if switch ON and =0 if OFF
  uint8_t level_3_status; // =1 if switch ON and =0 if OFF
  uint8_t send_report_btn; // =1 if button pressed, else =0
  uint8_t exit_btn; // =1 if button pressed, else =0
  uint8_t servo_2_move; // =1 if switch ON and =0 if OFF
  uint8_t servo_1_move; // =1 if switch ON and =0 if OFF
  uint8_t servo_3_move; // =1 if switch ON and =0 if OFF

  // output variables
  uint8_t rgb_led_1; // led state 0 .. 1
  uint8_t rgb_led_2; // led state 0 .. 1
  uint8_t rgb_led_3; // led state 0 .. 1
  uint8_t rgb_detect_1; // led state 0 .. 1
  uint8_t rgb_detect_2; // led state 0 .. 1
  uint8_t rgb_detect_3; // led state 0 .. 1
  uint8_t level_detect_1; // led state 0 .. 1
  uint8_t level_detect_3; // led state 0 .. 1
  uint8_t level_detect_2; // led state 0 .. 1

  // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0

} RemoteXY;
#pragma pack(pop)
uint8_t * level_detect[3] = { &(RemoteXY.level_detect_1), &(RemoteXY.level_detect_2), &(RemoteXY.level_detect_3) };
uint8_t * rgb_detect[3]   = { &(RemoteXY.rgb_detect_1),   &(RemoteXY.rgb_detect_2),   &(RemoteXY.rgb_detect_3) };

#define PIN_RGB_LED_1_BTN 8
#define PIN_RGB_LED_2_BTN 12
#define PIN_RGB_LED_3_BTN 13

struct user {
  String name;
  String status;
  uint8_t id[8];
  int32_t balance;
};

user current_user;

uint8_t CheckWho(uint8_t * card_id) {
  uint8_t cmd = CHECK_WHICH;
  uint8_t ans = 0;
  uint8_t length = 0;
  uint8_t name[32];
  uint8_t fname[32];
  int32_t balance = 0;
  Serial2.write(&cmd, 1);
  Serial2.write(card_id, 7);

  if (Serial2.readBytes(&ans, 1) != 1) return 0;
  if (ans) {
    if (Serial2.readBytes(&length, 1) != 1) return 0;
    if (Serial2.readBytes(name, length) != length) return 0;
    if (Serial2.readBytes((uint8_t *)&balance, 4) != 4) return 0;

    sscanf(name, "%s", fname);
    current_user.name = (const uint8_t *)fname;
    current_user.balance = balance;
    memcpy(current_user.id, card_id, 7);
    if (balance == -1) current_user.status = "ADM";
    else current_user.status = "USR";
    return 1;
  }
  else {
    return 0;
  }
}

void ResetUser(void) {
  current_user.name = "NaN";
  current_user.status = "NaN";
  current_user.balance = 0;
}

#define SENSORS_INIT_ATTEMPTS         10

#define PN532_PIN                     9

#define DIST_DETECT_THRES             30

#define COLOR_DETECT_THRES            120
#define COLOR_REJECT_THRES            100

#define DISP_HEADER             "|   1  |  2  |  3   | "

#define DISP_CONT_STATUS_NO_PROXIM        "E 20"
#define DISP_CONT_STATUS_NO_COLOR         "E 21"
#define DISP_CONT_STATUS_NO_SENS          "E 22"
#define DISP_CONT_STATUS_OK               "OKAY"
#define DISP_CONT_STATUS_Y                16
#define DISP_CONT_STATUS_X                12
#define DISP_CONT_STATUS_STEP             40

#define DISP_CONT_CLOSED                  "CLOS"
#define DISP_CONT_WRONG                   "WRNG"
#define DISP_CONT_FULL                    "FULL"
#define DISP_CONT_OPEN                    "OPEN"
#define DISP_CONT_OPEN_Y                  32
#define DISP_CONT_OPEN_X                  12
#define DISP_CONT_OPEN_STEP               40

#define DISP_LABEL_USER_X                 12
#define DISP_LABEL_USER_Y                 48
#define DISP_NAME_USER_X                  30
#define DISP_NAME_USER_Y                  48

#define DISP_BALANCE_LABEL                "Bonus "
#define DISP_BALANCE_LABEL_X              12
#define DISP_BALANCE_LABEL_Y              56
#define DISP_BALANCE_X                    54
#define DISP_BALANCE_Y                    56

#define ACTIVE      1
#define NOT_ACTIVE  0

void(* resetFunc)(void) = 0;

uint8_t mux_pins[3] = { 2, 4, 7 };

void MUX_Free(void) {
  digitalWrite(mux_pins[0], HIGH);
  digitalWrite(mux_pins[1], HIGH);
  digitalWrite(mux_pins[2], HIGH);
}

void MUX_Select(uint8_t channel) {
  for (uint8_t iter = 0; iter < 3; iter++) {
    if (channel & (1 << iter))
      digitalWrite(mux_pins[iter], HIGH);
    else
      digitalWrite(mux_pins[iter], LOW);
  }
  delay(5);
}

Adafruit_PN532    card_module(PN532_PIN, 100);

TroykaOLED oled_disp(0x3C);

uint8_t           color_led[3]      = { 8, 12, 13 };
Adafruit_TCS34725 color_hndl[3];
uint8_t           color_addr[3]     = { 3, 4, 5 };
uint8_t           color_active[3]   = { NOT_ACTIVE, NOT_ACTIVE, NOT_ACTIVE };

uint8_t           proxim_active[3]  = { NOT_ACTIVE, NOT_ACTIVE, NOT_ACTIVE };
uint8_t           proxim_addr[3]    = { 0, 1, 2 };
VL6180x *         proxim_hndl[3];

uint8_t           servo_addr[3]     = { 3, 5, 6 };
Servo             servo_hndl[3];

struct DRep_t {
  uint8_t servo[3];
  uint8_t rgb[3];
  uint8_t proxim[3];

  uint8_t send() {
    SendReport(this->servo, this->rgb, this->proxim);
    return 1;
  }
};

void setup() {

  Wire.begin();

  pinMode(mux_pins[0], OUTPUT);
  pinMode(mux_pins[1], OUTPUT);
  pinMode(mux_pins[2], OUTPUT);
  MUX_Free();

  Serial1.begin(57600);
  Serial2.begin(115200);
  Serial2.setTimeout(10000);

  // RFID module initialization

  card_module.begin();
  for (uint8_t attempt = 0; card_module.getFirmwareVersion() == 0; attempt++) {
    Serial1.println("RFID FAILURE");
    if (attempt == SENSORS_INIT_ATTEMPTS) {
      resetFunc();
    }
  }
  card_module.SAMConfig();

  // Display intialization

  oled_disp.begin();
  oled_disp.invertText();
  oled_disp.invertDisplay();
  oled_disp.setFont(font6x8);
  oled_disp.print(DISP_HEADER, 0, 0);

  oled_disp.print("|------|-----|------| ", 0, 8);
  oled_disp.print("|      |     |      | ", 0, 16);
  oled_disp.print("|------|-----|------| ", 0, 24);
  oled_disp.print("|      |     |      | ", 0, 32);
  oled_disp.print("|------+-----+------| ", 0, 40);
  oled_disp.print("|                   | ", 0, 48);
  oled_disp.print("|                   | ", 0, 56);

  for (uint8_t iter = 0; iter < 3; iter++) {

    // Color sensors initialization

    pinMode(color_led[iter], OUTPUT);
    MUX_Select(color_addr[iter]);

    for (uint8_t attempt = 0; attempt < SENSORS_INIT_ATTEMPTS; attempt++) {
      if (color_hndl[iter].begin()) {
        color_active[iter] = ACTIVE;
        break;
      }
      else {
        color_active[iter] = ACTIVE;
      }
      delay(100);
    }

    // Proximity sensors initialization

    MUX_Select(proxim_addr[iter]);
    proxim_hndl[iter] = new VL6180x(0x29);
    for (uint8_t attempt = 0; attempt < SENSORS_INIT_ATTEMPTS; attempt++) {
      if (proxim_hndl[iter]->VL6180xInit()) {
        proxim_active[iter] = ACTIVE;
        proxim_hndl[iter]->VL6180xDefautSettings();
      }
      else {
        proxim_hndl[iter]->VL6180xDefautSettings();
        proxim_active[iter] = ACTIVE;
        break;
      }
      delay(100);
    }

    if ((proxim_active[iter] == NOT_ACTIVE) && (color_active[iter] == NOT_ACTIVE)) oled_disp.print(DISP_CONT_STATUS_NO_SENS, DISP_CONT_STATUS_X + iter * DISP_CONT_STATUS_STEP, DISP_CONT_STATUS_Y);
    else if ((proxim_active[iter]) && (color_active[iter])) oled_disp.print(DISP_CONT_STATUS_OK, DISP_CONT_STATUS_X + iter * DISP_CONT_STATUS_STEP, DISP_CONT_STATUS_Y);
    else if (proxim_active[iter] == NOT_ACTIVE) oled_disp.print(DISP_CONT_STATUS_NO_PROXIM, DISP_CONT_STATUS_X + iter * DISP_CONT_STATUS_STEP, DISP_CONT_STATUS_Y);
    else oled_disp.print(DISP_CONT_STATUS_NO_COLOR, DISP_CONT_STATUS_X + iter * DISP_CONT_STATUS_STEP, DISP_CONT_STATUS_Y);

    oled_disp.print(DISP_CONT_CLOSED, DISP_CONT_OPEN_X + iter * DISP_CONT_OPEN_STEP, DISP_CONT_OPEN_Y);
    // Servo initialization

    servo_hndl[iter].attach(servo_addr[iter]);
    servo_hndl[iter].write(0);
  }

  RemoteXY_Init();
}

float col[3];
uint8_t dist;
uint8_t rfid[8];
uint8_t rfid_len;
uint8_t buff[64];

uint8_t auto_log_out = 0;

uint32_t trash_check[3] = { 0, 0, 0 };

uint8_t fill_data[3] = { 0, 0, 0 };

void loop() {
  MUX_Select(proxim_addr[0]);
  fill_data[0] = 0;
  fill_data[0] = 100 - (uint8_t)((float)(proxim_hndl[0]->getDistance()) / (float)255 * (float)100);
  MUX_Select(proxim_addr[1]);
  fill_data[1] = 0;
  fill_data[1] = 100 - (uint8_t)((float)(proxim_hndl[1]->getDistance()) / (float)255 * (float)100);
  MUX_Select(proxim_addr[2]);
  fill_data[2] = 0;
  fill_data[2] = 100 - (uint8_t)((float)(proxim_hndl[2]->getDistance()) / (float)255 * (float)100);
  SendFill(fill_data);

  if (GetEnabled() != 1){
    oled_disp.print("MAINTENANCE     ", DISP_LABEL_USER_X, DISP_LABEL_USER_Y);
    delay(1000);
  }
  else{
    oled_disp.print("                ", DISP_LABEL_USER_X, DISP_LABEL_USER_Y);
    if (card_module.readPassiveTargetID(PN532_MIFARE_ISO14443A, rfid, &rfid_len, 250)) {
      if (CheckWho(rfid)){
        Serial1.print("Card: ");
        card_module.PrintHex(rfid, rfid_len);
        Serial1.println(" ");
        oled_disp.print(current_user.status + " " + current_user.name, DISP_LABEL_USER_X, DISP_LABEL_USER_Y);
        if (current_user.status == "USR") {
          digitalWrite(color_led[0], HIGH);
          digitalWrite(color_led[1], HIGH);
          digitalWrite(color_led[2], HIGH);
          oled_disp.print(String(DISP_BALANCE_LABEL) + " " + String(current_user.balance), DISP_BALANCE_LABEL_X, DISP_BALANCE_LABEL_Y);
          while (1) {
            for (uint8_t iter = 0; iter < 3; iter++) {
              if ((proxim_active[iter]) && (color_active[iter])) {
                MUX_Select(proxim_addr[iter]);
                dist = 0;
                dist = proxim_hndl[iter]->getDistance();
                MUX_Select(color_addr[iter]);
                color_hndl[iter].getRGB(col, col + 1, col + 2);
                if (dist < DIST_DETECT_THRES) {
                  servo_hndl[iter].write(0);
                  if (trash_check[iter] > 5) {
                    current_user.balance += 10;
                    AddBonus(current_user.id, 10);
                    oled_disp.print(String(DISP_BALANCE_LABEL) + " " + String(current_user.balance), DISP_BALANCE_LABEL_X, DISP_BALANCE_LABEL_Y);
                  }
                  trash_check[iter] = 0;
                  oled_disp.print(DISP_CONT_FULL, DISP_CONT_OPEN_X + DISP_CONT_OPEN_STEP * iter, DISP_CONT_OPEN_Y);
                }
                else if ((dist >= DIST_DETECT_THRES) && ((col[iter] > COLOR_DETECT_THRES) && (col[(iter + 1) % 3] < COLOR_REJECT_THRES) && (col[(iter + 2) % 3] < COLOR_REJECT_THRES))) {
                  trash_check[iter]++;
                  servo_hndl[iter].write(180);
                  auto_log_out = 0;
                  oled_disp.print(DISP_CONT_OPEN, DISP_CONT_OPEN_X + DISP_CONT_OPEN_STEP * iter, DISP_CONT_OPEN_Y);
                }
                else {
                  if (trash_check[iter] > 5) {
                    current_user.balance += 10;
                    AddBonus(current_user.id, 10);
                    oled_disp.print(String(DISP_BALANCE_LABEL) + " " + String(current_user.balance), DISP_BALANCE_LABEL_X, DISP_BALANCE_LABEL_Y);
                  }
                  trash_check[iter] = 0;
                  servo_hndl[iter].write(0);
                  oled_disp.print(DISP_CONT_WRONG, DISP_CONT_OPEN_X + DISP_CONT_OPEN_STEP * iter, DISP_CONT_OPEN_Y);
                }
              }
            }
            if (auto_log_out++ >= 10) {
              ResetUser();
              oled_disp.print("                  ", DISP_LABEL_USER_X, DISP_LABEL_USER_Y);
              oled_disp.print("                  ", DISP_BALANCE_LABEL_X, DISP_BALANCE_LABEL_Y);
              auto_log_out = 0;
              break;
            }
            delay(500);
          }
        }
        else if (current_user.status == "ADM") {
          servo_hndl[0].write(180);
          servo_hndl[1].write(180);
          servo_hndl[2].write(180);
          while (1) {
            RemoteXY_Handler();
            delay(100);
  
            if (!(RemoteXY_isConnected())) {
              if (auto_log_out++ >= 50) {
                ResetUser();
                oled_disp.print("                  ", DISP_LABEL_USER_X, DISP_LABEL_USER_Y);
                oled_disp.print("                  ", DISP_BALANCE_LABEL_X, DISP_BALANCE_LABEL_Y);
                auto_log_out = 0;
                servo_hndl[0].write(0);
                servo_hndl[1].write(0);
                servo_hndl[2].write(0);
                break;
              }
              delay(40);
              continue;
            }
  
            auto_log_out = 0;
  
            if (RemoteXY.exit_btn) {
              ResetUser();
              oled_disp.print("                  ", DISP_LABEL_USER_X, DISP_LABEL_USER_Y);
              oled_disp.print("                  ", DISP_BALANCE_LABEL_X, DISP_BALANCE_LABEL_Y);
              auto_log_out = 0;
              servo_hndl[0].write(0);
              servo_hndl[1].write(0);
              servo_hndl[2].write(0);
              RemoteXY.exit_btn = 0;
              break;
            }
  
            if (RemoteXY.send_report_btn) {
              DRep_t report;
              report.servo[0]  = RemoteXY.servo_1_status; report.servo[1] = RemoteXY.servo_2_status; report.servo[2] = RemoteXY.servo_3_status;
              report.rgb[0]    = RemoteXY.rgb_1_status; report.rgb[1] = RemoteXY.rgb_2_status; report.rgb[2] = RemoteXY.rgb_3_status;
              report.proxim[0] = RemoteXY.level_1_status; report.proxim[1] = RemoteXY.level_2_status; report.proxim[2] = RemoteXY.level_3_status;
              oled_disp.print(" Report Sent     ", DISP_BALANCE_LABEL_X, DISP_BALANCE_LABEL_Y);
              report.send();
            }
  
            digitalWrite(PIN_RGB_LED_1_BTN, (RemoteXY.rgb_led_1_btn == 0) ? LOW : HIGH);
            digitalWrite(PIN_RGB_LED_2_BTN, (RemoteXY.rgb_led_2_btn == 0) ? LOW : HIGH);
            digitalWrite(PIN_RGB_LED_3_BTN, (RemoteXY.rgb_led_3_btn == 0) ? LOW : HIGH);
  
            servo_hndl[0].write((RemoteXY.servo_1_move == 1) ? 180 : 0);
            servo_hndl[1].write((RemoteXY.servo_2_move == 1) ? 180 : 0);
            servo_hndl[2].write((RemoteXY.servo_3_move == 1) ? 180 : 0);
  
            for (uint8_t iter = 0; iter < 3; iter++) {
              MUX_Select(proxim_addr[iter]);
              dist = 0;
              dist = proxim_hndl[iter]->getDistance();
              MUX_Select(color_addr[iter]);
              color_hndl[iter].getRGB(col, col + 1, col + 2);
  
              if (dist < DIST_DETECT_THRES) *(level_detect[iter]) = 1;
              else                          *(level_detect[iter]) = 0;
  
              if ((col[iter] > COLOR_DETECT_THRES) && (col[(iter + 1) % 3] < COLOR_REJECT_THRES) && (col[(iter + 2) % 3] < COLOR_REJECT_THRES))
                *(rgb_detect[iter]) = 1;
              else
                *(rgb_detect[iter]) = 0;
            }
          }
        }
      }
    }
  }
}
