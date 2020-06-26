local dtypes = {               // fixme: need to flesh out
    i4: "integer",
    i8: "integer",
    f4: "number",
    f8: "number",
};
local objif(key, val) = if std.type(val)=="null" then {} else {[key]:val};
local builtins(t) = (t == "boolean") || (t == "string") || (t == "number") || (t == "integer") || (t == "field") || (t == "object") || (t == "array");
local builtin(t) = if std.type(t) == "string" then builtins(t) else builtins(t.type);

local tn(t) = if builtin(t) then t else {"$ref":"#/definitions/"+t};
{
    
    boolean():: {type: "boolean"},

    // JSON Schema has two number types and range constraints may be given.
    number(dtype, extra={}):: {
        type:dtypes[dtype]}
        + {[k]:extra[k] for k in std.objectFields(extra)
           if std.member(["minimum","maximum","exclusiveMinimum","exclusiveMaximum"],k)},

    // Avro wants us to spell a byte like "\uABCD".  That lets us
    // give bytes directly in some JSON object but is not so good
    // for large binary data.  So we will also accept arbitrary
    // encoding.  Encoded can NOT be directly turned into Avro
    // bytes so some Avro aware interpreter is needed if encoded
    // bytes are to be used.
    bytes(encoding=null, media_type=null):: {
        type: "string",
    } + if std.type(encoding)=="null" then {
        pattern: '^(\\u[a-fA-F0-9]{4})+$',
    } else {
        contentEncoding: encoding} + objif("contentMediaType", media_type),

    // A pattern constrains the string with a regex or format
    // constrains the string to a fixed set formats ("uri",
    // "date", etc).
    string(pattern=null, format=null):: {
        type: "string" } + objif("pattern", pattern) + objif("format", format),


    // 
    field(name, type, default=null, doc=null):: {
        what:"field", name:name, type:tn(type)}+objif("default",default)+objif("doc",doc),

    // A record matches a JSON object wth some set of fields.
    // Name is ignored
    record(name, fields=[], doc=null) :: {
        _name: name,
        type: "object",
        properties: {[f.name]: f.type for f in fields},
        required: [f.name for f in fields],
    }+objif("doc",doc),

    // A sequence in JSON Schema is an array
    sequence(type):: { type:"array", items:tn(type), },
    
    // Like record, enum does not have a name
    enum(name, symbols, default=null, doc=null):: {
        _name: name,
        type:"string", enum:symbols}+objif("default",default)+objif("doc",doc),

}
