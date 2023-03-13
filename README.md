<!--
SPDX-FileCopyrightText: 2022 Alexander Zhang <alex@alexyzhang.dev>

SPDX-License-Identifier: AGPL-3.0-or-later
-->

# CppDiep

This is a very simple 2D game based on [Diep.io](https://diep.io/).
It is a personal project originally intended to be used as a reinforcement learning environment.

## Building

Building this project requires Box2D 2.4.1 and SFML 2.5.
Commands for Fedora 36:
```bash
sudo dnf install git gcc-c++ make cmake Box2D-devel SFML-devel
git clone https://codeberg.org/alexyz/cppdiep.git && cd cppdiep
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j $(nproc)
```

## Gameplay

You control the blue tank and try to kill the red tank, which will automatically shoot at you and move towards you.
Move with the WASD keys and aim with the mouse.
Left click to fire or press E to toggle automatic firing.

Demo: https://cppdiep.alexyzhang.dev/cppdiep.mp4
