#include <iostream> //August Oksavik, 470916, 16HBPROGA
#include <cstring>
#include <string>
#include <conio.h>


using namespace std;

class Dyr                   //baseklasse dyr
{

private:
	char navn[80];          // namn p� dyr

public:		
	Dyr() {};				//no-arg constructor
	void SkrivDyr();	    // skriver ut navent til dyret
	void LesDyr();			// henter navnet til dyret fra brukeren
	
};
class DyrILuft: public Dyr
{
private:
	int VingeSpenn;        //int for lengden p� vingespennet til dyret

public:
	DyrILuft() :Dyr() {};         //no-arg constructor
	
	void SkrivDyrILuft();  //Skriver ut vingespennet og navent
	void LesVinge();	   // leser inn vingespenn fra bruker
};
class DyrIVann : public Dyr
{
private: 
	int AntallFinner;     //int for antall finner p� sj�dyret

public:
	DyrIVann():Dyr() {};        //no-arg constructor

	void LesFinner();     // f�r antall finner fra brukeren
	void SkrivDyrIVann(); // skriver ut info om dyret
	void SkrivFinner();
};
class Insekt :public DyrILuft
{
private:
	int	AntallBein;     // int for antall bein p� insektet

public:
	Insekt():DyrILuft() {};        // no-arg constructor
	void LesBein();		// leser inn hvor mange bein p� dyret
	void SkrivInsekt(); //skriver ut hvor mange bein of anna info
};	
class Fugl : public DyrILuft
{
private:
	char Possisjon[80]; // char for hvor man kan finne dyret

public: 
	Fugl():DyrILuft() {};          //no-arg constructor
	void LesPoss();     //f�r possisjonen fra brukeren
	void SkrivFugl();   //skriver ut possisjon of anna info
	
};
class Fisk : public DyrIVann
{
private:
	float lengde;		// float for hvor lang fisken er
	char FiskeTrynne[20]= "";
public:
	Fisk():DyrIVann() {};	//no-arg constructor

	Fisk(char ch[20])
	{
		strcpy(FiskeTrynne, ch);
	};
		//1-arg constructor
	void LesLengde();   // leser inn lengden p� fisken 
	void SkrivFisk();   // skriver ut info om fisken
};
class SkallDyr : public DyrIVann
{
private:
	int AntallKloer;	// int for antall kl�r p� dyret

public:
	SkallDyr():DyrIVann() {};      // no-arg constructor
	void LesKloer();	//leser inn antal kloer fra bruker
	void SkrivSkallDyr();	//skriver ut info om skalldyret


};

int main()
{
	int a = 1;         //int for do while l�kke
	do
	{

		char b;     // char for brukerens sit svar
		cout << "Velg hvilket dyreart du vil registrere: | A = Insekt ";
		cout <<"| B = Fugl | C = Fisk | D = Skalldyr |";
		cout << "\nSkriv ein bokstav: ";
		b = _getch();		  // f�r in brukerens sit svar
		 b = toupper(b);	  // passer p� at input er stor bokstav
		switch (b)				// utf�rer switch utifra brukerens valg
		{

		case 'A':			
		{
			Insekt obj1;		//lager objekt for insekt
			obj1.LesDyr();		// f�r inn navn fra bruker
			obj1.LesVinge();	// f�r inn vingespenn
			obj1.LesBein();		// f�r inn antall bein p� insektet

			obj1.SkrivInsekt();		//skiver ut all relevant info

		}
		break;

		case 'B':
		{
			Fugl obj1;				//lager objekt av typen fugl
			obj1.LesDyr();			// f�r inn navn fra bruker
			obj1.LesPoss();			// f�r in possisjon fra bruker
			obj1.LesVinge();		// f�r inn vingespenn fra bruker

			obj1.SkrivFugl();		// skriver ut relevant info
		}
		break;

		case 'C':
		{
			char svar[20];			  // sjekker brukers input
			cout << "\nSkriv in navnet p� dyret: ";
			cin.getline(svar, '\n');  // f�r in brukers svar, og
									  // sjekker hvilken constructor
									  //som skal kj�res

			if (strlen(svar) > 2)     // ser om det er mer en 1 karakter
			{						  // i svar, og sender det til constructor
				Fisk obj1(svar); // objekt av type Fisk med svar som argument
				obj1.LesFinner();	  // f�r inn hvor mange finner fisken har
				obj1.LesLengde();	  // f�r inn lengden p� fisken

				obj1.SkrivFisk();     // skriver ut all relevant info
			}
			
			else
			{
				
				Fisk obj1;            // objekt av typen Fisk
				obj1.LesFinner();	  // f�r inn antall finner fra bruker
				obj1.LesLengde();	  // f�r in lengden p� fisken

				obj1.SkrivFisk();	  // skriver relevant info
			}

		}
		break;

		case 'D':
		{
			SkallDyr obj1;            // objekt av type skalldyr
			obj1.LesDyr();			  // leser in navn p� dyret
			obj1.LesFinner();		  // leser inn finner p� dyret
			obj1.LesKloer();		  // leser inn antal kl�r dyret har

			obj1.SkrivSkallDyr();      // skriver ut all relevant info
		}
		break;

		default:
		{
			cout << "\nFeil bokstav start p� nytt";
		}
				 break;
				 
		}
		cout << "\nHar du lyst � kj�ere programmet igjen? J|N\n";
		char  c;					// char for brukers valg
		c = _getch();				// f�r in brukeres valg
		c = toupper(c);				// gj�r om til stor bokstav
		if (c == 'J')				// sjekker om bruker valgte J/ja
		{
			a = 1;				// vist ja s� passer den p� at a forblir 1
			cout << '\n';
		}
		else
		{
			a = 0;	// vist noe annet en J blir trykkt s� avslutter programet
			
		}

	} while (a == 1);		// sjekker om programmet skal kj�res igjen
		return 0;
};


