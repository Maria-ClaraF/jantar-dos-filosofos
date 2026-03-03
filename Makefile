all:
	gcc -Wall filosofos_defeituoso.c -o defeituoso -lpthread
	gcc -Wall filosofos_corrigido.c -o corrigido -lpthread

clean:
	rm -f defeituoso corrigido



