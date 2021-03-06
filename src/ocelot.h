#ifndef OCELOT_H
#define OCELOT_H

#include <string>
#include <map>
#include <vector>
#include <unordered_map>
#include <set>
#include <memory>
#include <atomic>

using namespace std;

typedef uint32_t torid_t;
typedef uint32_t userid_t;

class user;
typedef shared_ptr<user> user_ptr;

typedef struct {
	int64_t uploaded;
	int64_t downloaded;
	int64_t corrupt;
	int64_t left;
	time_t last_announced;
	time_t first_announced;
	uint32_t announces;
	uint16_t port;
	bool visible;
	bool invalid_ip;
	user_ptr user;
	string ip_port;
	string ip;
} peer;

typedef map<string, peer> peer_list;

enum freetype { NORMAL, FREE, NEUTRAL };

typedef struct {
	torid_t id;
	uint32_t completed;
	int64_t balance;
	freetype free_torrent;
	time_t last_flushed;
	peer_list seeders;
	peer_list leechers;
	string last_selected_seeder;
	set<userid_t> tokened_users;
} torrent;

enum {
	DUPE, // 0
	TRUMP, // 1
	BAD_FILE_NAMES, // 2
	BAD_FOLDER_NAMES, // 3
	BAD_TAGS, // 4
	BAD_FORMAT, // 5
	DISCS_MISSING, // 6
	DISCOGRAPHY,// 7
	EDITED_LOG,// 8
	INACCURATE_BITRATE, // 9
	LOW_BITRATE, // 10
	MUTT_RIP,// 11
	BAD_SOURCE,// 12
	ENCODE_ERRORS,// 13
	BANNED, // 14
	TRACKS_MISSING,// 15
	TRANSCODE, // 16
	CASSETTE, // 17
	UNSPLIT_ALBUM, // 18
	USER_COMPILATION, // 19
	WRONG_FORMAT, // 20
	WRONG_MEDIA, // 21
	AUDIENCE // 22
};

typedef struct {
	int reason;
	time_t time;
} del_message;

typedef struct {
	bool gzip;
	bool html;
	bool http_close;
} client_opts_t;

typedef unordered_map<string, torrent> torrent_list;
typedef unordered_map<string, user_ptr> user_list;
typedef unordered_map<string, string> params_type;

struct stats_t {
	atomic<uint32_t> open_connections;
	atomic<uint64_t> opened_connections;
	atomic<uint64_t> connection_rate;
	atomic<uint32_t> leechers;
	atomic<uint32_t> seeders;
	atomic<uint64_t> requests;
	atomic<uint64_t> request_rate;
	atomic<uint64_t> announcements;
	atomic<uint64_t> succ_announcements;
	atomic<uint64_t> scrapes;
	atomic<uint64_t> bytes_read;
	atomic<uint64_t> bytes_written;
	time_t start_time;
};
extern struct stats_t stats;
#endif
