CROSS_COMPILE ?=arm-linux-gnueabihf-
CC  = $(CROSS_COMPILE)gcc
CPP = $(CROSS_COMPILE)g++
AR  = $(CROSS_COMPILE)ar

# config hdmi or panel display
CONFIG_SUPPORT_HDMI =

COM_FLAGS = -Wall -O2 -fPIC -mcpu=cortex-a9 -mfpu=neon-fp16 -mfloat-abi=hard -mthumb-interwork -marm
C_FLAGS   = $(COM_FLAGS) -std=c11
CPP_FLAGS = $(COM_FLAGS) -std=c++11

INCLUDES  = -I. \
            -I./sstar/include \
            -I./ffmpeg/include

TARGET_NAME  = dfplayer

CPP_SRCS  =
C_SRCS    =  $(wildcard *.c */*.c)

CPP_OBJS  = $(patsubst %.cpp, %.cpp.o, $(CPP_SRCS))
C_OBJS    = $(patsubst %.c, %.c.o, $(C_SRCS))

LIB_PATH  = -L./sstar/lib \
            -L./ffmpeg/lib

LIB_NAME  = -lavformat -lavcodec -lavutil -lswscale -lswresample
LIB_NAME += -pthread -lm -lmi_vdec -lmi_sys -lmi_divp -lmi_disp -lmi_ao -lmi_gfx -ldl -lmi_common
LIB_NAME += -lssl -lcrypto

LIB_NAME  += -lmi_panel

.PHONY: all prepare clean

all: prepare $(TARGET_NAME) finish

prepare:
	@echo
	@echo ">>>>========================================================"
	@echo "TARGET_NAME = $(TARGET_NAME)"
	@echo


clean:
	@rm -Rf $(CPP_OBJS)
	@rm -f $(C_OBJS)
	@rm -Rf $(TARGET_NAME)

finish:
	@echo "make done"
	@echo "<<<<========================================================"
	@echo

$(TARGET_NAME): $(CPP_OBJS) $(CPP_SRCS) $(C_OBJS) $(C_SRCS)
	@echo $(CC) -o $@ $(C_OBJS) $(CPP_OBJS) $(LIB_PATH) $(LIB_NAME) -lm -lpthread
	@$(CC) -o $@ $(C_OBJS) $(CPP_OBJS) $(LIB_PATH) $(LIB_NAME) -lm -lpthread

%.c.o : %.c
	@echo $(CC) $(C_FLAGS) $(INCLUDES) -c $< -o $@
	@$(CC) $(C_FLAGS) $(INCLUDES) -c $< -o $@

%.cpp.o : %.cpp
	@echo "compile $@"
	@$(CPP) $(CPP_FLAGS) $(INCLUDES) -c $< -o $@

