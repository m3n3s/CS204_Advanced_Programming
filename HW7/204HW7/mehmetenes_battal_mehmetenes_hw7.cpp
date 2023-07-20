#include <iostream>
#include <string>

using namespace std;

// MEHMET ENES BATTAL - HW7

unsigned char permute(unsigned char c)
{
	unsigned char result = 0;

	for(int i = 0; i < 8; i++)
	{
		unsigned int p; // position of the current bit in result
		unsigned int currentBit = 0;

		if(((1 << i) & c) != 0)
			currentBit = 1;
		
		if(i==0)
			p=2;
		else if(i==1)
			p=0;
		else if(i==2)
			p=3;
		else if(i==3)
			p=1;
		else if(i==4)
			p=6;
		else if(i==5)
			p=4;
		else if(i==6)
			p=7;
		else if(i==7)
			p=5;

		result = (result & ~(1 << p)) | (currentBit << p);
	}
	
	return result;
}

int main()
{
	cout << "*** Welcome to the Simple Data Encryption Application ***" << endl;

	string key, text;

	cout << "Please enter the encryption key: ";
	getline(cin, key);

	cout << "Please enter the plaintext to be encrypted: ";

	while(getline(cin, text))
	{
		cout << "Ciphertext: ";

		for(int i = 0; i < text.length(); i++)
		{
			unsigned char keyChar = key[i % key.length()];
			unsigned char encrypted = keyChar ^ permute(text[i]);

			cout << hex << (int) encrypted;
		}

		cout << endl << endl << "Please enter the plaintext to be encrypted: ";
	}

	return 0;
}