# ============================================================
# Makefile — EduGraph
# Cara pakai:
#   make          → kompilasi semua, hasilkan ./edugraph
#   make run      → kompilasi lalu langsung jalankan
#   make clean    → hapus file hasil kompilasi
# ============================================================

CC      = gcc
CFLAGS  = -Wall -Wextra -std=c11
TARGET  = edugraph
SRCS    = main.c materi.c linked_list.c bst.c tree.c ui.c
OBJS    = $(SRCS:.c=.o)

# --- Build utama ---
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^
	@echo ""
	@echo " [OK] Build berhasil! Jalankan dengan: ./$(TARGET)"

# --- Kompilasi tiap .c ke .o ---
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# --- Jalankan langsung setelah build ---
run: all
	@echo ""
	./$(TARGET)

# --- Bersihkan hasil kompilasi ---
clean:
	rm -f $(OBJS) $(TARGET)
	@echo " [OK] File build dihapus."

.PHONY: all run clean
