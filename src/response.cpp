#include <sstream>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include "response.h"
#include "misc_functions.h"

using namespace std;

const string response(const string &body, client_opts_t &client_opts) {
	string out;
	bool processed = false;
	if (client_opts.html) {
		out = "<html><head><meta name=\"robots\" content=\"noindex, nofollow\" /></head><body>" + body + "</body></html>";
		processed = true;
	}
	if (client_opts.gzip) {
		stringstream ss, zss;
		ss << body;
		boost::iostreams::filtering_streambuf<boost::iostreams::input> in;
		in.push(boost::iostreams::gzip_compressor());
		in.push(ss);
		boost::iostreams::copy(in, zss);
		out = zss.str();
		processed = true;
	}
	if (processed) {
		return response_head(out.length(), client_opts) + out;
	}
	return response_head(body.length(), client_opts) + body;
}

const string response_head(size_t content_length, client_opts_t &client_opts) {
	const string content_type = client_opts.html ? "text/html" : "text/plain";
	string head = "HTTP/1.1 200 OK\r\nServer: Ocelot 1.0";
	head += "\r\nContent-Type: " + content_type;
	if (client_opts.gzip) {
		head += "\r\nContent-Encoding: gzip";
	}
	if (client_opts.http_close) {
		head += "\r\nConnection: Close";
	}
	head += "\r\nContent-Length: " + inttostr(content_length) + "\r\n\r\n";
	return head;
}

const string error(const string &err, client_opts_t &client_opts) {
	return response("d14:failure reason" + inttostr(err.length()) + ':' + err + "12:min intervali5400e8:intervali5400ee", client_opts);
}

const string warning(const string &msg) {
	return "15:warning message" + inttostr(msg.length()) + ':' + msg;
}
