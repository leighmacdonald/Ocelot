#ifndef OCELOT_DB_H
#define OCELOT_DB_H
#pragma GCC visibility push(default)
#include <mysql++/mysql++.h>
#include <string>
#include <unordered_map>
#include <queue>
#include <mutex>
#include "config.h"

using namespace std;

class mysql {
	private:
		mysqlpp::Connection conn;
		string update_user_buffer;
		string update_torrent_buffer;
		string update_heavy_peer_buffer;
		string update_light_peer_buffer;
		string update_snatch_buffer;
		string update_token_buffer;

		queue<string> user_queue;
		queue<string> torrent_queue;
		queue<string> peer_queue;
		queue<string> snatch_queue;
		queue<string> token_queue;

		string mysql_db, mysql_host, mysql_username, mysql_password;
		bool u_active, t_active, p_active, s_active, tok_active;
		bool readonly;

		// These locks prevent more than one thread from reading/writing the buffers.
		// These should be held for the minimum time possible.
		mutex user_queue_lock;
		mutex torrent_buffer_lock;
		mutex torrent_queue_lock;
		mutex peer_queue_lock;
		mutex snatch_queue_lock;
		mutex token_queue_lock;

		void load_config(config * conf);
		void load_tokens(torrent_list &torrents);

		void do_flush_users();
		void do_flush_torrents();
		void do_flush_snatches();
		void do_flush_peers();
		void do_flush_tokens();

		void flush_users();
		void flush_torrents();
		void flush_snatches();
		void flush_peers();
		void flush_tokens();
		void clear_peer_data();

	public:
		bool verbose_flush;

		mysql(config * conf);
		void reload_config(config * conf);
		bool connected();
		void load_torrents(torrent_list &torrents);
		void load_users(user_list &users);
		void load_whitelist(vector<string> &whitelist);

		void record_user(const string &record); // (id,uploaded_change,downloaded_change)
		void record_torrent(const string &record); // (id,seeders,leechers,snatched_change,balance)
		void record_snatch(const string &record, const string &ip); // (uid,fid,tstamp)
		void record_peer(const string &record, const string &ip, const string &peer_id, const string &useragent); // (uid,fid,active,peerid,useragent,ip,uploaded,downloaded,upspeed,downspeed,left,timespent,announces,tstamp)
		void record_peer(const string &record, const string &peer_id); // (fid,peerid,timespent,announces,tstamp)
		void record_token(const string &record);

		void flush();

		bool all_clear();

		mutex torrent_list_mutex;
		mutex user_list_mutex;
		mutex whitelist_mutex;
};

#pragma GCC visibility pop
#endif
