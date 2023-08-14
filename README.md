obts-openbts
============

Refactoring RangeNetworks OpenBTS

Ubuntu 20.04
------------

Installed these packages:
 * build-essential
 * libortp-dev
 * libzmq3-dev (NodeManager)
 * libreadline-dev
 * libspdlog-dev
 * libsqlite3-dev
 * libosip2-dev

Gentoo is for Ricers
--------------------

Emerge these packages:
 * There's no libortp package, so will have to figure out how to build this later.

To Build and Run
----------------

 * `snap install --classic cmake`

 * `git clone ?`
 * `cd ?`
 * `cmake .`
 * `git pull && cmake --build .`
 * `obts-openbts`
