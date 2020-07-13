#ifndef DEMOCFG_COMP_STRUCTS_HPP
#define DEMOCFG_COMP_STRUCTS_HPP


namespace democfg {


    struct Source{
        int ntosend;
    };


    struct MySource : public Source {
        int myparam;
    };


} // namespace democfg

#endif