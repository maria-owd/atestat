#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;

ifstream f("dive-log.csv");

/**
  Structura pentru a stoca informatiile despre fiecare scufundare
  formatul este conform fisierului CSV exportat din programul Subsurface
 */
struct Dive {
  int diveNumber;
  char date[20];
  char time[10];
  int duration;
  float sac;
  int maxDepth;
  int avgDepth;
  char mode[20];
  int airTemp;
  int waterTemp;
  int cylinderSize;
  int startPressure;
  int endPressure;
  int o2;
  int he;
  char location[50];
  char gps[50];
  char diveMaster[50];
  char buddy[50];
  char suit[20];
  int rating;
  char visibility[20];
  char notes[100];
  float weight;
  char tags[50];
};

const int MAX_DIVES = 100;  // Numarul maxim de scufundari
const int MAX_LINE = 1000;  // Numarul maxim de caractere intr-o linie

const char SEP = ',';  // Separatorul din fisierul CSV
const char QUOTE =
    '"';  // Ghilimelele pentru a evita separarea in interiorul acestora
const char NEWLINE = '\n';  // Separatorul de linie

Dive diveLogs[MAX_DIVES];
int numDives = 0;

/**
 * Cauta urmatorul separator in linia de text,
 * tinand cont de ghilimele pentru a evita separarea in interiorul acestora
 * @param token - separatorul curent
 * @return char* - pointer la urmatorul separator gasit
 */
char* urmatorulSeparator(char*& token) {
  if (!token) return nullptr;

  char* start = token;
  bool intreGhilimele = false;

  while (*token) {
    if (*token == QUOTE) {
      intreGhilimele = !intreGhilimele;
    } else if (*token == SEP && !intreGhilimele) {
      *token = '\0';  // sfarsitul cuvantului
      token++;
      return start;
    }
    token++;
  }

  // nu a gasit separatorul, returneaza restul liniei
  return start;
}

void stergeGhilimele(char* str) {
  int len = strlen(str);
  if (len > 1 && str[0] == QUOTE && str[len - 1] == QUOTE) {
    for (int i = 1; i < len - 1; ++i) {
      str[i - 1] = str[i];
    }
    str[len - 2] = '\0';  // Null-terminate the string
  }
}

/**
 * Citeste o linie din fisierul CSV si o parseaza in structura Dive
 */
