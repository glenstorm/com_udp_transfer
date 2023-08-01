#include <iostream>
#include <string>
#include <vector>


#include "Message.h"
#include "serialstream.h"
#include <boost/array.hpp>
#include <boost/asio.hpp>

using namespace std;
using namespace boost::posix_time;
using boost::asio::ip::udp;

int main(int argc, char *argv[])
{
	if(argc != 3)
		return 0; // TODO: err

	string com_port = argv[1];

	cout << argv[1] << " --> " << argv[2] << endl;

	SerialOptions options;
	options.setDevice(argv[1]);
	options.setBaudrate(9600);
	options.setTimeout(seconds(5));

	SerialStream serial(options);
	serial.exceptions(ios::badbit | ios::failbit); //Important!

	boost::asio::io_context io_context;

	try
	{
		boost::system::error_code error;
		boost::asio::ip::udp::socket socket(io_context);
		socket.open(boost::asio::ip::udp::v4(), error);

		if (!error)
		{
			socket.set_option(boost::asio::ip::udp::socket::reuse_address(true));
			socket.set_option(boost::asio::socket_base::broadcast(true));

			boost::asio::ip::udp::endpoint senderEndpoint(boost::asio::ip::address_v4::broadcast(), atoi(argv[2]));

			for(int i = 0; i < 10; ++i)
			{
				// read com post 5 sec or wait end-char
				string s = "";
				try {
					serial >> s;
					cout << "serial > " << s << endl;
				} catch(TimeoutException& e) {
					cout << "Timeout error: " << e.what() << endl;
					serial.clear(); //Don't forget to clear error flags after a timeout
					cerr << "Timeout occurred" << endl;
				}

				// send udp message
				Message msg(s);
				const string received_data = msg.encrypt();

				cout << "send data: " << received_data << endl;
				socket.send_to(boost::asio::buffer(received_data.c_str(), received_data.size()), senderEndpoint);
	    	}
		}
		else
		{
			cout << "ERRORRRR!!!" << endl;
		}
		socket.close(error);
		cout << "SOCKET CLOSE" << endl;
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
