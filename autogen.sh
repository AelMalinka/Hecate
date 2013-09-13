#!/bin/bash

mkdir -p build-aux
aclocal -I m4
libtoolize
autoconf
autoheader
automake --add-missing
