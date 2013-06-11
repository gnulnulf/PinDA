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
OBJECTS = $(SOURCES:.cpp=.o)

all: ${PROGRAMS}
	@echo [ALL $(OBJECTS)]


#
#${PROGRAMS}: ${SOURCES}
	g++ ${CCFLAGS} -Wall -I. -L. $@.cpp -o $@
#	g++ ${CCFLAGS} -L../librf24/  -lrf24 $@.cpp -o $@


%.o: %.cpp
	@echo [g++ $@]
	@$(GPP) ${CCFLAGS} -fPIC -o $@ -c $< $(LDFLAGS) $(LDLIBS)

mcptest: $(OBJECTS)
	@echo [test $(OBJ)]
	@echo [link]
	@$(GPP) ${CCFLAGS} -o $@ $< $(LDFLAGS) $(LDLIBS) $(OBJECTS)

	
.c.o:
	@echo [GPP] $<
	@$(GPP)  $(CFLAGS) -fPIC -c $< -o $@

clean:
	@rm -rf $(PROGRAMS) $(OBJECTS)

install: all
	test -d $(prefix) || mkdir $(prefix)
	test -d $(prefix)/bin || mkdir $(prefix)/bin
	for prog in $(PROGRAMS); do \
	  install -m 0755 $$prog $(prefix)/bin; \
	done

.PHONY: install
