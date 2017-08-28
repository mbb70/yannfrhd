CC=/usr/local/Cellar/gcc/7.2.0/bin/g++-7
all:
	$(CC) main.cpp \
	-Wcast-align \
	-Wmissing-declarations \
	-Wmissing-include-dirs \
	-Wswitch-enum \
	-Wswitch-default \
	-Wextra \
	-Wall \
	-Werror \
	-Winvalid-pch \
	-Wformat=2 \
	-Wmissing-format-attribute \
	-Wformat-nonliteral \
	-Wodr \
	-flto -lm -O3 -ffast-math -lpthread -I/Users/mbrown/local/include -L/Users/mbrown/local/lib -lcblas -latlas