void parseLine(char* line, Dive& log) {
  char* sep = line;  // separatorul incepe cu inceputul liniei

  if (sep) log.diveNumber = atoi(urmatorulSeparator(sep));

  if (sep) {
    strcpy(log.date, urmatorulSeparator(sep));
    stergeGhilimele(log.date);
  } else
    strcpy(log.date, "N/A");

  if (sep) {
    strcpy(log.time, urmatorulSeparator(sep));
    stergeGhilimele(log.time);
  } else
    strcpy(log.time, "N/A");

  if (sep)
    log.duration = atoi(urmatorulSeparator(sep));
  else
    log.duration = 0;

  if (sep)
    log.sac = atof(urmatorulSeparator(sep));
  else
    log.sac = 0.0f;

  if (sep)
    log.maxDepth = atoi(urmatorulSeparator(sep));
  else
    log.maxDepth = 0;

  if (sep)
    log.avgDepth = atoi(urmatorulSeparator(sep));
  else
    log.avgDepth = 0;

  if (sep) {
    strcpy(log.mode, urmatorulSeparator(sep));
    stergeGhilimele(log.mode);
  } else
    strcpy(log.mode, "N/A");

  if (sep)
    log.airTemp = atoi(urmatorulSeparator(sep));
  else
    log.airTemp = 0;

  if (sep)
    log.waterTemp = atoi(urmatorulSeparator(sep));
  else
    log.waterTemp = 0;

  if (sep)
    log.cylinderSize = atoi(urmatorulSeparator(sep));
  else
    log.cylinderSize = 0;

  if (sep)
    log.startPressure = atoi(urmatorulSeparator(sep));
  else
    log.startPressure = 0;

  if (sep)
    log.endPressure = atoi(urmatorulSeparator(sep));
  else
    log.endPressure = 0;

  if (sep)
    log.o2 = atoi(urmatorulSeparator(sep));
  else
    log.o2 = 0;

  if (sep)
    log.he = atoi(urmatorulSeparator(sep));
  else
    log.he = 0;

  if (sep) {
    strcpy(log.location, urmatorulSeparator(sep));
    stergeGhilimele(log.location);
  } else
    strcpy(log.location, "N/A");

  if (sep) {
    strcpy(log.gps, urmatorulSeparator(sep));
    stergeGhilimele(log.gps);
  } else
    strcpy(log.gps, "N/A");

  if (sep) {
    strcpy(log.diveMaster, urmatorulSeparator(sep));
    stergeGhilimele(log.diveMaster);
  } else
    strcpy(log.diveMaster, "N/A");

  if (sep) {
    strcpy(log.buddy, urmatorulSeparator(sep));
    stergeGhilimele(log.buddy);
  } else
    strcpy(log.buddy, "N/A");

  if (sep) {
    strcpy(log.suit, urmatorulSeparator(sep));
    stergeGhilimele(log.suit);
  } else
    strcpy(log.suit, "N/A");

  if (sep)
    log.rating = atoi(urmatorulSeparator(sep));
  else
    log.rating = 0;

  if (sep) {
    strcpy(log.visibility, urmatorulSeparator(sep));
    stergeGhilimele(log.visibility);
  } else
    strcpy(log.visibility, "N/A");

  if (sep) {
    strcpy(log.notes, urmatorulSeparator(sep));
    stergeGhilimele(log.notes);
  } else
    strcpy(log.notes, "N/A");

  if (sep)
    log.weight = atof(urmatorulSeparator(sep));
  else
    log.weight = 0.0f;

  if (sep) {
    strcpy(log.tags, urmatorulSeparator(sep));
    stergeGhilimele(log.tags);
  } else
    strcpy(log.tags, "N/A");
}

void citire() {
  if (!f.is_open()) {
    cerr << "Error: Could not open file 'dive-log.csv'." << endl;
    exit(1);
  }

  char line[MAX_LINE];

  // Skip the header line
  if (!f.getline(line, MAX_LINE)) {
    cerr << "Error: File 'dive-log.csv' is empty or malformed." << endl;
    exit(1);
  }

  while (f.getline(line, MAX_LINE) && numDives < MAX_DIVES) {
    parseLine(line, diveLogs[numDives++]);
  }

  if (numDives == 0) {
    cerr << "Error: No valid dive logs found in 'dive-log.csv'." << endl;
    exit(1);
  }
}

void afisareCapTabel() {
  cout << "+------+---------------------+---------+----------+-------------------------------+" << endl;
  cout << "| Nr.  | Data si ora         | Durata  | Adancime | Locul scufundarii             |" << endl;
  cout << "+------+---------------------+---------+----------+-------------------------------+" << endl;
}

void afisareLinie(const Dive& dive) {
  cout << "| " << setw(4) << left << dive.diveNumber << " | "
       << setw(10) << left << dive.date << " " << setw(8) << dive.time << " | "
       << setw(7) << right << dive.duration << " min | "
       << setw(8) << dive.maxDepth << " m | "
       << setw(30) << left << dive.location << " |" << endl;
}

