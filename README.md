# Ocelot

Ocelot is a BitTorrent tracker written in C++ for the [Gazelle](http://whatcd.github.io/Gazelle/) project. It supports requests over TCP and can only track IPv4 peers.

  This is a WIP fork to integrate cmake and postgres over autotools and mysql. This is *not* meant to be a 
  direct drop in replacement on a Gazelle based site as it will also require changes, which i will not
  be doing or be going over at all since i am not interested in gazelle itself.


## Ocelot Compile-time Dependencies

* [GCC/G++](http://gcc.gnu.org/) (4.7+ required; 4.8.1+ recommended)
* [Boost](http://www.boost.org/) (1.55.0+ required)
* [libev](http://software.schmorp.de/pkg/libev.html) (required)
* [MySQL++](http://tangentsoft.net/mysql++/) (3.2.0+ required)
* [TCMalloc](http://goog-perftools.sourceforge.net/doc/tcmalloc.html) (optional, but strongly recommended)

## Installation

The [Gazelle installation guides](https://github.com/WhatCD/Gazelle/wiki/Gazelle-installation) include instructions for installing Ocelot as a part of the Gazelle project.

### Standalone Installation

* Create the following tables according to the [Gazelle database schema](https://raw.githubusercontent.com/WhatCD/Gazelle/master/gazelle.sql):
 - `torrents`
 - `users_freeleeches`
 - `users_main`
 - `xbt_client_whitelist`
 - `xbt_files_users`
 - `xbt_snatched`

* Edit `ocelot.conf` to your liking.

* Build Ocelot:

        ./configure
        make
        make install

## Running Ocelot

### Run-time options:

* `-c <path/to/ocelot.conf>` - Path to config file. If unspecified, the current working directory is used.
* `-v` - Print queue status every time a flush is initiated.

### Signals

* `SIGHUP` - Reload config
* `SIGUSR1` - Reload torrent list, user list and client whitelist
