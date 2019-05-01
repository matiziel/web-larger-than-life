# web-larger-than-life
Gra Larger Than Life na przeglądarkę w architekturze klient-serwer.

Do uruchomienia wymagane:
-biblioteki boost
-python flask

Aby uruchomić aplikację należy przejść do katalogu projektu i wpisać w konsoli: python3.6 run.py
Aplikacja składa się z dwóch prostych widoków jako prototyp interfejsu.

Główna logika gry jako moduł do języka python. Dostępna w katalogu /larger_than_life/models/src.
Działanie można przetestować uruchamiając skrypt /larger_than_life/models/src/main.py (wymagana instalacja pygame).
Kompilacja modułu: 
$ cd /larger_than_life/models/src
$ make

Testowane na Ubuntu 18.04 LTS

