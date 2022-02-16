FLAGS = -Wall -ansi -pedantic

Dining_philosophers_problem: Dining_philosophers_problem.c
gcc $(FLAGS) -o Dining_philosophers_problem Dining_philosophers_problem.c

clean:
	rm Dining_philosophers_problem