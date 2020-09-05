#include <bits/stdc++.h>
using namespace std;
#define N 3

vector<vector<int> > solucion;
map<int,pair<int,int> > puzzle; //numeros del tablero con sus respectivas posiciones en el

typedef struct Nodo{
    vector<vector<int> > estado;
    int h;
    int costo;
    Nodo* padre;
}Nodo;

typedef struct compareH{
    bool operator()(pair<int,Nodo*> const& h1, pair<int,Nodo*> const& h2){
        return h1.first>h2.first;
    }
}compareH;

map<int,Nodo> grafo;

void tipo_puzzle(int n){
    if(n == 2) solucion = {{1,2},{3,0}};
    if(n == 3) solucion = {{1,2,3},{4,5,6},{7,8,0}};
    if(n == 4) solucion = {{1,2,3,4},{5,6,7,8},{9,10,11,0}};

}

void print(Nodo* act){
    for(int i = 0; i < act->estado.size(); i++){
        for(int j = 0; j < act->estado.size(); j++){
            cout<<act->estado[i][j]<<" ";
        }
        cout<<endl;
    }
}

void mostrarCamino(Nodo* n){
    Nodo *parent = n->padre;
    vector<Nodo*> camino;
    while(parent != NULL){
        camino.push_back(parent);
        parent = parent->padre;
    }
    reverse(camino.begin(),camino.end());
    for(int i = 0; i < camino.size(); i++){
        print(camino[i]);
        cout<<"---------"<<endl;
    }
    cout<<camino.size()<<endl;
}

void setPosiciones(vector<vector<int> > estado){
    for(int i = 0; i < estado.size(); i++){
        for(int j = 0; j < estado.size(); j++){
            pair<int,int> p = make_pair(i,j);
            puzzle[estado[i][j]] = p;
        }
    }
}

vector<Nodo*> expandir(Nodo* estado){ //expande el estado actual y obtiene sus hijos
    setPosiciones(estado->estado);
    int posx = puzzle[0].first;
    int posy = puzzle[0].second;
    int xx[] = {0,0,-1,1};	//"dirección" en la que se puede mover en eje x
	int yy[] = {-1,1,0,0};	//lo mismo para eje y
    int a,b;
    int n = estado->estado.size();
    vector<Nodo*> hijos;
    for(int i = 0; i < 4; i++){
        a = xx[i] + posx;
        b = yy[i] + posy;
        if(a < 0 || a >= n || b < 0 || b >= n){
            continue;
        }
        pair<int,int> p = make_pair(a,b);
        Nodo *hijo = new Nodo;
        hijo->estado = estado->estado;
        hijo->estado[puzzle[0].first][puzzle[0].second] = estado->estado[a][b];
        hijo->estado[a][b] = 0;
        hijo->padre = estado;
        hijo->costo = estado->costo + 1;
        hijos.push_back(hijo);
    }
    return hijos;
}

void printhijos(vector<Nodo> hijos){
    for(int i = 0; i < hijos.size(); i++){
        for(int j = 0; j < hijos[i].estado.size(); j++){
            for(int k = 0; k < hijos[i].estado.size(); k++){
                cout<<hijos[i].estado[j][k]<<" ";
            }
            cout<<endl;
        }
        printf("asdasd\n\n");
    }
}
bool expandido(vector<vector<int> > estado,vector<Nodo*> explorado){
    for(int i = 0; i < explorado.size(); i++){
        if(explorado[i]->estado == estado) return true;
    }
    return false;
}

int manhattan(vector<vector<int> > puzzle){
    int dist = 0;
    for(int i = 0; i < puzzle.size(); i++){
        for(int j = 0; j < puzzle.size(); j++){
            for(int k = 0; k < puzzle.size(); k++){
                for(int l = 0; l < puzzle.size(); l++){
                    if(puzzle[i][j] != 0){
                        if(puzzle[i][j] == solucion[k][l]){
                            dist += abs(i-k) + abs(j-l);
                            break;
                        }

                    }
                }
            }
        }
    }
    return dist;
}

