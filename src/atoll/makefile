default:

# ==========

root= ..
include $(root)/share.mk

gccflags += -iquote $(guroot) -iquote $(root)

# ==========

name= atoll

cfiles= \
	diagram.c \
	coast.c \
	breakpoint.c \
	circle.c \
	treasure.c \
	hedge.c \
	fence.c \

# ==========

lib:
	gcc -c $(gccflags) $(args) $(cfiles)
	mkdir -p $(obdir)
	mv *.o $(obdir)
	ar rcs $(root)/lib$(name).a $(obdir)/*.o

# whatever the current debugging flags/defines are can be pencilled in here.
debug:
	make lib args="$(args)"

testcomp:
	gcc $(gccflags) -iquote tests $(args) \
		tests/$(tf) \
		\
		-L $(root) -l $(name) \
		-l gumetry \
		-L $(guroot) -l gu \
		-lm \
		$(links)

# ==========

.PHONY: test
test: ./a.out
	./a.out $(args)

diagram_init:
	make testcomp "tf=diagram_init.c"

breakpoint:
	make testcomp "tf=breakpoint.c"

beachsort:
	make testcomp "tf=beachsort.c"

prime:
	make testcomp "tf=prime.c"

siteEvent:
	make testcomp "tf=siteEvent.c"

circumcenter:
	make testcomp "tf=circumcenter.c"

treasure:
	make testcomp "tf=treasure.c" "links= -lSDL2 -lgumetry" "args= -iquote $(root)"

checkCircles:
	make testcomp "tf=checkCircles.c"

display:
	make testcomp "tf=display.c" "links= -lSDL2"

convergence:
	make testcomp "tf=convergence.c"

simple:
	make testcomp "tf=simple.c" "links= -lSDL2"

simple_step_lib:
	make lib args="-DATOLL_DEBUG_treasure"
simple_step:
	make testcomp "tf=simple.c" "links= -lSDL2" "args=-DDEBUGSTEP"
