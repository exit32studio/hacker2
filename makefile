# compile the crack program
# use the clang compiler
CC = clang

#compiler flags
# -ggdb3 adds debugging information
# -Wall turns on almost every warning
CFLAGS = -ggdb3 -Wall

#link files
LFLAGS = -lcs50 -lcrypt

#filenames
TARGET = crack

all: $(TARGET)

$(TARGET): $(TARGET).c ; $(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c $(LFLAGS)
    

