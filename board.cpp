#include "board.hpp"

board::board()
{
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            this->num[i][j]=0;
            this->hide[i][j]=0;
        }
    }
}

void board::modif(int i,int j,int number)
{
    this->num[i][j]=number;
}

void board::afisare()
{
    cout<<"the sudoku board is: "<<endl;
    for (int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            if(hide[i][j]==1)
            {
                cout<<"0 ";
            }
            else{
            cout<<num[i][j]<<" ";
            }
        }
        cout<<endl;
    
    }
}

int board::getNumar(int linie,int coloana)
{
    return this->num[linie][coloana];
}

bool board::getHide(int linie,int coloana)
{
    return this->hide[linie][coloana];
}

//verificam daca numarul ales este valid conform regulilor sudoku
bool board::isValid(int linie,int coloana,int number)
{
    if((linie>8)||(coloana>8)) return false;
    if((number<1)||(number>9)) return false;

    int i,j;

    //pentru linie ; daca exista acelasi numar pe acea linie
    for(j=0;j<9;j++)
    {
        if(this->getNumar(linie,j)==number) return false;
    }

    //pentru coloana ; daca exista acelasi nr pe acea coloana
    for(i=0;i<9;i++)
    {
        if(this->getNumar(i,coloana)==number) return false;
    }

    //pentru chenar 3x3
    int colChenar=coloana/3; //vezi desenul
    int linChenar=linie/3;
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            if(this->getNumar(i+3*linChenar , j+3*colChenar)==number) return false;
        }
    }
    return true;
}

bool board::generare(int linie,int coloana)
{
    if((linie==8)&&(coloana==9))
    {
        return true; //we got to the end of the board
    }
    
    if(coloana==9) //we got to the end of the line
    {
        return this->generare(linie+1,0); //start on a new line
    }

    //generare vector cu valorile de la 1 la 9
    vector<int> numere={1,2,3,4,5,6,7,8,9};

    //initializare random number generator
    random_device rd;
    mt19937 g(rd());

    //shuffle al vectorului
    shuffle(numere.begin(), numere.end(), g);
    
    //backtracking for finding the a number that qualifies
    for(int num : numere)
    {
        if(this->isValid(linie,coloana,num)==true) 
        {
            this->modif(linie,coloana,num);
            if(this->generare(linie,coloana+1)==true)
            {
                return true;
            }
            this->modif(linie,coloana,0); //backtrack reset
            
        }
    }

    return false; //nu s-a gasit niciun numar care sa mearga
}

void board::makeSudoku()
{
    if(this->generare(0,0)==true)
    {
        this->afisare();
    }
    else{
        cout<<"Nu s-a putut genera sudoku.";
    }
}

board::~board()
{

}