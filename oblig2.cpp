// August Oksavik, 16HBPROGA, 470916


//  Programmet holder orden p† ansatte i en bedrift/organisasjon,
//  deres partnere og barn. 

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif 

//  INCLUDE:
#include  <iostream>         //  cin, cout
#include  <fstream>          //  ifstream, ofstream
#include  <cstring>          //  strcpy, strlen, strncmp
#include  <cctype>           //  toupper
#include  <cstdlib>          //  itoa
#include <iomanip>			// setw

using namespace std;

//  CONST:
const int MAXSVAR = 10000;	// max antall sifer et ansatt nummer kan ha
const int MAXANS = 100;     //  Max.antall ansatte.
const int MAXBARN = 20;     //  Max.antall barn EN ansatt kan ha.
const int MAXTXT = 80;     //  Max.lengde for en tekst/streng.
const int DATOLEN = 7;     //  Fast lengde for en dato (inkl. '\0').

						   //  ENUM:
enum Kjonn { jente, gutt };
char tab = '\t';

//  DEKLARASJON AV FUNKSJONER:
void skrivMeny();
char les();
int  les(char* t, int min, int max);
int  finnesAllerede(int ansNr);
void smettInn();
void lesFraFil();
void skrivTilFil();
void nyAnsatt();
void partnerEndring();
void nyttBarn();
void dataOmAnsatt();
void alleEttAar();
void fjernAnsatt();
void linje();

//  KLASSER:
class Person {                   //  Abstrakt baseklasse.
protected:
	char  fodselsdato[DATOLEN];   //  Dens f›dselsadato p† formen: ††mmdd
	char* fornavn;                //  Personens fornavn.

public:
	Person()		// får in fornavn og fødselsdato fra bruker
	{
		cout << "skriv inn persones F›deselsdato p† formen ††mmdd: ";
		cin >> fodselsdato;
		char temp[MAXTXT];			//lager en temp
		cout << "Skriv in personens fornavn: ";
		cin >> temp;
		fornavn = new char[strlen(temp)];	//lager char utifra strls på temp
		strcpy(fornavn, temp);
		
	}

	Person(ifstream & inn)			// får inn fødselsdato og fornavn fra fil
	{
		char temp[MAXTXT];
		inn >> fodselsdato;
		inn >> temp;
		fornavn = new char[strlen(temp)];
		strcpy(fornavn, temp);
	}

	~Person() 
	{
	}

	void skrivTilFil(ofstream & ut) 
	{
		ut << fodselsdato<<tab;		//skriver fodesldato og fornavn til fil
		ut << fornavn <<tab;
	
	}

	
};


class Barn : public Person {          //  Konkret klasse.
private:
	Kjonn kjonn;                       //  Barnets kj›nn (jente eller gutt).

public:
	Barn()						//constructor
	{
	int n = 1;									
		
		do							//spør bruker og får inn kjønnet til barnet
		{	
			
			
			cout << "Hva er barnets kj›nn? J/G: ";
			char ch;
			cin >> ch; cin.ignore();
			ch = toupper(ch);		// gjør om til uppercase
			if ( ch == 'J')
			{
				kjonn = jente;
				n = 1;				//passer på at løkken ikke kjøres igjen
			}
			else if (ch  == 'G')
			{
				kjonn = gutt;
				n = 1;
			} 
			else                 //om bruker trykker noen annet enn J/G
			{
				cout << "input ikke godkjent prøv igjen";
				n = 0;
			}
		} while (n == 0);

	}

	Barn(ifstream & inn) : Person(inn)
	{

		int n;
		inn >> n;						//henter binær verdi for barnets kjønn
		if (n == 0)kjonn = jente;		//setter det til riktig enum
		else if (n == 1)kjonn = gutt;


	}

	void skrivTilFil(ofstream & ut)	
	{
		Person::skrivTilFil(ut);//skriver til fil barnets info
		ut << kjonn;			// skriver binært barnets kjønn
	}

	void display() 
	{
		cout << "\nBarnets\n Fornavn: " << fornavn;	// skriver ut fornavn
		cout << "\nFødselsdato: " << fodselsdato;	// og fødselsdato
		cout << "\nKj›nn: ";
		if (kjonn == 0) cout << "Jente";	   //sjekker hvilket kjønn
		else if (kjonn == 1) cout << "Gutt";  // barnet er og skriver det ut
	}

	int Aar()			//rentunerer int utifra barns fødeår
	{
		char temp[2];						//lager en temp strlse 2
		temp[0] = fodselsdato[1];			// seter første og andre
		temp[1] = fodselsdato[2];		// verdi i fødselsdato over til temp
		return atoi(temp);			//gjør om temp til og int og retunerer
	}

};


