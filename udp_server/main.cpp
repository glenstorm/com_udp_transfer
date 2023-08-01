//
// server.cpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2023 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <ctime>
#include <iostream>
#include <string>
#include <boost/array.hpp>
#include <boost/bind/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::udp;
using namespace std;

class udp_server
{
public:
	udp_server(boost::asio::io_context& io_context)
		: socket_(io_context, udp::endpoint(udp::v4(), 1234))
		{
			start_receive();
		}

private:
	void start_receive()
	{
		socket_.async_receive_from(
			boost::asio::buffer(recv_buffer_), remote_endpoint_,
			boost::bind(&udp_server::handle_receive, this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
			}

			void handle_receive(const boost::system::error_code& error, std::size_t n)
			{
				if (!error)
				{
					std::string line(recv_buffer_.begin(), recv_buffer_.begin() + n);
					cout << line << endl;
					start_receive();
				}
			}

			udp::socket socket_;
			udp::endpoint remote_endpoint_;
			boost::array<char, 255> recv_buffer_;
};

int main()
{
	try
	{
		boost::asio::io_context io_context;
		udp_server server(io_context);
		io_context.run();
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
