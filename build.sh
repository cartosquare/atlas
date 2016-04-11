#!/bin/sh

gyp --depth=. -Dnode_root_dir=. geotag.gyp
make BUILDTYPE=Release

