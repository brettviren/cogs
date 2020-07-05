function(schema) {
    local int = schema.number("Int", dtype="i4"),
    local source = schema.record("Source", fields=[
        schema.field("ntosend", int, -1,
                doc="Number of messages to source, negative means run forever"),
    ], doc="A config for a source component"),

    // etc for other types of components

    types: [ int, source ],
}
