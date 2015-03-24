#ifndef OCELOT_CONFIG_H
#define OCELOT_CONFIG_H

#include <string>
#include <map>

using namespace std;

class confval {
	private:
		bool bool_val;
		uint32_t uint_val;
		string str_val;
		enum {
			CONF_NONEXISTENT,
			CONF_BOOL,
			CONF_UINT,
			CONF_STR,
		} val_type;
	public:
		confval();
		confval(bool value);
		confval(uint32_t value);
		confval(const char * value);
		uint32_t get_uint();
		bool get_bool();
		string get_str();
		void set(const string &val);
};

class config {
	private:
		template <typename T> void add(const string &setting_name, T value);
		string trim(const string str);
		void init();
		confval * get(const string &setting_name);
		map<string, confval> settings;
		confval * dummy_setting;
	public:
		config();
		void load(istream &conf_file);
		void load(const string &conf_file_path, istream &conf_file);
		void reload();
		bool get_bool(const string &setting_name);
		uint32_t get_uint(const string &setting_name);
		string get_str(const string &setting_name);
		void set(const string &setting_name, const string &value);
};

template <typename T> void config::add(const string &setting_name, T value) {
	confval setting(value);
	settings[setting_name] = setting;
}
#endif
