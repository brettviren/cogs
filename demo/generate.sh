#!/bin/bash
set -e

wd=$(dirname $(realpath $BASH_SOURCE))
cd $wd
echo "codegen in $(pwd)"

echo "Rendering nlohmann::json serialization code"
moo render-many demo-render.jsonnet

echo "Compiling Avro schema files"
moo compile -m . demo-avro.jsonnet
echo "Generating Avro code"
for n in *_avro.json; do
    avrogencpp -n democfg -i $n -o $(basename $n .json).hpp && rm $n
done     

echo "Validating configuration"
moo validate --sequence -S schema -s demo-config.jsonnet -D model demo-config.jsonnet
echo
echo "null above means okay!"

echo "Compiling configuration to cogs stream file"
moo compile -D model demo-config.jsonnet > demo-config.json

