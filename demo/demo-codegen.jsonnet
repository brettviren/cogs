local moo = import "moo.jsonnet";

local s = {
    node: import "node-schema.jsonnet",
    comp: import "comp-schema.jsonnet",
    head: import "head-schema.jsonnet",
};

local render_one = function(cg) [
    moo.render(cg, "avro_%s.hpp.j2"%t, "%s_%s.hpp"%[cg.name,t])
    for t in ["nljs", "structs"]];


local cg = moo.schema.avro.codegen;
std.flattenArrays([render_one(cg(k, s[k], "democfg")) for k in std.objectFields(s)])



