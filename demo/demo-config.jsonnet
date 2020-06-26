// This file creates a demo cogs configuration stream file which is a
// JSON array that ping-pongs between a header and a payload

/// First, define some functions to create our configuration objects
/// so they will be valid-by-construction.  Unfortunately, I see no
/// way to generate these from schema.  But, once written and debugged
/// they may be for all subsequent configuration object authoring.


local head(impname, instname) = {
    impname: impname, instname:instname};

local node(ident, ports=[], comps=[]) = {
    ident:ident, portdefs:ports, compdefs:comps};

local portdef(ident, links) = {
    ident:ident, links:links};

local link(borc, address) = {
    linktype: borc, address: address };

local compdef(ident, type_name, portlist, cfg="") = {
    ident:ident, type_name:type_name, portlist:portlist, config:cfg };

// Component-level configuration objects 
local source(ntosend) = { ntosend: ntosend};

local node_schema = import "node-schema.jsonnet";
local comp_schema = import "comp-schema.jsonnet";
local head_schema = import "head-schema.jsonnet";

local jscm = import "json-schema.jsonnet";

local local_jscm = import "json-schema.jsonnet";

local compound(types, top=null) = {
    ret : {
        definitions: {[t._name]:t for t in types}
    } + if std.type(top) == "null"
    then types[std.length(types)-1]
    else top,
}.ret;

local schema = {
    head: compound(head_schema(jscm).types),
    comp: compound(comp_schema(jscm).types),
    node: compound(node_schema(jscm).types),
};


{
    // Another Jsonnet may import this one to reuse these functions.
    generate:: {
        head:head, node:node, portdef:portdef, link:link, compdef:compdef,
    },

    // this "oneOf" is outside abstract moc schema but is JSON Schema
    //validate: moc.jscm.sequence({oneOf:jscm}),

    // A test model
    model: [
        head("demoSource", "mycomp_source1"),
        source(42),

        head("demoNode", "mynode_inst1"),
        node("mynode1",
             ports=[portdef("src",[link("bind","tcp://127.0.0.1:5678")])],
             comps=[compdef("mycomp_source1", "demoSource", ["src"])]),
    ],

    // element by element schema
    schema: [
        schema.head,
        schema.comp,
        schema.head,
        schema.node,
    ],


    // may validate with:
    // $ moo validate --sequence \
    //  -S schema -s demo/demo-config.jsonnet \
    //  -D model demo/demo-config.jsonnet

}

