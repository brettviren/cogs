// The only generated type we need to know in here is ConfigHeader.
#include "head_nljs.hpp"

#include "factory.hpp"

#include "cogs/stream.hpp"
#include "cogs/issues.hpp"

int main(int argc, char* argv[])
{
    if (argc != 2) {
        ERS_INFO("usage: " << argv[0] << " <uri>");
        return -1;
    }
    
    /// Note, this whole main() itself could be a configuration-driven
    /// component.  However, to create this encroaches on framework
    /// features and so needs discussion.

    std::string uri = argv[1];
    ERS_INFO("loading " << uri);

    // This will return a valid stream or throw an issue.
    auto cs = cogs::make_stream(uri);

    while (true) {
        cogs::object obj;
        try {
            obj = cs->pop();
        }
        catch (const cogs::stream_exhausted& se) {
            ERS_INFO("configuration stream done");
            break;
        }

        // cogs uses nlohman::json objects with generated
        // to_json/from_json functions to serialize to generated Avro
        // types.  This app assumes the config string ping-pongs
        // between a "header" object of fixed type followed by a
        // configuration object for the component described by the
        // header.
        auto header = obj.get<democfg::ConfigHeader>();

        ERS_INFO("lookup: [" << header.impname << "]: "
                 << "\"" << header.instname << "\"");
        auto cfgble = demo::configurable(header.impname, header.instname);
        assert(cfgble);
        obj = cs->pop();

        ERS_INFO("configure: [" << header.impname << "]: "
                 << "\"" << header.instname << "\"");
        cfgble->configure(obj);
    }

    return 0;
}
