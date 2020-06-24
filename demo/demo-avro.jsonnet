// compile with -m
local moo = import "moo.jsonnet";
local moc = import "moc.jsonnet";
local node = import "node-schema.jsonnet";
local comp = import "comp-schema.jsonnet";
local head = import "head-schema.jsonnet";

{
    "node_avro.json": node(moc.avro).types,
    "comp_avro.json": comp(moc.avro).types,
    "head_avro.json": head(moc.avro).types,
}
