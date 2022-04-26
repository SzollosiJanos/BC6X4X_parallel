# BC6X4X_parallel
# Féléves feladat

---

## Feladat leírás:
> - C-ben több különböző rendező algoritmus összehasonlítása posix és openmp segítségével több szálon, méret alapján rendezve(10000-500000 sor).
> - Python-ban quicksort rendező algoritmus mérése(elméleti síkon működik több szálon, gyakorlati szinten valamiért rettentő lassú).

---

## Mérések: (Minden mérés 500000 sorig tart, 10000 sorjával növelve)
#Összes futási idő:
> - Insertation sort:                       5867.089
> - Minimum sort(párhuzamosítás nélkül):    5535.599
> - Minimum sort(openmp):                   2060.149
> - Merge sort(párhuzamosítás nélkül):      3.595
> - Merge sort(pthread):                    3.222
> - quicksort(párhuzamosítás nélkül):       1.280
> - quicksort(openmp):                      1.155
> - Python quicksort:                       Megmérhetetlen sokáig tart(10.000 sor 23 másodperc, 20.000 sor már 120+ másodperc) a továbbiakban nem fog szerepelni
> - Indok: A Python rendelkezik thread-el, de ez nem teljesen működik úgy, ahogy C nyelvben is(GlobalInterpreterLock).
> Összeségében a leggyorsabb: Quicksort(párhuzamosítással)
> Összeségében a leglassabb: Insertation

#Futási idő nagy méret esetén:
> - Insertation sort:                       342.264
> - Minimum sort(párhuzamosítás nélkül):    322.362
> - Minimum sort(openmp):                   95.974
> - Merge sort(párhuzamosítás nélkül):      0.141
> - Merge sort(pthread):                    0.094
> - quicksort(párhuzamosítás nélkül):       0.047
> - quicksort(openmp):                      0.047
> Összeségében a leggyorsabb: Quicksort(párhuzamosítással) és Quicksort(párhuzamosítás nélkül is)
> Összeségében a leglassabb: Insertation

#Futási idő kis méret esetén:
> - Insertation sort:                       0.125
> - Minimum sort(párhuzamosítás nélkül):    1.344
> - Minimum sort(openmp):                   0.131
> - Merge sort(párhuzamosítás nélkül):      0.015
> - Merge sort(pthread):                    0.000
> - quicksort(párhuzamosítás nélkül):       0.000
> - quicksort(openmp):                      0.000
> Összeségében a leggyorsabb: Quicksort(párhuzamosítással) és Quicksort(párhuzamosítás nélkül is) és merge sort(párhuzamosítással)
> Összeségében a leglassabb: Minimum sort(párhuzamosítás nélkül)
#Grafikonok: meresek.xlsm