void afisareDetaliata() {
  for (int i = 0; i < numDives; ++i) {
    Dive dive = diveLogs[i];

    cout << "Dive #" << dive.diveNumber << ":" << endl;
    cout << "  Date: " << dive.date << endl;
    cout << "  Time: " << dive.time << endl;
    cout << "  Duration: " << dive.duration << " minutes" << endl;
    cout << "  SAC: " << dive.sac << endl;
    cout << "  Max Depth: " << dive.maxDepth << " meters" << endl;
    cout << "  Avg Depth: " << dive.avgDepth << " meters" << endl;
    cout << "  Mode: " << dive.mode << endl;
    cout << "  Air Temp: " << dive.airTemp << " °C" << endl;
    cout << "  Water Temp: " << dive.waterTemp << " °C" << endl;
    cout << "  Cylinder Size: " << dive.cylinderSize << " liters" << endl;
    cout << "  Start Pressure: " << dive.startPressure << " bar" << endl;
    cout << "  End Pressure: " << dive.endPressure << " bar" << endl;
    cout << "  O2: " << dive.o2 << "%" << endl;
    cout << "  He: " << dive.he << "%" << endl;
    cout << "  Location: " << dive.location << endl;
    cout << "  GPS: " << dive.gps << endl;
    cout << "  Dive Master: " << dive.diveMaster << endl;
    cout << "  Buddy: " << dive.buddy << endl;
    cout << "  Suit: " << dive.suit << endl;
    cout << "  Rating: " << dive.rating << "/5" << endl;
    cout << "  Visibility: " << dive.visibility << endl;
    cout << "  Notes: " << dive.notes << endl;
    cout << "  Weight: " << dive.weight << " kg" << endl;
    cout << "  Tags: " << dive.tags << endl;
    cout << "----------------------------------------" << endl;
  }
}

void afisare() {
  afisareCapTabel(); 

  // Afișează fiecare scufundare
  for (int i = 0; i < numDives; ++i) {
    afisareLinie(diveLogs[i]);
  }

  // Linie de încheiere
  cout << "+------+---------------------+---------+----------+-------------------------------+" << endl;
}

void adaugareScufundare() {
  if (numDives >= MAX_DIVES) {
    cout << "Nu mai este loc pentru scufundari!" << endl;
    return;
  }

  Dive newDive = {};
  newDive.diveNumber = numDives + 1;

  cout << "Introduceti detaliile scufundarii #" << newDive.diveNumber << endl;

  cout << "Data (format: YYYY-MM-DD): ";
  cin.getline(newDive.date, sizeof(newDive.date));

  cout << "Ora (format: HH:MM): ";
  cin.getline(newDive.time, sizeof(newDive.time));

  cout << "Durata (minute): ";
  cin >> newDive.duration;

  cout << "Adancime maxima (metri): ";
  cin >> newDive.maxDepth;

  cin.ignore();  // sterge newline-ul ramas in buffer

  cout << "Locul scufundarii: ";
  cin.getline(newDive.location, sizeof(newDive.location));

  // Adaugati aici restul campurilor dorite

  diveLogs[numDives++] = newDive;

  cout << "Scufundarea a fost adaugata cu succes!" << endl;
}

/**
 * Editare scufundare
 */
void editareScufundare() {
  if (numDives == 0) {
    cout << "Nu exista scufundari in jurnal pentru a fi editate!" << endl;
    return;
  }

  afisare();  // Afișează jurnalul pentru a permite utilizatorului să aleagă o
              // scufundare
  int diveNumber;
  cout << "Introduceti numarul scufundarii pe care doriti sa o editati: ";
  cin >> diveNumber;

  // Găsește scufundarea după număr
  int index = -1;
  for (int i = 0; i < numDives; ++i) {
    if (diveLogs[i].diveNumber == diveNumber) {
      index = i;
      break;
    }
  }

  if (index == -1) {
    cout << "Scufundarea cu numarul #" << diveNumber << " nu a fost gasita!"
         << endl;
    return;
  }

  Dive& dive = diveLogs[index];
  cout << "Editati detaliile pentru scufundarea #" << dive.diveNumber << ":"
       << endl;

  cin.ignore();  // Curăță buffer-ul înainte de a citi șiruri de caractere

  cout << "Data curenta (" << dive.date << "): ";
  cin.getline(dive.date, sizeof(dive.date));

  cout << "Ora curenta (" << dive.time << "): ";
  cin.getline(dive.time, sizeof(dive.time));

  cout << "Durata curenta (" << dive.duration << " minute): ";
  cin >> dive.duration;

  cout << "Adancime maxima curenta (" << dive.maxDepth << " metri): ";
  cin >> dive.maxDepth;

  cin.ignore();  // Curăță buffer-ul

  cout << "Locul curent al scufundarii (" << dive.location << "): ";
  cin.getline(dive.location, sizeof(dive.location));

  // Adaugă alte câmpuri dacă este necesar
  cout << "Editarea scufundarii #" << dive.diveNumber << " a fost finalizata!"
       << endl;
}

