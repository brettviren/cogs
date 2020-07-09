#!/bin/bash
set -e

wd=$(dirname $(realpath $BASH_SOURCE))
cd $wd
echo "codegen in $(pwd)"

echo "Codegen for structs and serialization"
moo render-many demo-codegen.jsonnet

echo "Validating configuration"
moo -S schema -D model validate --sequence -s demo-config.jsonnet demo-config.jsonnet
echo
echo "null above means okay!"

echo "Compiling configuration to cogs stream file"
moo -D model compile demo-config.jsonnet > demo-config.json

