# Konfigurasi Compiler dan Flag
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -I$(SRC_DIR)

# Direktori
SRC_DIR = Code/Bagian
OBJ_DIR = obj

# File Sumber dan Object
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Nama Output Executable
TARGET = edugraph.exe

# Rule Utama
all: $(TARGET)

# Rule untuk mengompilasi file Object menjadi Executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Rule untuk mengompilasi file .c menjadi .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Membuat direktori obj jika belum ada (Windows kompatibel)
$(OBJ_DIR):
	@if not exist $(OBJ_DIR) mkdir $(OBJ_DIR)

# Membersihkan file hasil kompilasi (Windows kompatibel)
clean:
	@if exist $(OBJ_DIR) rmdir /s /q $(OBJ_DIR)
	@if exist $(TARGET) del /q $(TARGET)

.PHONY: all clean