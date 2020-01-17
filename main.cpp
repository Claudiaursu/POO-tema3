#include <iostream>
using namespace std;
#include <set>
#include <tuple>
#include<typeinfo>
#include <cstring>
#include<string.h>
#include<vector>

class Film;
class Persoana
{
protected:
    string CNP;
    string nume;
    string nume_film;
    float procent_incasari;

public:
    Persoana();
    Persoana(string, string, string,float);
    ~Persoana();
    Persoana& operator=(const Persoana&);
    friend istream& operator>>(istream&, Persoana&);
    friend ostream& operator<<(ostream&, Persoana&);
    virtual void afisare();
    virtual void citire();
    float return_procent() const
    {
        return procent_incasari;
    };
    string returnFilm() const
    {
        return nume_film;
    };
    string returnNume() const
    {
        return nume;
    };
    string returnCNP() const
    {
        return CNP;
    };
    friend bool operator<(const Persoana&, const Persoana&);

    friend float returnValBani(Persoana, Film);
};



class Film
{
    string nume;
    string tip;
    int durata;
    float incasari;
public:
    Film();
    Film(string, string, int,float);
    ~Film();
    Film& operator=(const Film&);
    friend istream& operator>>(istream&, Film&);
    friend ostream& operator<<(ostream&, Film&);
    void afisare();
    string returnNume() const
    {
        return nume;
    };
    float returnIncasari() const
    {
        return incasari;
    };
    int returnDurata() const
    {
        return durata;
    };
    string returnTip() const
    {
        return tip;
    };
    friend float returnValBani(Persoana, Film);
    friend bool operator<(const Film&,const Film&);
    friend float returnValProcent(float, Film );

    friend class Persoana;
};


float returnValBani(Persoana p, Film f)
{
    float bonus;
    if(p.returnFilm()==f.returnNume() )
        bonus=f.returnIncasari()*p.return_procent()*0.01;
    return bonus;
}

class Regizor : public Persoana
{
    float suma;
public:
    Regizor();
    Regizor(string, string, string,float,float);
    ~Regizor();
    Regizor& operator=(const Regizor&);
    friend istream& operator>>(istream&, Regizor&);
    friend ostream& operator<<(ostream&, Regizor&);
    friend bool operator<(Regizor&, Regizor&);
    void afisare();
    void citire();
    float returnSuma() const
    {
        return suma;
    }
};

class Actor : public Persoana
{
    bool principal;
public:
    Actor();
    Actor(string, string, string,float,bool);
    ~Actor();
    Actor& operator=(const Actor&);
    friend istream& operator>>(istream&, Actor&);
    friend ostream& operator<<(ostream&, Actor&);
    friend bool operator<(Actor&, Actor&);
    void afisare();
    void citire();
    bool returnTip() const
    {
        return principal;
    };

};


bool operator<(const Persoana& p1, const Persoana& p2)
{
    if(p1.returnCNP()<p2.returnCNP())
        return true;
    else
        return false;
}

bool operator<(const Film& f1, const Film& f2)
{
    if(f1.returnIncasari()<f2.returnIncasari())
        return true;
    else
        return false;
}

bool operator<(const Regizor& r1, const Regizor& r2)
{
    if(r1.returnCNP()<r2.returnCNP())
        return true;
    else
        return false;
}

bool operator<(const Actor& a1, const Actor& a2)
{
    if(a1.returnCNP()<a2.returnCNP())
        return true;
    else
        return false;
}

template <class Actor>
float calculeaza_bonus(Actor a)
{
    float bonus;
    if(a.returnTip()==true)
        bonus=10+a.return_procent();
    else
        bonus=a.return_procent();
    return bonus;
}

template <>
float calculeaza_bonus(Regizor r)
{
    float bonus;
    bonus=r.returnSuma();
    return bonus;
}

Persoana :: Persoana()
{
    nume="Anonim";
    procent_incasari=0;
}

Persoana :: Persoana(string cnp,string num, string film, float procent)
{
    CNP=cnp;
    nume=num;
    nume_film=film;
    procent_incasari=procent;
}

Persoana :: ~Persoana()
{
    //dtor
}

