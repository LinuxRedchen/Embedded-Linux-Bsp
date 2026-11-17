CC ?= gcc

CFLAGS := -Wall -Werror -I.

LDFLAGS := 

SUBDIR := sub1 sub2

OBJS := main.o
include $(foreach dir,$(SUBDIR),$(dir)/Makefile)

DEPFILE := $(OBJS:.o=.d)
-include $(DEPFILE)

TARGET := Test

all := $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)
%.o : %.c
	$(CC) -MMD -c $(CFLAGS) $< -o $@

clean :
	rm -f $(TARGET) $(DEPFILE) $(OBJS)
.PHONY : clean all
