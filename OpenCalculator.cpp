// This program uses the system() function to open the calculator
#include <iostream>
#include <windows.h>
#include <cstdlib> // for system() function
using namespace std;

int main()
{
    cout << "Opening the calculator...\n";
    system("calc.exe"); // this command opens the calculator in Windows

    //Now we check the privileges of this program
    // Get the current process token
    HANDLE hToken;
    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken))
    {
        cout << "OpenProcessToken failed: " << GetLastError() << endl;
        return -1;
    }

    // Get the token elevation information
    TOKEN_ELEVATION te;
    DWORD dwSize;
    if (!GetTokenInformation(hToken, TokenElevation, &te, sizeof(te), &dwSize))
    {
        cout << "GetTokenInformation failed: " << GetLastError() << endl;
        CloseHandle(hToken);
        return -1;
    }

    // Check the elevation level
    string message;
    if (te.TokenIsElevated)
    {
        message = "This program is running with administrator privileges.";
    }
    else
    {
        message = "This program is running with standard user privileges.";
    }

    // Display the message in a messagebox
    MessageBox(NULL, message.c_str(), "Privileges", MB_OK | MB_ICONINFORMATION);

    // Close the token handle
    CloseHandle(hToken);
}