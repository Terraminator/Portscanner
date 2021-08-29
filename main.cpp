#include "EasySock.hpp"
#include "Thread_Pool.hpp"
#include <chrono>
typedef std::chrono::high_resolution_clock Clock;

int scanner(string target, int port) {
	EasySock easysock(target, port);
	int r = easysock.connect_to_target();
	easysock.clean_up();
	if (r == 0) {
		cout << "Port " << port << " is opened!" << endl;
	}
	return(0);
}

void banner() {
	system("color a");
	std::cout << R"(
._____     ______   .______     .___________.        _______.  ______     ___      .__   __. .__   __.  _______ .______      
|   _  \   /  __  \  |   _  \    |           |       /       | /      |   /   \     |  \ |  | |  \ |  | |   ____||   _  \     
|  |_)  | |  |  |  | |  |_)  |   `---|  |----`      |   (----`|  ,----'  /  ^  \    |   \|  | |   \|  | |  |__   |  |_)  |    
|   ___/  |  |  |  | |      /        |  |            \   \    |  |      /  /_\  \   |  . `  | |  . `  | |   __|  |      /     
|  |      |  `--'  | |  |\  \----.   |  |        .----)   |   |  `----./  _____  \  |  |\   | |  |\   | |  |____ |  |\  \----.
| _|       \______/  | _| `._____|   |__|        |_______/     \______/__/     \__\ |__| \__| |__| \__| |_______|| _| `._____|
    
)" << '\n';
	cout << "Coded by Terraminator: https://github.com/Terraminator" << endl;
	system("color 9");
	cout << endl;
	cout << endl;
	cout << endl;
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

	cout << "Scan for " << target << " started!" << endl;
	Thread_Pool tpool;
	auto t1 = Clock::now();
	for (int i{ 1 }; i < 4501; i++) {
		tpool.add_thread_to_pool(scanner, target, i);
		Sleep(1);
	}
	tpool.start_pool();
	auto t2 = Clock::now();
	cout << "Scan for " << target << " finished in " << chrono::duration_cast<std::chrono::seconds>(t2 - t1).count() << " Seconds!" << endl;
	cout << "__________________________________________________";
	return(0);
}