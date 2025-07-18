# Makefile for Towers of Hanoi visualization
# Author: Kostadin Slavov a.k.a ThunderHorn

CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99
TARGET = hanoi
SOURCES = main.c
HEADERS = hanoi.h

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET)
