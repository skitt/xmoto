#!/bin/sh

set -ex

brew update

# packages to be checked for before installing them
for pkg in cmake ninja jpeg libpng \
           bzip2 curl sqlite3 libxml2 zlib; do
  brew list "$pkg" &>/dev/null || brew install "$pkg"
done

# install the rest of the packages
brew install gettext sdl sdl_mixer sdl_net sdl_ttf

