// This file creates a demo cogs configuration stream file which is a
// JSON array that ping-pongs between a header and a payload

/// FIXME
/// FIXME
/// FIXME
/// FIXME
/// FIXME
///
/// Define some functions to create our configuration objects.  In
/// future these functions may be generated by providing
/// *-schema.jsonnet with a schema function generating schema.
/// 
/// FIXME
/// FIXME
/// FIXME
/// FIXME
/// FIXME
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
local moc = import "moc.jsonnet";

local jscm = [
    node_schema(moc.jscm),
    comp_schema(moc.jscm),
    head_schema(moc.jscm),
];


{
    // this "oneOf" is outside abstract moc schema but is JSON Schema
    validate: moc.jscm.sequence({anyOf:jscm}),

    model: [
        head("demoSource", "mycomp_source1"),
        source(42),

        head("demoNode", "mynode_inst1"),
        node("mynode1",
             ports=[portdef("src",[link("bind","")])],
             comps=[compdef("mycomp_source1", "demoSource", ["src"])]),
    ]
}

