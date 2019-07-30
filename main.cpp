#include <iostream>
#include <cstring>
#include <cstdlib>
#define StrLen 200
using namespace std;

char* cazul_simplu(int linie){
    char numar_char[30][StrLen]={"zero","un","deux","trois","quatre","cinq","six","sept","huit","neuf","dix","onze","douze","treize","quatorze","quinze","seize","dix-sept","dix-huit","dix-neuf","vingt","trente","quarante","cinquante","soixante"};
    return numar_char[linie];
}

char * leaga_numar(char numar_initial[StrLen],char legatura[StrLen],char restul_numarului[StrLen]){
        char numar_nou[StrLen];
        strcpy(numar_nou,numar_initial);
        strcat(numar_nou,legatura);
        strcat(numar_nou,restul_numarului);
        return numar_nou;
}

char* cazul_70(int numar){
    int rest,cat;
    rest = numar % 10;
    cat = numar / 10;
    if(!rest) return cazul_simplu(18+cat);
    else if(rest == 1){
        return leaga_numar(cazul_simplu(18+cat)," ","et un");
    }
    else{
        return leaga_numar(cazul_simplu(18+cat),"-",cazul_simplu(rest));
    }
}

char* cazul_79(int numar){
    int rest,cat;
    rest = numar % 10;
    cat = numar / 10;
    if(!rest)
        return "soixante-dix";
    else if(rest == 1)
        return "soixante et onze";
    else{
        return leaga_numar("soixante","-",cazul_simplu(rest+10));
    }
}

char* numar_unitati(int cat,int rest){
    if(cat == 8)
        if(rest)
            return cazul_simplu(rest);
        else
            return "dix";
    else
        return cazul_simplu(rest+10);
}

char* cazul_99(int numar){
    int rest,cat;
    rest = numar % 10;
    cat = numar / 10;
    if(!rest && cat==8)
        return "quatre-vingts";
    else
        return leaga_numar("quatre-vingt","-",numar_unitati(cat,rest));
}

char* numar_sutimi(int cat){
    if(cat>1)
        return strcat(cazul_simplu(cat)," ");
    else
        return "";
}

char * convert_char(string string_primit){
    char*char_normal = new char[string_primit.length() + 1];
    strcpy(char_normal,string_primit.c_str());
    return char_normal;
}

string procesare_numar(int numar){
    char numar_char[StrLen]="";
    int rest,cat;
    if(numar<=19)
        return strcpy(numar_char,cazul_simplu(numar));
    else
    if(numar <= 69)
            return strcpy(numar_char,cazul_70(numar));
    else
    if(numar <= 79)
           return strcpy(numar_char,cazul_79(numar));
    else
    if(numar <= 99)
            return strcpy(numar_char,cazul_99(numar));
    else
    if(numar <= 999){
        if(numar == 100)
            return "cent";
        rest = numar % 100;
        cat = numar / 100;
        if(!rest){
            return strcpy(numar_char,leaga_numar(cazul_simplu(cat)," ","cents"));
        }
        else
            return strcpy(numar_char,leaga_numar(numar_sutimi(cat),"cent ",convert_char(procesare_numar(rest))));
    }
    else
    if(numar<= 999999){
        if(numar == 1000) return "mille";
        rest = numar % 1000;
        cat = numar / 1000;
        if(cat>1)
            strcpy(numar_char,leaga_numar(numar_char,convert_char(procesare_numar(cat))," "));
        strcat(numar_char,"mille ");
        if(rest)strcat(numar_char,procesare_numar(rest).c_str());
        return numar_char;
    }
    else {
        if(numar == 1000000) return "un million";
        rest = numar % 1000000;
        cat = numar / 1000000;
        strcpy(numar_char,leaga_numar(numar_char,convert_char(procesare_numar(cat))," "));
        if(cat>1)
            strcat(numar_char,"millions ");
        else
            strcat(numar_char,"million ");
        if(rest)strcat(numar_char,procesare_numar(rest).c_str());
        return numar_char;
    }
}

