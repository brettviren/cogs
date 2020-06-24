local objif(key, val) = if std.type(val)=="null" then {} else {[key]:val};
{
    // A lookup between dtype and avro type
    local dtypes = {               // fixme: need to flesh out
        i4: "int",
        i8: "long",
        f4: "float",
        f8: "double",
    },
    local typeref(what) = if std.type(what)=="string" then what else
        if what.type == "record" then what.name else what,

    // fixme: need function to resolve a type structure to a type
    // name.  For record it is .name which is the type.  All
    // others it is .type

    boolean():: {type:"boolean"},

    // Avro has only four number types and any extra args are ignored.
    number(dtype, extra={}):: {type:dtypes[dtype], dtype:dtype},
    
    // Avro bytes type is fundamental
    bytes(encoding=null, media_type=null):: {type:"bytes"},

    // Avro strings are fundamental.  Pattern and format ignored
    string(pattern=null, format=null):: {type:"string"},

    // A field is an attribute of a record.
    field(name, type, default=null, doc=null):: {
        name:name, type:typeref(type)
    } + objif("default",default) + objif("doc", doc),

    // A record is a class/struct/object.  
    record(name, fields=[], doc=null) :: {
        type: "record", name:name, fields:fields
    } + objif("doc",doc),

    // A sequence in avro is an array
    sequence(type):: { type:"array", items:typeref(type), },

    enum(name, symbols, default=null, doc=null):: {
        type:"enum", name:name, symbols:symbols}+objif("default",default)+objif("doc",doc),
}
