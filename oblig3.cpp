//August oksavik, 16HBPROGA, 470916

// › - Ø |  † - Å

//programet holder orden på leger og deres resept og hvilke pasienter de blir
//gitt til.

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif 

//  INCLUDE:
#include "ListTool2A.h"
#include <iostream>			 // cout, cin
#include  <fstream>          //  ifstream, ofstream
#include  <cstring>          //  strcpy, strlen, strncmp
#include  <cctype>           //  toupper


using namespace std;

//  CONST:
const int MAXTEXT = 80;
const int TELEMAX = 99999999;
const int TELEMIN = 10000000;
const int MAXDATO = 20150101;
const int MINDATO = 20251231;


//  DEKLARASJON AV FUNKSJONER:
void skrivMeny();
void NyttResept();
void LegeResept();
void PasientResept();
void FjernGamle();
void SkrivTilFil();
void LesFraFil();
void Hjelp();
char les();
int les(char*, int, int);

				//classe for resept
class Resept : public NumElement
{
private: 
	char* PersNavn;
	char* MedNavn;
	int	  Mengde;
	
public: 
	Resept(int tall):NumElement(tall) // får in info om resept fra bruker
	{
		char pers[MAXTEXT];
		char Med[MAXTEXT];
		int m;
		cout << "skriv in Personens navn: ";
		cin.getline(pers, MAXTEXT);
		cout << pers;
		cout << "skriv in Medisinens navn: ";
		cin.getline(Med, MAXTEXT);
		cout << Med;
		m = les("skriv in mendge medisin i milligram", 1, 1000);
		PersNavn = new char[strlen(pers) + 1];
		strcpy(PersNavn, pers);
		MedNavn = new char[strlen(Med) + 1];
		strcpy(MedNavn, Med);
		Mengde = m;
	}

	Resept(int n, ifstream & inn): NumElement(n)//leser inn info fra fil
	{
		char temp1[MAXTEXT];
		char temp2[MAXTEXT];
		inn.getline(temp1, MAXTEXT);
		PersNavn = new char[strlen(temp1) + 1];
		strcpy(PersNavn, temp1);
		inn.getline(temp2, MAXTEXT);
		MedNavn = new char[strlen(temp2) + 1]; 
		strcpy(MedNavn, temp2);
		inn >> Mengde; 

	}

	~Resept()		// sletter pointers
	{
		delete(PersNavn);
		delete(MedNavn);
 	}
	char* ReturNavn()
	{
		return PersNavn;
	}
	void display()
	{
		cout << "\n Dato skrevet: " << number;
		cout << "\nPersonens navn: " << PersNavn;
		cout << "\nMedisin: " << MedNavn;
		cout << "\nMengde medisin: " << Mengde;
	}
	void SkrivTilFil(ofstream & ut) //skriver ut til fil
	{
		ut << number << endl;
		ut << PersNavn << endl;
		ut << MedNavn << endl;
		ut << Mengde << endl;
	}
	int ReturDato()
	{
		return number;
	}
};

				//lege klasse
class Lege : public TextElement
{
private:
	List* resept;
	char* adresse;
	int telefon;

public:
	Lege(char* st): TextElement(st)		//leser inn info fra bruker
	{	
		resept = new List(Sorted);	// inizialiserer resept liste
		char temp[MAXTEXT];
		int n;
		cout << "skriv inn leges adresse: ";
		cin.getline(temp, MAXTEXT);
		adresse = new char[strlen(temp) + 1];
		telefon = les("skriv inn leges telefon nummer: ", 1000000, 99999999);
	

	}
	Lege(ifstream & inn, char* ch): TextElement(ch) // leser inn info fra fil
	{
		resept = new List(Sorted);  // inizialiserer resept liste
		int antallResept;
		int dato;
		char temp[MAXTEXT];
		inn.getline(temp, MAXTEXT);		//henter adresse fra fil
		adresse = new char[strlen(temp) + 1];
		strcpy(adresse, temp);
		inn >> telefon;				// henter tlfnr
		inn >> antallResept;		//antall resept
		Resept* buffer;			//buffer Resept peker
		for (int i = 1; i <= antallResept; i++)
		{
			inn >> dato; inn.ignore();
			buffer = new Resept(dato, inn); //lager nytt objekt via buffer
			resept->add(buffer);		// adder buffer til resept lista
		}
		delete(buffer); //frigjør minne
	}
	~Lege()
	{
		delete(resept);
		delete(adresse);
	}
	void display()
	{
		cout << "\nlegens navn: " << text;
		cout << "\nLegens adresse: " << adresse;
		cout << "\nLegens telefon nr: " << telefon;
	}
	
