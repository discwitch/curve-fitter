CC = gcc

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g -Wall
ENDFLAGS = -lm

# the build target executable:
TARGET = fit
MAIN = main.c
MATH = calculations.c
READ = read_csv.c
FITTERS = fitting_functions.c
TEST = fit_assessment.c

$(TARGET):
	$(CC) $(CFLAGS) $(MAIN) -o $(TARGET)  $(MATH) $(READ) $(FITTERS) $(TEST) $(ENDFLAGS)

clean:
	$(RM) $(TARGET)