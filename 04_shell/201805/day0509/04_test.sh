#! /bin/sh

test "$(whoami)" != 'root' && (echo you are using a non-privileged account; exit 1)
