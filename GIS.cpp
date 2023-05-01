#include <iostream>

using namespace std;

/*
	CMake project build process - Michael Sinclair
*/

int main(int argc, char* argv[]) {
	for (int i = 1; i < argc; i++)
		cout << argv[i] << endl;

	cout << "Hello, world!" << endl;

	return 0;
}