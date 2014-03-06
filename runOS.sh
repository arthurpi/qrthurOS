#!/bin/bash

# Emulates qrthurOS with bochs

bochs -f ./misc/bochsrc 'display_library: sdl'

# Debugging
$HOME/srcs/bochs-2.6.2/bochs -f ./misc/bochsrc 'display_library: sdl'
