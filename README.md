### Student: Romulescu Florin-Sorin
### Grupă: 323CA
### Limbaj de programare: C++17


# Temă 4 - Protocoale de Comunicații

## Descriere.
În această temă am avut de realizat un client care să poată interacționa cu un server deja implementat printr-un REST API. Clientul, scris în C++, trebuie să trimită către server comenzile pe care acesta le primește de la tastatură și să înțeleagă răspunsurile serverului.

Trimiterea comenzilor se va realiza prin translatarea acestora într-un `HTTP request` corespunzător.

## Compilare.

Codul se va compila prin comanda de mai jos. Toate Fișierele obiect se vor afla în directorul `/obj`.
```Makefile
make
```

```Makefile
make run
```
```Makefile
make clean
```
!!! Dacă se decomentează linia 19 din `utils.hpp` codul va fi compilat cu mesaje adiționale de debugging, cum ar fi:

- Conectarea/deconectarea la server
- Scrierea mesajelor trimise și primite în fișierul `log.txt`

```C++
#define DEBUG // Uncomment this line to enable debug mode
```

## Biblioteci
- `Laborator 10`: În realizarea temei am folosit funcțiile din fișierele `helpers.h` și `buffer.h` peste care am adăugat funcții wrapper în C++.
- `nlohmann json`: Pentru a lucra cu json am folosit biblioteca [nlohmann json](https://github.com/nlohmann/json).

## Structură fișiere
    /
    - Makefile
    - main -> executabilul din urma compilării
    - README -> acest fișier =)
    - obj/ -> aici se află fișierele obiect rezultate în urma compilării
    - log.txt -> fișier pentru debugging. Va fi creat doar daca programul va fi compilat cu debugging activat
    - src/
        - main.cpp -> Fișierul cu funcția main
        - lib/
            - Fișiere .cpp și .c care conțin implementarea headerelor
            - Commands/
                - Fișiere.cpp care conțin implementarea claselor din headerul Commands.h
        - include/
            - Fișiere .hpp
            - json.hpp -> biblioteca nlohmann json
            - helpers/
                - Fișiere .h (preluate din labul 10)

## Implementare.
---
Pentru implementarea temei m-am folosit de următoarele clase:

### 1. Input
Clasa Input va conține toți parametrii care pot fi primiți de la tastatură și se va ocupa de inputul pe care utilizatorul îl transmite.
În această clasă metoda statică `mainloop()` va crea un obiect Input și va citit parametrii corespunzători de la tastatură folosindu-ne de un `switch`. După ce determinăm fiecare parametru necesar pentru realizarea comenzii vom crea un obiect Command pe care îl vom folosi pt a executa comanda primită la tastatură.

### 2. Command
Clasa Command este o clasă abstractă care conține metodele abstracte `execute()` și `respond()` plus obiectul HTTPParser `parser`. Din această clasă derivăm câte o clasă pentru fiecare comandă care va implementa metodele abstracte pentru comanda lor specifică. Implementările comenzilor se află în subdirectorul `src/lib/Commands`.

Tot aici avem și clasa CommandFactory care folosește un design pattern Factory. Ea are o metodă `build(COMMAND_TYPE type)` care îmi întoarce un pointer către un obiect Command.

### 3. HTTPParser
Clasa HTTPParser este folosită pentru a crea un `HTTP request` valid către server. Implementarea se află în metoda `toString()` care realizează translatarea folosindu-ne de câmpurile nevide ale obiectului (completarea câmpurilor se face la execuția comenzii).

### 4. Session
Clasa Session folosește un design pattern singleton pentru a avea acces la acceași instanță oriunde în program. Ea salvează date specifice unei sesiuni precum cokieurile, tokenul JWT, utilizatorul, parola, plus un buffer în care vom pune requesturile noastre.

---
În fișierul `utils.hpp` am construit wrappers peste funcțiile importate din laboratorul 10 pentru a le folosi cu clasele din C++. Tot aici avem metode pentru a extrage codul de status, cookieurile și corpul unui `HTTP response`.

### 5. Main
În funcția main vom adăuga structurile de tip `pollfd` într-un vector pentru a știi când citim ceva la fișier și când primim ceva de la server. Cei doi membrii ai vectorului vor fi populați astfel:
```C++
    // Add stdin and socket to pollfd
    pollfds.push_back({
        .fd = 0,
        .events = 0x0001,
        .revents = 0
    });
    // Add socket to pollfd
    pollfds.push_back({
        .fd = sockdfd,
        .events = 0x0001,
        .revents = 0
    });
```
**Note:** sockfd a fost declarat mai sus când am făcut conexiunea cu serverul.

După vom instanția obiectului clasei singleton `Session` pentru a avea toate datele globale pe care le vom folosi pe parcursul programului (precum coada de requesturi sau statusul răspunsului).

în `do-while` vom face comunicarea cu serverul și citirea de la tastatură prin funcția `poll`. Când vom vrea să golim coada de requesturi vom încerca să ne reconectăm la server pentru a fi siguri că avem conexiunea deschisă.

Pe lângă outputurile care sunt date de comenzi, succesul comenzii este descris în prompt după execuția acesteia.

```
[OK] > 
[FAIL] > 
```

## Bibliotecă JSON
Am folosit biblioteca nlohmann json pentru a construi payloadul requestului pe care vreau să îl trimit. Am utilizat această bibliotecă pentru că îmi permite să lucrez cu construcții json cu o sintaxă apropiată de celelalte clase din STL.

Am utilizat biblioteca pentru definirea unui payload
```C++
using nlohmann::json=json;
json payload;
```
și parsarea câmpurilor în obiectul json:
```C++
parser->setPayload(nlohmann::json::parse(R"(
        {
            "username": ")" + this->username + R"(",
            "password": ")" + this->password + R"("
        }
    )"));
```
(**P.S.** Așa a fost explicat în documentația de pe github. Am tratat toate funcțiile din biliotecă ca pe niște black boxuri.)

## Probleme întâmpinate
- **Pierderea conexiunii cu serverul:** am stat puțin prea mult să rezolv problema asta până să îmi dau seama că mă pot reconecta la server înainte să trimit. Nush dacă pot face mai elegant de atât. Cred că sunt mult chestii redundante prin cod din cauza problemei (de exemplul coada de requesturi în care se află cel mult un request, dar aia e nu mai stau să modific acum).
- **Testarea automată:** când am încercat să trimit inputul printr-un fișier nu a mers bine. Sper să aveți mai mult noroc decât mine cu asta. Măcar trimiterea manuală merge cum trebuie.

