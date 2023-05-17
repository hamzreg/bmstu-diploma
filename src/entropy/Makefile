CC := gcc
CFLAGS := -std=c99 -Wall -Werror -pedantic

TARGET := app.exe

SRC_DIR := ./src
CFILES := $(wildcard $(SRC_DIR)/*.c)

HDRS_DIR := ./inc
HDRS := $(wildcard $(HDRS_DIR)/*.h)

OBJ_DIR := ./out
OBJS := $(CFILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)


.PHONY: clean sw binomial

$(TARGET): $(OBJS)
	$(CC) $^ -o $@ -lm

$(OBJ_DIR):
	@mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HDRS) $(OBJ_DIR)
	$(CC) $(CFLAGS) $(UFLAGS) -c $< -o $@ -lm

sw:
	./$(TARGET) input.png 0 0

binomial:
	./$(TARGET) input.png 1 0

clean:
	$(RM) -rf $(OBJ_DIR) *.exe
