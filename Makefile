MUSTACHE=mustach
TEST_INT=test_int
TEST_OBJ=test_obj

.PHONY: all generate clean

all: generate
	$(CC) -o $(TEST_INT) stack_int.c test_int.c
	$(CC) -o $(TEST_OBJ) stack_obj.c test_obj.c

generate:
	$(MUSTACHE) data_int.json stack_header.txt > stack_int.h
	$(MUSTACHE) data_int.json stack.txt > stack_int.c
	$(MUSTACHE) data_obj.json stack_header.txt > stack_obj.h
	$(MUSTACHE) data_obj.json stack.txt > stack_obj.c

clean:
	$(RM) $(TEST_INT) $(TEST_OBJ) stack_int.h stack_int.c stack_obj.h stack_obj.c