/**
 * Stergere scufundare
 */
void stergereScufundare() {
  if (numDives == 0) {
    cout << "Nu exista scufundari in jurnal pentru a fi sterse!" << endl;
    return;
  }

  afisare();  // Afișează jurnalul pentru a permite utilizatorului să aleagă o
              // scufundare
  int diveNumber;
  cout << "Introduceti numarul scufundarii pe care doriti sa o stergeti: ";
  cin >> diveNumber;

  // Găsește scufundarea după număr
  int index = -1;
  for (int i = 0; i < numDives; ++i) {
    if (diveLogs[i].diveNumber == diveNumber) {
      index = i;
      break;
    }
  }

  if (index == -1) {
    cout << "Scufundarea cu numarul #" << diveNumber << " nu a fost gasita!"
         << endl;
    return;
  }

  // Șterge scufundarea prin mutarea tuturor elementelor următoare cu o poziție
  // înapoi
  for (int i = index; i < numDives - 1; ++i) {
    diveLogs[i] = diveLogs[i + 1];
    diveLogs[i].diveNumber = i + 1;  // Reindexează numerele scufundărilor
  }

  numDives--;  // Reduce numărul total de scufundări
  cout << "Scufundarea #" << diveNumber << " a fost stearsa cu succes!" << endl;
}

/**
 * Salvează jurnalul de scufundări în fișierul CSV original
 */
void salvareJurnal() {
  ofstream outFile("dive-log.csv");

  if (!outFile.is_open()) {
    cerr << "Error: Nu s-a putut deschide fișierul 'dive-log.csv' pentru "
            "scriere."
         << endl;
    return;
  }

  // Scrie antetul fișierului CSV
  outFile
      << "dive number,date,time,duration [min],sac [l/min],maxdepth "
         "[m],avgdepth [m],mode,airtemp [C],watertemp [C],cylinder size "
         "[l],startpressure [bar],endpressure [bar],o2 [%],he "
         "[%],location,gps,divemaster,buddy,suit,rating,visibility,notes,"
         "weight [kg],tags\n";

  // Scrie fiecare scufundare în fișier
  for (int i = 0; i < numDives; ++i) {
    Dive dive = diveLogs[i];
    outFile << dive.diveNumber << ","
            << "\"" << dive.date << "\","
            << "\"" << dive.time << "\"," << dive.duration << "," << dive.sac
            << "," << dive.maxDepth << "," << dive.avgDepth << ","
            << "\"" << dive.mode << "\"," << dive.airTemp << ","
            << dive.waterTemp << "," << dive.cylinderSize << ","
            << dive.startPressure << "," << dive.endPressure << "," << dive.o2
            << "," << dive.he << ","
            << "\"" << dive.location << "\","
            << "\"" << dive.gps << "\","
            << "\"" << dive.diveMaster << "\","
            << "\"" << dive.buddy << "\","
            << "\"" << dive.suit << "\"," << dive.rating << ","
            << "\"" << dive.visibility << "\","
            << "\"" << dive.notes << "\"," << dive.weight << ","
            << "\"" << dive.tags << "\"\n";
  }

  outFile.close();
  cout << "Jurnalul a fost salvat cu succes în 'dive-log.csv'!" << endl;
}

/**
 * Cautare scufundare dupa locatie
 */
