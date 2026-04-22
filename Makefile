program: main modul1 modul2
	g++ ./lib/main.o ./lib/modul1_kayit.o ./lib/modul2_gunluk.o -o ./bin/program

main:
	g++ -I "include" -c main.cpp -o ./lib/main.o

modul1:
	g++ -I "include" -c ./src/modul1_kayit.cpp -o ./lib/modul1_kayit.o

modul2:
	g++ -I "include" -c ./src/modul2_gunluk.cpp -o ./lib/modul2_gunluk.o

clean:
	del lib\*.o bin\program.exe
