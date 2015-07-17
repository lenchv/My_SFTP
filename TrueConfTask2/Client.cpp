#include "MyTCP.h"
#include "MyTCPClient.h"
#include "MyFTPClient.h"
#include <iostream>
#include <thread>

using namespace std;
#pragma once

void ShowSendingData(MyFTPClient &obj) {
	cout << "Send file " << obj.getFileName() << endl;
	unsigned int curLen;
	while (!obj.isClose() && obj.getSize() != obj.getFileLength()) {
		curLen = obj.getSize();
		this_thread::sleep_for(chrono::milliseconds(500));
		cout << obj.getSize() << " bytes " << 2*(obj.getSize() - curLen) << " b/sec" << endl;
	}
}

int main(int argc, const char **argv) {
	if (argc == 3) {
		try {
			MyFTPClient *cl = new MyFTPClient(argv[2]);
			thread thr(ShowSendingData, ref(*cl));
			try {
				cl->connect(argv[1], "2000");
				cl->sendFile();
			}
			catch (ConnectException ex) {
				cout << "Connect: " << ex;
			}
			catch (HostByNameException ex) {
				cout << "Host name: " << ex;
			}
			catch (InetPtonException ex) {
				cout << "InetPton: " << ex;
			}
			catch (SendException ex) {
				cout << "Send: " << ex;
			}
			catch (MyTCPException ex) {
				cout << ex;
			}
			catch (MyFTPException ex) {
				cout << ex;
			}
			thr.join();
			delete cl;
		}
		catch (WSAStartupException ex) {
			cout << "WSAStartup: " << ex;
		}
		catch (SocketException ex) {
			cout << "Open socket: "<< ex;
		}
		catch (ConnectException ex) {
			cout << "Connect: " << ex;
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
		catch (MyFTPException ex) {
			cout << ex;
		}
	}
	else {
		cout << "Enter parameters:\n";
		cout << "1st - IP of server\n";
		cout << "2nd - relative path to file\n";
	}
	system("pause");
	return 0;
}
