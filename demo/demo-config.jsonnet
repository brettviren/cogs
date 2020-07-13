// This file creates a demo cogs configuration stream file which is a
// JSON array that ping-pongs between a header and a payload

local moo = import "moo.jsonnet";


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
local mysource(p, src) = { myparam: p } + src;

local node_schema = import "node-schema.jsonnet";
local comp_schema = import "comp-schema.jsonnet";
local head_schema = import "head-schema.jsonnet";

local schema = {
    head: moo.schema.json.build(head_schema),
    comp: moo.schema.json.build(comp_schema),
    node: moo.schema.json.build(node_schema),
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
        head("demoMySource", "mycomp_source1"),
        mysource(24, source(42)),

        head("demoNode", "mynode_inst1"),
        node("mynode1",
             ports=[portdef("src",[link("bind","tcp://127.0.0.1:5678")])],
             comps=[compdef("mycomp_source1", "demoMySource", ["src"])]),
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

