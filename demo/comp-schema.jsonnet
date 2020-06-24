function(schema) {
    local source = schema.record("Source", fields=[
        schema.field("ntosend", schema.number(dtype="i4"), -1,
                doc="Number of messages to source, negative means run forever"),
    ], doc="A config for a source component"),

    // etc for other types of components

    types: [ source ],
}