void greedy(vector<vector<int> > estado){
    priority_queue<pair<int,Nodo*>, vector<pair<int,Nodo*> >, compareH> open;
    int h = manhattan(estado);
    Nodo* actual = new Nodo;
    actual->estado = estado;
    actual->padre = NULL;
    open.push(make_pair(h,actual));
    vector<Nodo*> closed;
    vector<Nodo*> expandidos;
    while(!open.empty()){
        actual = open.top().second;
        open.pop();
        closed.push_back(actual);
        setPosiciones(actual->estado);
        if(actual->estado == solucion){
            cout<<"Solucion encontrada"<<endl;
            mostrarCamino(actual);
            return;
        }
        vector<Nodo*> hijo = expandir(actual);
        for (int i = 0; i < hijo.size(); i++){
            if(!expandido(hijo[i]->estado,closed)){
                open.push(make_pair(manhattan(hijo[i]->estado),hijo[i]));
            }
        }
    }
}

void Astar(vector<vector<int> > estado){
    priority_queue<pair<int,Nodo*>, vector<pair<int,Nodo*> >, greater<pair<int,Nodo*> > > open;
    int h = manhattan(estado);
    Nodo* actual = new Nodo;
    actual->estado = estado;
    actual->costo = 0;
    actual->padre = NULL;
    open.push(make_pair(h,actual));
    vector<Nodo*> closed;       //cambiar por set<Nodo*>
    while(!open.empty()){
        actual = open.top().second;
        open.pop();
        closed.push_back(actual);
        setPosiciones(actual->estado);
        if(actual->estado == solucion){
            cout<<"Solucion encontrada"<<endl;
            mostrarCamino(actual);
            return;
        }
        vector<Nodo*> hijo = expandir(actual);
        for (int i = 0; i < hijo.size(); i++){
            h = manhattan(hijo[i]->estado);
            int cactual = h+hijo[i]->costo;
            if(!expandido(hijo[i]->estado,closed) && actual->costo < cactual){
                open.push(make_pair(cactual,hijo[i]));
            }
        }
    }
}

void DFS(vector<vector<int> > estado){
    stack<Nodo*> s;
    Nodo *actual = new Nodo;
    actual->estado = estado;
    actual->padre = NULL;
    s.push(actual);
    vector<Nodo*> explorado;
    while(!s.empty()){
        actual = s.top();
        s.pop();
        setPosiciones(actual->estado);
        if(actual->estado == solucion){
            cout<<"Solucion encontrada:"<<endl;
            mostrarCamino(actual);
            print(actual);
            return;
        }
        if(!expandido(actual->estado,explorado)){
            explorado.push_back(actual);
        }
        vector<Nodo*> hijo = expandir(actual);
        for(int i = 0; i < hijo.size(); i++){
            if(!expandido(hijo[i]->estado,explorado)){
                hijo[i]->padre = actual;
                s.push(hijo[i]);
            }
        }
    }
    cout<<"Solucion no encontrada"<<endl;
}

void BFS(vector<vector<int> > estado){
    queue<Nodo*> q;
    Nodo *actual = new Nodo;
    actual->estado = estado;
    actual->padre = NULL;
    q.push(actual);
    vector<Nodo*> explorado;
    while(!q.empty()){
        actual = q.front();
        setPosiciones(actual->estado);
        q.pop();
        explorado.push_back(actual);
        if(actual->estado == solucion){
            cout<<"Solucion encontrada:"<<endl;
            mostrarCamino(actual);
            return;
        }
        vector<Nodo*> hijo = expandir(actual);
        for(int i = 0; i < hijo.size(); i++){
            if(!expandido(hijo[i]->estado,explorado)){
                q.push(hijo[i]);
                explorado.push_back(hijo[i]);
            }
        }
    }
}
int main(){
    for(int i = 0; i < N*N; i++){
        pair<int,int> p = make_pair(0,0);
        pair<int,pair<int,int> > par = make_pair(0,p);
        puzzle.insert(par);
    }
    string line;
    ifstream input("puzzle.txt");
    getline(input,line);
    int n = stoi(line),num;
    tipo_puzzle(n);
    vector<vector<int> > estado(n);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cin.rdbuf(input.rdbuf());
            cin>>num;
            estado[i].push_back(num);
        }
    }
    cout<<"__Puzzle__"<<endl;
    for(int i = 0; i < estado.size(); i++){
        for(int j = 0; j < estado.size(); j++){
            cout<<estado[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<"\nPrueba con A*"<<endl;
    Astar(estado);
    cout<<"\nPrueba con Greedy"<<endl;
    greedy(estado);
    cout<<"\nPrueba con BFS"<<endl;
    BFS(estado);
    cout<<"\nPrueba con DFS"<<endl;
    DFS(estado);
    return 0;
}