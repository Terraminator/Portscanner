#include "EasySock.hpp"
#include "Thread_Pool.hpp"
#include <chrono>
#include <fstream>
typedef std::chrono::high_resolution_clock Clock;


void banner() {
	system("color a");
	std::cout << R"(

.______     ______   .______     .___________.
|   _  \   /  __  \  |   _  \    |           |
|  |_)  | |  |  |  | |  |_)  |   `---|  |----`
|   ___/  |  |  |  | |      /        |  |
|  |      |  `--'  | |  |\  \----.   |  |
| _|       \______/  | _| `._____|   |__|
)" << '\n';
	std::cout << R"(
     _______.  ______     ___      .__   __. .__   __.  _______ .______      
    /       | /      |   /   \     |  \ |  | |  \ |  | |   ____||   _  \     
   |   (----`|  ,----'  /  ^  \    |   \|  | |   \|  | |  |__   |  |_)  |    
    \   \    |  |      /  /_\  \   |  . `  | |  . `  | |   __|  |      /     
.----)   |   |  `----./  _____  \  |  |\   | |  |\   | |  |____ |  |\  \----.
|_______/     \______/__/     \__\ |__| \__| |__| \__| |_______|| _| `._____|
                                                                                                                          
)" << '\n';
	cout << "Coded by Terraminator: https://github.com/Terraminator" << endl;
	cout << endl;
	cout << endl;
	cout << endl;
}


int scanner(string target, int port) {
	EasySock easysock(target, port);
	int r = easysock.connect_to_target();
	easysock.clean_up();
	if (r == 0) {
		ofstream writer("ports.txt", ios::app);
		writer << port << endl;
		writer.close();
	}
	return(0);
}

int clear_ports() {
	std::ofstream ofs("test.txt", std::ofstream::trunc);

	ofs << "";

	ofs.close();
	return(0);
}


 string get_ip() {
	 string target;
	 cout << "If you just  want to test the script use: 45.33.32.156(Ip of scanme.nmap.org)!"<< endl;
	 cout << "Enter Ip of Target: ";
	 cin >> target;
	 cout << endl;
	 return(target);
}

int main() {
	banner();
	string target;
	for (target = get_ip(); target.length() < 7; target=get_ip()) {
		cout << "Please enter a valid Ip!" << endl;
	}
	clear_ports();
	cout << "Scan for " << target << " started!" << endl;
	Thread_Pool tpool;
	auto t1 = Clock::now();
	for (int i{ 1 }; i < 4501; i++) {
		tpool.start_thread(scanner, target, i);
	}
	tpool.wait_for_pool();
	string tp;
	std::ifstream ports("ports.txt");
	std::string line;
	while (std::getline(ports, line)) {
		if (line != "") {
			cout << "Port " + line + " is opened!" << endl;
		}
	}
	auto t2 = Clock::now();
	cout << "Scan for " << target << " finished in " << chrono::duration_cast<std::chrono::seconds>(t2 - t1).count() << " Seconds!" << endl;
	cout << "__________________________________________________" << endl;
	system("pause");
	return(0);
}