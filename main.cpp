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
	cout << "___________    ________       __________    _______________ " << endl;
	cout << "|     _    | /    _    \\    /   _      |  |______  ______| " << endl;
	cout << "|    |_|   | |   | |   |    /   | |    /         | |        " << endl;
	cout << "|__________| |   | |   |   |    |_|  /           | |        " << endl;
	cout << "|  |         |   | |   |   |    _    \\           | |       " << endl;
	cout << "|  |         |   | |   |   |   / \\    \\          | |      " << endl;
	cout << "|  |         |   | |   |   |  |   |    |         | |        " << endl;
	cout << "|  |         |   |_|   |   |  |    |   |         | |        " << endl;
	cout << "|__|         \\________ /   |__|     |__|         |_|       " << endl;
	cout << " _________       _________                        _           _     _           _                     __________  " << endl;
	cout << "/ ________\\    /  _____  \\        //\\\\       | |\\\\     | |   | |\\\\     | |   __________      /   _      | " << endl;
	cout << "| |______       | |     \\ \\      //  \\\\      | | \\\\    | |   | | \\\\    | |  | | _______|    /   | |    /  " << endl;
	cout << "|________ \\    | |      \\_\\    //    \\\\     | |  \\\\   | |   | |  \\\\   | |  | ||_______    |    |_|  /    " << endl;
	cout << "        |  |    | |        _     //______\\\\    | |   \\\\  | |   | |   \\\\  | |  | | _______|   |    _    \\   " << endl;
	cout << " _______/  /    | |______/ /    //________\\\\   | |    \\\\ | |   | |    \\\\ | |  | ||_______    |   / \\    \\ " << endl;
	cout << " \\________|    \\________/    //          \\\\  |_|     \\\\|_|   |_|     \\\\|_|  |_|________|   |  |   |    |  " << endl;
	cout << "                                                                                                   |__|    |___|  " << endl;
	cout << "Coded by Terraminator: https://github.com/Terraminator" << endl;
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