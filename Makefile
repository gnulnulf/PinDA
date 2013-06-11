TARGET:= rpi
ifeq ($(OS),Windows_NT)
    HOSTOS=windows
    ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
	HOSTARCH=amd64
    endif
    ifeq ($(PROCESSOR_ARCHITECTURE),x86)
	HOSTARCH=x86
    endif
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
	HOSTOS=linux
    endif
    ifeq ($(UNAME_S),Darwin)
	HOSTOS=darwin
    endif
    UNAME_P := $(shell uname -m)
    ifeq ($(UNAME_P),x86_64)
	HOSTARCH=amd64
    endif
    ifneq ($(filter %86,$(UNAME_P)),)
	HOSTARCH=x86
    endif
    ifneq ($(filter arm%,$(UNAME_P)),)
	HOSTARCH=arm
    endif
    ifeq ($(HOSTARCH),)
        HOSTARCH:=$(UNAME_P)
    endif
    ifeq ($(HOSTOS),)
        HOSTOS:=$(UNAME_S)
    endif
endif
LOGFILE=$(TARGETOS)$(TARGETARCH).log
bin:.status
	@make -f $(TARGET).mk  2> $(LOGFILE)
clean:
	@make -f $(TARGET).mk clean 2> $(LOGFILE)

rpi:.status
	@make -f rpi.mk 2> $(LOGFILE)
	
.status:
	@echo HOST OS   = $(HOSTOS)
	@echo HOST ARCH = $(HOSTARCH)
	@echo TARGET = $(TARGET)
