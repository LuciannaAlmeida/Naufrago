CFLAGS = -Wall -pedantic -ansi -O2 -g -ggdb3 -lalleg-4.2.2 
dependencies = main.o estado_inicial.o imprime_estado_atual.o jogo.o movimenta_elementos.o naufrago.o visualizacao_grafica.o coral.o colisoes.o asimov.o bote.o imprime_informacoes.o teclas.o
dependencies_for_tests = estado_inicial.o imprime_estado_atual.o jogo.o movimenta_elementos.o naufrago.o visualizacao_grafica.o coral.o colisoes.o asimov.o bote.o imprime_informacoes.o teclas.o
objects = lib/main.o lib/estado_inicial.o lib/imprime_estado_atual.o lib/jogo.o lib/movimenta_elementos.o lib/naufrago.o lib/visualizacao_grafica.o lib/coral.o lib/colisoes.o lib/asimov.o lib/bote.o lib/imprime_informacoes.o lib/teclas.o
objects_for_tests = lib/estado_inicial.o lib/imprime_estado_atual.o lib/jogo.o lib/movimenta_elementos.o lib/naufrago.o lib/visualizacao_grafica.o lib/coral.o lib/colisoes.o lib/asimov.o lib/bote.o lib/imprime_informacoes.o lib/teclas.o

all: lib ${dependencies}
	clear
	gcc ${CFLAGS} -o exe ${objects}

main.o: lib src/main.c
	gcc ${CFLAGS} -c src/main.c -o lib/main.o

estado_inicial.o: lib src/estado_inicial.c src/estado_inicial.h
	gcc ${CFLAGS} -c src/estado_inicial.c -o lib/estado_inicial.o

imprime_estado_atual.o: lib src/imprime_estado_atual.c src/imprime_estado_atual.h
	gcc ${CFLAGS} -c src/imprime_estado_atual.c -o lib/imprime_estado_atual.o

jogo.o: lib src/jogo.c src/jogo.h
	gcc ${CFLAGS} -c src/jogo.c -o lib/jogo.o

movimenta_elementos.o: lib src/movimenta_elementos.c src/movimenta_elementos.h
	gcc ${CFLAGS} -c src/movimenta_elementos.c -o lib/movimenta_elementos.o

naufrago.o: lib src/naufrago.c src/naufrago.h
	gcc ${CFLAGS} -c src/naufrago.c -o lib/naufrago.o

visualizacao_grafica.o: lib src/visualizacao_grafica.c src/visualizacao_grafica.h
	gcc ${CFLAGS} -c src/visualizacao_grafica.c -o lib/visualizacao_grafica.o

coral.o: lib src/coral.c src/coral.h
	gcc ${CFLAGS} -c src/coral.c -o lib/coral.o

colisoes.o: lib src/colisoes.c src/colisoes.h
	gcc ${CFLAGS} -c src/colisoes.c -o lib/colisoes.o

asimov.o: lib src/asimov.c src/asimov.h
	gcc ${CFLAGS} -c src/asimov.c -o lib/asimov.o

bote.o: lib src/bote.c src/bote.h
	gcc ${CFLAGS} -c src/bote.c -o lib/bote.o 

imprime_informacoes.o: lib src/imprime_informacoes.c src/imprime_informacoes.h
	gcc ${CFLAGS} -c src/imprime_informacoes.c -o lib/imprime_informacoes.o 

teclas.o: lib src/teclas.c src/teclas.h
	gcc ${CFLAGS} -c src/teclas.c -o lib/teclas.o 

doc/Relatorio.pdf: doc/src/Relatorio.tex
	pdflatex doc/src/Relatorio.tex
	pdflatex doc/src/Relatorio.tex
	pdflatex doc/src/Relatorio.tex
	pdflatex doc/src/Relatorio.tex
	rm -f Relatorio.dvi Relatorio.aux Relatorio.log Relatorio.toc
	mv Relatorio.pdf doc/

doc: doc/Relatorio.pdf

testes: lib ${dependencies_for_tests} src/minunit.c
	gcc ${CFLAGS} src/minunit.c ${objects_for_tests} -o teste
	clear	
	./teste

lib: 
	mkdir lib

clean:
	rm -rf exe teste lib doc/Relatorio.pdf Relatorio.out
