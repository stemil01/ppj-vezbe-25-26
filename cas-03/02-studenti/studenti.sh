#!/usr/sbin/bash

# Izvuci iz HTML tabele 'studenti.html' samo validne informacije o studentima (ime, prezime i broj indeksa) i na osnovu njih
# generisati imena odgovarajucih alas naloga. Izlaz sortirati po imenu rastuce i dodati redne brojeve uz svako ime.
# Primer izlaza:
# 1. Mika Mikic mi22023
# 2. Pera Peric mi21123
# 3. Zika Zikic mi23003

grep --color -E '<td>[a-zA-Z]+\s+[a-zA-Z]+\s*</td>\s*<td>\s*([1-9][0-9]{,2})\s*/\s*(20([01][0-9]|2[0-5]))\s*</td>' studenti.html |
sed -E 's/\b([1-9])\b/00\1/g' |       # dodavanje vodecih nula jednocifrenim brojevima
sed -E 's/\b([1-9][0-9])\b/0\1/g' |   # dodavanje vodecih nula dvocifrenim brojevima
sed -E 's/<td>\s*(([a-zA-Z]+)\s+([a-zA-Z]+))\s*<\/td>\s*<td>\s*([0-9]+)\s*\/\s*20([0-9]{2})\s*<\/td>/\2 \3 mi\5\4/g' |
sed -E 's/(\s)+/\1/g' |
sort |
grep -n .* |                          # dodavanje rednih brojeva
sed -E 's/:/\./g'                     # zamena ':' sa '.'

