#include"Header.h"

//Compare
bool compare1(Card* a, Card* b)
{	
	//true: a bé hơn --- false: b bé hơn
	int n = min(a->ID.size(), b->ID.size());
	for (int i = 0; i < n; i++)
	{
		if (int(a->ID[i]) < int(b->ID[i]))
			return true;
		else if (int(a->ID[i]) > int(b->ID[i]))
			return false;
	}
	if (a->ID.size() == n) return true;
	else return false; 
}
bool compare2(Card* a, Card* b)
{
	//true: a bé hơn --- false: b bé hơn
	if (a->Mana < b->Mana) return true;
	else if (a->Mana > b->Mana) return false;
	else
	{
		if (a->Health < b->Health) return true;
		else if (a->Health > b->Health) return false;
		else return compare1(a, b);
	}
}
bool compare3(Card* a, Card* b)
{
	//true: a bé hơn --- false: b bé hơn
	if (a->Attack + a->Health < b->Attack + b->Health) return true;
	else if (a->Attack + a->Health > b->Attack + b->Health) return false; 
	else
	{
		if (a->Mana < b->Mana) return true;
		else if (a->Mana > b->Mana) return false;
		else return compare1(a, b);
	}
}
void updateP(Card*& root, Card* a)
{
	root->ID = a->ID; 
	root->Name = a->Name; 
	root->Set = a->Set;
	root->Type = a->Type;
	root->Collectible = a->Collectible;
	root->Mana = a->Mana;
	root->Attack = a->Attack;
	root->Health = a->Health;
	root->Armor = a->Armor;
}
//AVL - Insert
int Height(Card* root)
{
	if (root == NULL) return 0; 
	else
	{
		int l = Height(root->left);
		int r = Height(root->right);
		if (l > r) return 1 + l;
		else return 1 + r; 
	}
}
void LeftRotate(Card*& root) {
	Card* p = root->right;
	root->right = p->left;
	p->left = root;
	root = p;
}
void RightRotate(Card*& root) {
	Card* p = root->left;
	root->left = p->right;
	p->right = root;
	root = p;
}
void balance(Card*& root) 
{
	int bal = Height(root->left) - Height(root->right);
	if (bal > 1) 
	{ 
		// Cây lệch trái
		if (Height(root->left->left) >= Height(root->left->right)) //Cây lệch trái trái
			RightRotate(root);
		if (Height(root->left->left) < Height(root->left->right)) 
		{ 
			//Cây lệch trái phải
			LeftRotate(root->left);
			RightRotate(root);
		}
	}
	if (bal < -1) 
	{
		//Cây lệch phải
		if (Height(root->right->right) >= Height(root->right->left)) //Cây lệch phải phải
			LeftRotate(root);
		if (Height(root->right->right) < Height(root->right->left)) 
		{ 
			//Cây lệch phải trái
			RightRotate(root->right);
			LeftRotate(root);
		}
	}
}
void Insert1(Card*&root, Card* a)
{
	if (root == NULL)
		root = a;
	else if (root->ID == a->ID)
		updateP(root, a);
	else if (compare1(root, a))
		Insert1(root->right, a);
	else if (!compare1(root, a))
		Insert1(root->left, a);
	balance(root);
}
void Insert2(Card*& root, Card* a)
{
	if (root == NULL)
		root = a;
	else if (root->Mana == a->Mana && root->ID == a->ID)
		updateP(root, a);
	else if (compare2(root, a))
		Insert2(root->right, a);
	else if (!compare2(root, a))
		Insert2(root->left, a);
	balance(root);
}
void Insert3(Card*& root, Card* a)
{
	if (root == NULL)
		root = a;
	else if (root->Attack + root->Health == a->Attack + a->Health && root->Mana == a->Mana && root->ID == a->ID)
		updateP(root, a);
	else if (compare3(root, a))
		Insert3(root->right, a);
	else if (!compare3(root, a))
		Insert3(root->left, a);
	balance(root);
}
Card* readToBuildAVL1(string filename)
{
	Card* root = NULL; 
	fstream input;
	input.open(filename, ios::in);
	string s; 
	getline(input, s);
	while (!input.eof())
	{
		Card* a = new Card; 
		getline(input, a->ID, ';');
		getline(input, a->Name, ';');
		getline(input, a->Set, ';');
		getline(input, a->Type, ';');
		getline(input, s, ';');
		a->Collectible = (s == "False")? 0 : 1;
		getline(input, s, ';');
		a->Mana = stoi(s);
		getline(input, s, ';');
		a->Attack = stoi(s);
		getline(input, s, ';');
		a->Health = stoi(s);
		getline(input, s);
		a->Armor = stoi(s);
		a->left = NULL; 
		a->right = NULL;
		Insert1(root, a);
	}
	input.close();
	return root; 
}
Card* readToBuildAVL2(string filename)
{
	Card* root = NULL;
	fstream input;
	input.open(filename, ios::in);
	string s;
	getline(input, s);
	while (!input.eof())
	{
		Card* a = new Card;
		getline(input, a->ID, ';');
		getline(input, a->Name, ';');
		getline(input, a->Set, ';');
		getline(input, a->Type, ';');
		getline(input, s, ';');
		a->Collectible = (s == "FALSE") ? 0 : 1;
		getline(input, s, ';');
		a->Mana = stoi(s);
		getline(input, s, ';');
		a->Attack = stoi(s);
		getline(input, s, ';');
		a->Health = stoi(s);
		getline(input, s);
		a->Armor = stoi(s);
		a->left = NULL;
		a->right = NULL;
		Insert2(root, a);
	}
	input.close();
	return root;
}
Card* readToBuildAVL3(string filename)
{
	Card* root = NULL;
	fstream input;
	input.open(filename, ios::in);
	string s;
	getline(input, s);
	while (!input.eof())
	{
		Card* a = new Card;
		getline(input, a->ID, ';');
		getline(input, a->Name, ';');
		getline(input, a->Set, ';');
		getline(input, a->Type, ';');
		getline(input, s, ';');
		a->Collectible = (s == "FALSE") ? 0 : 1;
		getline(input, s, ';');
		a->Mana = stoi(s);
		getline(input, s, ';');
		a->Attack = stoi(s);
		getline(input, s, ';');
		a->Health = stoi(s);
		getline(input, s);
		a->Armor = stoi(s);
		a->left = NULL;
		a->right = NULL;
		Insert3(root, a);
	}
	input.close();
	return root;
}
//Remove
//CompareID
bool compareEqual(Card* a, Card* b)
{
	if (a->Armor == b->Armor
		&& a->Attack == b->Attack
		&& a->Collectible == b->Collectible
		&& a->Health == b->Health
		&& a->ID == b->ID
		&& a->Mana == b->Mana
		&& a->Set == b->Set
		&& a->Name == b->Name
		&& a->Type == b->Type
	) return true;
	else return false; 
}
bool compareID(string ID1, string ID2)
{
	int n = min(ID1.size(), ID2.size());
	for (int i = 0; i < n; i++)
	{
		if (int(ID1[i]) < int(ID2[i]))
			return true;
		else if (int(ID1[i]) > int(ID2[i]))
			return false;
	}
	if (ID1.size() == n) return true;
	else return false;
}
void Remove1(Card*& root, string ID)
{
	if (root == NULL) return;
	else if (root->ID == ID)
	{
		if (root->left == NULL && root->right == NULL)
		{
			delete root; 
			root = NULL;
		}
		else if (root->left != NULL && root->right == NULL)
		{
			Card* p = root;
			root = root->left;
			delete p;
		}
		else if (root->left == NULL && root->right != NULL)
		{
			Card* p = root; 
			root = root->right; 
			delete p;
		}
		else
		{
			Card* p = root->right;
			while (p->left != NULL)
			{
				p = p->left;
			}
			updateP(root, p);
			Remove1(root->right, p->ID);
		}
	}
	else if (compareID(root->ID, ID))
		Remove1(root->right, ID);
	else if (!compareID(root->ID, ID))
		Remove1(root->left, ID);
	if (root == NULL)
		return; 
	balance(root);
}
void Remove2(Card*& root, Card* a)
{
	if (root == NULL) return;
	else if (root->ID == a->ID)
	{
		if (root->left == NULL && root->right == NULL)
		{
			delete root;
			root = NULL;
		}
		else if (root->left != NULL && root->right == NULL)
		{
			Card* p = root;
			root = root->left;
			delete p;
		}
		else if (root->left == NULL && root->right != NULL)
		{
			Card* p = root;
			root = root->right;
			delete p;
		}
		else
		{
			Card* p = root->right;
			while (p->left != NULL)
			{
				p = p->left;
			}
			updateP(root, p);
			Remove2(root->right, p);
		}
	}
	else if (compare2(root, a))
		Remove2(root->right, a);
	else if (!compare2(root, a))
		Remove2(root->left, a);
	if (root == NULL)
		return;
	balance(root);
}
void Remove3(Card*& root, Card* a)
{
	if (root == NULL) return;
	else if (root->ID == a->ID)
	{
		if (root->left == NULL && root->right == NULL)
		{
			delete root;
			root = NULL;
		}
		else if (root->left != NULL && root->right == NULL)
		{
			Card* p = root;
			root = root->left;
			delete p;
		}
		else if (root->left == NULL && root->right != NULL)
		{
			Card* p = root;
			root = root->right;
			delete p;
		}
		else
		{
			Card* p = root->right;
			while (p->left != NULL)
			{
				p = p->left;
			}
			updateP(root, p);
			Remove3(root->right, p);
		}
	}
	else if (compare3(root, a))
		Remove3(root->right, a);
	else if (!compare3(root, a))
		Remove3(root->left, a);
	if (root == NULL)
		return;
	balance(root);
}
//Remove when same properties 
void Remove4(Card*& root, Card* a)
{
	if (root == NULL) return;
	else if (root->ID == a->ID)
	{
		if (!compareEqual(root, a)) return;
		if (root->left == NULL && root->right == NULL)
		{
			delete root;
			root = NULL;
		}
		else if (root->left != NULL && root->right == NULL)
		{
			Card* p = root;
			root = root->left;
			delete p;
		}
		else if (root->left == NULL && root->right != NULL)
		{
			Card* p = root;
			root = root->right;
			delete p;
		}
		else
		{
			Card* p = root->right;
			while (p->left != NULL)
			{
				p = p->left;
			}
			updateP(root, p);
			Remove4(root->right, p);
		}
	}
	else if (compareID(root->ID, a->ID))
		Remove4(root->right, a);
	else if (!compareID(root->ID, a->ID))
		Remove4(root->left, a);
	if (root == NULL)
		return;
	balance(root);
}
void Remove5(Card*& root, Card* a)
{
	if (root == NULL) return;
	else if (root->ID == a->ID)
	{
		if (!compareEqual(root, a)) return;
		if (root->left == NULL && root->right == NULL)
		{
			delete root;
			root = NULL;
		}
		else if (root->left != NULL && root->right == NULL)
		{
			Card* p = root;
			root = root->left;
			delete p;
		}
		else if (root->left == NULL && root->right != NULL)
		{
			Card* p = root;
			root = root->right;
			delete p;
		}
		else
		{
			Card* p = root->right;
			while (p->left != NULL)
			{
				p = p->left;
			}
			updateP(root, p);
			Remove5(root->right, p);
		}
	}
	else if (compare2(root, a))
		Remove5(root->right, a);
	else if (!compare2(root, a))
		Remove5(root->left, a);
	if (root == NULL)
		return;
	balance(root);
}
void Remove6(Card*& root, Card* a)
{
	if (root == NULL) return;
	else if (root->ID == a->ID)
	{
		if (!compareEqual(root, a)) return;
		if (root->left == NULL && root->right == NULL)
		{
			delete root;
			root = NULL;
		}
		else if (root->left != NULL && root->right == NULL)
		{
			Card* p = root;
			root = root->left;
			delete p;
		}
		else if (root->left == NULL && root->right != NULL)
		{
			Card* p = root;
			root = root->right;
			delete p;
		}
		else
		{
			Card* p = root->right;
			while (p->left != NULL)
			{
				p = p->left;
			}
			updateP(root, p);
			Remove6(root->right, p);
		}
	}
	else if (compare3(root, a))
		Remove3(root->right, a);
	else if (!compare3(root, a))
		Remove6(root->left, a);
	if (root == NULL)
		return;
	balance(root);
}
//TRAVEL
void LNR(Card* root)
{
	if (root)
	{
		LNR(root->left);
		cout << root->ID << ";" << root->Name << ";" << root->Set << ";" << root->Type << ";";
		cout << root->Mana << ";" << root->Attack << ";" << root->Health << ";" << root->Armor << "\n";
		LNR(root->right);
	}
}
void LevelTravel(Card* root)
{
	queue<Card*> q; 
	q.push(root);
	Card* item;
	while (!q.empty())
	{
		item = q.front();
		cout << item->ID << " ";
		if(item->left != NULL) q.push(item->left);
		if (item->right != NULL) q.push(item->right);	
		q.pop();
	}
}
void printLevel(Card* root, int level)
{
	if (root == NULL) return;
	if (level == 1)
	{
		cout << root->ID << ";" << root->Name << ";" << root->Set << ";" << root->Type << ";";
		cout << root->Mana << ";" << root->Attack << ";" << root->Health << ";" << root->Armor << "\n";
	}
	else if (level > 1)
	{
		printLevel(root->left, level - 1);
		printLevel(root->right, level - 1);
	}
}
void levelOrder(Card* root)
{
	int h = Height(root);
	for (int i = 1; i <= h; i++)
	{
		printLevel(root, i);
		cout << "\n";
	}
}
//Patch2 insert
void ReBuild1(string filename,Card*& root)
{
	fstream input;
	input.open(filename, ios::in);
	string s, temp;
	getline(input, s);
	while (!input.eof())
	{
		Card* a = new Card;
		getline(input, a->ID, ';');
		s = a->ID;
		temp = s.substr(0, 6);
		if (temp == "remove")
			break;
		getline(input, a->Name, ';');
		getline(input, a->Set, ';');
		getline(input, a->Type, ';');
		getline(input, s, ';');
		a->Collectible = (s == "False") ? 0 : 1;
		getline(input, s, ';');
		a->Mana = stoi(s);
		getline(input, s, ';');
		a->Attack = stoi(s);
		getline(input, s, ';');
		a->Health = stoi(s);
		getline(input, s);
		a->Armor = stoi(s);
		a->left = NULL;
		a->right = NULL;
		Remove1(root, a->ID);
		Insert1(root, a);
	}
	int i = 0;
	while (!input.eof())
	{
		Card* a = new Card;
		if(i != 0) getline(input, a->ID, ';');
		else
		{
			a->ID = s.substr(7);
			i++;
		}
		getline(input, a->Name, ';');
		getline(input, a->Set, ';');
		getline(input, a->Type, ';');
		getline(input, s, ';');
		a->Collectible = (s == "False") ? 0 : 1;
		getline(input, s, ';');
		a->Mana = stoi(s);
		getline(input, s, ';');
		a->Attack = stoi(s);
		getline(input, s, ';');
		a->Health = stoi(s);
		getline(input, s);
		a->Armor = stoi(s);
		a->left = NULL;
		a->right = NULL;
		Remove4(root, a);
	}
}
void Rebuild2(string filename, Card*& root)
{
	fstream input;
	input.open(filename, ios::in);
	string s, temp;
	getline(input, s);
	while (!input.eof())
	{
		Card* a = new Card;
		getline(input, a->ID, ';');
		s = a->ID;
		temp = s.substr(0, 6);
		if (temp == "remove")
			break;
		getline(input, a->Name, ';');
		getline(input, a->Set, ';');
		getline(input, a->Type, ';');
		getline(input, s, ';');
		a->Collectible = (s == "False") ? 0 : 1;
		getline(input, s, ';');
		a->Mana = stoi(s);
		getline(input, s, ';');
		a->Attack = stoi(s);
		getline(input, s, ';');
		a->Health = stoi(s);
		getline(input, s);
		a->Armor = stoi(s);
		a->left = NULL;
		a->right = NULL;
		Card* temp = NULL;
		search(root, a->ID, temp);
		if(temp!= NULL) Remove2(root, temp);
		Insert2(root, a);
	}
	int i = 0;
	while (!input.eof())
	{
		Card* a = new Card;
		if (i != 0) getline(input, a->ID, ';');
		else
		{
			a->ID = s.substr(7);
			i++;
		}
		getline(input, a->Name, ';');
		getline(input, a->Set, ';');
		getline(input, a->Type, ';');
		getline(input, s, ';');
		a->Collectible = (s == "False") ? 0 : 1;
		getline(input, s, ';');
		a->Mana = stoi(s);
		getline(input, s, ';');
		a->Attack = stoi(s);
		getline(input, s, ';');
		a->Health = stoi(s);
		getline(input, s);
		a->Armor = stoi(s);
		a->left = NULL;
		a->right = NULL;
		Remove5(root, a);
	}
}
void Rebuild3(string filename, Card*& root)
{
	fstream input;
	input.open(filename, ios::in);
	string s, temp;
	getline(input, s);
	while (!input.eof())
	{
		Card* a = new Card;
		getline(input, a->ID, ';');
		s = a->ID;
		temp = s.substr(0, 6);
		if (temp == "remove")
			break;
		getline(input, a->Name, ';');
		getline(input, a->Set, ';');
		getline(input, a->Type, ';');
		getline(input, s, ';');
		a->Collectible = (s == "False") ? 0 : 1;
		getline(input, s, ';');
		a->Mana = stoi(s);
		getline(input, s, ';');
		a->Attack = stoi(s);
		getline(input, s, ';');
		a->Health = stoi(s);
		getline(input, s);
		a->Armor = stoi(s);
		a->left = NULL;
		a->right = NULL;
		Card* temp = NULL;
		search(root, a->ID, temp);
		if(temp != NULL) Remove3(root, temp);
		Insert3(root, a);
	}
	int i = 0;
	while (!input.eof())
	{
		Card* a = new Card;
		if (i != 0) getline(input, a->ID, ';');
		else
		{
			a->ID = s.substr(7);
			i++;
		}
		getline(input, a->Name, ';');
		getline(input, a->Set, ';');
		getline(input, a->Type, ';');
		getline(input, s, ';');
		a->Collectible = (s == "False") ? 0 : 1;
		getline(input, s, ';');
		a->Mana = stoi(s);
		getline(input, s, ';');
		a->Attack = stoi(s);
		getline(input, s, ';');
		a->Health = stoi(s);
		getline(input, s);
		a->Armor = stoi(s);
		a->left = NULL;
		a->right = NULL;
		Remove6(root, a);
	}
}
//Linklist
void PrintLink(Node* root)
{
	Node* cur = root; 
	while (cur != NULL)
	{
		cout << cur->ID << ";" << cur->Name << ";" << cur->Set << ";" << cur->Type << ";";
		cout << cur->Mana << ";" << cur->Attack << ";" << cur->Health << ";" << cur->Armor << "\n";
		cur = cur->next;
	}
}
Node* readToBuildLink1(string filename)
{
	Node* root = NULL;
	Node* cur = root;
	fstream input;
	input.open(filename, ios::in);
	string s;
	getline(input, s);
	while (!input.eof())
	{
		Node* a = new Node;
		getline(input, a->ID, ';');
		getline(input, a->Name, ';');
		getline(input, a->Set, ';');
		getline(input, a->Type, ';');
		getline(input, s, ';');
		a->Collectible = (s == "False") ? 0 : 1;
		getline(input, s, ';');
		a->Mana = stoi(s);
		getline(input, s, ';');
		a->Attack = stoi(s);
		getline(input, s, ';');
		a->Health = stoi(s);
		getline(input, s);
		a->Armor = stoi(s);
		a->next = NULL;
		if (root == NULL)
		{
			root = a;
			cur = root;     
		}
		else
		{
			cur->next = a;
			cur = cur->next;
		}
	}
	input.close();
	return root;
}
Node* readToBuildLink2(string filename)
{
	Node* root = NULL;
	Node* cur = root;
	fstream input;
	input.open(filename, ios::in);
	string s;
	getline(input, s);
	while (!input.eof())
	{
		Node* a = new Node;
		getline(input, a->ID, ';');
		getline(input, a->Name, ';');
		getline(input, a->Set, ';');
		getline(input, a->Type, ';');
		getline(input, s, ';');
		a->Collectible = (s == "False") ? 0 : 1;
		getline(input, s, ';');
		a->Mana = stoi(s);
		getline(input, s, ';');
		a->Attack = stoi(s);
		getline(input, s, ';');
		a->Health = stoi(s);
		getline(input, s);
		a->Armor = stoi(s);
		a->next = NULL;
		if (root == NULL)
		{
			root = a;
			cur = root;
		}
		else
		{
			cur = root; 
			if (a->Mana < root->Mana)
			{
				a->next = root;
				root = a;
			}
			else if (a->Mana == root->Mana)
			{
				if (compareID(root->ID, a->ID))
				{
					if(root->next == NULL)
						root->next = a;
					else
					{
						Node* p = root->next->next;
						root->next = a;
						a->next = p;
					}
				}
				else
				{
					a->next = root;
					root = a;
					continue;
				}
			}
			else 
			{
				Node* prev = cur;
				int check = 1; 
				while (cur->next != NULL)
				{
					cur = cur->next;
					if (cur->Mana > a->Mana)
					{
						a->next = cur;
						prev->next = a;
						check = 0;
						break;
					}
					else if (cur->Mana == a->Mana)
					{
						if (compareID(cur->ID, a->ID))
						{
							if (cur->next == NULL)
								cur->next = a;
							else
							{
								Node* p = cur->next;
								cur->next = a;
								a->next = p;
							}
						}
						else
						{
							a->next = cur;
							prev->next = a;
						}
						check = 0;
						break;
					}
					prev = cur;
				}
				if(check) prev->next = a; 
			}
		}
	}
	input.close();
	return root;
}
Node* readToBuildLink3(string filename)
{
	Node* root = NULL;
	Node* cur = root;
	Node* prev = cur; 
	fstream input;
	input.open(filename, ios::in);
	string s;
	getline(input, s);
	while (!input.eof())
	{
		Node* a = new Node;
		getline(input, a->ID, ';');
		getline(input, a->Name, ';');
		getline(input, a->Set, ';');
		getline(input, a->Type, ';');
		getline(input, s, ';');
		a->Collectible = (s == "False") ? 0 : 1;
		getline(input, s, ';');
		a->Mana = stoi(s);
		getline(input, s, ';');
		a->Attack = stoi(s);
		getline(input, s, ';');
		a->Health = stoi(s);
		getline(input, s);
		a->Armor = stoi(s);
		a->next = NULL;
		if (root == NULL)
		{
			root = a;
			cur = root;
			prev = cur;
		}
		else
		{
			while (cur->Set != a->Set && cur->next != NULL)
			{
				prev = cur; 
				cur = cur->next;
			}
			if (cur->Set != a->Set && cur->next == NULL)
			{
				cur->next = a;
				prev = a;
			}
			else
			{
				while (cur->Set == a->Set && CompareManaID(cur, a) && cur->next != NULL)
				{
					prev = cur;
					cur = cur->next;
				}
				if (CompareManaID(cur, a) && cur->next == NULL)
				{
					cur->next = a;
					prev = a;
				}
				else
				{
					a->next = cur; 
					prev->next = a;
					prev = cur;
				}
			}
			cur = root;
		}
	}
	input.close();
	return root;
}
bool CompareManaID(Node* a, Node* b)
{
	if (a->Mana < b->Mana)return true;
	else if (a->Mana > b->Mana) return false;
	else return compareID(a->ID, b->ID);
}
void updateN(Node* root, Node* a)
{
	root->ID = a->ID;
	root->Name = a->Name;
	root->Set = a->Set;
	root->Type = a->Type;
	root->Collectible = a->Collectible;
	root->Mana = a->Mana;
	root->Attack = a->Attack;
	root->Health = a->Health;
	root->Armor = a->Armor;
}
//InsertLink
void insertL1(Node*& root, Node* a)
{
	Node* cur = root;
	while (cur->next != NULL)
	{
		if (cur->ID == a->ID)
		{
			updateN(cur, a);
			return;
		}
		cur = cur->next;
	}
	cur->next = a; 
}
void insertL2(Node*& root, Node* a)
{
	Node* cur;
	cur = root;
	if (a->Mana < root->Mana)
	{
		a->next = root;
		root = a;
	}
	else if (a->Mana == root->Mana)
	{
		if (compareID(root->ID, a->ID))
		{
			if (root->next == NULL)
				root->next = a;
			else
			{
				Node* p = root->next->next;
				root->next = a;
				a->next = p;
			}
		}
		else
		{
			a->next = root;
			root = a;
		}
	}
	else
	{
		Node* prev = cur;
		int check = 1;
		while (cur->next != NULL)
		{
			cur = cur->next;
			if (cur->Mana > a->Mana)
			{
				a->next = cur;
				prev->next = a;
				check = 0;
				break;
			}
			else if (cur->Mana == a->Mana)
			{
				if (compareID(cur->ID, a->ID))
				{
					if (cur->next == NULL)
						cur->next = a;
					else
					{
						Node* p = cur->next;
						cur->next = a;
						a->next = p;
					}
				}
				else
				{
					a->next = cur;
					prev->next = a;
				}
				check = 0;
				break;
			}
			prev = cur;
		}
		if (check) prev->next = a;
	}
}
void insertL3(Node*& root, Node* a)
{
	Node* cur = root;
	Node* prev = cur;
	while (cur->Set != a->Set && cur->next != NULL)
	{
		prev = cur;
		cur = cur->next;
	}
	if (cur->Set != a->Set && cur->next == NULL)
	{
		cur->next = a;
		prev = a;
	}
	else
	{
		while (cur->Set == a->Set && CompareManaID(cur, a) && cur->next != NULL)
		{
			prev = cur;
			cur = cur->next;
		}
		if (CompareManaID(cur, a) && cur->next == NULL)
		{
			cur->next = a;
			prev = a;
		}
		else
		{
			a->next = cur;
			prev->next = a;
			prev = cur;
		}
	}
	cur = root;
}
void Delete(Node*& root, Node* a)
{
	Node* cur = root; 
	Node* rev,* prev;
	if (a->ID == root->ID)
	{
		rev = root; 
		root = root->next;
		delete rev;
		rev = NULL;
	}
	else
	{
		prev = cur;
		cur = cur->next;
		while (cur != NULL)
		{
			if (cur->ID == a->ID)
			{
				rev = cur;
				prev->next = cur->next;
				delete rev; 
				return;
			}
			prev = cur;
			cur = cur->next;
		}
	}
}
//Rebuild
void reBuildL1(string filename, Node*& root)
{
	fstream input;
	input.open(filename, ios::in);
	string s, temp;
	getline(input, s);
	while (!input.eof())
	{
		Node* a = new Node;
		getline(input, a->ID, ';');
		s = a->ID;
		temp = s.substr(0, 6);
		if (temp == "remove")
			break;
		getline(input, a->Name, ';');
		getline(input, a->Set, ';');
		getline(input, a->Type, ';');
		getline(input, s, ';');
		a->Collectible = (s == "False") ? 0 : 1;
		getline(input, s, ';');
		a->Mana = stoi(s);
		getline(input, s, ';');
		a->Attack = stoi(s);
		getline(input, s, ';');
		a->Health = stoi(s);
		getline(input, s);
		a->Armor = stoi(s);
		a->next = NULL;
		Delete(root, a);
		insertL1(root, a);
	}
	int i = 0;
	while (!input.eof())
	{
		Node* a = new Node;
		if (i != 0) getline(input, a->ID, ';');
		else
		{
			a->ID = s.substr(7);
			i++;
		}
		getline(input, a->Name, ';');
		getline(input, a->Set, ';');
		getline(input, a->Type, ';');
		getline(input, s, ';');
		a->Collectible = (s == "False") ? 0 : 1;
		getline(input, s, ';');
		a->Mana = stoi(s);
		getline(input, s, ';');
		a->Attack = stoi(s);
		getline(input, s, ';');
		a->Health = stoi(s);
		getline(input, s);
		a->Armor = stoi(s);
		a->next = NULL;
		Delete(root, a);
	}
	input.close();
}
void reBuildL2(string filename, Node*& root)
{
	fstream input;
	input.open(filename, ios::in);
	string s, temp;
	getline(input, s);
	while (!input.eof())
	{
		Node* a = new Node;
		getline(input, a->ID, ';');
		s = a->ID;
		temp = s.substr(0, 6);
		if (temp == "remove")
			break;
		getline(input, a->Name, ';');
		getline(input, a->Set, ';');
		getline(input, a->Type, ';');
		getline(input, s, ';');
		a->Collectible = (s == "False") ? 0 : 1;
		getline(input, s, ';');
		a->Mana = stoi(s);
		getline(input, s, ';');
		a->Attack = stoi(s);
		getline(input, s, ';');
		a->Health = stoi(s);
		getline(input, s);
		a->Armor = stoi(s);
		a->next = NULL;
		Delete(root, a);
		insertL2(root, a);
	}
	int i = 0;
	while (!input.eof())
	{
		Node* a = new Node;
		if (i != 0) getline(input, a->ID, ';');
		else
		{
			a->ID = s.substr(7);
			i++;
		}
		getline(input, a->Name, ';');
		getline(input, a->Set, ';');
		getline(input, a->Type, ';');
		getline(input, s, ';');
		a->Collectible = (s == "False") ? 0 : 1;
		getline(input, s, ';');
		a->Mana = stoi(s);
		getline(input, s, ';');
		a->Attack = stoi(s);
		getline(input, s, ';');
		a->Health = stoi(s);
		getline(input, s);
		a->Armor = stoi(s);
		a->next = NULL;
		Delete(root, a);
	}
	input.close();
}
void reBuildL3(string filename, Node*& root)
{
	fstream input;
	input.open(filename, ios::in);
	string s, temp;
	getline(input, s);
	while (!input.eof())
	{
		Node* a = new Node;
		getline(input, a->ID, ';');
		s = a->ID;
		temp = s.substr(0, 6);
		if (temp == "remove")
			break;
		getline(input, a->Name, ';');
		getline(input, a->Set, ';');
		getline(input, a->Type, ';');
		getline(input, s, ';');
		a->Collectible = (s == "False") ? 0 : 1;
		getline(input, s, ';');
		a->Mana = stoi(s);
		getline(input, s, ';');
		a->Attack = stoi(s);
		getline(input, s, ';');
		a->Health = stoi(s);
		getline(input, s);
		a->Armor = stoi(s);
		a->next = NULL;
		Delete(root, a);
		insertL3(root, a);
	}
	int i = 0;
	while (!input.eof())
	{
		Node* a = new Node;
		if (i != 0) getline(input, a->ID, ';');
		else
		{
			a->ID = s.substr(7);
			i++;
		}
		getline(input, a->Name, ';');
		getline(input, a->Set, ';');
		getline(input, a->Type, ';');
		getline(input, s, ';');
		a->Collectible = (s == "False") ? 0 : 1;
		getline(input, s, ';');
		a->Mana = stoi(s);
		getline(input, s, ';');
		a->Attack = stoi(s);
		getline(input, s, ';');
		a->Health = stoi(s);
		getline(input, s);
		a->Armor = stoi(s);
		a->next = NULL;
		Delete(root, a);
	}
	input.close();
}
//Menu
void AVL1()
{
	string filename;
	Card* root;
	int check = 1;
	cout << "YOU HAVE CHOOSE AVL - ID\n";
	cout << "Input file name --- Example: patch1.txt\n";
	cout << "Input: ";
	cin >> filename;
	root = readToBuildAVL1(filename);
	AVLChoice(root,check);
	while (check != 0)
	{
		cout << "YOUR CHOICE:\n";
		AVLChoice(root, check);
	}
}
void AVL2()
{
	string filename;
	Card* root;
	int check = 2;
	cout << "YOU HAVE CHOOSE AVL - Mana->Health->ID\n";
	cout << "Input file name --- Example: patch1.txt\n";
	cout << "Input: ";
	cin >> filename;
	root = readToBuildAVL2(filename);
	while (check != 0)
	{
		cout << "YOUR CHOICE:\n";
		AVLChoice(root, check);
	}
}
void AVL3()
{
	string filename;
	Card* root;
	int check = 3;
	cout << "YOU HAVE CHOOSE AVL - Atk + Heath->Mana->ID\n";
	cout << "Input file name --- Example: patch1.txt\n";
	cout << "Input: ";
	cin >> filename;
	root = readToBuildAVL3(filename);
	AVLChoice(root, check);
	while (check != 0)
	{
		cout << "YOUR CHOICE:\n";
		AVLChoice(root, check);
	}
}
void LL1()
{
	int check = 1; 
	string filename;
	Node* a;
	cout << "YOU HAVE CHOOSE Linked List - Order in file\n";
	cout << "Input file name --- Example: patch1.txt\n";
	cout << "Input: ";
	cin >> filename;
	a = readToBuildLink1(filename);
	while (check != 0)
	{
		cout << "YOUR CHOICE:\n";
		LinkListChoice(a, check);
	}
}
void LL2()
{
	int check = 2; 
	string filename;
	Node* a;
	cout << "YOU HAVE CHOOSE Linked List - Mana -> ID\n";
	cout << "Input file name --- Example: patch1.txt\n";
	cout << "Input: ";
	cin >> filename;
	a = readToBuildLink2(filename);
	while (check != 0)
	{
		cout << "YOUR CHOICE:\n";
		LinkListChoice(a, check);
	}
}
void LL3()
{
	int check = 3;
	string filename;
	Node* a;
	cout << "YOU HAVE CHOOSE Linked List - Set->Mana->ID\n";
	cout << "Input file name --- Example: patch1.txt\n";
	cout << "Input: ";
	cin >> filename;
	a = readToBuildLink3(filename);
	while (check != 0)
	{
		cout << "YOUR CHOICE:\n";
		LinkListChoice(a, check);
	}
}
void AVLChoice(Card*& root, int& check)
{
	cout << "0. END\n";
	cout << "1. Inorder Traverse\n";
	cout << "2. Level Traverse\n";
	cout << "3. Update\n";
	int n;
	cin >> n;
	if (n == 1)
		LNR(root);
	else if (n == 2)
		levelOrder(root);
	else if (n == 3)
	{
		string filename;
		cout << "Input file name --- Example: patch1.txt\n";
		cin >> filename;
		if (check == 1)
			ReBuild1(filename, root);
		else if (check == 2)
			Rebuild2(filename, root);
		else
			Rebuild3(filename, root);
	}
	else
	{
		check = 0; 
		return;
	}
}
void LinkListChoice(Node*& a, int& check)
{
	cout << "0. END\n";
	cout << "1. Show List\n";
	cout << "2. Update\n";
	int n; 
	cin >> n;
	if (n == 1)
		PrintLink(a);
	else if(n == 2)
	{
		string filename;
		cout << "Input file name --- Example: patch1.txt\n";
		cin >> filename;
		if (check == 1)
			reBuildL1(filename, a);
		else if (check == 2)
			reBuildL2(filename, a);
		else
			reBuildL3(filename, a);
	}
	else
	{
		check = 0; 
		return;
	}
}
void search(Card* root, string ID, Card*& a)
{
	//Em dùng BFS để tìm kiếm do dữ liệu đầu vào của em nhập không thể so sánh đường đi
	if (root == NULL) return;
	queue<Card*> bf_queue;
	bf_queue.push(root);
	/* Vòng lặp kết thúc khi queue rỗng */
	while (!bf_queue.empty()) {
		Card* current = bf_queue.front();
		bf_queue.pop(); /* Lấy phần tử đầu tiên ra khỏi queue */
		if (current->ID == ID)
		{
			a = current;
			break;
		}
		/* Enqueue con trái và con phải của current vào bf_queue.*/
		if (current->left != NULL) {
			bf_queue.push(current->left);
		}
		if (current->right != NULL) {
			bf_queue.push(current->right);
		}
	}
}