// compile with -m

// avro domain schema
local avro = import "avro-schema.jsonnet";

// application level schema
local node = import "node-schema.jsonnet";
local comp = import "comp-schema.jsonnet";
local head = import "head-schema.jsonnet";

{
    "node_avro.json": node(avro).types,
    "comp_avro.json": comp(avro).types,
    "head_avro.json": head(avro).types,
}
