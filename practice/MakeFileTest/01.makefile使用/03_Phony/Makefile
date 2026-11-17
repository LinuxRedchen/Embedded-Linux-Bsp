AppTest : a.o b.o c.o
	gcc $^ -o $@

%.o : %.c
	gcc -c $< -o $@

clean :
	rm *.o AppTest

.PHONY : clean