bool verifica_interval(int numar){
    if(numar >= 0 && numar <= 10000000)return true;
    return false;
}

bool este_numar_corect(char numar[StrLen]){
    char numere[11]= "1234567890";
    int lungime,i;
    lungime = strlen(numar);
    for(i=0;i<lungime;i++){
        if(!strchr(numere,numar[i]))return false;
    }
    return verifica_interval(atoi(numar));
}

int verifica_putere(char numar[StrLen]){
    if(!strcmp(numar,"millions") || !strcmp(numar,"million"))return 1000000;
    if(!strcmp(numar,"mille"))return 1000;
    if(!strcmp(numar,"cent") || !strcmp(numar,"cents"))return 100;
    return 0;
}

int decodifica_numar(char numar[StrLen]){
    int numar_construit=0,lungime;
    char numere_simple[7][StrLen]={"vingt","trente","quarante","cinquante","soixante","","quatrevingt"},numere[20][StrLen]={"zero","un","deux","trois","quatre","cinq","six","sept","huit","neuf","dix","onze","douze","treize","quatorze","quinze","seize","dix-sept","dix-huit","dix-neuf"},*p,*q,aux[10];
    for(int i=0;i<20;i++)
        if(!strcmp(numere[i],numar))return i;
    q = strstr(numar,"quatre-vingt");
    if(q){
        if(strlen(q)==13)lungime = 13;
        else lungime = 12;
        strcpy(aux,q+lungime);
        strncpy(q,"quatrevingt",lungime);
        strcat(numar,aux);
    }
    p = strchr(numar,'-');
    if(!p){
        for(int i=0;i<7;i++){
            if(!strcmp(numar,numere_simple[i]))return (i+2)*10;
        }
    }
    else{
        numar_construit = numar_construit + decodifica_numar(p+1);
        *p = 0;
        numar_construit = numar_construit + decodifica_numar(numar);
        return numar_construit;
    }
    return -1;
}


int procesare_cuvant(char numar[StrLen]){
    int numar_construit=0,gasit=0,numar_final[StrLen],total_numere=0;
    char *p;
    p = strtok (numar," ");
    while (p != NULL)
    {
        if(strcmp(p,"et")){
            gasit = decodifica_numar(p);
            if(gasit != -1){
                    numar_construit = numar_construit + gasit;
            }
            else {
                gasit = verifica_putere(p);
                if(gasit){
                        if(numar_construit == 0)numar_construit = 1;
                            numar_construit = numar_construit * gasit;
                        if(gasit>999){
                            numar_final[++total_numere] = numar_construit;
                            numar_construit = 0;
                        }
                }
            }
        }
        p = strtok (NULL, " ");
    }
    for(int i=1;i<=total_numere;i++){
            numar_construit = numar_construit + numar_final[i];
    }
    return numar_construit;
}

char * curatare_spatii(char * numar){
    char* cpy = numar;
    char* temp = numar;

    while (*cpy)
    {
        if (*cpy != ' ')
            *temp++ = *cpy;
        cpy++;
    }
    *temp = 0;
    return numar;
}

bool verifica_cuvant_final(char * numar_primit,int numar_nou){
if(!strcmp(curatare_spatii(convert_char(procesare_numar(numar_nou))),curatare_spatii(numar_primit)) && verifica_interval(numar_nou))return 1;
return 0;
}

int main()
{
    char numar_primit[StrLen],copie_numar[StrLen];
    int numar_nou;
    cin.getline(numar_primit,StrLen);
    if(este_numar_corect(numar_primit))
        cout<<procesare_numar(atoi(numar_primit))<<endl;
    else{
        strcpy(copie_numar,numar_primit);
        numar_nou = procesare_cuvant(copie_numar);
        if(verifica_cuvant_final(numar_primit,numar_nou))cout<<numar_nou<<endl;
        else cout<<"Numarul introdus nu este corect !";
    }
    return 0;
}
