remove-list-graph:
	rm -f list_graph.exe

compile-list-graph:	
	gcc -o list_graph.exe list_graph.c

run-list-graph: remove-list-graph compile-list-graph
	./list_graph.exe
