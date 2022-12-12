/*
==============================================================
  AX12_UNO : control AX12 for UNO [WRITE ONLY]
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

#include "AX12_UNO_writeOnly.h"

// private
void AX12::setRegister(int id, int addr, int data) {
  int checksum = ~((id + 4 + AX_WRITE_DATA + addr + (data&0xff)) % 256);

  write(0xFF);
  write(0xFF);
  write(id);
  write(4);
  write(AX_WRITE_DATA);
  write(addr);
  write((data&0xff));
  write(checksum);
}

void AX12::setRegister_2byte(int id, int addr, int data) {
  int checksum = ~((id + 5 + AX_WRITE_DATA + addr + (data&0xFF) + ((data&0xFF00)>>8)) % 256);

  write(0xFF);
  write(0xFF);
  write(id);
  write(5);
  write(AX_WRITE_DATA);
  write(addr);
  write((data&0xff));
  write(((data&0xff00)>>8));
  write(checksum);
}

// public

AX12::AX12(uint8_t tx_pin) : SendOnlySoftwareSerial(tx_pin)  {}

AX12::~AX12() {}

void AX12::begin(long baud) {
  baudrate = baud;
  SendOnlySoftwareSerial::begin(baud);
}

void AX12::angleWrite(int id, int angle) {
  if(angle < 0) angle = 0;
  if(angle > 1023) angle = 1023;

  setRegister_2byte(id, AX_GOAL_POSITION_L, angle);
}

void AX12::torqueWrite(int id, bool isHigh) {
  setRegister(id, AX_TORQUE_ENABLE, isHigh);
}
void AX12::torqueLimitWrite(int id, int limit) {
  setRegister_2byte(id, AX_TORQUE_LIMIT_L, limit);
}

void AX12::setSpeed(int id, int speed) {
  if(speed < 0) speed = 0;
  if(speed > 1023) speed = 1023;

  setRegister_2byte(id, AX_GOAL_SPEED_L, speed); 
}

void AX12::changeMod(int id, bool isServo) {
  short t = 0;
  if(isServo) {
    setRegister_2byte(id, AX_CW_ANGLE_LIMIT_L, 0);
    while(t++ < 2000);
    setRegister_2byte(id, AX_CCW_ANGLE_LIMIT_L, 1023);
    while(t-- > 0);
  }
  else {
    setRegister_2byte(id, AX_CW_ANGLE_LIMIT_L, 0);
    while(t++ < 2000);
    setRegister_2byte(id, AX_CCW_ANGLE_LIMIT_L, 0);
    while(t-- > 0);
  }
}

void AX12::run(int id, int speed, bool isCw) {
  if(isCw)
    setRegister_2byte(id, AX_GOAL_SPEED_L, speed); 
  else
    setRegister_2byte(id, AX_GOAL_SPEED_L, speed+1024); 
}