	void NyResept()			// funksjon for nytt resept
	{
		int dato;
		cout << "skriv inn dato på formen ††††MMDD: ";
		cin >> dato; cin.ignore();
		 Resept* temp = new Resept(dato);	  //setter Resept peker til å være
		 resept->add(temp);	 // nytt objekt med dato som arg
		 delete(temp);		//frigjør minne
	}								//leger til temp objekt i lista
	void VisResept()		// kjører display for alle resept
	{
		resept->displayList();
	}

	void PersListe(char* ch)	//finner reseptet til ein git pasient
	{
		Resept* temp;		//temp resept peker
		int AntResept = resept->noOfElements();	// setter AntResept til 
		for (int i = 1; i <= AntResept; i++)	// antall respter legen har
		{
			temp = (Resept*)resept->removeNo(i);  //henter ut resept nr "i"
			if (strcmp(temp->ReturNavn(), ch) == 0)	// samenligner med funksjon
			{										//argument
				temp->display(); //kjører reseptet sin display hvist de er like
			}
			resept->add(temp);		// leger tilbake reseptet
		}
	}
	void SkrivTilFil(ofstream & ut) // skriver resept til fil
	{
		int antall = resept->noOfElements(); //antall resepter legen har
		ut << text << endl;				// navent til legen
		ut << adresse << endl;		
		ut << telefon << endl;
		ut << antall << endl;
		Resept* temp;				
		for (int i = 1; i <= antall; i++)
		{
			temp = (Resept*)resept->removeNo(i);// setter temp til resept nr i
			temp->SkrivTilFil(ut);				//kjører reseptets funksjon
			resept->add(temp);					//leger tilbake elementet
		}
	}
	void SlettResept(int d)				//sletter resept før en viss dato
	{
		Resept* temp;				// temp peker
		int dato;
		for (int i = 1; i <= resept->noOfElements(); i++)
		{
			temp = (Resept*)resept->removeNo(i);	//tar ut resept nr i
			dato = temp->ReturDato();			//seter dato til retur verdi
			if (dato < d)						//sjekker om dato er mindre en
			{									// angitt dato
				resept->destroy(dato);			// ødeleger hvis "true"
				
			}
		}
	}
	int AntallResept()					//retuner antall resept
	{
		return resept->noOfElements();
	}
	char* LegeNavn()			//legens navn
	{
		return text;
	}
};

//  GLOBALE VARIABLE:

List* leger = new List(Sorted);			// lager ny liste av typen sorted


int main()
{
	LesFraFil();					//leser fra fil i begynnlsen
	
	
	char kommando;                //  Brukerens ›nske/valg.
	skrivMeny();					//  Meny av brukerens valg
	kommando = les();
	while (kommando != 'Q')
	{	
	
		switch (kommando)
		{
		case 'R': NyttResept(); break;
		case 'L': LegeResept(); break;
		case 'P': PasientResept(); break;
		case 'F': FjernGamle(); break;
		case 'U': SkrivTilFil();  break;
		case 'I': LesFraFil(); break;
		case 'H': Hjelp(); break;
		default: skrivMeny(); break;
		}
		kommando = les();		//får inn nytt ønske
	}
	cout << "Vil du skrive til file før du avslutter? J/N";
	char ch = les();
	if (ch == 'J')
	{
		SkrivTilFil();
	}
	delete(leger);			//sletter leger pointer når programmet er over
	return 0;
}

