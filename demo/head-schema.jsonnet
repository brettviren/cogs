local moo = import "moo.jsonnet";
function(schema) {
    local ident = schema.string("Ident", pattern=moo.schema.re.ident_only),
    local cfghdr = schema.record("ConfigHeader", fields=[
        schema.field("impname", ident),
        schema.field("instname", ident)]),

    types: [ ident, cfghdr ],
}
