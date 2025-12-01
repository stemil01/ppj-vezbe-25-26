import sys
import re

"""
Zadatak: Izvuci i upisati informacije o knjizi u fajl 'informacije.txt' ciji se naslova zadaje
kao prvi argument komandne linije. Informacije o knjigama se nalaze u fajlu 'knjige.xml'.
Polja unutar XML tagova mogu da budu u proizvoljnom redosledu.
"""

# re.search
# re.match
# re.fullmatch
# re.finditer
# Match

# 1. argumenti komandne linije
if re.fullmatch(r".*\.xml", sys.argv[1]) is None:
    sys.exit("nije zadat XML fajl")

putanja = sys.argv[1]
naziv_knjige = sys.argv[2]

# 2. citanje sadrzaja fajla
try:
    with open(putanja, "r") as f:
        sadrzaj = f.read()
except IOError:
    sys.exit("greska pri otvaranju fajla")

# 3. izvlacenje podataka iz fajla
knjige_regex = r"<knjiga\s+rbr=\"(?P<rbr>\d+)\">\s*"\
    + r"(?P<info>.*?)"\
    + r"</knjiga>"

autor_regex = r"<autor>\s*(?P<autor>[A-Za-z.]+(\s+[A-Za-z.]+)*)\s*</autor>"
naslov_regex = r"<naslov>\s*(?P<naslov>[A-Za-z.']+(\s+[A-Za-z.']+)*)\s*</naslov>\s*"
izdavac_regex = r"<izdavac>\s*(?P<izdavac>[A-Za-z.'&]+(\s+[A-Za-z.'&]+)*)\s*</izdavac>\s*"
god_izdanja_regex = r"<god_izdanja>\s*(?P<god_izdanja>\d+)\s*</god_izdanja>\s*"
cena_regex = r"<cena\s+valuta=\"(?P<valuta>[A-Za-z]{3})\">\s*(?P<cena>\d+)\s*</cena>\s*"

autor_automat = re.compile(autor_regex)
naslov_automat = re.compile(naslov_regex)
izdavac_automat = re.compile(izdavac_regex)
god_izdanja_automat = re.compile(god_izdanja_regex)
cena_automat = re.compile(cena_regex)

knjige = {}
for match in re.finditer(knjige_regex, sadrzaj, re.DOTALL):
    info = match.group("info")
    rbr = match.group("rbr")

    autor_match = autor_automat.search(info)
    naslov_match = naslov_automat.search(info)
    izdavac_match = izdavac_automat.search(info)
    god_izdanja_match = god_izdanja_automat.search(info)
    cena_match = cena_automat.search(info)

    if autor_match is not None:
        autor = autor_match.group("autor")
    if naslov_match is not None:
        naslov = naslov_match.group("naslov")
    if izdavac_match is not None:
        izdavac = izdavac_match.group("izdavac")
    if god_izdanja_match is not None:
        god_izdanja = god_izdanja_match.group("god_izdanja")
    if cena_match is not None:
        cena = cena_match.group("cena")
        valuta = cena_match.group("valuta")

    knjige[naslov] = {
        "rbr": rbr,
        "autor": autor,
        "izdavac": izdavac,
        "god_izdanja": god_izdanja,
        "valuta": valuta,
        "cena": cena
    }

# 4. obrada
if naziv_knjige in knjige:
    trazena_knjiga = knjige[naziv_knjige]
else:
    sys.exit("naziv knjige ne postoji")

# 5. upis rezultata u fajl
try:
    izabrana_knjiga = knjige[naziv_knjige]
    with open("informacije.txt", "w") as f:
        f.write(f"{naziv_knjige}:\n")
        f.write(f"rbr: {izabrana_knjiga["rbr"]}\n")
        f.write(f"autor: {izabrana_knjiga["autor"]}\n")
        f.write(f"izdavac: {izabrana_knjiga["izdavac"]}\n")
        f.write(f"god_izdanja: {izabrana_knjiga["god_izdanja"]}\n")
        f.write(f"valuta: {izabrana_knjiga["valuta"]}\n")
        f.write(f"cena: {izabrana_knjiga["cena"]}\n")
except IOError:
    sys.exit("Greska prilikom upisivanja u fajl informacije.txt")