Persoana& Persoana :: operator=(const Persoana& ob)
{
    if(this!= &ob)
    {
        CNP=ob.CNP;
        nume=ob.nume;
        nume_film=ob.nume_film;
        procent_incasari=ob.procent_incasari;
    }
    return *this;
}



istream& operator>>(istream& in, Persoana& ob)
{
    cout<<endl;
    cout<<"Dati CNP-ul: ";
    in>>ob.CNP;
    cout<<"Dati numele: ";
    in>>ob.nume;
    cout<<"Dati numele filmului: ";
    in>>ob.nume_film;
    cout<<"Dati procentul din incasari: ";
    in>>ob.procent_incasari;
    return in;
}

ostream& operator<<(ostream& out, const Persoana& ob)
{
    out<<"CNP: "<<ob.returnCNP()<<endl;
    out<<"Numele: "<<ob.returnNume()<<endl;
    out<<"Numele filmului: "<<ob.returnFilm()<<endl;
    out<<"Procent incasari: "<<ob.return_procent()<<endl;
    return out;
}

void Persoana::afisare()
{
    cout<<"CNP: "<<CNP<<endl;
    cout<<"Numele: "<<nume<<endl;
    cout<<"Numele filmului: "<<nume_film<<endl;
    cout<<"Procent Incasari: "<<procent_incasari<<endl;
}

void Persoana :: citire()
{
    cout<<endl;
    cout<<"Dati CNP-ul: ";
    cin>>CNP;
    if(CNP.length()<7)
        throw CNP.length();

    cout<<endl<<"Dati numele: ";
    cin>>nume;
    cout<<endl<<"Dati numele filmului: ";
    cin>>nume_film;
    cout<<endl<<"Dati procentul din incasari: ";
    cin>>procent_incasari;
    if(procent_incasari>30)
        throw "Procentul de incasari pentru un angajat nu poate sa fie mai mare de 30 %";
}

Film :: Film()
{
    durata=0;
    incasari=0;
}

Film :: Film(string num, string tip_film, int dur, float bani)
{
    nume=num;
    tip=tip_film;
    durata=dur;
    incasari=bani;
}

Film :: ~Film()
{
    //dtor
}

Film& Film :: operator=(const Film& ob)
{
    if(this!=&ob)
    {
        nume=ob.nume;
        tip=ob.tip;
        durata=ob.durata;
        incasari=ob.incasari;
    }
    return *this;
}

istream& operator>>(istream& in, Film& ob)
{
    cout<<"Dati numele filmului ";
    in>>ob.nume;
    cout<<"Dati tipul ";
    in>>ob.tip;
    cout<<"Dati durata filmului ";
    in>>ob.durata;
    cout<<"Dati incasarile filmului ";
    in>>ob.incasari;
    return in;
}

ostream& operator<<(ostream& out, const Film& ob)
{
    out<<"Nume film: "<<ob.returnNume()<<endl;
    out<<"Tip: "<<ob.returnTip()<<endl;
    out<<"Durata: "<<ob.returnDurata()<<endl;
    out<<"Incasari: "<<ob.returnIncasari()<<endl;
    return out;
}

float returnValProcent(float procent, Film f)
{
    float castig=procent*0.01*f.returnIncasari();
    return castig;
}


void Film::afisare()
{
    cout<<"Nume film: "<<nume<<endl;
    cout<<"Tip: "<<tip<<endl;
    cout<<"Durata: "<<durata<<endl;
    cout<<"Incasari"<<incasari<<endl;
}

Regizor :: Regizor()
{
    suma=700;
}
Regizor :: Regizor(string a, string b, string c, float pr, float sum) :Persoana(a,b,c,pr)
{
    suma=sum;
}

Regizor::~Regizor()
{
    //dtor
}

Regizor& Regizor :: operator=(const Regizor& ob)
{
    if(this!=&ob)
    {
        suma=ob.suma;
    }
    return *this;
}


istream& operator>>(istream& in, Regizor& ob)
{
    in>>(Persoana&)ob;
    cout<<"Dati suma fixa: ";
    in>>ob.suma;
    return in;
}


ostream& operator<<(ostream& out, const Regizor& ob)
{
    out<<(const Persoana&)ob<<endl;
    out<<"Suma fixa: "<<ob.returnSuma()<<endl;

    return out;
}

