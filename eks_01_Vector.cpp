/**
 *   Programeksempel nr 1 - Vector (selvlaget enkel klasse).
 *
 *   Eksemplet viser en selvlaget implementasjon av container-klassen Vector.
 *   Det er laget kode for følgende funksjoner:
 *
 *     -  Vector(const int lengde = 200)
 *     -  ~Vector
 *     -  int   capacity()
 *     -  void  clear()
 *     -  void  display()
 *     -  bool  empty()
 *     -  T     get(const int pos)                   //  Dvs: ..... = vec[pos]
 *     -  bool  insert(const int pos, const T t)
 *     -  T     pop_back()
 *     -  T     pop_front()
 *     -  bool  push_back(const T t)
 *     -  bool  push_front(const T t)
 *     -  bool  remove(const int pos)
 *     -  void  resize(const int nyLengde)
 *     -  void  set(const int pos, const T value)    //  Dvs: vec[pos] = value
 *     -  int   size()
 *
 *   NB: For å formodentlig øke leseligheten og oversikten er medlems-
 *       funksjonene bevisst IKKE kommentert etter Doxygen-standarden.
 *
 *   @file     EKS_01_Vector.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>                  //  cout
#include <string>                    //  string
using namespace std;


/**
 *  Container-klassen Vector, som er en selvlaget versjon av STLs <vector>.
 *
 *  Inneholder en array av typen 'T', og to int'er som angir total
 *  kapasitet/lengde (capacity) og det nåværende antallet (size).
 */
template<typename T> //  'template'!  'T': fleksibel datatype!
class Vector {
    //  (finnes ikke direkte i Java!
    //   "Generics" er noe litt lignende.)
private:
    T *data; //  PEKER til array av typen 'T'.
    int kapasitet, antall; //  Max.lengde og nåværende antall.

public: //  Initierer medlemmer vha. default parameter:
    Vector(const int lengde = 200) {
        data = new T[lengde];
        kapasitet = lengde;
        antall = 0;
    }


    ~Vector() { delete [] data; } // Frigir allokert memory (vha.'new').


    int capacity() const { return kapasitet; }


    void clear() {
        //  Nullstiller arrayens bruk:
        //          for (int i = 0; i < antall; i++)  data[i] = 0;  //  Unødvendig?!!!
        antall = 0;
    }


    void display() const {
        //  Skriver HELE Vectorens innhold:
        for (int i = 0; i < antall; i++)
            cout << i << ": " << data[i] << "  ";
        cout << "\n\t'antall': " << antall << '\n';
    }


    bool empty() const { return (antall == 0); } //  Tomt eller ei.

    //  Tilsvarer:   .... = vec[pos].
    T get(const int pos) const {
        //  Henter (om mulig) element nr.pos:
        if (pos >= 0 && pos < antall) //  Innenfor bruksområde:
            return data[pos]; //  Returnerer aktuell verdi.
        else
            cout << "\nIndex out of bounds .....\n\n"; //  Egen melding ??
        return T();
    }

    //  Smetter inn (om mulig) 't' på plass 'pos':
    bool insert(const int pos, const T t) {
        if (antall == kapasitet) {
            resize(kapasitet + 100); //  Øker kapasiteten med 100.
        }
            if (pos >= 0  &&  pos <= antall) {       //  Lovlig indeks:
                for (int i = antall;  i > pos;  i--)  //  ALLE etter flyttes
                    data[i] = data[i-1];              //    opp ETT hakk.
                data[pos] = t;                        //  Ny smettes inn.
                antall++;                             //  Antall økes.
                return true;                          //  Innsmetting lyktes.
            }
                cout << "\nIndex out of bounds .....\n\n"; // Egen melding ??
            return false; //  Ingen innsmetting.
    }

    T pop_back() {
        //  Fjerner (om mulig) bakerste:
        if (!empty()) {
            //  Ikke tomt:
            T siste = data[antall - 1]; //  Tar vare på bakerste.
            antall--; //  Antallet reduseres med -1.
            return siste; //  Returnerer bakerste/siste.
        } else
            cout << "\nEmpty Vector - impossible to pop!\n\n";
        return T();
    }


    T pop_front() {
        //  Fjerner (om mulig) forreste:
        if (!empty()) {
            //  Ikke tomt:
            T forste = data[0]; //  Tar vare på forreste:
            remove(0); //  Fjerner den første.
            return forste; //  Returnerer den unnalagrede.
        } else
            cout << "\nEmpty Vector - impossible to pop!\n\n";
        return T();
    }


    bool push_back(const T t) {
        //  Legger ny inn bakerst,
        return insert(antall, t); //    vha. annen funksjon.
    }


    bool push_front(const T t) {
        //  Legger ny inn forrest,
        return insert(0, t); //    vha. annen funksjon.
    }


    bool remove(const int pos) {
        //  Fjerner (om mulig) element nr.'pos':
        if (pos >= 0 && pos < antall) {
            //  Lovlig indeks:
            for (int i = pos; i < antall - 1; i++) //  Flytter alle ETTERPÅ
                data[i] = data[i + 1]; //    ned ETT hakk.
            antall--; //  Totalantallet minskes.
            return true;
        } else {
            cout << "\nIndex out of bounds .....\n\n"; //  Egen melding ??
            return false;
        }
    }

    void resize(const int nyLengde) { //  Endrer kapasiteten til en større lengde, ikke mindre.
        if (nyLengde > kapasitet) {
            T *nyeData = new T[nyLengde]; //  Allokerer ny array.
            for (int i = 0; i < antall; i++)
                nyeData[i] = data[i]; //  Kopierer gamle verdier.
            delete [] data; //  Frigir gammel array.
            data = nyeData; //  Setter ny array som data.
            kapasitet = nyLengde; //  Oppdaterer kapasiteten.
        }
    }

    //  Tilsvarer:   vec[pos] = verdi.
    void set(const int pos, const T verdi) {
        if (pos >= 0 && pos < antall) //  Lovlig indeks:
            data[pos] = verdi; //  Setter til ny verdi.
        else
            cout << "\nIndex out of bounds .....\n\n"; //  Egen melding ??
    }


    int size() const { return antall; } // Antall nåværende elementer.
};


/**
 *  Hovedprogrammet:
 */
int main() {
    Vector<int> iVec; //  Lager en Vector av int'er.
    iVec.push_back(10);
    iVec.push_back(20);iVec.display();
    return 0;
}
