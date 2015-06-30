CPPUTEST_HOME = /usr/local/Cellar/cpputest/3.7.2
#ARDUINO = /Applications/Arduino.app/Contents/Resources/Java
#ARDUINO_CORE = $(ARDUINO)/hardware/arduino/avr/cores/arduino
#ARDUINO_HEADERS = $(ARDUINO)/hardware/tools/avr/avr/include
#ARDUINO_LIB = $(ARDUINO)/libraries
#ARDUINO_AVR = $(ARDUINO)/hardware/arduino/avr
#ARDUINO_AVR_LIB = $(ARDUINO_AVR)/libraries
#ARDUINO_USER = /Users/lorenl/Documents/Arduino
#ARDUINO_USER_LIB = $(ARDUINO_USER)/libraries
#CPPFLAGS += -I$(CPPUTEST_HOME)/include -I$(ARDUINO_CORE) -I$(ARDUINO_HEADERS) -I$(ARDUINO_AVR_LIB)/Wire -I$(ARDUINO_AVR_LIB)/Wire/utility -I$(ARDUINO_USER_LIB)/Adafruit_Motor_Shield_V2_Library
CPPFLAGS += -I$(CPPUTEST_HOME)/include -I. -I..
CXXFLAGS += -include $(CPPUTEST_HOME)/include/CppUTest/MemoryLeakDetectorNewMacros.h
CFLAGS += -include $(CPPUTEST_HOME)/include/CppUTest/MemoryLeakDetectorMallocMacros.h
LD_LIBRARIES = -L$(CPPUTEST_HOME)/lib -lCppUTest -lCppUTestExt


all: test spec arduino

MockArduino.o: MockArduino.c Arduino.h
	gcc $(CPPFLAGS) $(CFLAGS) -c -Wall -Werror -O2 $< -o $@

TestArduino.o: TestArduino.cpp Arduino.h
	g++ $(CPPFLAGS) $(CXXFLAGS) -c -Wall -Werror -O2 $< -o $@

arduino: TestArduino.o MockArduino.o
	g++ $(LD_LIBRARIES) -Wall -Werror -O2 $^ -o $@

#Spectrometer.cpp: Spectrometer.h

SpectrometerAdapter.o: ../SpectrometerAdapter.cpp Arduino.h ../SpectrometerAdapter.h
	g++ $(CPPFLAGS) $(CXXFLAGS) -c -Wall -Werror -O2 $< -o $@

Spectrometer.o: Spectrometer.cpp ../SpectrometerAdapter.h Spectrometer.h
	g++ $(CPPFLAGS) $(CXXFLAGS) -c -Wall -Werror -O2 $< -o $@

TestSpectrometer.o: TestSpectrometer.cpp ../SpectrometerAdapter.h Spectrometer.h
	g++ $(CPPFLAGS) $(CXXFLAGS) -c -Wall -Werror -O2 $< -o $@

TestSpectrometer.cpp: Spectrometer.h

test: test.o
	g++ $(LD_LIBRARIES) -Wall -Werror -O2 $^ -o $@

spec: TestSpectrometer.o MockArduino.o MockAdafruit_MotorShield.o SpectrometerAdapter.o Spectrometer.o
	g++ $(LD_LIBRARIES) -Wall -Werror -O2 $^ -o $@

.cpp.o:
	g++ $(CPPFLAGS) $(CXXFLAGS) -c -Wall -Werror -O2 $< -o $@

run: all
	#./test -c -v
	./spec -c -v
	./arduino -c -v

clean:
	rm -f *.o test
