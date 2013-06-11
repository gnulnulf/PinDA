#############################################################################
#
# Makefile for PinDA examples on Raspberry Pi
#
# License: GPL (General Public License)
# Author:  gnulnulf <arco@appeltaart.mine.nu>
# Date:    2013/06/05 (version 1.0)
#
# Description:
# ------------
# use make all and make install to install the examples
# You can change the install directory by editing the prefix line
#
prefix := /opt/pinda
RASPBERRY= -DRASPBERRY

# The recommended compiler flags for the Raspberry Pi
CCFLAGS= $(RASPBERRY) -Wall -Ofast -mfpu=vfp -mfloat-abi=hard -march=armv6zk -mtune=arm1176jzf-s
GPP=g++
#CCFLAGS=

# define all programs
#PROGRAMS = scanner pingtest pongtest
PROGRAMS = mcptest
SOURCES = $(wildcard *.cpp)
SOURCES += $(wildcard ./rpi/*.cpp)
#OBJECTS = build/rpi/$(SOURCES:.cpp=.o)
OBJECTS=$(join $(addprefix build/rpi/, $(dir $(SOURCES))), $(notdir $(SOURCES:.cpp=.o))) 
//OBJECTS+=$(BUILDDIR)mcptest.o
//OBJECTSRPI=$(join $(addprefix build/rpi/, $(dir $(SOURCES))), $(notdir $(SOURCES:.cpp=.o))) 


all: ${PROGRAMS}
	@echo [ALL $(OBJECTS)]


#
#${PROGRAMS}: ${SOURCES}
#	@g++ ${CCFLAGS} -Wall -I. -L. $@.cpp -o $@

build/rpi/mcptest.o:
	@echo [COMPILE i $<]
	@$(GPP) ${CCFLAGS} -fPIC -o $@ -c mcptest.ino $(LDFLAGS) $(LDLIBS)

build/rpi/%.o:%.cpp
	@echo [COMPILE b $<]
	@$(GPP) ${CCFLAGS} -fPIC -o $@ -c $< $(LDFLAGS) $(LDLIBS)


mcptest: $(OBJECTS)
	@echo [CREATE $@ ]
	@$(GPP) ${CCFLAGS} -o build/rpi/$@ $< $(LDFLAGS) $(LDLIBS) build/rpi/mcptest.o $(OBJECTS)

	
.c.o:
	@echo [GPP] $<
	@$(GPP)  $(CCFLAGS) -fPIC -c $< -o $@

clean:
	@rm -rf $(PROGRAMS) $(OBJECTS)

install: all
	test -d $(prefix) || mkdir $(prefix)
	test -d $(prefix)/bin || mkdir $(prefix)/bin
	for prog in $(PROGRAMS); do \
	  install -m 0755 $$prog $(prefix)/bin; \
	done

.PHONY: install
