local moo = import "moo.jsonnet";
local node = import "node-schema.jsonnet";
local comp = import "comp-schema.jsonnet";
local head = import "head-schema.jsonnet";

local render_nljs = function(name, schema) moo.render(
    model= {
        //types: schema(moo.schema.avro).types,
        types: moo.schema.avro.build(schema),
        namespace: "democfg",
        name:name,
    },
    template = "avro_nljs.hpp.j2",
    filename = name+"_nljs.hpp");

[
    render_nljs("node",node),
    render_nljs("comp",comp),
    render_nljs("head",head),
]

