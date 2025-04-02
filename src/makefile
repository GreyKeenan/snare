default:


root= .
include ./share.mk


cfiles= \
	main.c

links= \
	-L $(guroot) -l gu \
	\
	-L . \
	-l gumetry \

# ==========

dev: $(cfiles) \
	$(guroot)/libgu.a \
	libgumetry.a \
	
	gcc $(gccflags) \
		\
		$(args) \
		\
		$(cfiles) \
		\
		$(links)

run: a.out
	./a.out $(args)

clean:
	rm -rf */$(obdir)/*.o
	rm -f */a.out
	rm -f lib*.a
	rm -f a.out

# ==========

gu:
	cd $(guroot)/gu && make lib

all:
	make gumetry


.PHONY: gumetry
gumetry:
	cd gumetry && make lib

.PHONY: atoll
atoll:
	cd atoll && make lib
