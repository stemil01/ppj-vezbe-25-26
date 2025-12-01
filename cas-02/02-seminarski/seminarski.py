"""
Zadatak: U direktorijumu koji se zadaje kao jedini argument komandne linije nalaze
se radovi studenata (direktorijum 'radovi' je primer jednog ulaza). Taj direktorijum
sadrzi poddirektorijume sa nazivima koji odgovaraju alas nalozima studenata, dok se u
svakom poddirektorijumu nalaze uradjeni zadaci. Izvuci koje zadatke je uradio svaki student.
"""

import sys
import os
import re

if len(sys.argv) != 2:
    sys.exit("Pogresan broj argumenata komandne linije")

alas_regex = r"m[imnvrla]([01][0-9]|2[0-5])(00[1-9]|0[1-9][0-9]|[1-5][0-9]{2}|600)"
alas_automat = re.compile(alas_regex)
zadatak_regex = r"(?P<zad>[1-9][0-9]*)\.(c(pp)?|java)"
zadatak_automat = re.compile(zadatak_regex)

# radovi
putanja = sys.argv[1]
studenti = {}
for fajl in os.listdir(putanja):
    # mi23123
    alas_poklapanje = alas_automat.fullmatch(fajl)
    if alas_poklapanje is not None:
        alas = alas_poklapanje.group()
        alas_putanja = os.path.join(putanja, alas)
        if os.path.isdir(alas_putanja):
            studenti[alas] = set()
            for zadatak_fajl in os.listdir(alas_putanja):
                # 1.c
                zadatak_poklapanje = zadatak_automat.fullmatch(zadatak_fajl)
                if zadatak_poklapanje is not None:
                    studenti[alas].add(zadatak_poklapanje.group("zad"))

for alas, zadaci in studenti.items():
    print(alas, end=": ")
    for zad in zadaci:
        print(zad, end=" ")
    print()

