#ifndef WORKER_H
#define WORKER_H

#include <string>
#include <vector>
#include <list>
#include <unordered_map>
#include <iostream>
#include <mutex>
#include <ctime>
#include "site_comm.h"
#include "ocelot.h"

using namespace std;

enum tracker_status { OPEN, PAUSED, CLOSING }; // tracker status

class worker {
	private:
		config * conf;
		mysql * db;
		site_comm * s_comm;
		torrent_list &torrents_list;
		user_list &users_list;
		vector<string> &whitelist;
		unordered_map<string, del_message> del_reasons;
		tracker_status status;
		bool reaper_active;
		time_t cur_time;

		unsigned int announce_interval;
		unsigned int del_reason_lifetime;
		unsigned int peers_timeout;
		unsigned int numwant_limit;
		bool keepalive_enabled;
		string site_password;
		string report_password;

		mutex del_reasons_lock;
		void load_config(config * conf);
		void do_start_reaper();
		void reap_peers();
		void reap_del_reasons();
		string get_del_reason(int code);
		peer_list::iterator add_peer(peer_list &peer_list, const string &peer_id);
		inline bool peer_is_visible(user_ptr &u, peer *p);

	public:
		worker(config * conf_obj, torrent_list &torrents, user_list &users, vector<string> &_whitelist, mysql * db_obj, site_comm * sc);
		void reload_config(config * conf);
		string work(const string &input, string &ip, client_opts_t &client_opts);
		string announce(const string &input, torrent &tor, user_ptr &u, params_type &params, params_type &headers, string &ip, client_opts_t &client_opts);
		string scrape(const list<string> &infohashes, params_type &headers, client_opts_t &client_opts);
		string update(params_type &params, client_opts_t &client_opts);

		void reload_lists();
		bool shutdown();

		tracker_status get_status() { return status; }

		void start_reaper();
};
#endif
