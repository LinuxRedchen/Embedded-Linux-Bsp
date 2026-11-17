CC ?= gcc

CFLAGS := -Wall -Werror -I.

LDFLAGS := 

SUBFILE := Sub1 sub2

OBJS := main.o
include $(foreach dir,$(SUBFILE),$(dir)/Makefile)

DEPFILE := $(OBJS:.o=.d)
-include $(DEPFILE)

TARGET := AppTest

all := $(TARGET)
$(TARGET) : $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)

%.o : %.c
	$(CC) -MMD -c $< -o $@

clean : 
	rm -f $(OBJS) $(TARGET) $(DEPFILE)
.PHONY : clean all