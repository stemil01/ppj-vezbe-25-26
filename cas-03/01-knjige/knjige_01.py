import sys
import re

"""
Zadatak: Izvuci i upisati informacije o knjizi u fajl 'informacije.txt' ciji se naslova zadaje
kao prvi argument komandne linije. Informacije o knjigama se nalaze u fajlu 'knjige.xml'.
Sva polja u unutar XML tagova su uvek u istom redosledu.
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
knjige_regex = r"<knjiga\s+rbr=\"(?P<rbr>[1-9][0-9]*)\">"\
    + r"\s*<autor>(?P<autor>[a-zA-Z.]+(\s+[a-zA-Z.]+)*)<\/autor>\s*"\
    + r"<naslov>\s*(?P<naslov>[a-zA-Z']+(\s+[a-zA-Z']+)*)\s*<\/naslov>\s*"\
    + r"<izdavac>\s*(?P<izdavac>[a-zA-Z.'&]+(\s+[a-zA-Z.'&]+)*)\s*<\/izdavac>\s*"\
    + r"<god_izdanja>\s*(?P<god_izdanja>\d+)\s*<\/god_izdanja>\s*"\
    + r"<cena\s+valuta=\"(?P<valuta>[a-z]{3})\">\s*(?P<cena>\d+)\s*<\/cena>\s*"\
    + r"<\/knjiga>"

knjige = {}
for knjige_match in re.finditer(knjige_regex, sadrzaj):
    rbr = knjige_match.group("rbr")
    autor = knjige_match.group("autor")
    naslov = knjige_match.group("naslov")
    izdavac = knjige_match.group("izdavac")
    god_izdanja = knjige_match.group("god_izdanja")
    cena = knjige_match.group("cena")
    valuta = knjige_match.group("valuta")
    
    knjige[naslov] = {
        "rbr": rbr,
        "autor": autor,
        "izdavac": izdavac,
        "god_izdanja": god_izdanja,
        "cena": cena,
        "valuta": valuta
    }

# 4. obrada
if naziv_knjige in knjige:
    trazena_knjiga = knjige[naziv_knjige]
else:
    sys.exit("naziv knjige ne postoji")

# 5. upis rezultata u fajl
try:
    with open("informacije.txt", "w") as f:
        f.write(f"{naziv_knjige}\n")
        for k, v in trazena_knjiga.items():
            f.write(f"{k}: {v}\n")
except IOError:
    sys.exit("greska pri upisu u fajl")

