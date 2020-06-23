#include "cogs/stream.hpp"
#include "cogs/issues.hpp"
#include <fstream>

struct FileStream {
    std::fstream fstr;
    std::string filename;
    FileStream(const std::string& fname) : fstr(fname), filename(fname) {
        if (!fstr) {
            throw cogs::bad_file(ERS_HERE, fname);
        }
    }
};    

/// A JSON Stream is a URI pointing to data following
/// https://en.wikipedia.org/wiki/JSON_streaming
struct JsonStream : public FileStream, virtual public cogs::Stream {
    JsonStream(const std::string& fname) : FileStream(fname) {}
    virtual ~JsonStream() {}
    virtual cogs::object pop() {
        if (fstr.eof()) {
            throw cogs::stream_exhausted(ERS_HERE, filename);
        }
        cogs::object obj;
        try {
            fstr >> obj;
        }
        catch (const cogs::object::parse_error& pe) {
            if (pe.id == 101) {
                throw cogs::stream_exhausted(ERS_HERE, filename);
            }
            throw cogs::stream_corrupt(ERS_HERE, filename, pe.what());
        }
        if (not obj.is_object()) {
            throw cogs::stream_corrupt(ERS_HERE, filename, "not an object");
        }
        return obj;
    }
};

/// A JSON Array is a URI pointint to data holding a JSON array.
/// It slurps in the entire array and then iterates.
struct JsonArray : public FileStream, virtual public cogs::Stream {
    cogs::object arr;
    virtual ~JsonArray(){}
    JsonArray(const std::string& fname) : FileStream(fname) {
        try {
            fstr >> arr;
        }
        catch (const cogs::object::parse_error& pe) {
            throw cogs::stream_corrupt(ERS_HERE, filename, pe.what());
        }
        if (not arr.is_array()) {
            throw cogs::stream_corrupt(ERS_HERE, filename, "not an array");
        }
    }

    virtual cogs::object pop() {
        if (arr.empty()) {
            throw cogs::stream_exhausted(ERS_HERE, filename);
        }
        auto obj = arr[0];
        arr.erase(0);
        if (not obj.is_object()) {
            throw cogs::stream_corrupt(ERS_HERE, filename, "not an object");
        }
        return obj;
    }
};


cogs::stream_p cogs::make_stream(std::string uri)
{
    // This factory is hand crafted for now.  Todo later is to make it
    // extensible.

    auto dot = uri.find_last_of(".");
    auto sep = uri.find("://");

    std::string ext = uri.substr(dot+1);
    std::string scheme = "";
    std::string fname = uri;
    if (sep != std::string::npos) {
        scheme = uri.substr(0, sep);
        fname = uri.substr(sep+3);
    }
    
    if (scheme.empty() or scheme == "file") {

        if (ext == "json") {
            return std::make_unique<JsonArray>(fname);
        }
        if (ext == "jstream") {
            return std::make_unique<JsonStream>(fname);
        }
    }
    throw cogs::unsupported_uri(ERS_HERE, uri);
}