void Regizor::afisare()
{
    cout<<"CNP: "<<CNP<<endl;
    cout<<"Numele: "<<nume<<endl;
    cout<<"Numele filmului: "<<nume_film<<endl;
    cout<<"Procent Incasari: "<<procent_incasari<<endl;
    cout<<"Suma fixa: "<<suma<<endl;
}

void Regizor :: citire()
{
    cout<<endl;
    cout<<"Dati CNP-ul: ";
    cin>>CNP;
    if(CNP.length()<7)
        throw CNP.length();
    cout<<"Dati numele: ";
    cin>>nume;
    cout<<"Dati numele filmului: ";
    cin>>nume_film;
    cout<<"Dati procentul din incasari: ";
    cin>>procent_incasari;
    cout<<"Dati suma fixa: ";
    cin>>suma;
    if(suma>1000)
        throw "Suma fixa pt regizori nu poate fi mai mare decat 1000";
}

Actor :: Actor()
{
    principal= false;
}

Actor :: Actor(string a, string b, string c, float pr, bool princ) : Persoana(a,b,c,pr)
{
    principal= princ;
}

Actor ::~ Actor()
{
    //dtor
}

Actor& Actor :: operator=(const Actor& ob)
{
    if(this!=&ob)
    {
        principal=ob.principal;
    }
    return *this;
}


istream& operator>>(istream& in, Actor& ob)
{
    in>>(Persoana&)ob;
    cout<<"Este actor principal?(d/n): ";
    char aux;
    in>>aux;
    while(aux!='d' && aux!='n')
    {
        in>>aux;
    }
    if(aux=='d')
        ob.principal=true;
    if(aux=='n')
        ob.principal=false;
    return in;
}


ostream& operator<<(ostream& out, const Actor& ob)
{
    out<<(const Persoana&)ob<<endl;
    if(ob.returnTip()==true)
        out<<"Actor principal"<<endl;

    return out;
}

void Actor :: afisare()
{

    cout<<"CNP: "<<CNP<<endl;
    cout<<"Numele: "<<nume<<endl;
    cout<<"Numele filmului: "<<nume_film<<endl;
    cout<<"Procent Incasari: "<<procent_incasari<<endl;
    if(principal==true)
        cout<<"Actor principal"<<endl;
}

void Actor :: citire()
{
    cout<<endl;
    cout<<"Dati CNP-ul: ";
    cin>>CNP;
    if(CNP.length()<7)
        throw CNP.length();

    cout<<"Dati numele: ";
    cin>>nume;
    cout<<"Dati numele filmului: ";
    cin>>nume_film;
    cout<<"Dati procentul din incasari: ";
    cin>>procent_incasari;
    if(procent_incasari>30)
        throw "Procentul de incasari pentru un angajat nu poate sa fie mai mare de 30 %";
    cout<<"Este actor principal?(d/n): ";
    char aux;
    cin>>aux;
    while(aux!='d' && aux!='n')
    {
        cin>>aux;
    }
    if(aux=='d')
        principal=true;
    if(aux=='n')
        principal=false;
}


template <class T>
class FirmaDistributie
{
    T **listaPersonal;  //pentru a ilustra conceptul de RTTI in sabloane
    static int nrPers;
    static int nrActori;

public:
    FirmaDistributie();
    ~FirmaDistributie();
    void citire();
    void afisare();
    friend istream& operator>>(istream&, FirmaDistributie<T>&);
    friend ostream& operator<<(ostream&, FirmaDistributie<T>&);
    FirmaDistributie& operator=(const FirmaDistributie<T>&);
    template<class X>
    void adaugaPersonal( X ob);
    static int returnNrPers()
    {
        return nrPers;
    };
    static int returnNrAct()
    {
        return nrActori;
    };

};


template <class T>
int FirmaDistributie<T> :: nrPers=0;
template <class T>
int FirmaDistributie<T> :: nrActori=0;

template <class T>
FirmaDistributie<T> :: FirmaDistributie()
{
    listaPersonal=new T* [100]; //100 de persoane pot participa in total la facerea unui film
}

template <class T>
FirmaDistributie<T> :: ~FirmaDistributie()
{
    //dtor
    for(int i=0; i<nrPers; i++)
        delete []listaPersonal[i];
    delete[] listaPersonal;
}


