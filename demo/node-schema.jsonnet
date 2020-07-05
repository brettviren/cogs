local moo = import "moo.jsonnet";
function(schema) {
    local ident = schema.string("Ident", pattern=moo.schema.re.ident_only),
    local address = schema.string("Address", pattern=moo.schema.re.uri),

    local ltype = schema.enum("LinkType", ["bind","connect"], default="bind",
                         doc="How a port links to an address"),
    local link = schema.record("Link", fields= [
        schema.field("linktype", ltype,
                doc="The socket may bind or connect the link"),
        schema.field("address", address, 
                doc="The address to link to")
    ], doc="Describes how a single link is to be made"),

    local linklist = schema.sequence("LinkList", link),

    local port = schema.record("Port", fields=[
        schema.field("ident", ident,
                doc="Identify the port uniquely in th enode"),
        schema.field("links", linklist, 
                doc="Describe how this port should link to addresses"),
    ], doc="A port configuration object",),
    local portlist = schema.sequence("PortList", ident), 
    local portdefs = schema.sequence("PortDefs", port), 

    local extra_config = schema.string("ExtraConfig"), 

    local comp = schema.record("Comp", fields=[
        schema.field("ident", ident, 
                doc="Identify copmponent instance uniquely in the node"),
        schema.field("type_name", ident, 
                doc="Identify the component implementation"),
        schema.field("portlist", portlist,
                doc="Identity of ports required by component"),
        schema.field("config", extra_config,
                doc="Per instance configuration string used by node")
    ], doc="An object used by the node to partly configure a component"),
    local compdefs = schema.sequence("CompDefs", comp),

    local node = schema.record("Node", fields=[
        schema.field("ident", ident,
                doc="Idenfity the node instance"),
        schema.field("portdefs", portdefs,
                doc="Define ports on the node to be used by components"),
        schema.field("compdefs", compdefs,
                doc="Define components the node should instantiate and configure"),
    ], doc="A node configures ports and components"),

    types: [ ident, address, ltype, link, linklist,
             port, portlist, portdefs,
             extra_config, comp, compdefs, node ],
}
