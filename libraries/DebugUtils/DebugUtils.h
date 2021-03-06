/*
DebugUtils.h - Simple debugging utilities.
Copyright (C) 2011 Fabio Varesano <fabio at varesano dot net>

Ideas taken from:
http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1271517197

This program is free software: you can redistribute it and/or modify
it under the terms of the version 3 GNU General Public License as
published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef DEBUGUTILS_H
#define DEBUGUTILS_H

#ifdef DEBUG_OUTPUT
#define DEBUG_INIT(speed) Serial.begin(speed);
#define DEBUG_PRINT(str) Serial.print(str);
#define DEBUG_PRINTLN(str) Serial.println(str);
#define DEBUG_PRETTYPRINT(str)    \
  Serial.print(millis());     \
  Serial.print(": ");    \
  Serial.print(__PRETTY_FUNCTION__); \
  Serial.print(' ');      \
  Serial.print(__FILE__);     \
  Serial.print(':');      \
  Serial.print(__LINE__);     \
  Serial.print(' ');      \
  Serial.println(str);
#elif defined(WIFI_OUTPUT)
#include <UnoWiFiDevEd.h>
#define CIAO_WRITE(str) Ciao.write("mqtt","arduino/DebugUtils/debug", str);
#define DEBUG_INIT(speed) Ciao.begin(); delay(5000);
#define DEBUG_PRINT(str) CIAO_WRITE(str)
#define DEBUG_PRINTLN(str) CIAO_WRITE(str)
#define DEBUG_PRETTYPRINT(str) \
  CIAO_WRITE(millis());     \
  CIAO_WRITE(__PRETTY_FUNCTION__); \
  CIAO_WRITE(__FILE__);     \
  CIAO_WRITE(__LINE__);     \
  CIAO_WRITE(str);
#else
#define DEBUG_INIT(speed)
#define DEBUG_PRINT(str)
#define DEBUG_PRINTLN(str)
#define DEBUG_PRETTYPRINT(str)
#endif

#endif

