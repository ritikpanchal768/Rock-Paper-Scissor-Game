#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <time.h>
using namespace std;
class player
{
private:
 string user_name;
 int wins;
 int loses;
 int ties;
 int total;
public:
 player()
 {
 srand(time(0));
 cout << "Welcome to the Game, Buddy" << endl;
 // Starting game
 int choose;
 cout << "Are you a new player?? " << endl;
 cout << "Enter 1 for yes 2 for no " << endl;
 cin >> choose;
 if (choose == 1)
 {
 wins = loses = ties = total = 0;
 getdata();
 }
 else
 {
 load_game();
 }
 }
 void getdata()
 {
 cout << "Enter your gaming name here: " << endl;
 // To clear buffer
 cin >> ws;
 getline(cin, user_name);
 cout << "You choose: " << user_name << " as your gaming name" << endl
;
 cout << "Lets begin the game" << endl;
 }
 void lose()
 {
 cout << "Sorry! You lose the game " << endl;
 loses++;
 total++;
 }
 void win()
 {
 cout << "Hurray! You win the game " << endl;
 wins++;
 total++;
 }
 void tie()
 {
 cout << "Ahh!! It's a tie" << endl;
 ties++;
 total++;
 }
 void generate_report()
 {
 cout << "Win Percentage: " << (float)wins / (float)total << endl;
 cout << "Loss Percentage: " << (float)loses / (float)total << endl;
 }
 void save_game()
 {
 ofstream p2("playerdetails.txt");
 p2 << "Total Games: " << total
 << "\nWins: " << wins
 << "\nLoses: " << loses << endl;
 }
 void load_game()
 {
 ifstream p2("playerdetails.txt");
 char ch;
 wins = loses = ties = total = 0;
 p2.seekg(13, ios::cur);
 p2.get(ch);
 while (ch != '\n')
 {
 total = (total * 10) + (ch - '0');
 p2.get(ch);
 }
 p2.seekg(4, ios::cur);
 p2.get(ch);
 while (ch != '\n')
 {
 wins = (wins * 10) + (ch - '0');
 p2.get(ch);
 }
 p2.seekg(6, ios::cur);
 p2.get(ch);
 while (ch != '\n')
 {
 loses = (loses * 10) + (ch - '0');
 p2.get(ch);
 }
 }
};
void determine_winner(player &p, int user_choice, int comp_choice)
{
 // Printing Choices
 string s[3] = {"Rock", "Paper", "Scissors"};
 cout << "Your choice: " << s[user_choice - 1] << endl;
 cout << "Computer choice: " << s[comp_choice - 1] << endl;
 if (user_choice == comp_choice)
 {
 p.tie();
 }
 else if (user_choice == 1)
 {
 if (comp_choice == 3)
 p.win();
 else
 p.lose();
 }
 else if (user_choice == 2)
 {
 if (comp_choice == 1)
 p.win();
 else
 p.lose();
 }
 else
 {
 if (comp_choice == 2)
 p.win();
 else
 p.lose();
 }
}
int take_your_turn()
{
 int choice;
 cout << "Choose your move" << endl;
 cout << "Enter" << endl;
 cout << "1: Rock" << endl;
 cout << "2: Paper" << endl;
 cout << "3: Scissors" << endl;
 cin >> choice;
 try
 {
 if (choice >= 1 && choice <= 3)
 return choice;
 throw(0);
 }
 catch (...)
 {
 cout << "Dear user, You have entered an exception" << endl;
 cout << "Try Again!!" << endl;
 return take_your_turn();
 }
}
int computer_turn()
{
 return rand() % 3 + 1;
}
int re_match()
{
 int choice;
 cout << "Do you want to play again " << endl;
 cout << "Enter: 0 for NO and 1 for YES" << endl;
 cin >> choice;
 try
 {
 if (choice >= 0 && choice <= 1)
 return choice;
 throw(0);
 }
 catch (...)
 {
 cout << "Dear user, You have entered an exception" << endl;
 cout << "Try Again!!" << endl;
 return re_match();
 }
}
int main()
{
 player p;
 while (true)
 {
 // Choosing Values
 int user_choice, comp_choice;
 user_choice = take_your_turn();
 comp_choice = computer_turn();
 // Determining Winner
 determine_winner(p, user_choice, comp_choice);
 // Re-Match
 if (!re_match())
 {
 cout << "Thanks for playing" << endl;
 p.save_game();
 p.generate_report();
 break;
 }
 }
 return 0;
}