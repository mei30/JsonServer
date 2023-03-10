#include <iostream>

#include "Server.h"
#include "ConfigurationService.h"

using namespace std;

int main()
{
	std::cout << "Server Starting..." << endl;

	core::ConfigurationService service;
	service.read("configuration.proto");
	Server s;
	s.listen();
	return 0;
}