template <class T>
void FirmaDistributie<T> :: citire()
{
    T *ob= new T();
    ob->citire();
    listaPersonal[nrPers]=ob;
    nrPers++;

}

template <class T>
void FirmaDistributie<T> :: afisare()
{
    for(int i=0; i<nrPers; i++)
    {
        listaPersonal[i]->afisare();
        cout<<endl;
    }
}

template <class T> template <class X>
void FirmaDistributie<T> :: adaugaPersonal(X ob)
{
    listaPersonal[nrPers]=ob;

    if( strstr( typeid(*(listaPersonal[nrPers])).name(),"Actor")!=NULL )
        nrActori++;

    nrPers++;

}

template<class T>
ostream& operator<<(ostream& out, FirmaDistributie<T>& ob)
{
    for(int i=0; i<ob.nrPers; i++)
    out<<ob.listaPersonal[i];
    return out;
}

template<class T>
istream& operator>>(istream& in, FirmaDistributie<T>& ob)
{
    for(int i=0; i<ob.nrPers; i++)
    in>>ob.listaPersonal[i];
    return in;
}


template <>
class FirmaDistributie<Actor>
{
    static int nrActPrincipali;
    Actor *listaPrincipali;
public:
    FirmaDistributie();
    ~FirmaDistributie();
    friend istream& operator>>(istream&, FirmaDistributie<Actor>&);
    friend ostream& operator<<(ostream&, FirmaDistributie<Actor>&);
    void addActorPrincipal(Actor);
    void afiseazaPrincipali();
    static int returnPrincip()
    {
        return nrActPrincipali;
    };

};


int FirmaDistributie<Actor>::nrActPrincipali=0;

FirmaDistributie<Actor> :: FirmaDistributie()
{
    listaPrincipali=new Actor[50];
}

FirmaDistributie<Actor> :: ~FirmaDistributie()
{
    delete []listaPrincipali;
}

void FirmaDistributie<Actor> :: addActorPrincipal( Actor ob)
{
    listaPrincipali[nrActPrincipali]=ob;
    nrActPrincipali++;
}

void FirmaDistributie<Actor> :: afiseazaPrincipali()
{
    for(int i=0; i<nrActPrincipali; i++)

    {
        cout<<(const Actor)listaPrincipali[i];
        cout<<endl;
    }
}

ostream& operator<<(ostream& out, FirmaDistributie<Actor>& ob)
{
    for(int i=0; i<ob.returnPrincip(); i++)
    out<<(const Actor)ob.listaPrincipali[i];
    return out;
}

istream& operator>>(istream& in, FirmaDistributie<Actor>& ob)
{
    for(int i=0; i<ob.returnPrincip(); i++)
    in>>ob.listaPrincipali[i];
    return in;
}

