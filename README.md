SPROSÓB KORZYSTANIA Z PROGRAMU

Aby uruchomić program należy:
- otworzyć plik 'ant' w terminalu (./ant)
- przy wywoływaniu posłużyć się flagami i podać argumenty (przewidziane są wartości domyślne w przypadku braku flag/argumentów)

Dostępne flagi:
-m (liczba wierszy siatki)
-n (liczba kolumn siatki)
-i (liczba iteracji)
-d (zwrot startowy mrowki): 0 - góra (^), 1 - prawo (>), 2 - dół (v), 3 - lewo (<)
-f (przedrostek nazwy plików wynikowych, np. dla '-f plik': plik_1, plik_2, plik_X...
-g (generowanie losowej siatki według procentowego zapełnienia czarnymi polami, np. dla '-g 50': siatka będzie zapełniona czarnymi polami w 50%
-r (nazwa pliku z gotową siatką do wczytania)

Wartości domyślne:
- wiersze: 50
- kolumny: 50
- iteracje: 500
- zwrot mrówki: 0 (w górę)
- zapełnienie siatki czarnymi polami: 0 (cała biała)
- zapis na wyjście standardowe (stdout)

Program zapisuje kolejne iteracje Mrówki Langtona do momentu osiągnięcia oczekiwanej liczby iteracji lub natrafienia przez mrówkę na ścianę.
Iteracje zapisywane są w oddzielnych plikach o nazwie zdefiniowanej przez użytkownika lub na wyjście standardowe, w przypadku braku parametru pliku.
Pliki zapisywane są w folderze 'out'.

Do programu załączona jest przykładowa siatka testowa 'maptest' dla funkcji wczytywania gotowej siatki dla Mrówki.
