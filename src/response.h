#ifndef RESPONSE_H
#define REPSONSE_H

#include <string>
#include "ocelot.h"

using namespace std;

const string response(const string &body, client_opts_t &client_opts);
const string response_head(size_t content_length, client_opts_t &client_opts);
const string error(const string &err, client_opts_t &client_opts);
const string warning(const string &msg);
#endif
