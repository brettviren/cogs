local re = import "re.jsonnet";
function(schema) {
    local ident = schema.string(pattern=re.ident_only),
    local cfghdr = schema.record("ConfigHeader", fields=[
        schema.field("impname", ident),
        schema.field("instname", ident)]),

    types: [ cfghdr ],
}
