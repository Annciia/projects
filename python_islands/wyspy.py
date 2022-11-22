import time

#Przykładowa mapa.
n= 6
l= [ "001000", "011000", "100001", "011001", "011111", "011000" ]
l= [ list(x) for x in l ]

#Wszystkie obszary lądu, mające wspólną krawędź, tworzą jedną wyspę - początkowo 0 wysp znalezionych.
liczba_wysp= 0


#Pokazuje obecny stan całej mapy.
def printujMape(y, x, zjadacz):
    print("\nLICZBA WYSP:", liczba_wysp);
    for i in range(n):
        for j in range(n):
            if i == y and j == x:
                if zjadacz:
                    print(" 🐱 ", end='')
                else:
                    print(" 🐈 ", end='')
            else:
                if l[i][j] == '0':
                    print(" 🌊 ", end='')
                else:
                    print(" 🌴 ", end='')
        print("")
    print("")
    time.sleep(2)

#Zamiana wyspy na morze. Sprawdzanie sąsiednich lokalizacji, czy są wyspą.
def zerujWyspe(y, x):
    l[y][x]= '0'
    printujMape(y, x, True)
    if y+1 < n and l[y+1][x] == '1':
        zerujWyspe(y+1, x)
    if y-1 >= 0 and l[y-1][x] == '1':
        zerujWyspe(y-1, x)
    if x+1 < n and l[y][x+1] == '1':
        zerujWyspe(y, x+1)
    if x-1 >= 0 and l[y][x-1] == '1':
        zerujWyspe(y, x-1)


#main
printujMape(-1, -1, False) #Pierwotny stan mapy z wyspami.

for y in range(n):
    for x in range(n):
        printujMape(y, x, False)
        if l[y][x] == '1':
            zerujWyspe(y, x)
            liczba_wysp= liczba_wysp+1

printujMape(n, n, False) #Końcowy stan mapy, po zliczeniu wysp (wszędzie morze).