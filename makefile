myFileSystem: main.o List.o Map.o Tree.o
	gcc main.o List.o Map.o Tree.o -o myFileSystem

main.o: main.c List.h Map.h Tree.h FolFil.h
	gcc -c main.c

List.o: List.c List.h
	gcc -c List.c

Map.o: Map.c Tree.h List.h
	gcc -c Map.c

Tree.o: Map.c Tree.h List.h
	gcc -c Tree.c
	
clean: 
	rm -f *.o

	
