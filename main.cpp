#include <iostream>
#include <vector>

using namespace std;

class Masina {
private:
	int masa;
	int snaga;
	string proizvodjac;
	Masina* prethodni;
	Masina* sledeci;
public:
	Masina(int masa, int snaga, string proizvodjac) {
		this->prethodni = nullptr;
		this->sledeci = nullptr;
		this->masa = masa;
		this->snaga = snaga;
		this->proizvodjac = proizvodjac;
	}

	void setMasa(int masa) {
		this->masa = masa;
	}

	int getMasa() {
		return this->masa;
	}

	void setSnaga(int snaga) {
		this->snaga = snaga;
	}

	int getSnaga() {
		return this->snaga;
	}

	void setProizvodjac(string proizvodjac) {
		this->proizvodjac = proizvodjac;
	}

	string getProizvodjac() {
		return this->proizvodjac;
	}

	virtual void detalji() {
		 cout << "Masina proizvodjaca " << this->proizvodjac << ", maksimalne snage " << this->snaga << "kw, mase " << this->masa << "." << endl;
	}

	virtual bool aktiviraj() = 0;
	virtual double trenutnaSnaga() = 0;

	void prethodnik(Masina* masina) {
		this->prethodni = masina;
	}

	void sledbenik(Masina* masina) {
		this->sledeci = masina;
	}

	void ispisPrethodnika() {
		Masina* pr = this->prethodni;
		while (pr != nullptr) {
			pr->detalji();
			pr = pr->prethodni;
		}
	}

	void ispisSledbenika() {
		Masina* sl = this->sledeci;
		while (sl != nullptr) {
			sl->detalji();
			sl = sl->sledeci;
		}
	}
};

class PoluautomatskaMasina : public Masina {
private:
	int brojRadnihMesta;
	int brojRadnika;
public:
	PoluautomatskaMasina(int masa, int snaga, string proizvodjac, int brojRadinhMesta, int brojRadnika) : Masina(masa, snaga, proizvodjac) {
		this->brojRadnihMesta = brojRadinhMesta;
		this->brojRadnika = brojRadnika;
	}

	void setBrojRadnihMesta(int brojRadnihMesta) {
		this->brojRadnihMesta = brojRadnihMesta;
	}

	int getBrojRadnihMesta() {
		return this->brojRadnihMesta;
	}

	void setBrojRadnika(int brojRadnika) {
		this->brojRadnika = brojRadnika;
	}

	int getBrojRadnika() {
		return this->brojRadnika;
	}

	void dodajRadnike(int brojRadnika) {
		int radnici = this->brojRadnika + brojRadnika;
		if (radnici > this->brojRadnihMesta) {
			cout << "Nema dovoljno radnih mesta!" << endl;
			return;
		}
		this->brojRadnika = radnici;
	}

	void ukloniRadnike(int brojRadnika) {
		int radnici = this->brojRadnika - brojRadnika;
		if (radnici < 0) {
			cout << "Nema toliko radnika!" << endl;
			return;
		}
		this->brojRadnika = radnici;
	}

	double trenutnaSnaga() {
		return Masina::getSnaga() * ((double)(this->brojRadnika) / this->brojRadnihMesta);
	}

	void detalji() {
		cout << "Masina proizvodjaca " << Masina::getProizvodjac() << ", maksimalne snage " << Masina::getSnaga() << "kw, trenutne snage " << this->trenutnaSnaga() << "kw, mase " << Masina::getMasa()
			 << ", kapaciteta radnih mesta " << this->brojRadnihMesta << " radnika na kojoj je angazovano " << this->brojRadnika << " radnika." << endl;
	}

	bool aktiviraj() {
		if (this->brojRadnika > 0) {
			cout << "Uspesno aktivirana!" << endl;
			return true;
		}
		else {
			cout << "Neuspesno aktivirana!" << endl;
			return false;
		}
	}
};