class Voksen : public Person {   //  Abstrakt baseklasse.
protected:
	char* etternavn;              //  Den voksnes etternavn.

public:
	Voksen()			//får in etternavn 
	{
		char temp[MAXTXT];
		cout << "skriv inn ansattes etternavn: ";
		cin >> temp;
		etternavn = new char[strlen(temp) + 1];
		strcpy(etternavn, temp);
	}

	Voksen(ifstream & inn) : Person(inn)	//får in etternavn fra fil
	{
		char temp[MAXTXT];
		inn >> temp;
		etternavn = new char[strlen(temp) + 1];
		strcpy(etternavn, temp);
	}

	~Voksen() 
	{
		delete(etternavn);
	}

	void skrivTilFil(ofstream & ut) //skriver etternavn til fil
	{
		ut << etternavn << tab;
	}

	void display()  // displayer fornavn, etternavn og fødselsdato for voksne
	{
		cout << "\n\nPersonens\nFornavn: " << fornavn;
		cout << "\nEtternavn: " << etternavn;
		cout << "\nF›delsdato: " << fodselsdato;

	}

	//  ANDRE MEDLEMSFUNKSJONER ?

};


class Partner : public Voksen {  //  Konkret klasse.
private:
	int telefon1;                 //  Partnerens 1.treff-telefon (f.eks. jobb)
	int telefon2;                 //  Partnerens 2.treff-telefon (f.eks. mobil)

public:
	Partner()					//får inn relevant info fra bruker
	{
		cout << "Skriv inn partners jobb telefon nummer: ";
		cin >> telefon1;
		cout << "Skriv inn partners mobil telefon nummer: ";
		cin >> telefon2;
	}

	Partner(ifstream & inn) : Voksen(inn)  // får in relevant info fra fil
	{
		inn >> telefon1;
		inn >> telefon2;
	}

	void skrivTilFil(ofstream & ut)	//skriver til fil alle verdier fra person,
	{							//voksne og partner.
		Person::skrivTilFil(ut);
		Voksen::skrivTilFil(ut);
		ut << telefon1 << tab;
		ut << telefon2 << tab;
	}

	void display()		//skriver ut partner info
	{
		Voksen::display();
		cout << "\nJobb nummer: " << telefon1;
		cout << "\nMobil nummer: " << telefon2;
	}


};


class Ansatt : public Voksen //  Konkret klasse.
{       
private:
	int      nr;                       //  Unikt/entydig ansatt-nummer.
	int      antBarn;                  //  Antall barn vedkommende har.
	char*    adresse;                  //  Gate- og postadresse.
	Partner* partner;                  //  Peker til partneren.
	Barn*    barn[MAXBARN + 1];          //  Pekere til alle barna.
	bool	 part;
public:
	Ansatt() {
		cout << "\n\nWARNING 1: En Ansatt opprettes ALLTID med et nummer!\n\n";
	}

	Ansatt(int n)		//nullstiler verdier og får inn info
	{
		partner = NULL;        //nullstiler pointer så den kan if testes senere
		part = 0;			// initsialisere part
		char temp[MAXTXT];	
		nr = n;						//setter nr til å være lik constructor-arg
		antBarn = 0;								//initisalisere antbarn
		cout << "Skriv inn ansattes adresse: ";
		cin >> temp;						//lager ny char utifra temp
		adresse = new char[strlen(temp) + 1];
		strcpy(adresse, temp);
		
	}

	Ansatt(int n, ifstream & inn) : Voksen(inn)  //nullstiler variable og får 
	{											// inn info
		partner = NULL;		//nullstiller pointer
		
		nr = n;				// setter nr lik constructor-arg
		char temp[MAXTXT];
		inn >> temp;
		antBarn = 0;
		adresse = new char[strlen(temp) + 1];
		strcpy(adresse, temp);
		inn >> part;			// får in binær bool verdi
		
		if (part)				//sjekker om ansatt har ein partner
		{
			partner = new Partner(inn);	//lager ny partner obj utifra fil info
		}
		inn >> antBarn;				//sjekker om ansatt har barn og hvor mange
        if (antBarn && antBarn < MAXBARN)  //sjekker om han kan ta in flere barn
		{
            for (int i = 1; i <= antBarn; i++)	// lager barn utifra hvormange
			{									// filen oppgir
                barn[i] = new Barn(inn);		//
            }
        }
	}

