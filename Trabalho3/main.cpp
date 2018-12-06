#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <vector>

using namespace std;

struct Index
{
    string palavra;
    int index[50];
};

void opcoes();
void ordenar(int *indice, string *palavra,string* espelho);
void procurar (Index *invertido, string x,string *espelho,int ocorrencia);
void arrumarInd(int *indice,string *palavra,Index*invertido);

int main()
{

    int menu;
    opcoes();
    cin>>menu;
    system("clear");

    int contText=0;
    int counter=0,wordSize=0;
    int indice[980];

    string palavra[980];
    string espelho[980];
    string line;

    Index arquivo[980];

    ifstream myFile("Historia.txt");

    for(int k=0; k<980; k++)
    {
        indice[k]=0;
        for(int l=0; l<50; l++)
            arquivo[k].index[l]=-1;
    }

    while(menu!=0)
    {
        if(menu==0)
        {
            break;
        }
        if(menu==1)
        {
            string content;
            if(myFile.is_open())
            {
                while(! myFile.eof())
                {
                    myFile >> content;
                    cout << content << " ";
                }
            }
        }

        else if(menu==2)
        {

            if(myFile.is_open())
            {

                while (std::getline(myFile, line))
                {
                    for(char charzin : line)
                    {
                        char auxAnt;
                        counter++;

                        if(((64<charzin)&&(charzin<91))
                                ||((96<charzin)&&(charzin<123)))
                        {
                            palavra[contText]+=charzin;
                            wordSize++;
                        }
                        else
                        {
                            if(((64<auxAnt)&&(auxAnt<91))
                                    ||((96<auxAnt)&&(auxAnt<123)))
                            {

                                indice[contText]=counter-wordSize;
                                wordSize=0;
                                contText++;
                            }
                        }
                        auxAnt=charzin;
                    }
                }

                myFile.close();
            }

            ordenar(indice,palavra,espelho);
            arrumarInd(indice,palavra,arquivo);


        }


        else if(menu==3)
        {
            system("clear");
            string inserir;
            cout<<"Insira a palavra"<<endl;
            cin>>inserir;
            procurar(arquivo,inserir,espelho,0);
        }
        else if(menu==4)
        {
            system("clear");
            string inserir;
            cout<<"Insira a palavra"<<endl;
            cin>>inserir;
            procurar(arquivo,inserir,espelho,1);
        }
        opcoes();
        cin>>menu;

    }



    return 0;
}


void opcoes()
{
    cout<<endl;
    cout<<"0-> Sair"<<endl;
    cout<<"1-> Ler arquivo"<<endl;
    cout<<"2-> Arquivo Invertido"<<endl;
    cout<<"3-> Procurar palavra"<<endl;
    cout<<"4-> Procurar ocorrencia"<<endl;
}


void ordenar(int *indice, string *palavra,string *espelho)
{
    int i, j,temp2=2;
    string temp;
    for(i =0; i<980; i++)
    {
        espelho[i]=palavra[i];
    }
    for (i = 0; i < 979 ; i++)
    {
        for (j = (i+1); j < 980; j++)
        {
            if (palavra[j].compare(palavra[i])<0)
            {
                temp = palavra[i];
                temp2= indice[i];
                palavra[i] = palavra[j];
                indice[i]=indice[j];
                palavra[j] = temp;
                indice[j]=temp2;

            }
        }
    }


}

void arrumarInd(int *indice,string *palavra,Index* invertido)
{

    int i,j,l=0,cont=-1;
    string anterior=palavra[0];


    for( i=0; i<980; i++)
    {
        if(palavra[i]!=anterior)
        {
            j=0;
            cont++;
            invertido[cont].palavra=palavra[i];
            invertido[cont].index[j]=indice[i];

        }
        else
        {
            j++;
            invertido[cont].index[j]=indice[i];

        }

        anterior=palavra[i];

    }

    for( i=0; i<458; i++)
    {
        cout<< "|"<<invertido[i].palavra<<":";
        for(j=0; j<50; j++)
        {
            if(invertido[i].index[j]!=-1)
                cout<<invertido[i].index[j]<<" ";
        }
        cout<<endl;

    }


}

void procurar(Index *invertido, string x,string *espelho,int ocorrencia)
{
    int i;
    for ( i=0; i<980; i++)
    {
        if (x==invertido[i].palavra)
        {
            cout<<invertido[i].palavra<<":";
            for(int j=0; j<50; j++)
            {
                if(invertido[i].index[j]!=-1)
                    cout<<invertido[i].index[j]<<" ";
            }
            cout<<endl;

            break;
        }

    }

    if(ocorrencia==1)
    {
        for(i=0; i<980; i++)
        {

            if(x==espelho[i])
            {
                cout<<espelho[i-2]<<" ";
                cout<<espelho[i-1]<<" ";
                cout<<espelho[i]<<" ";
                cout<<espelho[i+1]<<" ";
                cout<<espelho[i+2]<<" ";
                cout<<endl;
            }
        }
    }
    else if(ocorrencia==0)
    {
        for(i=0; i<980; i++)
        {

            if(x==espelho[i])
            {
                cout<<espelho[i-2]<<" ";
                cout<<espelho[i-1]<<" ";
                cout<<espelho[i]<<" ";
                cout<<espelho[i+1]<<" ";
                cout<<espelho[i+2]<<" ";
                cout<<endl;
                break;
            }
        }

    }

}
