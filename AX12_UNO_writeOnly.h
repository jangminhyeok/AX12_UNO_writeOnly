/*
==============================================================
  AX12_UNO : control AX12 for UNO
  Arduino Uno를 위한 AX-12 제어 라이브러리
==============================================================
  Version : 006-W
  Comment : Rx를 무시, 다이나믹셀에 데이터 쓰기만 가능한 테스트 버전
==============================================================
  Based on :
  "ArbotiX library for AX/RX control" by Michael E. Ferguson
  "SendOnlySoftwareSerial" by Nick Gammon
==============================================================
  Copyright (c) 2016 CHO Hwiwon @ 서울로봇아카데미.  All right reserved.

  This library is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation; either version 2.1 of the License, or (at your option) any later version.
  이 라이브러리는 자유 소프트웨어입니다. 소프트웨어의 피양도자는 자유 소프트웨어 재단이 공표한 GNU 약소 일반 공중 사용 허가서 2.1판 또는 그 이후 판을 임의로 선택해서, 그 규정에 따라 라이브러리를 개작하거나 재배포할 수 있습니다.
  This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
  이 라이브러리는 유용하게 사용될 수 있으리라는 희망에서 배포되고 있지만, 특정한 목적에 맞는 적합성 여부나 판매용으로 사용할 수 있으리라는 묵시적인 보증을 포함한 어떠한 형태의 보증도 제공하지 않습니다. 보다 자세한 사항에 대해서는 GNU 약소 일반 공중 사용 허가서를 참고하시기 바랍니다.
  You should have received a copy of the GNU Lesser General Public License along with this library; if not, write to the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
  GNU 약소 일반 공중 사용 허가서는 이 라이브러리와 함께 제공됩니다. 만약, 이 문서가 누락되어 있다면 자유 소프트웨어 재단(Free Software Foundation, Inc.)으로 문의하시기 바랍니다.
*/

#ifndef AX12_UNO_writeOnly_h
#define AX12_UNO_writeOnly_h

#include "SendOnlySoftwareSerial.h"

#define AX12_BUFFER_SIZE            32

/** EEPROM AREA **/
#define AX_MODEL_NUMBER_L           0
#define AX_MODEL_NUMBER_H           1
#define AX_VERSION                  2
#define AX_ID                       3
#define AX_BAUD_RATE                4
#define AX_RETURN_DELAY_TIME        5
#define AX_CW_ANGLE_LIMIT_L         6
#define AX_CW_ANGLE_LIMIT_H         7
#define AX_CCW_ANGLE_LIMIT_L        8
#define AX_CCW_ANGLE_LIMIT_H        9
#define AX_SYSTEM_DATA2             10
#define AX_LIMIT_TEMPERATURE        11
#define AX_DOWN_LIMIT_VOLTAGE       12
#define AX_UP_LIMIT_VOLTAGE         13
#define AX_MAX_TORQUE_L             14
#define AX_MAX_TORQUE_H             15
#define AX_RETURN_LEVEL             16
#define AX_ALARM_LED                17
#define AX_ALARM_SHUTDOWN           18
#define AX_OPERATING_MODE           19
#define AX_DOWN_CALIBRATION_L       20
#define AX_DOWN_CALIBRATION_H       21
#define AX_UP_CALIBRATION_L         22
#define AX_UP_CALIBRATION_H         23
/** RAM AREA **/
#define AX_TORQUE_ENABLE            24
#define AX_LED                      25
#define AX_CW_COMPLIANCE_MARGIN     26
#define AX_CCW_COMPLIANCE_MARGIN    27
#define AX_CW_COMPLIANCE_SLOPE      28
#define AX_CCW_COMPLIANCE_SLOPE     29
#define AX_GOAL_POSITION_L          30
#define AX_GOAL_POSITION_H          31
#define AX_GOAL_SPEED_L             32
#define AX_GOAL_SPEED_H             33
#define AX_TORQUE_LIMIT_L           34
#define AX_TORQUE_LIMIT_H           35
#define AX_PRESENT_POSITION_L       36
#define AX_PRESENT_POSITION_H       37
#define AX_PRESENT_SPEED_L          38
#define AX_PRESENT_SPEED_H          39
#define AX_PRESENT_LOAD_L           40
#define AX_PRESENT_LOAD_H           41
#define AX_PRESENT_VOLTAGE          42
#define AX_PRESENT_TEMPERATURE      43
#define AX_REGISTERED_INSTRUCTION   44
#define AX_PAUSE_TIME               45
#define AX_MOVING                   46
#define AX_LOCK                     47
#define AX_PUNCH_L                  48
#define AX_PUNCH_H                  49
/** Status Return Levels **/
#define AX_RETURN_NONE              0
#define AX_RETURN_READ              1
#define AX_RETURN_ALL               2
/** Instruction Set **/
#define AX_PING                     1
#define AX_READ_DATA                2
#define AX_WRITE_DATA               3
#define AX_REG_WRITE                4
#define AX_ACTION                   5
#define AX_RESET                    6
#define AX_SYNC_WRITE               131
/** Error Levels **/
#define ERR_NONE                    0
#define ERR_VOLTAGE                 1
#define ERR_ANGLE_LIMIT             2
#define ERR_OVERHEATING             4
#define ERR_RANGE                   8
#define ERR_CHECKSUM                16
#define ERR_OVERLOAD                32
#define ERR_INSTRUCTION             64
/** AX-S1 **/
#define AX_LEFT_IR_DATA             26
#define AX_CENTER_IR_DATA           27
#define AX_RIGHT_IR_DATA            28
#define AX_LEFT_LUMINOSITY          29
#define AX_CENTER_LUMINOSITY        30
#define AX_RIGHT_LUMINOSITY         31
#define AX_OBSTACLE_DETECTION       32
#define AX_BUZZER_INDEX             40

#define ID_ALL    254
#define SERVO     1
#define DC        0
#define CW        1
#define CCW       0

class AX12 : public SendOnlySoftwareSerial {
private:
  void setRegister(int id, int addr, int data);
  void setRegister_2byte(int id, int addr, int data);

public:
  long baudrate;
  AX12(uint8_t tx_pin);
  ~AX12();

  void begin(long baud);
  void angleWrite(int id, int angle);
  void torqueWrite(int id, bool isHigh);
  void torqueLimitWrite(int id, int limit);
  void setSpeed(int id, int speed);
  void changeMod(int id, bool isServo);
  void run(int id, int speed, bool isCw);
};

#endif // AX12_UNO_writeOnly_h