int main()
{

    cout<<"Adauga film: f"<<endl;
    cout<<"Afiseaza tot personalul pentru toate filmele, stocati in FirmaDisributie (clasa template): p "<<endl;
    cout<<"Afiseaza tot personalul pentru toate filmele, stocati in set<tuple>>: q "<<endl;
    cout<<"Iesire: x"<<endl;

    set<tuple<Persoana,Film,float>> personalFilme;
    FirmaDistributie<Persoana> distributie;
    FirmaDistributie<Actor> actoriPrincipali;

    char aux;
    cin>>aux;
    while(aux !='x')
    {
        switch(aux)
        {
        case 'f':
        {
            Film f;
            cin>>f;

            cout<<"Adauga actor: a"<<endl;
            cout<<"Adauga regizor: r"<<endl;
            cout<<"Adauga personal tehnic: t"<<endl;
            cout<<"Inapoi la meniul principal: b"<<endl;
            char aux2;
            cin>>aux2;
            while(aux2!='b')
            {
                switch(aux2)
                {
                case 'a':
                {
                    Actor *ac=new Actor();
                    try
                    {
                        ac->citire();
                    }
                    catch (const char *mesaj)
                    {
                        cout<<mesaj<<endl;
                        cout<<"Introduceti va rugam, din nou datele pt acest actor!";
                        ac->citire();
                    }
                    catch (unsigned int lungime)
                    {
                        cout<<"CNP ul nu poate avea "<<lungime<<" caractere"<<endl;
                        cout<<"Va rugam sa introduceti cel putin 7 caractere"<<endl;
                        cout<<"Introduceti va rugam, din nou datele pt acest actor!";
                        ac->citire();
                    }


                    distributie.adaugaPersonal(ac);
                    if(ac->returnTip()==true)
                        actoriPrincipali.addActorPrincipal(*ac);


                    Persoana *persoana= new Persoana();
                    persoana=ac;

                    float procentFinal=calculeaza_bonus(*ac);
                    float bonus= returnValProcent(procentFinal,f);

                    tuple<Persoana,Film,float> angajat;
                    angajat=make_tuple(*persoana,f,bonus);
                    personalFilme.insert(angajat);


                    break;
                }
                case 'r':
                {
                    Regizor *reg=new Regizor();
                    try
                    {
                        reg->citire();
                    }
                    catch(const char* mesaj1)
                    {
                        cout<<mesaj1<<endl;
                        cout<<"Introduceti va rugam, din nou datele pt acest regizor!";
                        reg->citire();
                    }
                    catch(float x)
                    {
                        cout<<"Procentul de incasari pentru un angajat nu poate sa fie mai mare de 30 %"<<endl;
                        cout<<"Introduceti va rugam, din nou datele pt acest regizor!";
                        reg->citire();
                    }
                    catch (unsigned int lungime)
                    {
                        cout<<"CNP ul nu poate avea "<<lungime<<" caractere"<<endl;
                        cout<<"Va rugam sa introduceti cel putin 7 caractere"<<endl;
                        cout<<"Introduceti va rugam, din nou datele pt acest regizor!";
                        reg->citire();
                    }

                    distributie.adaugaPersonal(reg);

                    Persoana *persoana=new Persoana();
                    persoana=reg;
                    float bonus=returnValBani(*reg,f);
                    bonus+=reg->returnSuma();

                    tuple<Persoana,Film,float> angajat;
                    angajat=make_tuple(*persoana,f,bonus);
                    personalFilme.insert(angajat);

                    break;
                }

                case 't':
                {
                    Persoana *teh=new Persoana();
                    try
                    {
                        teh->citire();
                    }
                    catch(const char * mesaj)
                    {
                        cout<<mesaj<<endl;
                        cout<<"Introduceti va rugam, din nou datele pt acest personal tehnic!";
                        teh->citire();
                    }
                    catch (unsigned int lungime)
                    {
                        cout<<"CNP ul nu poate avea "<<lungime<<" caractere"<<endl;
                        cout<<"Va rugam sa introduceti cel putin 7 caractere"<<endl;
                        cout<<"Introduceti va rugam, din nou datele pt acest personal tehnic!";
                        teh->citire();
                    }

                    distributie.adaugaPersonal(teh);

                    Persoana *persoana=new Persoana();
                    persoana=teh;
                    float bonus=returnValBani(*teh,f);

                    tuple<Persoana,Film,float> angajat;
                    angajat=make_tuple(*persoana,f,bonus);
                    personalFilme.insert(angajat);

                    break;
                }

                }
                cin>>aux2;
            }
            cout<<endl<<"--------------------------------------"<<endl;
            cout<<"Adauga film: f"<<endl;
            cout<<"Afiseaza tot personalul pentru toate filmele, stocati in FirmaDisributie (clasa template): p "<<endl;
            cout<<"Afiseaza tot personalul pentru toate filmele, stocati in set<tuple>>: q "<<endl;
            cout<<"Iesire: x"<<endl;
            break;
        }

        case 'p':
        {
            cout<<endl;
            cout<<endl<<"Personalul cuprinde "<<FirmaDistributie<Persoana>::returnNrAct()<<" actori in total. Actori principali : "<<FirmaDistributie<Actor>::returnPrincip()<<endl;
            cout<<"In total "<<FirmaDistributie<Persoana>::returnNrPers()<<" persoane: "<<endl;
            distributie.afisare();
            break;
        }

        case 'q':
        {
            cout<<endl;
            set<tuple<Persoana, Film, float>> :: iterator j;
            for(j=personalFilme.begin(); j!=personalFilme.end(); j++)
                cout<<get<0>(*j)<<endl<<get<1>(*j)<<endl<<get<2>(*j)<<endl;

            break;
        }
        }
        cin>>aux;
    }
    return 0;


}
