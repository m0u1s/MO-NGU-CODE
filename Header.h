#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<queue>

using namespace std;
struct Node
{
	string ID, Name, Set, Type;
	bool Collectible;
	int Mana, Attack, Health, Armor;
	Node* next;
};
struct Card
{
	string ID, Name, Set, Type;
	bool Collectible;
	int Mana, Attack, Health, Armor;
	Card* left, * right;
};
bool compare1(Card* a, Card* b);
bool compare2(Card* a, Card* b);
bool compare3(Card* a, Card* b);
void updateP(Card*& root, Card* a);
//AVL - Insert
int Height(Card* root);
void LeftRotate(Card*& root);
void RightRotate(Card*& root);
void balance(Card*& root);
void Insert1(Card*& root, Card* a);
void Insert2(Card*& root, Card* a);
void Insert3(Card*& root, Card* a);
Card* readToBuildAVL1(string filename);
Card* readToBuildAVL2(string filename);
Card* readToBuildAVL3(string filename);
//Remove
//CompareID
bool compareEqual(Card* a, Card* b);
bool compareID(string ID1, string ID2);
void Remove1(Card*& root, string ID);
void Remove2(Card*& root, Card* a);
void Remove3(Card*& root, Card* a);
void Remove4(Card*& root, Card* a);
void Remove5(Card*& root, Card* a);
void Remove6(Card*& root, Card* a);
//TRAVEL
void LNR(Card* root);
void LevelTravel(Card* root);
void printLevel(Card* root, int level);
void levelOrder(Card* root);
//Patch2 insert
void ReBuild1(string filename, Card*& root);

//Linklist
void updateN(Node* root, Node* a);
bool CompareManaID(Node* a, Node* b);
Node* readToBuildLink1(string name);
void PrintLink(Node* root);
Node* readToBuildLink2(string filename);
Node* readToBuildLink3(string filename);
//rebuild
void reBuildL1(string filename, Node*& root);
void reBuildL2(string filename, Node*& root);
void reBuildL3(string filename, Node*& root);
//InsertLink
void insertL1(Node*& root, Node* a);
void insertL2(Node*& root, Node* a);
void insertL3(Node*& root, Node* a);
void AVL1();
void AVL2();
void AVL3();
void LL1();
void LL2();
void LL3();
void AVLChoice(Card*& root, int& check);
void LinkListChoice(Node*& a,int& check);
void search(Card* root, string ID, Card*& a);