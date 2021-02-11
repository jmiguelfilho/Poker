//
//  main.cpp
//  Poker
//
//  Created by João Miguel on 17/06/20.
//  Copyright © 2020 João Miguel. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <string>
#include <ctime>

#define QTDE_MAOS 4

using namespace std;

int f;

enum figura{dois, tres, quatro, cinco, seis, sete, oito,
 nove, dez, valete, dama, rei, as};
enum simbolo{ouros, espadas, copas, paus};

char figuras[][as+1] = {" 2", " 3", " 4", " 5", " 6", " 7", " 8", " 9",
 "10", "VA", "DA", "RE", "AS"};
char simbolos[][4] = {"o", "e", "c", "p"};

struct Carta{
    figura valor;
    simbolo naipe;
    string c_str(){
        return (string)figuras[valor] + (string)simbolos[naipe];
    }
};

struct Jogo{
    int quantidade;
    figura valor;
};

Carta proximaCarta(){
    static figura f = dois;
    static simbolo s = ouros;
    Carta temp;
    temp.valor = f;
    temp.naipe = s;
    f = (figura)((f + 1)%(as+1));
    if (f==dois)
        s = (simbolo)((s + 1)%(paus+1));
    return temp;
}

template <class T>
void imprimir(vector<T> v){
    typename vector<T>::iterator it;
    for (it = v.begin(); it != v.end(); it++)
        cout << (*it).c_str() << " ";
    cout << endl;
}

bool conta_figuras(Carta value){
    return value.valor == f;
}

int main(int argc, char **argv)
{

    int i, j, q, contagem_f;
    vector<Carta> baralho(52), mesa(5);
    vector<Carta>::iterator it;
    vector< vector<Carta> > maos(QTDE_MAOS);
    vector< vector<Jogo> > jogos(QTDE_MAOS);
    bool dupla, trinca;
    
    srand ( unsigned ( time (NULL) ) );
    
    //gera baralho
    generate_n(baralho.begin(), 52, proximaCarta);

    //imprime baralho
    cout << "Baralho inicial\n";
    imprimir(baralho);
    
    //embaralha
    random_shuffle(baralho.begin(), baralho.end());
    
    //imprime baralho
    cout << endl;
    cout << "Baralho embaralhado\n";
    imprimir(baralho);

    //gera maos
    for (i=0; i<QTDE_MAOS;i++)
        maos[i].resize(2);

    q = 52;
    for (j = 0; j < 2; j++)
        for (i=0; i<QTDE_MAOS;i++){
            maos[i][j] = baralho[--q];
            baralho.pop_back();
        }
    
    //gera mesa
    --q;//joga fora
    baralho.pop_back();

    mesa[0] = baralho[--q];
    baralho.pop_back();
    mesa[1] = baralho[--q];
    baralho.pop_back();
    mesa[2] = baralho[--q];
    baralho.pop_back();

    --q;//joga fora
    baralho.pop_back();

    mesa[3] = baralho[--q];
    baralho.pop_back();

    --q;//joga fora
    baralho.pop_back();

    mesa[4] = baralho[--q];
    baralho.pop_back();

    cout << endl;
    //imprime maos e mesa
    for (i=0; i<4;i++){
        cout << "Mao " << i << ": ";
        imprimir(maos[i]);
    }

    cout << "Mesa : ";
    imprimir(mesa);
    
    //expande maos com mesa
    for (i=0; i<QTDE_MAOS;i++){
        maos[i].resize(7);
        for (j=0;j<5;j++)
            maos[i][j+2] = mesa[j];
    }

    cout << endl;
    //imprime maos extendida
    for (i=0; i<QTDE_MAOS;i++){
        cout << "Mao " << i << ": ";
        imprimir(maos[i]);
    }

    //imprime contagens
    cout << endl;
    for (i=0; i<QTDE_MAOS;i++){
        for (f = dois; f<=as; f++){
            contagem_f = count_if(maos[i].begin(), maos[i].end(), conta_figuras);
            if (contagem_f>1){
                cout << "Mao " << i << " possui ";
                switch(contagem_f){
                    case 2:
                        cout << " dupla";
                    break;
                    case 3:
                        cout << "trinca";
                    break;
                    case 4:
                        cout << "quadra";
                    break;
                }
                cout << " de " << figuras[f] << endl;
                Jogo temp;
                temp.quantidade = contagem_f;
                temp.valor = (figura)f;
                jogos[i].push_back(temp);
            }
        }
    }
    
    //verifica fullhouse
    cout << endl;
    for (i=0; i<QTDE_MAOS;i++){
        dupla = trinca = false;
        
        for (j = 0; j< (int)jogos[i].size(); j++){
            Jogo temp = jogos[i][j];
            dupla = dupla || temp.quantidade == 2;
            trinca = trinca || temp.quantidade == 3;
        }
        
        if (dupla && trinca){
            cout << "Mao " << i << ": FULL HOUSE" << endl;
        }
    }

    //verifica carta maior
    int k;
    cout << endl;
    for (i=0; i<QTDE_MAOS;i++){
        if (!jogos[i].size()){
            f = -1;
            for (j = 0; j<(int)maos[i].size();j++){
                if (maos[i][j].valor > f){
                   f = maos[i][j].valor;
                    k = j;
                }
            }
            cout << "Mao " << i << ": Maior Carta ";
            cout << maos[i][k].c_str() << endl;
        }
    }
    
    //verifica straight
    system("pause");
    return 0;
}
