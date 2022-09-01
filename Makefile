project_exe : Bplus_Tree.o hash.o file.o TF_IDF.o main.o
		gcc -o project_exe Bplus_Tree.o hash.o file.o TF_IDF.o  main.o -lm

Bplus_Tree.o : Bplus_Tree.c
		gcc -c -o Bplus_Tree.o Bplus_Tree.c

hash.o : hash.c
		gcc -c -o hash.o hash.c

file.o : file.c
		gcc -c -o file.o file.c

TF_IDF.o : TF_IDF.c
		gcc -c -o TF_IDF.o TF_IDF.c 

main.o : main.c
		gcc -c -o main.o main.c

clean :
		rm *.o project_exe
