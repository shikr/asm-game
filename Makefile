CC      := gcc
AS      := nasm
LD 	    := gcc

SRC_DIR := src
OUT_DIR := build

TARGET  := $(OUT_DIR)/game
INCLUDE := -I./include -I./termbox2

CFLAGS  := $(INCLUDE) -Wall -Wextra -g -O2
ASFLAGS := -f elf64

C_SRCS  := $(wildcard $(SRC_DIR)/*.c)
AS_SRCS := $(wildcard $(SRC_DIR)/*.asm)

C_OBJS  := $(patsubst $(SRC_DIR)/%.c, $(OUT_DIR)/%.o, $(C_SRCS))
AS_OBJS := $(patsubst $(SRC_DIR)/%.asm, $(OUT_DIR)/%.o, $(AS_SRCS))
OBJS    := $(C_OBJS) $(AS_OBJS)

.PHONY: all
all: $(OUT_DIR) $(TARGET) compile_commands

$(TARGET): $(OBJS)
	$(LD) -o $@ $^
	@echo "[LD]  $@"

$(OUT_DIR):
	@mkdir -p $(OUT_DIR)

$(OUT_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "[CC]  $<"
	$(CC) $(CFLAGS) -c $< -o $@

$(OUT_DIR)/%.o: $(SRC_DIR)/%.asm
	@echo "[AS]  $<"
	$(AS) $(ASFLAGS) $< -o $@

compile_commands:
	@printf '[\n' > compile_commands.json
	@first=1; for f in $(C_SRCS); do \
	    [ $$first -eq 0 ] && printf ',\n' >> compile_commands.json; \
	    printf '  {"directory": "%s", "command": "$(CC) $(CFLAGS) -c %s", "file": "%s"}' \
	        "$$(pwd)" "$$f" "$$f" >> compile_commands.json; \
	    first=0; \
	done
	@printf '\n]\n' >> compile_commands.json

.PHONY: debug
debug: CFLAGS += -DDEBUG -O0
debug: all

.PHONY: release
release: CFLAGS := -Wall -O3 $(INCLUDE)
release: ASFLAGS := -f elf64
release: all

.PHONY: run
run: all
	@./$(TARGET)

.PHONY: gdb
gdb: all
	gdb ./$(TARGET)

.PHONY: clean
clean:
	@rm -rf $(OUT_DIR)
	@echo "[CLEAN] objetos y ejecutables eliminados."