	~Ansatt()  // sletter partner og alle barna
	{
		delete(partner);	
		for (int i = 1; i <= antBarn; i++) 
		{
			delete barn[i];

		}

	
	}
	void skrivTilFil(ofstream & ut)    //skriver ut relevant info om ansatt
	{									
		Person::skrivTilFil(ut);
		Voksen::skrivTilFil(ut);
		ut << adresse << tab;		//adresse og bool for partner skrives ut
		ut << part << tab;
		if (part)				// skriver partners info hvist part= true
		{
			partner->skrivTilFil(ut);
		}
		ut << antBarn << tab;		//skriver ut antal barn og deres info
		if (antBarn <= MAXBARN)
		{
			for (int i = 1; i <= antBarn; i++)
			{
				barn[i]->skrivTilFil(ut);	
			}
		}
	}


	void display()		// skriver ut ansat nr og adresse for ansatt + voksen
	{					//info
		Voksen::display();
		cout << "\nAnsatt nummer: " << nr;
		cout << "\nAdresse: "<< adresse;
		
		 if (partner != NULL)	//sjekker om partner inneholder noe og displayer
		{
			partner->display();		
		}
		 if (antBarn > 0)		//sjekker om ansatt har barn og skriver ut info
		 {
			 for (int i = 1; i <= antBarn; i++)
			 {
				 barn[i]->display();
			 }
		 }
	}
	void nyPart()	// sjekker om partner inneholder noe og erstatter
	{
		if (partner != NULL)delete(partner);
		cout << "Vil du legge inn ein ny partener? J/N ";
		if (les() == 'J')
		{
			partner = new Partner;
			part = 1;
		}
	}
	int skrivNr()		// retunere nr
	{
		return(nr);
	}

	void NyttBarn()	// lager nytt barn objekt om det er mulig
	{
		if (antBarn >= MAXBARN + 1)
		{
			cout << "Maks antall barn er n†d";
		}
		else
		{
			barn[++antBarn] = new Barn;
		}
	}
	void BarnAar(int n)	// sjekker hvilke ansatte har barn født i spesifikt år
	{
		cout << antBarn;
		for (int i = 1; i < antBarn; i++)
		{
			if (barn[i]->Aar() == n)
			{
				cout << "ansatt nr: " << nr;
				cout << "Har barn født i dette året" << endl;

			}
		}
	}


};

//  GLOBALE VARIABLE:
Ansatt* ansatte[MAXANS + 1];     //  Array med peker til alle de ansatte.
int sisteBrukt;                //  Siste 'skuff' brukt av "ansatte"-arrayen.

							   //  HOVEDPROGRAMMET:
int main() {
	char kommando;                //  Brukerens ›nske/valg.

	lesFraFil();                  //  Leser inn hele datastrukturen fra fil.
	skrivMeny();					//  Meny av brukerens valg
	skrivTilFil();
	kommando = les();             //  Leser brukerens ›nske/valg
	
	while (kommando != 'Q') {
		switch (kommando) {
		case 'N': nyAnsatt();       break;   //  Legg inn (om mulig) ny ansatt.
		case 'P': partnerEndring(); break;   //  Endre data om partner.
		case 'B': nyttBarn();       break;   //  Legg inn (om mulig) nytt barn.
		case 'D': dataOmAnsatt();   break;   //  Skriv alle data om en ansatt.
		case 'A': alleEttAar();     break;   //  Ansnr med barn f›dt et gitt †r.
		case 'F': fjernAnsatt();    break;   //  Fjern/slett en ansatt.
		default:  skrivMeny();      break;   //  Meny av brukerens valg.
		}
		
		kommando = les();           //  Leser brukerens ›nske/valg.
	}
	return 0;
}

//  DEFINISJON AV FUNKSJONER:
void skrivMeny() {
	cout << "\n\nFLGENDE KOMMANDOER ER TILGJENGELIGE:";
	cout << "\n\tN - Ny ansatt";
	cout << "\n\tP - Partner-endring";
	cout << "\n\tB - nytt Barn";
	cout << "\n\tD - alle Data om en ansatt";
	cout << "\n\tA - Alle barn f›dt ett gitt †r";
	cout << "\n\tF - Fjern en ansatt";
	cout << "\n\tQ - Quit / avslutt";
}


char les() {                     //  Leser og returnerer ETT upcaset tegn.
	char ch;
	cout << "\n\nSkriv ein bokstav:  ";
	cin >> ch;  cin.ignore();
	return (toupper(ch));
}
//  Skriver ledetekst (t), leser og
//    returnerer et tall mellom min og max:
int les(char* t, int min, int max) {
	int tall;
	do {
		cout << '\t' << t << " (" << min << '-' << max << "):  ";
		cin >> tall;  cin.ignore();
	} while (tall < min || tall > max);
	return tall;
}

