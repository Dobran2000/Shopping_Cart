#include<vector>
#include<sstream>
#include<fstream>
#include<stdlib.h>
#include<iostream>
using namespace std;

class Client
{public:
	vector<vector<string>> date_clienti;
	vector<string> v;
	int lines = 0;
	string nume;
	string prenume;
	string suma2;
	string zi;//ziua cumpararii
	string luna;//luna cumpararii
	string an;//anu; cumparararii
     Client();
	~Client();
	void read_csv(string file);
	void show_Clienti();
	void citire_vanzari();
	vector<vector<string>> Vanzari;
	vector<string> vect;

};
Client::Client()
{
}
Client::~Client()
{
	cout << "Obiectul a fost distrus";
}
void Client::read_csv(string file)
{
	ifstream in(file);
	string line, field;
	this->lines = 0;

	while (getline(in, line))
	{
		this->v.clear();
		stringstream ss(line);
		++this->lines;
		while (getline(ss, field, ','))
		{
			this->v.push_back(field);
		}
		this->date_clienti.push_back(this->v);
	}
	in.close();

}
void Client::show_Clienti()
{
	for (int i = 0;i < this->lines;i++)
	{
		cout << date_clienti[i][0] << " ";
	}
}

class Cumparaturi :public Client
{
public:
	vector<vector<string>> date_vanzari;
	vector<string> vec;
	vector<vector<string>> Inventar;
	void afisare_vanzari();
	int lines_Inventar = 0;
	string suma2;
	void citire_inventar(string file);
	void afisare_inventar();
	void afisare_lista();
	void citire_vanzari(string file);
	void afisare_vanzari(string file);
	void afisare_suma_lunara(string luna);
	int lines_Vanzari = 0;
	int contor = 0;
	int suma = 0;
	int contor2 = 0;
	const char delim = '*';
	vector<string> final;
	string Lista_Cumparaturi;
	vector<string> LISTA_CUMPARATURI;
	void afisare_suma_categorie(string categorie);
	void tokenize(string const &str, const char delim, vector<string> &out);
	void afisare_lista_Cumparaturi(string file);
	string cumparaturi;
    vector<int> pozitii;
	void afisare_suma_anuala(string an);
	void sterge_produs(string file, string nume,
		string prenume, string zi, string luna,
		string an, string nume_produs, string categorie);
	
};

void Cumparaturi::citire_inventar(string file)
{
	ifstream in(file);
	string line, field;
	this->lines_Inventar = 0;

	while (getline(in, line))
	{
		this->vec.clear();
		stringstream ss(line);
		++this->lines_Inventar;

		while (getline(ss, field, ','))
		{
			this->vec.push_back(field);
		}
		this->Inventar.push_back(this->vec);
	}
}
void Cumparaturi::afisare_inventar()
	{
		for (int i = 0;i < this->lines_Inventar;i++)
		{
			cout << Inventar[i][0] << "," << Inventar[i][1] << endl;
		}

	}
void Cumparaturi::citire_vanzari(string file)
{
	ifstream in(file);
	string line, field;
	this->lines_Vanzari = 0;

	while (getline(in, line))
	{
		this->vect.clear();
		stringstream ss(line);
		++this->lines_Vanzari;
		while (getline(ss, field, ','))
		{
			this->vect.push_back(field);
		}
		this->Vanzari.push_back(this->v);
	}
	in.close();
}
void Cumparaturi::tokenize(string const &str, const char delim, vector<string> &out)
{
	stringstream ss(str);
	string s;
	while (std::getline(ss, s, delim)) {
		out.push_back(s);
	}
}

