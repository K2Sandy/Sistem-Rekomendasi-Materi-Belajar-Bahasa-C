

CC = gcc
CFLAGS = -Wall -std=c11

ALL_DIR = All
MOD_DIR = Bagian

ALL_SRC = $(ALL_DIR)/Allin1.c
MOD_SRCS = $(MOD_DIR)/main.c \
           $(MOD_DIR)/materi.c \
           $(MOD_DIR)/linked_list.c \
           $(MOD_DIR)/bst.c \
           $(MOD_DIR)/tree.c \
           $(MOD_DIR)/ui.c

ALL_TARGET = allin1.exe
MOD_TARGET = edugraph.exe

.PHONY: all modular allinone clean

all: $(MOD_TARGET)

modular: $(MOD_TARGET)

allinone: $(ALL_TARGET)

$(MOD_TARGET): $(MOD_SRCS)
	$(CC) $(CFLAGS) $^ -o $@

$(ALL_TARGET): $(ALL_SRC)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	if exist $(MOD_TARGET) del /Q $(MOD_TARGET)
	if exist $(ALL_TARGET) del /Q $(ALL_TARGET)
	if exist $(MOD_DIR)\*.o del /Q $(MOD_DIR)\*.o