void Dyr::SkrivDyr()	    //Definerer SkrivDyr
{
	cout << navn;		 // skriver ut navnet p� dyret
}
void Dyr::LesDyr()		     //definerer LesDyr uten arg
{
		cout << "\nSkriv in navn p� dyret: ";
		cin >> navn; cin.ignore();		//f�r inn navn fra brukeren
};


void DyrILuft::LesVinge()				  // definere lesVinge
{	
	cout << "\nSkriv in vingespennet p� Dyret i cm: ";
	cin >> VingeSpenn;	// f�r inn vingespenn fra bruker
	
};
void DyrILuft::SkrivDyrILuft()			 //definere SkrivDyrILuft
{
	cout << "\nNavnet p� dyret er: ";
	SkrivDyr();							//skriver ut navent p� dyret
	cout << "\nog har eit vingespenn p� ";
	cout << VingeSpenn << "cm";		// skriver ut vinge spennet
	

};
void DyrIVann::LesFinner()			// definere LesFinner
{
	cout << "\nSkriv in antall finner p� dyret: ";
	cin >> AntallFinner;				// f�r in antall finner fra bruker
	
};
void DyrIVann::SkrivDyrIVann()			//definere SkrivDyrIVann
{
		cout << "\nNavnet p� dyret er: ";
		SkrivDyr();							// skriver ut navnet
		cout << "\nog det har ";
		cout << AntallFinner << " finner\n";		//skriver ut antall finner
};
void DyrIVann::SkrivFinner()
{
	cout << AntallFinner;				// skriver ut antall finner
}
void Fisk::SkrivFisk()						//definere SkrivFisk
{
	if (strlen(FiskeTrynne) > 2)    // sjekker om navnet har mer en 1 karakter
	{
		cout << "\nNavnet p� dyret er: ";
		cout << FiskeTrynne;			// skriver ut navnet til fisken
	}
	cout << "\ndet har ";
	SkrivFinner();						// skriver ut finner
	cout << " finner";
	cout << "\nfisken er " << lengde;		// skriver ut lengden p� fisken
	cout << "cm lang\n"; 
};
void Fisk::LesLengde()					// definere LesLengde
{
	cout << "Skriv inn lengden p� Fisken i cm: ";
	cin >> lengde;						// f�r inn lengden fra bruker
};
void SkallDyr::LesKloer()            //Definere LesKloer
{
	cout << "Skriv in antall kl�r p� skalldyret ";
	cin >> AntallKloer;				//f�r in antall kl�r fra bruker
};
void SkallDyr::SkrivSkallDyr()		//definere SkrivSkallDyr
{
	SkrivDyrIVann();			 //kaller p� SkrivDyrIVann funksjon
	cout << "Skalldyret har ";
	cout << AntallKloer << " kl�r\n";	// skriver ut antall kl�r
	;
};
void Fugl::LesPoss()			// definere LesPoss
{
	
	cout << "Skriv inn hvor man finner dette dyret: ";
	cin >> Possisjon;		// f�r inn char for posisijon fra bruker
};
void Fugl::SkrivFugl()		// definere SkrivFugl
{
	SkrivDyrILuft();		//kaller p� SkrivDyrILuft funksjon

	cout << "\nMan finner dette dyret I ";
	cout << Possisjon;		// skriver ut possisjonen til dyret
};
void Insekt::LesBein()		// definerer LesBein
{
	cout << "Skriv in antall bein til dyret: ";
	cin >> AntallBein;		// f�r inn antall bein fra bruker
};
void Insekt::SkrivInsekt()	// definere SkrivInsekt
{
	SkrivDyrILuft();		//kaller p� SkrivDyrILuft funskjon
	cout << "\ndyret har ";
	cout << AntallBein << " bein";	// skriver ut antall bein
};