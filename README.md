
# Dive-Log  
## Jurnal Electronic de Scufundări

**Autor:** Maria Maiorescu  
**Clasa:** XII MI-2  
**Colegiul Național:** C.D. Loga, Timișoara

---

## Scopul Proiectului
- Gestionarea unui jurnal electronic de scufundări.
- Importarea datelor exportate din aplicația **Subsurface** în format CSV.
- Adăugare, editare și ștergere de scufundări.
- Căutare rapidă după locație.
- Oferirea de statistici și vizualizări detaliate pentru analiza scufundărilor.

---

## Funcționalități principale
- 📄 Import date CSV (format Subsurface).
- ➕ Adăugare/Editare/Ștergere scufundări.
- 🔍 Căutare scufundări după locație.
- 📊 Vizualizare tabelară și detaliată a jurnalului.
- 📈 Generare de statistici relevante.

---

## Structura de date principală
```cpp
struct Dive {
    int diveNumber;
    char date[20];
    char time[10];
    int duration;
    float sac; // consum aer
    int maxDepth;
    ...
    char location[50];
    ...
};
```

---

## Fluxul principal al programului
1. Citirea fișierului CSV cu scufundări: `citire()`
2. Afișarea meniului interactiv: `afisareMeniu()`
3. Operațiuni disponibile:
   - Afișare jurnal scufundări
   - Adăugare/Editare/Ștergere
   - Căutare după locație
   - Vizualizare detaliată
   - Salvare jurnal în CSV
   - Statistici scufundări

---

## Exemple de cod

### Citirea fișierului CSV:
```cpp
void citire() {
    ifstream f(FILE_NAME);
    while (f.getline(line, MAX_LINE) && numDives < MAX_DIVES) {
        citesteLinie(line, diveLogs[numDives++]);
    }
}
```
---

## Statistici generate automat
- 🏆 **Top 3 cele mai lungi scufundări**
- 🏅 **Top 3 cele mai adânci scufundări**
- ✅ **Cele mai eficiente scufundări** (consum aer mic)
- ⚠️ **Cele mai ineficiente scufundări** (consum aer mare)
- 📍 **Locuri populare de scufundare**
- ⏱️ **Durata medie a scufundărilor**
- 📏 **Adâncimea medie a scufundărilor**

---

## Dificultăți întâmpinate
- **Prelucrarea fișierului CSV:** separatorul fiind virgula, dar unele câmpuri text sunt încadrate în ghilimele și conțin virgulă internă.
- **Calculul locațiilor populare:** utilizarea unei structuri auxiliare pentru numărarea aparițiilor.
- **Sortarea pentru statistici:** utilizarea unui vector auxiliar pentru a proteja datele originale.
- **Inconsistențe în datele CSV:** tratarea câmpurilor neutilizate sau incomplete.
