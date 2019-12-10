#include <iostream>
#include <fstream>
using namespace std;

class encrypt_decrypt
{
public:
    void file_read(string*,const int*, int*);
    void encrypt(string*,char*,const int*);
    void decrypt(string*);
    void decrypt_write(string*, char*, int*, bool);
};

void encrypt_decrypt::encrypt(string* recieved_file_name, char* recieved_char,const int* recieved_key)
{
    char map[66]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','0','1','2','3','4','5','6','7','8','9',' ','\n','.',','};
    int char_key;
    for(int i=0;i<66;i++)
    {
        if(*recieved_char==map[i])
        {
            char_key=i+*recieved_key;
            if(char_key>65)
            {
                char_key=char_key - 65;
            }
            ofstream output_file;
            string cipher_file=*recieved_file_name+"_encrypted.txt";
            output_file.open(cipher_file, ios::out | ios::app);
            if(output_file.is_open() && output_file.good())
            {
                output_file<<map[char_key];
            }
            else
            {
                cout<<"\nError creating cipher file!!\n";
            }
            output_file.close();
            break;
        }
    }
}

void encrypt_decrypt::file_read(string* recieved_file_name,const int* recieved_key, int* recieved_choice)
{
    char word_from_file;
    ifstream input_file;
    input_file.open(*recieved_file_name+".txt");
    if(input_file.good() && input_file.is_open())
    {
        while(input_file.get(word_from_file))
        {
            if(*recieved_choice==1)
            {
                encrypt(recieved_file_name, &word_from_file, recieved_key);
            }
            else if(*recieved_choice==2)
            {
                decrypt(recieved_file_name);
            }
        }
        input_file.close();
    }
    else
    {
        cout<<"\nError opening file\n\n";
    }
}

int main()
{
    encrypt_decrypt object;
    string file_name;
    int choice, key_choice, random_key;
    while(1)
    {
        cout<<"1. Encrypt file\n2. Decrypt file\n0. Exit\nINPUT: ";
        cin>>choice;
        if (choice==1 || choice==2)
        {
            if(choice==1)
            {
                cout<<"NOTE: '.txt' extension will be appended by the program!!\nEnter file name to be encrypted: ";
                cin.ignore();
                getline(cin,file_name);
                cout<<"Enter key: ";
                cin>>random_key;
                if (random_key>65)
                {
                    random_key=random_key%66;
                }
                else
                {
                    object.file_read(&file_name, &random_key, &choice);
                }
            }
            else if(choice==2)
            {
                cout<<"NOTE: '.txt' extension will be appended by the program!!\nEnter file name to be decrypted: ";
                cin.ignore();
                getline(cin,file_name);
                object.file_read(&file_name, &random_key, &choice);
            }
            else
            {
                cout<<"\nInvalid choice!!!\n\n";
            }
        }
        else if(choice==0)
        {
            return 0;
        }
        else
        {
            cout<<"\nINVALID INPUT!!\n\n";
        }
    }
}