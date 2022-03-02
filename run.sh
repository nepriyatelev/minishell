gcc *.c library_function/*.c -lreadline && ./a.out
#-fsanitize=address
#leaks --atExit -- 