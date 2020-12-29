CC = gcc

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g -Wall -lm

# the build target executable:
TARGET = fit
MAIN = main.c
MATH = calculations.c
READ = read_csv.c
FITTERS = linear_regression.c
TEST = fit_assessment.c

$(TARGET):
	$(CC) $(MAIN) -o $(TARGET)  $(MATH) $(READ) $(FITTERS) $(TEST) $(CFLAGS)

clean:
	$(RM) $(TARGET)