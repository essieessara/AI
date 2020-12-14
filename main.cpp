#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <ctime>
using namespace std;
bool provocation = false; // used to display a provocative screen
char input[43]; // There are 42 places to play in the board .. this array represent them
void Board();
int PlayOut = 0;
int EVA = 0;
// EVA and PlayOut are working while NegaMax Function is working .. in NegaMax's way it will definitely make any winning move
// as it goes deep so when this happens PlayOut increases by 1 and EVA increases by 1 if its a winnning move or decreases by 1 if it the opposite
// so we can evaluate neutral moves for MiniMax by dividing EVA / PlayOut * 100 so we get a percentage
int winning();
int GetValue(int t);
int AIManager();
int NegaMax(int Depth);
void clean()
{
    provocation = false;
    for(int i = 0 ; i<= 80 ; i++)
        input[i]=' ';
}

int GetValue(int column) // pass this function a column that you want to play in and it will return its value in input array ..
{
    if(column > 7)
        return 0;
    int n;
    for(int i = 0 ; i<= 6 ; i++)
    {
        if( input[column+7*i] == ' '  )
        {
            n = column+7*i;
            break;
        }
    }
    if ( n > 42 )
        return 0;
    return n;
}

int winning() // Winning algorithm
{
    int temp=0;
    for(int i = 1 ; i<= 42 ; i++)
    {
        if(input[i] != ' ')
        {
            temp++;
            if( i - int((i-1)/7) * 7 <= 4  )
                if( input[i] == input [i+1] && input[i] == input[i+2] && input[i] == input[i+3] )
                    if(input[i] == 'X' )
                        return 1 ;
                    else
                        return 2;
            if( i <= 21 )
                if ( input[i] == input[i+7] && input[i] == input[i+14] && input[i] == input[i+21]  )
                    if(input[i] == 'X' )
                        return 1 ;
                    else
                        return 2;
            if( i - int((i-1)/7) * 7 <= 4 && i<=18  )
                if(input[i] == input[i+8] && input[i] == input[i+16] && input[i]==input[i+24])
                    if(input[i] == 'X' )
                        return 1 ;
                    else
                        return 2;
            if( i - int((i-1)/7) * 7 >= 4 && i <= 21   )
                if(input[i] == input[i+6] && input[i] == input[i+12] && input[i]==input[i+18])
                    if(input[i] == 'X' )
                        return 1 ;
                    else
                        return 2;
        }

    }
    if (temp == 42)
        return 3;
    return 0;
}
void Board() // Draw board
{
    cout<<endl<<"    1   "<<"    2   "<<"    3   "<<"    4   "<<"    5   "<<"    6   "<<"    7   "<<endl;

    int j = 42;
    for(int i = 0 ; i<= 23 ; i++)
    {
        if(i % 4 == 0)
            cout<<string(57,'-');
        else
        {
            if( (i - 2) % 4 == 0)
            {
                j=42-(0.25*i+0.5)*6-((0.25*i+0.5)-1) ;
                for(int i = 0 ; i<=6 ; i++)
                {
                    cout<<"|"<<"   "<<input[j]<<"   ";
                    j++;
                }
                cout<<"|";
            }
            else
            {
                for(int i = 0 ; i<=6 ; i++)
                    cout<<"|"<<string(7,' ');
                cout<<"|";
            }
        }
        cout<<endl;
    }
    cout<<string(57,'-');
    if(provocation == true)
        cout<<endl<<"Hehe I'm sure of my winning :D "<<endl;
}

void PlayPosition(char XO) // Function that asks you to enter where you like to play
{
    int sth;
    cout<<endl<<"where would you like to play"<<endl;
    while(true)
    {
        cin>>sth;
        sth=GetValue(sth);
        if( sth != 0 )
        {
            input[sth] = XO;
            return ;
        }
        else
            cout<<"ERROR"<<endl;
    }
}

int main() // main function
{
    srand(time(0));
    clean();
    while(true)
    {
        input[AIManager()]='O';
        system("cls");
        Board();
        int winningtemp = winning();
        if(winningtemp!=0)
        {
            if(winningtemp == 1)
                cout<<endl<<"Player 2 WON !";
            else if (winningtemp == 2)
                cout<<endl<<"Player 1 WON ! " ;
            else if (winningtemp == 3)
                cout<<"You Tie ! ";
            getch();
            clean();
        }
        else
            PlayPosition('X');
    }
}
int AIManager() // AI Algorithm
{
    float chance[2] = {9999999 , 0 };
    for(int column = 1 ; column <= 7 ; column ++)
    {
        PlayOut = 0;
        EVA=0;
        int PlayNumber = GetValue(column);
        if( PlayNumber != 0 )
        {

            input[PlayNumber] = 'O';
            if(winning()==2)
               {
                   input[PlayNumber]=' ';
                   return PlayNumber ;
               }
            float temp = -(100*NegaMax(1));
            if(PlayOut != 0)
                temp =- ((100*EVA)/PlayOut);
            if(-temp >= 100)
                provocation = true;
            if( chance[0] > temp  )
            {
                chance[0] = temp  ;
                chance[1] = PlayNumber;
            }
             //  cout<<endl<<-temp<<"   "<<EVA << "   " <<PlayOut;
            input[PlayNumber] = ' ';
        }
    }
    return chance[1];
}
int NegaMax(int Depth) // MiniMax algorithm in NegaMax form
{
    char XO;
    int PlayNumber[8] = {0,0,0,0,0,0,0,0}; // The values of the input[] for every column
    int chance=0;
    if(Depth % 2 != 0)
        XO='X';
    else
        XO='O';
    for(int column = 1 ; column <= 7 ; column ++)
        PlayNumber[column]=GetValue(column);
    for(int column = 1 ; column <= 7 ; column++)
    {
        if(PlayNumber[column] != 0)
        {
            input[PlayNumber[column]]=XO;
            if( winning() != 0 )
            {
                PlayOut ++;
                if(XO=='O')
                    EVA ++;
                else
                    EVA --;
                input[PlayNumber[column]]=' ';
                return -1;
            }
            input[PlayNumber[column]]=' ';
        }
    }
    if(Depth <= 6)
    {

        for(int column = 1 ; column <= 7 ; column ++)
        {
            int temp=0;
            if( PlayNumber[column] != 0 )
            {
                input[PlayNumber[column]]=XO;
                if( winning() != 0 )
                {
                    PlayOut++;
                    if(XO=='O')
                        EVA++;
                    else
                        EVA--;
                    input[PlayNumber[column]]=' ';
                    return -1;
                }
                temp = NegaMax(Depth+1);
                if(column == 1)
                    chance = temp;
                if(chance < temp)
                    chance = temp;
                input[PlayNumber[column]]=' ';
            }
        }
    }
    return -chance;

}
