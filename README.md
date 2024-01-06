# projects
My collection of code.

- **Merge sort.** Porównanie prędkości sortowania _n_ elementów dla tablic z liczbami: losowymi, w kolejności rosnącej, malejącej, stałych i rosnąco-malejących V. Program generuje wyniki czasów w milisekundach i zapisuje wyniki do pliku, z którego następnie korzysta skrypt Gnuplot. Po wykonaniu programu napisanego w języku C, uruchamiamy skrypt w Gnuplot, który generuje wykres.

- **Islands.** Program pokazuje obecną lokalizację kota. Kot przechodzi po planszy w poszukiwaniu wysp. Jeśli napotka na fragment lądu, "zjada" go i sprawdza sąsiednie lokalizacje na planszy, czy nie ma dalszych fragmentów wyspy, połączonych ze sobą krawędzią. W ten sposób "zjada" całą wyspę i udaje się na dalsze poszukiwania. Program ponadto zlicza ilość "zjedzonych" wysp.

- **Notes Organizer.** Aplikacja webowa ASP.NET, służąca do zarządzania i przechowywania notatek. Organizer notatek implementuje podstawowe operacje CRUD. Aplikacja oparta jest na architekturze cebulowej. Obecna wersja przechowuje stan aplikacji w pamięci RAM.

- **Readers–writers problem.** Program wykorzystuje mechanizmy synchronizacji procesów System V Linux. Program jest oparty na klasycznym problemie synchronizacji - czytelnicy i pisarze (w czytelni może przebywać wiele czytelników lub jeden pisarz). Ponadto program realizuje dodatkowe założenia: jest faza relaksu i faza pobytu w czytleni. Każdy proces może w fazie relaksu zmieniać swoją rolę z czytelnika na pisarza i odwrotnie. Napisane przez pisarza dzieła umieszczane są w kolejce komunikatów, przy czym zainteresowane dziełem są te procesy, które w momencie dodawania działa są w roli czytelnika. Po przeczytaniu dzieła przez wszystkie zainteresowane procesy, dzieło jest usuwane z kolejki. Czytelnik podczas pobytu w czytelni może przeczytać co najwyżej jedno dzieło. Pisarz podczas pobytu w czytelni również może przeczytać co najwyżej jedno dzieło oraz może napisać co najwyżej jedno dzieło. Liczba procesów jest ustalona. Także kolejka komunikatów ma ustaloną max ilość dzieł.

- **Form.** Formularz z walidacją poprawności wypełnienia pól. Błędne wypełnienie pola sygnalizowane jest czerwoną ramką i gwiazdką. Wysyłanie formularza jest zablokowane do momentu poprawnego wypełnienia wszystkich jego pól - przy próbie wysłania, nad formularzem pojawia się lista ze szczegółowymi błędami.

- **Table.** Tabelka z możliwością wypełniania pól, dodawania wierszy, zmiany kolejności wierszy, usuwania pojedynczych wierszy oraz usuwania wielu zaznaczonych wierszy. Zliczanie liczby wierszy tabeli.

- **To Do List.** Aplikacja w React.js, w której wpisuje się rzeczy do zrobienia i wykreśla się wykonane zadania. Wykonane zadania można ukryć lub usunąć.