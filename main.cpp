#include"Header.h"
int main()
{
	string filename;
	Card* root;
	Node* a;
	cout << "0. END\n";
	cout << "1. AVL - ID\n";
	cout << "2. AVL - Mana - Heal - ID\n";
	cout << "3. AVL - Atk + Heal - Mana - ID\n";
	cout << "4. LinkList - Order in file\n";
	cout << "5. LinkList - Mana - ID\n";
	cout << "6. LinkList - Set - Mana - ID\n";
	cout << "YOUR CHOICE: ";
	int n;
	cin >> n;
	switch (n)
	{
		case 1:
			AVL1();
			break;
		case 2:
			AVL2();
			break;
		case 3:
			AVL3();
			break;
		case 4: 
			LL1();
			break;
		case 5:
			LL2();
			break;
		case 6:
			LL3();
			break;
		default:
			break;
	}
	return 0;
}