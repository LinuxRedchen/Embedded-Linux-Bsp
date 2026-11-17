files = a.o b.o c.o

dep_files := $(patsubst %,.%.d,$(files))
dep_files := $(wildcard $(dep_files))

CFLAGS := -Werror -I./include

AppTest : a.o b.o c.o
	gcc $^ -o $@
-include $(dep_files)
%.o : %.c
	gcc -c $(CFLAGS) $< -o $@ -MD -MF .$@.d

clean :
	rm *.o AppTest -f
cleandep :
	rm $(dep_files) -f

.PHONY :clean cleandep
