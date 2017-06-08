#include <iostream>
#include <fstream>
#include <string.h>
#include <string>

using namespace std;

const unsigned int tableSize = 21;

struct Node
{
    unsigned int count;
	Node* next;
    string word;
    

};


    Node* hashtab[tableSize];
    
    unsigned int hashFunction(string word)
    {
        unsigned int hash =0;
        for (unsigned int i=0; i < word.length(); i++) 
			hash+=(char)word[i];
        return hash%tableSize;
    }
	
	unsigned int hashFunction2(string word)
{
	int h = 0;
	for (int i = 0;i < word.length();i++)
		h = 13 * h + ( char)word[i];
	return h % tableSize;
}


    
    void addNew (unsigned int hash, string key)
    {
        Node* newNode = new Node;
        newNode->count = 1;
        newNode->word = key;
        newNode->next = hashtab[hash];
       hashtab[hash] = newNode;
    }
   
    
    Node* searchWord (unsigned int hash, string key)
    {
        Node* temp = hashtab[hash];
        while (temp)
        {
            if (temp->word == key) return temp;
            temp=temp->next;
        }
        return nullptr;
    }
    
	
    
    
    void addNode (string key)
    {
        unsigned int hash = hashFunction(key);
        Node* found = searchWord(hash, key);
        if (!found) addNew(hash, key);
            else found -> count++;
    }
	 
    
    void info (Node* current)
    {
        cout << "\nСлово '" << current->word<<"'" ;
		cout<<hashFunction(current->word)<<endl;
    }
    
    void print ()
    {
        for (unsigned int i =0; i< tableSize; i++)
            if (hashtab[i])
            {
                Node* tmp = hashtab[i];
                cout << "\nHash: " << i;
                while (tmp)
                {
                    info(tmp);
                    tmp=tmp -> next;
                }
            }
    }

	 void info1 (Node* current)
    {
        cout << "\nСлово '" << current->word<<"'"<<endl;
		cout<<hashFunction2(current->word)<<endl;
    }
    
    void print1 ()
    {
        for (unsigned int i =0; i< tableSize; i++)
            if (hashtab[i])
            {
                Node* tmp = hashtab[i];
                cout << "\nHash: " << i;
                while (tmp)
                {
                    info1(tmp);
                    tmp=tmp -> next;
                }
            }
    }
	


int main(int argc, char * argv[]) 
{
	
	setlocale(LC_CTYPE, "rus");
	 struct listnode *node ;
	 int count = 0;
	 int collisions = 0;
	  int collisions1 = 0;
	  int array[30000]={0}, array1[30000]={0};
	 string x;
	 string pat;
	  cout << "\n Введите путь к файлу: " << endl;
	 getline (cin, pat);
	 ifstream input(pat);
	if(!input.is_open())
		cout << "Файл не может быть открыт!\n"; 
	
	while(!input.eof())
		{
			
			input>>x;
			count++;
			addNode(x);
			if ((array[hashFunction(x)]++) > 0)
			{
            collisions++;
			}
			if ((array1[hashFunction2(x)]++) > 0)
			{
            collisions1++;
			}
	}
	print();
    print1();
	cout << "Коллизии 1-ой хеш ф-и =" << collisions << endl;
	cout << "Коллизии 2-ой хеш ф-и =" << collisions1 << endl;
	double t=(collisions+collisions1)/2;
	cout<<"Среднее количество коллизий ="<<t<<endl;
		system("pause");
  return(0);
}
