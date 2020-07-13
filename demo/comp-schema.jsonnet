function(schema) {
    local int = schema.number("Int", dtype="i4"),
    local source = schema.record("Source", fields=[
        schema.field("ntosend", int, -1,
                doc="Number of messages to source, negative means run forever"),
    ], doc="A config for a source component"),

    // etc for other types of components

    // A schema for configuration to be dispatched to a subclass of a
    // Source.

    local mysource = schema.record("MySource", fields=[
        schema.field("myparam", int, 42, doc="Some config for my implementation of Source"),
    ], bases = [ source ]),
    
    types: [ int, source, mysource ],
}
