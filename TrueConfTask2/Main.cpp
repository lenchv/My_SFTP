#include "MyTCP.h"
#include "MyTCPServer.h"
#include "MyFTPServer.h"
#include <iostream>
#include <thread>

using namespace std;
#pragma once

void ShowRecieveData(MyFTPServer &obj) {
	while (!obj.isOpenFile());
	cout << "Recieve file " << obj.getFileName() << endl;
	cout << "Length file: " << obj.getFileLength() << " bytes" << endl;
	unsigned int curLen = 0;
	while ( !obj.isClose() && (obj.getSize() != obj.getFileLength())) {
		curLen = obj.getSize();
		this_thread::sleep_for(chrono::milliseconds(500));
		cout << obj.getSize() <<" bytes " << (obj.getSize() - curLen)*2 << " b/sec" << endl;
	}
}

int main(int argc, const char **argv) {
	try {
		MyFTPServer *serv = new MyFTPServer("2000");
		if (argc == 2) {
			serv->setDirectory(argv[1]);
		}
		thread thr(ShowRecieveData, ref(*serv));
		try {
			cout << "Work directory: " << serv->getDirectory() << endl;
			cout << "Wait client..." << endl;
			serv->connect();
			cout << "Client "<<serv->getClientInfo() << " connected." << endl;
			serv->recieveFile();
		}
		catch (AcceptException ex) {
			cout << "Accept: " << ex;
		}
		catch (SocketOptionException ex) {
			cout << "Socket option: " << ex;
		}
		catch (BindException ex) {
			cout << "Bind: " << ex;
		}
		catch (ListenException ex) {
			cout << "Listen: " << ex;
		}
		catch (HostByNameException ex) {
			cout << "Host name: " << ex;
		}
		catch (InetPtonException ex) {
			cout << "InetPton: " << ex;
		}
		catch (RecieveException ex) {
			cout << "Recieve exception: " << ex;
		}
		catch (MyTCPException ex) {
			cout << ex;
		}

		thr.join();
		delete serv;
	}
	catch (SocketOptionException ex) {
		cout << "Socket option: " << ex;
	}
	catch (BindException ex) {
		cout << "Bind: " << ex;
	}
	catch (ListenException ex) {
		cout << "Listen: " << ex;
	}
	catch (HostByNameException ex) {
		cout << "Host name: " << ex;
	}
	catch (InetPtonException ex) {
		cout << "InetPton: " << ex;
	}
	catch (MyTCPException ex) {
		cout << ex;
	}
	system("pause");
	return 0;
}