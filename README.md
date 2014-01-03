mod_lowercase_username
======================

Apache 2.x module for converting request user (REMOTE_USER) to lower case.

Many LDAP servers allow case-insensitive matching on user names. This
causes a problem for backend programs that expect case-sensitive
usernames. This module provides a workaround for this problem by
converting user names to lower case in Apache.

Installation
------------

1. Compile and install using APXS:

    apxs -i -c mod_lowercase_username.c

2. Load the module:

    LoadModule lowercase_username_module modules/mod_lowercase_username.so

Bugs
----

This module is not configurable. It converts all usernames for all virtual
hosts, directories, and locations across the entire server to lower case.