void Cumparaturi::afisare_lista_Cumparaturi(string file)
{


	for (int i = 0;i < this->lines; i++)
	{
		suma = 0;

		Lista_Cumparaturi.clear();
		Lista_Cumparaturi.append(this->date_clienti[i][5]);
		tokenize(Lista_Cumparaturi, delim, final);
		
		for (size_t i = 0;i < final.size();i++)
		{
			cout << final.at(i) << " ";
			cout << endl;
		}
		for (size_t j = 0;j < final.size();j++)
		{
			for (size_t k = 0; k < this->lines_Inventar;k++)
			{
				if (final.at(j) == Inventar[k][0])
				{
					suma = suma + stoi(this->Inventar[k][1]);
					pozitii.push_back(k);

				
					if (suma != 0)
					{
						contor++;
						if (cumparaturi.size() == 0)
						{
							cumparaturi.append(this->Inventar[k][0]);
							//cout << cumparaturi;
						}
						else
						{

							cumparaturi.append("*");

							cumparaturi.append(this->Inventar[k][0]);
							//cout <<"Jean"<< cumparaturi << endl;
						}
					}
			
					suma2 = to_string(suma);
					cout << "Puck este " << suma2 << endl;
				}

			}
		}
			this->vect.clear();
			this->vect.push_back(date_clienti[i][0]);
			this->vect.push_back(date_clienti[i][1]);
			this->vect.push_back(cumparaturi);
			this->vect.push_back(date_clienti[i][2]);
			this->vect.push_back(date_clienti[i][3]);
			this->vect.push_back(date_clienti[i][4]);
			this->vect.push_back(suma2);
			this->vect.push_back(date_clienti[i][6]);
			
			this->date_vanzari.push_back(this->vect);
			++this->lines_Vanzari;
		
			
			ofstream out(file);
			
        

		this->vect.clear();
		cumparaturi.clear();
		contor = 0;
		contor2 = 0;
		pozitii.clear();
		suma2.clear();
		contor = 0;
		contor2 = 0;
		final.clear();
	}
}
void Cumparaturi::afisare_vanzari()
{

	for (int i = 0; i < this->lines_Vanzari; i++)
		cout << this->date_vanzari[i][0] << ',' << this->date_vanzari[i][1]
		<< ',' << this->date_vanzari[i][2] << ',' << this->date_vanzari[i][3] <<','
		<<  this->date_vanzari[i][4]  <<',' << this->date_vanzari[i][5] 
		<<','<< this->date_vanzari[i][6]<<','<<this->date_vanzari[i][7]<< endl;
}
void Cumparaturi::afisare_suma_lunara(string luna)
{
	int suma_lunara = 0;
	for (int i = 0; i < this->lines_Vanzari; i++)
	{
		if (this->date_vanzari[i][4] == luna)
		{
			suma_lunara = suma_lunara + stoi(this->date_vanzari[i][6]);

	    }
    }
	cout << "Suma lunara pe luna " << luna << "este " << suma_lunara << endl;


}
void Cumparaturi::afisare_suma_anuala(string an)
{
	int suma_anuala = 0;
	for (int i = 0; i < this->lines_Vanzari; i++)
	{
		if (this->date_vanzari[i][5] == an)
		{
			suma_anuala = suma_anuala + stoi(this->date_vanzari[i][6]);

		}
	}
	cout << "Suma anuala pe anul  " << an<< "este " << suma_anuala << endl;

}
void Cumparaturi::afisare_suma_categorie(string categorie)
{
	int suma_medie = 0;
	for (int i = 0; i < this->lines_Vanzari; i++)
	{
		if (this->date_vanzari[i][7] == categorie)
		{
			suma_medie = suma_medie + stoi(this->date_vanzari[i][6]);

		}
	}
	
	cout << "Suma medie  " << categorie << "este " << suma_medie << endl;

}

void Cumparaturi::sterge_produs(string file, string nume,
	string prenume, string zi, string luna,
	string an, string nume_produs, string categorie)
{
	int sum = 0;
	int pozitie;
	char delim2 = '*';
	vector<string> final2;
	bool find = false;
	for (int i = 0; i < this->lines_Vanzari && !find; ++i)
	{
		tokenize(this->date_vanzari[i][2], delim2, final2);
		for (int j = 0;j < final2.size();i++)

		{
			   if (final.at(j) == nume_produs
				&& this->date_vanzari[i][0] == nume
				&& this->date_vanzari[i][1] == prenume
				&& this->date_vanzari[i][3] == zi
				&& this->date_vanzari[i][4] == luna
				&& this->date_vanzari[i][5] == an
				&& this->date_vanzari[i][7] == categorie)
			{
			
				find = true;
				pozitie = i;
			}
			for(int k=0;k<this->lines_Inventar;k++)
				
				if (final.at(pozitie) == Inventar[k][0])
				{
				
					sum = stoi(this->date_vanzari[pozitie][6])-stoi(Inventar[k][1]);
						
				}
				
			{
				this->date_vanzari[i].pop_back();
				find = true;
				pozitie = i;
			}
		}

		cout << "Suma e " <<sum << endl;
		if (find)
		{
			--this->lines_Vanzari;
			ofstream out(file);

		}
	}
}

int main()
{
	Client client;
	client.read_csv("Clienti.txt");
	client.show_Clienti();
	Cumparaturi cumparaturi;
	cumparaturi.read_csv("Clienti.txt");
	cumparaturi.citire_inventar("Inventar.txt");
	cumparaturi.afisare_inventar();
	cumparaturi.citire_vanzari("Vanzari.txt");
	cumparaturi.afisare_lista_Cumparaturi("Vanzari.txt");
	cumparaturi.afisare_vanzari();
	cumparaturi.afisare_suma_lunara("Mai");
	cumparaturi.afisare_suma_anuala("2020");
	cumparaturi.afisare_suma_categorie("Barbati_Femei_Accesorii");
	cumparaturi.sterge_produs("Vanzari.txt","Popescu", "Gheorghe", "12", "Mai", "2020", "hanorac", "Barbati_Femei_Accesorii");
	cumparaturi.afisare_vanzari();


}