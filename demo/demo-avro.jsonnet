// compile with -m

// avro domain schema
local moo = import "moo.jsonnet";

// application level schema
local node = import "node-schema.jsonnet";
local comp = import "comp-schema.jsonnet";
local head = import "head-schema.jsonnet";

{
    "node_avro.json": moo.schema.avro.build(node),
    "comp_avro.json": moo.schema.avro.build(comp),
    "head_avro.json": moo.schema.avro.build(head),
}
