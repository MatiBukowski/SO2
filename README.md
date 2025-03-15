# Systemy Operacyjne 2
## Projekt 1 - Problem jedzących filozofów
### Informacje ogólne
Celem projektu było napisanie programu rozwiązującego problem jedzących filozofów.

Problem jedzących filozofów to klasyczny problem synchronizacji w programowaniu współbieżnym.
Polega on na tym, że pięciu filozofów siedzi przy okrągłym stole, na którym znajdują się widelce 
(pomiędzy każdą parą filozofów). Filozofowie na przemian myślą i jedzą, ale żeby jeść, muszą 
jednocześnie podnieść dwa widelce – jeden z lewej i jeden z prawej strony.
Problem polega na tym, jak zapewnić, aby filozofowie mogli jeść bez wpadania w zakleszczenie.

### Użyte technologie
* Język projektu: C++ w wersji 20
* Wykorzystane IDE: CLion 2024.2.2

### Pliki projektu
* Plik __main.cpp__ - kod uruchamiający cały program - plik wykonywalny: __SO2_P2.exe__
* Plik __philoProblem.cpp__ - pierwsza wersja rozwiązania problemu jedzących filozofów (bez użycia biblioteki _semaphore_)
* Plik __philoProblem2.cpp__ - druga wersja rozwiązania problemu jedzących filozofów (używająca biblioteki _semaphore_)

### Uruchomienie
Aby uruchomić projekt, w zakładce "Run / Debug Configurations" należy wybrać konfigurację __SO2_P1__, a następnie wcisnąc przycisk __Run__.

## Projekt 2 - Wielowątkowy serwer czatu
### Informacje ogólne
Celem projektu było stworzenie wielowątkowego serwera chatu, z którym będą mogli łączyć się klienci i konwersować między sobą. 

### Użyte technologie
* Język projektu: C++ w wersji 20
* Wykorzystane IDE: CLion 2024.2.2
* Biblioteka obługująca porty na Windows: winsock2

### Pliki projektu
* Katalog __Client__ - znajduje się w nim program klienta łączącego się z serwerem - plik wykonywalny: __Client.exe__
* Katalog __Server__ - znajduje się w nim program serwera, do którego przyłączają się klienci - plik wykonywalny: __Server.exe__
* Plik __Constants.cpp__ - plik, w którym znajdują się wyświetlane komunikaty dla odpowiednich wyjątków
* Plik __startup.cpp__ - kod uruchamiający podaną przez użytkownika liczbę klientów - plik wykonywalny: __SO2_P2.exe__

### Uruchomienie
Aby uruchomić projekt, należy wykonać następujące kroki:
1. w zakładce "Run / Debug Configurations" należy wybrać konfigurację __Server__, a następnie wcisnąc przycisk __Run__.
2. Po uruchomieniu serwera, w zakładce "Run / Debug Configurations" należy wybrać konfigurację __SO2_P2__, a następnie wcisnąc przycisk __Run__.
3. Po uruchomieniu konfiguracji __SO2_P2__ wyskoczy okno terminala, w którym należy podać ilość klientów łączących się z serwerm chatu.
4. Po podaniu liczby klientów, uruchamiana jest podana liczbą plików __Client.exe__ w osobnych terminalach - łączą się oni z serwerem i mogą między sobą konwersować.

