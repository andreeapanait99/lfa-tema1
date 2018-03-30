#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>
using namespace std;
class tranzitie
{
    char stare_init[5];
    char stare_finala[5];
    char caracter[10];
public:
    tranzitie(char[5],char[5],char[10]);
    void afisare();
    const char* get_stare_init() const;
    const char* get_stare_finala() const;
    const char* get_caracter() const;
};
tranzitie::tranzitie(char si[5],char sf[5],char c[10])
{
    strcpy(stare_init,si);
    strcpy(stare_finala,sf);
    strcpy(caracter,c);
}
void tranzitie::afisare()
{
    cout<<stare_init<<" "<<stare_finala<<" "<<caracter<<endl;
}
const char* tranzitie::get_stare_init() const
{
    return &stare_init[0];
}
const char* tranzitie::get_stare_finala() const
{
    return &stare_finala[0];
}
const char* tranzitie::get_caracter() const
{
    return &caracter[0];
}
int main()
{
    ifstream f("automat.in");
    vector <tranzitie> v;
    char q0[5],qc[5],si[5],sf[5],c[10], cuv[100];
    char alfabet[100][100],stari[100][100],final[100][100],rasp[2];
    int i,n_alf,n_stari,n_final,n_tranz,j,fin=0,op=1,nr;
    f>>n_stari;
    for (i=0; i<n_stari; i++) f>>stari[i];
    //for (i=0;i<n_stari;i++) cout<<stari[i]<<endl;
    f>>n_alf;
    for (i=0; i<n_alf; i++) f>>alfabet[i];
    //for (i=0;i<n_alf;i++) cout<<alfabet[i]<<endl;
    f>>q0;
    f>>n_final;
    for (i=0; i<n_final; i++) f>>final[i];
    //for (i=0;i<n_final;i++) cout<<final[i]<<endl;
    f>>n_tranz;
    for (i=0; i<n_tranz; i++)
    {
        f>>si>>sf>>c;
        tranzitie a(si,sf,c);
        v.push_back(a);
    }
    //for (i=0; i<n_tranz; i++) v[i].afisare();
    cout<<"* este cuvantul vid"<<endl;
    while (op)
    {
        cout<<"Introduceti numarul de caractere: ";
        cin>>nr;
        cout<<"Introduceti cuvantul (caracterele separate prin spatiu): ";
        strcpy(qc,q0);
        cin>>cuv;
        fin=0;
        i=1;
        if (cuv[0]=='*'&&strcmp(final[0],qc)==0) fin=1;
        else while (i<=nr)
            {
                int exista=0;
                for (j=0; j<n_alf; j++)
                    if (strcmp(alfabet[j],cuv)==0) exista=1;
                if (exista==0) goto et;
                exista=0;
                for (j=0; j<v.size(); j++)
                    if (strcmp(v[j].get_stare_init(),qc)==0&&strcmp(v[j].get_caracter(),cuv)==0)
                    {
                        exista=1;
                        break;
                    }
                if (exista==0) goto et;
                strcpy(qc,v[j].get_stare_finala());
                i++;
                if (i>nr) break;
                cin>>cuv;
            }
        for (i=0; i<n_final; i++)
            if (strcmp(qc,final[i])==0) fin=1;
et:
        if (fin==1) cout<<"Cuvantul apartine limbajului";
        else cout<<"Cuvantul nu apartine limbajului";
        cout<<endl<<"Doriti sa mai introduceti un cuvant? (da/nu) ";
        cin>>rasp;
        if (rasp[0]=='n') op=0;
    }
    f.close();
    return 0;
}
