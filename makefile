prod_cons_MT: prod_cons_MT.c main.c
	gcc -o prod_cons_MT prod_cons_MT.c main.c -I. -Wall -g
run:
	./prod_cons_MT 3 3 3
