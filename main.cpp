#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
	if(argc != 3)
		return 0; // TODO: err

	string com_port = argv[1];
	string udp_port = argv[2];

	cout << com_port << " --> " << udp_port << endl;

	return 0;
}
