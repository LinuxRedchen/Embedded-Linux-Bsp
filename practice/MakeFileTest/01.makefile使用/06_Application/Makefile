
CC ?= gcc

CFLAGS := -Wall -Werror -I

LDFLAGS :=

SUBDIR = Dirone Dirtwo

OBJS :=main.o
include $(foreach dir,$(SUBDIR),$(dir)/Makefile)

DEPFILE := $(OBJS:.o=.d)
-include (DEPFILE)

TARGET := TestApp

all := $(TARGET)
$(TARGET) : $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)

%.o : %.c
	$(CC) -MMD -c $(CFLAGS) $< -o $@

clean : 
	rm -f $(OBJS) $(DEPFILE) $(TARGET)

.PHONY : clean all