//  Leter etter en ansatt med et gitt nummer
int finnesAllerede(int ansNr)   //    ("ansNr"). Retur: indeks eller 0.
{
	for (int i = 1; i < sisteBrukt; i++)		//sjekker ansatt nummer overens
	{											// med bruker input
		if (ansatte[i]->skrivNr() == ansNr ) { return i; }
	}
	return 0;
}


void smettInn()						//  Innstikkssortering av ETT objekt:
{
	for (int k = 1; k < sisteBrukt; k++)	//sjekker første i lista opp mot 
	{										// resten av listen og plasere 
		for (int i = 1; i < sisteBrukt; k++)	//minste først. Gjør dette for
		{										// alle pekere
			if (ansatte[i]->skrivNr() > ansatte[k]->skrivNr())
			{
				swap(ansatte[i], ansatte[k]);
			}
		}
	}
}
	


void lesFraFil()					 //  Leser HELE datastrukturen fra fil:
{           

	ifstream inn("ansatt.dta");		//leser fra fra fil ansatt.dta
	int nr;
	char ch;
	while (inn.good())				// sjekker at neste bit = good
	{
		inn >> nr;
		ansatte[++sisteBrukt] = new Ansatt(nr, inn); //lager nye objekt utifra
													//info fra fil
		
	}
}


void skrivTilFil()//  Skriver HELE datastrukturen til fil:
{                 
	ofstream ut("ansattUt.dta");
	for (int i = 1; i < sisteBrukt; i++)
	{
		ut << ansatte[i]->skrivNr() << tab;	//skriver først ansatt nummer
		ansatte[i]->skrivTilFil(ut);		//skriver så resten av info
		ut << endl;
	}
}

void nyAnsatt()						 //  N - NY ANSATT:
{  
	int svar;						
	if (sisteBrukt < MAXANS)
	{
		cout << "skriv eit ansatt nummer: ";
		cin >> svar;
		if (finnesAllerede(svar) == 0)		//sjekker om ansatt finnes
		{
			ansatte[++sisteBrukt] = new Ansatt(svar);	//lager ny om ikke
		}
		else
		{
			cout << "Ansatt finnes allerede";
		}
	}
	else
	{
		cout << "\nMaks antall ansatte er n†d";
	}
	skrivTilFil();
}


void partnerEndring()  //  P - ENDRE DATA OM PARTNER:
{   
	int n;								
	int index;
	cout << "Skriv in ansatt nummeret til en ansatt";
	cin >> n; cin.ignore();
	index = finnesAllerede(n);		//sjekker om ansatt finnes
	ansatte[index]->nyPart();		//kjører så nypart funksjon
	skrivTilFil();
}


void nyttBarn() //  B - NYTT BARN:
{
	int n;
	int k;
	cout << "Skriv in eit ansatt nummer";
	cin >> n; cin.ignore();
	k = finnesAllerede(n);		//sjekker om ansatt finnes

	if (k != 0)					//hvist han finnes, lager nytt barn
	{
		ansatte[k]->NyttBarn();
	}
	else
	{
		cout << "ansatt finnes ikke";
	}
	skrivTilFil();
}


void dataOmAnsatt()                 //  D - SKRIVER ALLE DATA OM EN ANSATT:
{
	int c;
	int index;
	cout << "skriv inn eit ansatt nummer";
	cin >> c; cin.ignore();
	index = finnesAllerede(c);		
	if (index != 0)
	{
		ansatte[index]->display();		// skriver ut info om ansatt finnes
	}
	else
	{
		cout << "ansatte finnes ikke";
	}

}

//  A - SKRIVER ALLE ANSATT MED BARN
void alleEttAar()                  //      FDT ET GITT R:
{
	int n;
	cout << "skriv in eit årstall, 4 siffer: ";
	cin >> n;
	n= n % 100;					//gjør om 1999 til 99, etc
	cout << "ansatte som har barn født i: ";
	cout << setw(2) << n << endl;			//setter buffer til 2, så 00 
											//skrives ut
	for (int i = 1; i < sisteBrukt; i++)
	{
		ansatte[i]->BarnAar(n);				//sjekker hvilke ansatte har barn
	}										//i spesifisert år
	
}


void fjernAnsatt()                  //  F - FJERN/SLETT EN ANSATT
{
	int p;
	int index;
	cout << "Skriv eit ansatt nummer: ";
	cin >> p;
	index = finnesAllerede(p);
	if (index != 0)
	{
		for (int i = index; i < sisteBrukt; i++)	//om ansatt finnes
		{											//blir han flyttet bakerst
			swap(ansatte[i], ansatte[i + 1]);		// og slettet
		}
		delete(ansatte[index]);
		cout << "personen blir slettet";
	}
	if (index == 0)
	{
		cout << "Personen finnes ikke";
	}
}