#include "comp_nljs.hpp"

#include "factory.hpp"
#include "ports.hpp"

#include "cogs/configurable.hpp"
#include "cogs/issues.hpp"


namespace demo {

    // class Sink, etc

    class Source : public cogs::Configurable,
                   public demo::PortuserBase {
      public:
        Source() {
            ERS_INFO("Source:\tconstructing");
        }
        virtual ~Source() {
            ERS_INFO("Source:\tdestructing");
        }

        virtual void configure(cogs::object obj) {
            auto co = cogs::cfgobj<democfg::Source>(obj);
            configure(std::move(co));
        }

        void configure(democfg::Source&& cfg) {
            ERS_INFO("Source:\tconfigured to send " << cfg.ntosend << " things");
        }
        
        virtual void set_port(demo::Port p) {
            ERS_INFO("Source:\tgiven port " << p.ident);
        }
    };

    class MySource : public Source {
      public:
        MySource() {
            ERS_INFO("MySource:\tconstructing");
        }
        virtual ~MySource() {
            ERS_INFO("MySource:\tdestructing");
        }
        
        virtual void configure(cogs::object obj) {
            Source::configure(obj);
            auto co = cogs::cfgobj<democfg::MySource>(obj);
            configure(std::move(co));
        }

        void configure(democfg::MySource&& cfg) {
            ERS_INFO("MySource:\tconfigured with myparm " << cfg.myparam);
        }
    };

}


//
DEMO_REGISTER_COMPONENT(demoSource, demo::Source);
//
DEMO_REGISTER_COMPONENT(demoMySource, demo::MySource);