void cautareScufundare() {
  if (numDives == 0) {
    cout << "Nu exista scufundari in jurnal pentru a fi cautate!" << endl;
    return;
  }

  char searchTerm[50];
  cout << "Introduceti un sir de caractere pentru cautare in locatie: ";
 // cin.ignore(); // Curăță buffer-ul
  cin.getline(searchTerm, sizeof(searchTerm));

  bool found = false;

  afisareCapTabel(); // Afișează capul de tabel

  // Caută și afișează scufundările care conțin șirul de caractere
  for (int i = 0; i < numDives; ++i) {
    if (strstr(diveLogs[i].location, searchTerm) != NULL) { // Verifică dacă locația conține șirul
      found = true;
      afisareLinie(diveLogs[i]);
    }
  }

  // Linie de încheiere
  cout << "+------+---------------------+---------+----------+-------------------------------+" << endl;

  if (!found) {
    cout << "Nu s-au gasit scufundari care sa contina '" << searchTerm << "' in locatie." << endl;
  }
}

/**
 * Afisare logo cofetarie
 */
void logo() {
  cout << endl;
  cout << "    ___  _           _              " << endl;
  cout << "    |   \\(_)_ _____  | |   ___  __ _ " << endl;
  cout << "    | |) | \\ V / -_) | |__/ _ \\/ _` |" << endl;
  cout << "    |___/|_|\\_/\\___| |____\\___/\\__, |" << endl;
  cout << "                               |___/ " << endl;
}

/**
 * Afisare meniu principal
 *
 * @return int -> optiunea selectata
 */
int afisareMeniu() {
  logo();
  cout << endl << "*** Alegeti optiunea dorita ***" << endl << endl;
  cout << "1. Jurnalul de scufundari" << endl;
  cout << "2. Jurnalul de scufundari detaliat" << endl;
  cout << "3. Adaugare scufundare" << endl;
  cout << "4. Editare scufundare" << endl;
  cout << "5. Stergere scufundare" << endl;
  cout << "6. Cautare scufundare" << endl;
  cout << "7. Statistici scufundari" << endl;
  cout << "8. Salvare jurnal" << endl;
  cout << "9. Despre program" << endl;
  cout << "0. Iesire din program" << endl;

  int opt;

  cout << endl << endl << "Alegeti numarul optiunii: ";
  cin >> opt;

  // sterge lista de caractere de la tastatura
  cin.clear();
  fflush(stdin);

  return opt;
}

/**
 * Afisare membrii echipei
 */
void despreProgram() {
  cout << "Proiect atestat 2025: Dive-Log" << endl;
  cout << "♥ " << "autor: Maiorescu Maria" << endl;
  cout << "♥ " << "clasa XII MI-2" << endl;
  cout << "♥ " << "Colegiul National CD Loga Timisoara" << endl;
}

/**
 * Procesare comenzi de la utilizator
 * Iesirea din program se face cu optiunea 0
 */
void meniuPrincipal() {
  int opt;
  do {
    cout << endl << endl;
    opt = afisareMeniu();
    cout << endl << endl;
    switch (opt) {
      case 1:
        afisare();
        break;

      case 2:
        afisareDetaliata();
        break;

      case 3:
        adaugareScufundare();
        break;

      case 4:
        editareScufundare();
        break;

      case 5:
        stergereScufundare();
        break;

      case 6:
        cautareScufundare();
        break;

      case 7:
        cout << "Optiunea nu este implementata inca!" << endl;
        break;
      case 8:
        salvareJurnal();
        break;

      case 9:
        despreProgram();
        break;
      case 0:
        // exit, nu facem nimic
        break;
      default:
        // optiune gresita
        cout << "Optiunea '" << opt << "' este gresita!" << endl;
    }

    // se asteapta apasare Enter pentru a vizualiza rezultatele
    if (opt) {
      cout << endl << "Apasati Enter pentru a continua ...";
      cin.get();
    }
  } while (opt);
}

/**
 * Functie principala
 */
int main() {
  citire();

  meniuPrincipal();

  return 0;
}
