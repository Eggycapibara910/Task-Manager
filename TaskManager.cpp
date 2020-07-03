#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <psapi.h>
#include<iostream>
#include<string>
#include<fstream>
using namespace std;




void PrintProcessNameAndID(DWORD processID)
{
	TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");

	// Get a handle to the process.

	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
		PROCESS_VM_READ,
		FALSE, processID);

	// Get the process name.

	if (NULL != hProcess)
	{
		HMODULE hMod;
		DWORD cbNeeded;

		if (EnumProcessModules(hProcess, &hMod, sizeof(hMod),
			&cbNeeded))
		{
			GetModuleBaseName(hProcess, hMod, szProcessName,
				sizeof(szProcessName) / sizeof(TCHAR));
		}
	}

	// Print the process name and identifier.
	
	_tprintf(TEXT("%s  (PID: %u)\n"), szProcessName, processID);

	// Release the handle to the process.

	CloseHandle(hProcess);
}

int main(void)
{
	

	DWORD aProcesses[1024], cbNeeded, cProcesses;
	unsigned int i;

	if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))
	{
		return 1;
	}


	

	cProcesses = cbNeeded / sizeof(DWORD);

	

	for (i = 0; i < cProcesses; i++)
	{
		if (aProcesses[i] != 0)
		{
			PrintProcessNameAndID(aProcesses[i]);
		}
	}
		ofstream myfile;
	myfile.open("Log.txt"); //Creates a txt file with the process list 
	myfile << aProcesses;
	cout << "\n Press ENTER to continue\n";
	string close;
	getline(std::cin, close);


	cout << " Write the name of the Process(default extension is .exe)\n";
	cout << " Type 'exit' to finish the execution\n";
		string name;
	cin >> name;
	if (name =="exit") { system("taskkill /f /im ProcessKiller.exe"); }
	else {
		system(("taskkill /f /im " + name + ".exe").c_str()); //Kills the process by its name
	}
		return 0;

	
}

