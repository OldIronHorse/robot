BOARD_TAG=uno
ARDUINO_PORT=/dev/ttyACM*
ARDUINO_LIBS=Wire wiinunchuk
USER_LIB_PATH=../../libraries
OS := $(shell uname)
ifeq ($(OS), Darwin)
ARDUINO_DIR=/Applications/Arduino.app/Contents/java
include /usr/local/opt/arduino-mk/Arduino.mk
else
ARDUINO_DIR=/usr/share/arduino
include /usr/share/arduino/Arduino.mk
endif
include $(USER_LIB_PATH)/testing/testing.mk
