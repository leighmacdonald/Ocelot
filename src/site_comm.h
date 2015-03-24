#ifndef OCELOT_SITE_COMM_H
#define OCELOT_SITE_COMM_H
#include <string>
#include <boost/asio.hpp>
#include <queue>
#include <mutex>

#include "config.h"

using boost::asio::ip::tcp;
using namespace std;

class site_comm {
	private:
		string site_host;
		string site_path;
		string site_password;
		mutex expire_queue_lock;
		string expire_token_buffer;
		queue<string> token_queue;
		bool readonly;
		bool t_active;
		void load_config(config * conf);
		void do_flush_tokens();

	public:
		bool verbose_flush;
		site_comm(config * conf);
		void reload_config(config * conf);
		bool all_clear();
		void expire_token(int torrent, int user);
		void flush_tokens();
		~site_comm();
};
#endif
