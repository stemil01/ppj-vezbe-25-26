"""
Zadatak: Iz HTML tabele 'studenti.html' izvuci imena i prezimena studenata
kao i ukupan broj poena koji su osvojili (zbir poena sa pismenog i uzmenog).
Takve podatke sortirati po broju osvojenih poena i ispisati na standardni izlaz.
"""

# 1. izvlacenje podataka iz html fajla pomocu regularnih izraza
# 2. obrada podataka u pajtonu
# 3. ispis

import re
import sys

try:
    with open("studenti.html", "r") as f:
        sadrzaj = f.read()
except IOError:
    sys.exit("greska pri otvaranju fajla")

regex = r"<tr>\s*"\
    + r"<td>\s*(?P<ime>[A-Z][a-z]+\s+[A-Z][a-z]+)\s*<\/td>\s*"\
    + r"<td>\s*(?P<pismeni>\d+)\s*<\/td>\s*"\
    + r"<td>\s*(?P<usmeni>\d+)\s*<\/td>\s*"\
    + r"<\/tr>"

studenti = []
for poklapanje in re.finditer(regex, sadrzaj):
    ime = poklapanje.group("ime")
    pismeni = int(poklapanje.group("pismeni"))
    usmeni = int(poklapanje.group("usmeni"))
    studenti.append([ime, pismeni + usmeni])

studenti.sort(key=lambda s: s[1], reverse=True)

for student in studenti:
    print(f"{student[0]}\t{student[1]}")
