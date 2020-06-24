#include "comp_nljs.hpp"

#include "factory.hpp"
#include "ports.hpp"

#include "cogs/configurable.hpp"
#include "cogs/issues.hpp"


namespace demo {

    // class Sink, etc

    class Source : public cogs::Configurable<democfg::Source>,
                   public demo::PortuserBase {
      public:
        virtual void configure(democfg::Source&& cfg) {
            ERS_INFO("Source will send " << cfg.ntosend);
        }
        
        virtual void set_port(demo::Port p) {
            ERS_INFO("Source given port " << p.ident);
        }
    };

}


DEMO_REGISTER_COMPONENT("demoSource", demo::Source);
