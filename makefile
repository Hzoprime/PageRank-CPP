.PHONY: clean run clean_intermediate
task = dense
teleport = 0.85

intermediate = *.gch *.o *.tmp
cc = g++ -std=c++17 -O3
object = headers.o io.o dense_dynamic.o block_stripe.o
main = main.o
executable = pagerank.exe

run: $(object) $(main) execute
	./$(executable) $(task) $(teleport)

%.o : %.cpp
	$(cc) -c $<

execute :
	$(cc) *.o -o $(executable)

dense: $(object) $(main) execute
	./$(executable) dense $(teleport)

block: $(object) $(main) execute
	./$(executable) block $(teleport)

clean_intermediate:
	rm -rf $(intermediate)

clean: clean_intermediate
	rm -rf $(executable)
