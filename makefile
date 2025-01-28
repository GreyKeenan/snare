
src= src
obdir= objects

gccflags= \
	-std=c99 \
	-Wpedantic \
	-Wall \
	-Wextra \
	-iquote .

main: \
	$(src)/libgunc.a \
	$(src)/libchalk.a \
	$(src)/libcookie.a \
	\
	$(src)/main.c
	
	cd $(src) && \
	gcc $(gccflags) \
		-o ../a.out \
		\
		$(args) \
		\
		main.c \
		\
		-L . \
		-l gunc \
		-l SDL2

all:
	make gunc
	make chalk
	make cookie
	make

run: ./a.out
	./a.out $(args)


library: $(lib_requires)
	cd $(src)/$(lib_name) \
	&& \
	gcc $(gccflags) \
		-c \
		\
		$(lib_args) \
		\
		$(lib_cfiles) \
		\
		$(lib_links) \
	&& \
	mkdir -p $(obdir) \
	&& \
	mv *.o $(obdir)
	ar rcs $(src)/lib$(lib_name).a $(src)/$(lib_name)/$(obdir)/*.o

gunc:
	make library \
		lib_name=gunc \
		lib_cfiles=" \
			file_logger.c \
			list.c \
		"

chalk:
	make library \
		lib_name=chalk \
		lib_args="-iquote .." \
		lib_cfiles=" \
			random.c \
			compare_point.c \
		" \
		lib_links=" \
			-lm \
		"

cookie: $(src)/libgunc.a
	make library \
		lib_name=cookie \
		lib_args=" \
			-iquote .. \
			-L .. \
		" \
		lib_cfiles=" \
			fortune.c \
		" \
		lib_links=" \
			-l gunc \
		"
