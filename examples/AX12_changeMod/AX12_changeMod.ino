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

#include <AX12_UNO_writeOnly.h>

AX12 xel(7);      // D7핀을 TX로 설정 (변경가능)

int id = ID_ALL;  // ID_ALL = 254 (브로드캐스팅)

void setup() {
  xel.begin(9600);
  delay(100);
  xel.changeMod(id,false); // true : 서보(관절)모드, false : DC(바퀴)모드
}

void loop() {
  xel.run(id,800,true);   // run(id,speed,cw)
  delay(500);
  xel.run(id,0,true);      // true : CW방향 회전, false : CCW방향 회전
  delay(500);
  xel.run(id,800,false);
  delay(500);
  xel.run(id,0,false);
  delay(500);
}
