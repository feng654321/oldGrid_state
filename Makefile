#
# Makefile 
#

RUNTIMEDIR = $(HOME)/platform_v2/runtime

LIBDIR = $(RUNTIMEDIR)/lib

ifndef CROSS
CROSS=arm-linux-
endif

INSTALL    = install
CC         = $(CROSS)gcc
STRIPTOOL  = $(CROSS)strip
RM         = rm -f

LD_FLAGS = 
LD_FLAGS += -lpax_db 
LD_FLAGS += -lpax_driver
LD_FLAGS += -lpax_base
LD_FLAGS += -lm
LD_FLAGS += -lpthread

CFLAGS  = -Iinclude -Iinc -I$(RUNTIMEDIR)/lib_head
CFLAGS += -mtune=arm9tdmi -msoft-float -DFACTORY_MODE_ENABLE
CFLAGS += $(subst \",, $(strip $(WARNINGS))) -Wstrict-prototypes -Wno-trigraphs -Wall -fno-strict-aliasing
CFLAGS += $(call check_gcc,-fno-stack-protector,)
CFLAGS += -std=gnu99 -fno-builtin -O2 -fgnu89-inline
CFLAGS2 = -Wl,-rpath,/usr1/bin:/usr1/lib

INSTALL_DIR=$(RUNTIMEDIR)/util
TARGET = meter_test
PUBLICSRC = 
LOCALSRC = main.c src/ap_meter.c src/vt_platform.c src/api_drive.c src/timerapi.c src/gol_data.c src/ap_datastorage.c src/ap_profunction.c src/gol_version.c \
			src/gol_function.c src/ap_ade7758.c src/ap_powerclac.c src/ap_powercount.c src/ap_priceswitch.c src/ap_demand.c src/ap_harmonic.c src/savemeter_to_dbf.c
#SOURCES = $(LOCALSRC) $(PUBLICSRC)
SOURCES = $(wildcard src/*.c) main.c public/app_ipcs.c
OBJS = $(patsubst %.c,%.o,$(SOURCES))


all: $(TARGET)

$(TARGET):$(OBJS)
	$(CC) $(LD_FLAGS) $(CFLAGS) $(CFLAGS2) -o $(TARGET) $(OBJS) -L$(LIBDIR)
	$(STRIPTOOL) -R .comment -R .note --strip-unneeded $(TARGET)
	
clean:
	$(RM) -f $(OBJS) $(TARGET) *.o *~

install:
	install -d $(INSTALL_DIR)
	install $(TARGET) $(INSTALL_DIR)
