local re = import "re.jsonnet";
function(schema) {
    local ident = schema.string(pattern=re.ident_only),
    local address = schema.string(pattern=re.uri),

    local ltype = schema.enum("LinkType", ["bind","connect"], default="bind",
                         doc="How a port links to an address"),
    local link = schema.record("Link", fields= [
        schema.field("linktype", "LinkType",
                doc="The socket may bind or connect the link"),
        
        schema.field("address", address, 
                doc="The address to link to")
    ], doc="Describes how a single link is to be made"),
    local port = schema.record("Port", fields=[
        schema.field("ident", ident,
                doc="Identify the port uniquely in th enode"),
        schema.field("links", schema.sequence("Link"), 
                doc="Describe how this port should link to addresses"),
    ], doc="A port configuration object",),
    local comp = schema.record("Comp", fields=[
        schema.field("ident", ident, 
                doc="Identify copmponent instance uniquely in the node"),
        schema.field("type_name", ident, 
                doc="Identify the component implementation"),
        schema.field("portlist", schema.sequence(ident), 
                doc="Identity of ports required by component"),
        schema.field("config", schema.string(), 
                doc="Per instance configuration string used by node")
    ], doc="An object used by the node to partly configure a component"),
    local node = schema.record("Node", fields=[
        schema.field("ident", ident,
                doc="Idenfity the node instance"),
        schema.field("portdefs", schema.sequence("Port"), 
                doc="Define ports on the node to be used by components"),
        schema.field("compdefs", schema.sequence("Comp"),
                doc="Define components the node should instantiate and configure"),
    ], doc="A node configures ports and components"),

    types: [ ltype, link, port, comp, node ],
}
