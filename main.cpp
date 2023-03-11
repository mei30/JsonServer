#include <iostream>

#include "Server.h"

using namespace std;

int main()
{
	Server::instance().init();
	Server::instance().run();

	return 0;
}