class AutomatskaMasina : public Masina {
private:
	int pohabanost;
public:
	AutomatskaMasina(int masa, int snaga, string proizvodjac, int pohabanost) : Masina(masa, snaga, proizvodjac) {
		this->pohabanost = pohabanost;
	}

	void setPohabanost(int pohabanost) {
		this->pohabanost = pohabanost;
	}

	int getPohabanost() {
		return this->pohabanost;
	}

	string ispravnost() {
		if (this->pohabanost < 100) {
			return "ispravna";
		}
		else return "neispravna";
	}

	void detalji() {
		cout << "Masina proizvodjaca " << Masina::getProizvodjac() << ", maksimalne snage " << Masina::getSnaga() << "kw, mase " << Masina::getMasa()
			 << ", pohabanosti " << this->pohabanost << " je trenutno " << this->ispravnost() << "." << endl;

	}

	virtual bool aktiviraj() {
		if (this->pohabanost < 100) {
			cout << "Uspesno aktivirana!" << endl;
			this->pohabanost > 100 ? this->pohabanost = 100 : this->pohabanost += 25;
			return true;
		}
		else {
			cout << "Neuspesno aktivirana!" << endl;
			return false;
		}
	}

	double trenutnaSnaga() {
		return Masina::getSnaga();
	}
};

class Proizvod {
private:
	string naziv;
	double kvalitet;
public:
	Proizvod(string naziv, double kvalitet) {
		this->naziv = naziv;
		this->kvalitet = kvalitet;
	}

	void setNaziv(string naziv) {
		this->naziv = naziv;
	}

	string getNaziv() {
		return this->naziv;
	}

	void setKvalitet(double kvalitet) {
		this->kvalitet = kvalitet;
	}

	double getKvalitet() {
		return this->kvalitet = kvalitet;
	}
};

class ProizvodnaLinija {
private:
	vector<Masina*> masine;
public:
	ProizvodnaLinija() {

	}

	void setMasine(vector<Masina*> masine) {
		this->masine = masine;
	}

	vector<Masina*> getMasine() {
		return this->masine;
	}

	void dodajMasinu(Masina* masina) {
		this->masine.push_back(masina);
	}

	void detalji() {
		cout << "Masina ima ukupno " << this->masine.size() << endl;
		int i = 1;
		for (vector<Masina*>::iterator it = this->masine.begin(); it != this->masine.end(); ++it) {
			cout << i << ". ";
			(*it)->detalji();
			i++;
		}
	}

	bool aktivirajMasine() {
		bool svi = true;
		for (vector<Masina*>::iterator it = this->masine.begin(); it != this->masine.end(); ++it) {
			if ((*it)->aktiviraj()==false) {
				svi = false;
			}
		}
		return svi;
	}

	bool proizvedi(string naziv) {
		if (this->aktivirajMasine()) {
			double trenutna = 0;
			int maksimalna = 0;
			for (vector<Masina*>::iterator it = this->masine.begin(); it != this->masine.end(); ++it) {
				maksimalna += (*it)->getSnaga();
				trenutna += (*it)->trenutnaSnaga();
			}
			double kvalitet = trenutna / maksimalna;
			Proizvod proizvod(naziv, kvalitet);
			cout << "Proizveden " << proizvod.getNaziv() << " kvaliteta " << proizvod.getKvalitet() << endl;
			return true;
		}
		else return false;
	}
};

int main() {
	ProizvodnaLinija linija;
	PoluautomatskaMasina *polu = new PoluautomatskaMasina (1000, 300, "Samsung", 200, 100);
	AutomatskaMasina *automatska = new AutomatskaMasina(2000, 500, "Intel", 25);
	linija.dodajMasinu(polu);
	linija.dodajMasinu(automatska);
	linija.detalji();
	linija.proizvedi("Laptop");
	linija.proizvedi("Mobilni");
	linija.proizvedi("Televizor");
	linija.proizvedi("Tablet");
	return 0;
}
