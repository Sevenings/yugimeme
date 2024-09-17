

compile:
	g++ -o yugimeme yugimeme.cpp `pkg-config --cflags --libs opencv2`

compile-linux:
	g++ -o yugimeme_win yugimeme.cpp `pkg-config --cflags --libs opencv2`

run:
	./yugimeme imagens/Empresário.jpeg empresario 'O Empresario' 1200 800 'O criador de todas as cartas. Gosta de ficar sentado em sua cadeira de chefe admirando suas criacoes e pensando em ideias absurdas e criativas de novas cartas.'

