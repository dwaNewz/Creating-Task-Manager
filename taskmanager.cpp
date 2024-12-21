#include <iostream>
#include <windows.h>
#include <tlhelp32.h>
using namespace std;

// Function to list all running processes
void ListProcesses() {
    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;

    // Take a snapshot of all processes in the system
    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE) {
        cout << "Failed to take process snapshot." << endl;
        return;
    }

    pe32.dwSize = sizeof(PROCESSENTRY32);

    // Retrieve information about the first process
    if (!Process32First(hProcessSnap, &pe32)) {
        cout << "Failed to get first process." << endl;
        CloseHandle(hProcessSnap);
        return;
    }

    cout << "\nList of running processes:" << endl;
    cout << "-------------------------------" << endl;
    cout << "PID\tProcess Name" << endl;
    cout << "-------------------------------" << endl;

    do {
        cout << pe32.th32ProcessID << "\t" << pe32.szExeFile << endl;
    } while (Process32Next(hProcessSnap, &pe32));

    CloseHandle(hProcessSnap);
}

// Function to terminate a process by PID
void TerminateProcessByPID(DWORD pid) {
    HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pid);
    if (hProcess == NULL) {
        cout << "Unable to open process with PID " << pid << "." << endl;
        return;
    }

    if (TerminateProcess(hProcess, 0)) {
        cout << "Process with PID " << pid << " terminated successfully." << endl;
    } else {
        cout << "Failed to terminate process with PID " << pid << "." << endl;
    }

    CloseHandle(hProcess);
}

int main() {
    int choice;
    DWORD pid;

    do {
        cout << "\nMenu:" << endl;
        cout << "1. List all running processes" << endl;
        cout << "2. Terminate a process by PID" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                ListProcesses();
                break;
            case 2:
                cout << "Enter the PID of the process to terminate: ";
                cin >> pid;
                TerminateProcessByPID(pid);
                break;
            case 3:
                cout << "Exiting program..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 3);

    return 0;
}
