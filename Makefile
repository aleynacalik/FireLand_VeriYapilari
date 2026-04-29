all: program

program: main modul1 modul2 modul3 modul4 modul5 modul6
	g++ ./lib/main.o ./lib/modul1_kayit.o ./lib/modul2_gunluk.o ./lib/modul3_stack.o ./lib/modul4_queue.o ./lib/modul5_tree.o ./lib/modul6_hash.o -o ./bin/program.exe

main:
	g++ -I "include" -c main.cpp -o ./lib/main.o

modul1:
	g++ -I "include" -c ./src/modul1_kayit.cpp -o ./lib/modul1_kayit.o

modul2:
	g++ -I "include" -c ./src/modul2_gunluk.cpp -o ./lib/modul2_gunluk.o

modul3:
	g++ -I "include" -c ./src/modul3_stack.cpp -o ./lib/modul3_stack.o

modul4:
	g++ -I "include" -c ./src/modul4_queue.cpp -o ./lib/modul4_queue.o

modul5:
	g++ -I "include" -c ./src/modul5_tree.cpp -o ./lib/modul5_tree.o

modul6:
	g++ -I "include" -c ./src/modul6_hash.cpp -o ./lib/modul6_hash.o

run:
	.\bin\program.exe

clean:
	del /Q lib\*.o bin\program.exe0
