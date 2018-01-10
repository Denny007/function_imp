PRO:=func_test
CFLAGS := -O0 -g3 -Wall

SRC += function_imp.c

OBJ_SRC += $(patsubst %.c,%.o,$(SRC))

.PHONY:all
all:$(PRO)

$(PRO):$(OBJ_SRC)
	$(CC) -o $@  $^ $(LDFLAGS)

$(OBJ_SRC):%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY:clean
clean:
	rm -rf *.o $(PRO)