void skrivMeny()
{
	cout << "TILGJENGELIGE KOMMANDOER\n";
	cout << "R - nytt resept\n";
	cout << "L - Oversikt over reseptene fra en bestemt lege\n";
	cout << "P - Oversikt over resepter til en bestemt pasient\n";
	cout << "F - Fjern alle gamle resept\n";
	cout << "U - Skriv til fil+\n";
	cout << "I - les fra fil\n";
	cout << "H - Hjelp\n";
	cout << "Q - Avslutt programmet\n";
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

void NyttResept()		
{
	char buffer[MAXTEXT];
	cout << "Skriv inn legens navn: ";
	cin.getline(buffer, MAXTEXT); 
	Lege* temp;					
	if (temp = (Lege*)leger->remove(buffer))//sjekker og henter ut brukers valg
	{										//kjører nyResept funskjon om
		temp->NyResept();					//legen finnes
	}
	else                //hvis ikke legen finnes lages nye lege og nyResept
	{					//funskjonen kjøres
		temp = new Lege(buffer);
		temp->NyResept();
	}
	leger->add(temp);//legger tilbake ny lege eller gammel lege
	delete(temp);
}

void LegeResept()	//oversikt over en git leges resepter
{
	char temp[MAXTEXT];		
	cout << "skriv inn ein leges navn: ";
	cin.getline(temp, MAXTEXT);		// får inn brukers valg
	Lege* buffer = (Lege*)leger->remove(temp);	//lager buffer pointer og
			// får henter brukers valg fra listen som blir gjort om til lege*
	if (buffer== NULL)		//sjekker om lege ikke finnes
	{
		cout << "Lege finnes ikke";
	}
	else          // hvis lege finnes, visses hans resept of blir lagt tilake
	{											// i lista
		buffer->VisResept();
		leger->add(buffer);
	}

}

void PasientResept()			//skriver ut ein git passients resepter
{
	char ch[MAXTEXT];
	cout << "Skriv inn pasientens navn: ";
	cin.getline(ch, MAXTEXT);	//får in brukers valg
	Lege* buffer;				//buffer peker
	int antlege = leger->noOfElements();	//antall leger
	for (int i = 1; i <= antlege; i++)		
	{
		buffer = (Lege*)leger->removeNo(i); //setter buffer til lege nr "i"
		buffer->PersListe(ch);				// kjører legens persliste funksjon
		leger->add(buffer);					// med brukers input som arg
	}										//legger så tilbake legen i lista
}

void FjernGamle()				//fjerner gamle resept før ein git dato
{
	Lege* temp;
	int dato;
	cout << "skriv inn ein dato for sletting: ";
	cin >> dato;					//får inn brukers valg
	for (int i = 1; i <= leger->noOfElements(); i++)
	{
		temp = (Lege*)leger->removeNo(i); // setter temp peker til lege nr "i"
		temp->SlettResept(dato);		//kjører slettResept funskjon med
										//brukers valg som argument
		if (temp->AntallResept() != 0)	//sjekker om lege har 0 resept
		{		
			leger->add(temp);			//hvis ikke, legges legen tilbake
		}
	}
}

void LesFraFil()	//leser info om lege og resept fra fil
{
	int antall;
	ifstream inn("LegerInn.dta");
	inn >> antall;		// får inn antall leger
	Lege* temp;			
	char Navn[MAXTEXT];
	for (int i = 1; i <= antall; i++)
	{
		inn.ignore();
		inn.getline(Navn, MAXTEXT); //henter inn lege navn fra andre linje
		temp = new Lege(inn, Navn);	//lager nytt objekt og kjører constuctor
		leger->add(temp);			// legger til ny lege in list 
		delete(temp);				// frigir minne
	}

}

void SkrivTilFil()  // skriver ut all info til fil
{
	ofstream ut("LegerUt.dta", ofstream::trunc);	//lager ny stream som
	int antall = leger->noOfElements();			//sletter det som stod der
	ut << antall << endl;						//før	
	Lege* temp;									
	for (int i = 1; i <= antall; i++)
	{
		temp = (Lege*) leger->removeNo(i);	//henter ut relevant lege
		temp->SkrivTilFil(ut);				// kjører legens funksjon
		leger->add(temp);					//leger tilbake legen
	}
}

void Hjelp()
{
	cout << "\nR - Registrer nytt resept, vist lege ikke finnes,";
	cout << " så registreres nye lege og relevant info";
	cout << "\nL - Ein git leges resepter blir skrevet ut p† skjermen";
	cout << "\nP - Ein git pasients resepter blir skrevet ut p† skjermen";
	cout << "\nF - Fjerner alle resepter f›r ein git dato";
	cout << "\nU - Skriver alle resept til fil";
	cout << "\nI - Henter alle resepter fra fil";
}