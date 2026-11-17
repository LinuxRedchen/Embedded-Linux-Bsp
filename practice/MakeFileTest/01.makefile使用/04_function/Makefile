A := a.c b.c c.c

B = $(foreach f,$(A),$(f:.c=.o))

C = a b c dl

D = $(filter %l,$(C))
E = $(filter-out %l,$(C))

F = $(wildcard $(A))

G = $(patsubst %.c,%.a,$(A))

all:
	@echo B = $(B)
	@echo D = $(D)
	@echo E = $(E)
	@echo F = $(F)
	@echo G = $(G)