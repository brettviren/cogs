/**
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *     https://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#ifndef NODE_AVRO_HPP_1975975583__H_
#define NODE_AVRO_HPP_1975975583__H_


#include <sstream>
#include "boost/any.hpp"
#include "avro/Specific.hh"
#include "avro/Encoder.hh"
#include "avro/Decoder.hh"

namespace democfg {
enum class LinkType: unsigned {
    bind,
    connect,
};

struct Link {
    LinkType linktype;
    std::string address;
    Link() :
        linktype(LinkType()),
        address(std::string())
        { }
};

struct Port {
    std::string ident;
    std::vector<Link > links;
    Port() :
        ident(std::string()),
        links(std::vector<Link >())
        { }
};

struct Comp {
    std::string ident;
    std::string type_name;
    std::vector<std::string > portlist;
    std::string config;
    Comp() :
        ident(std::string()),
        type_name(std::string()),
        portlist(std::vector<std::string >()),
        config(std::string())
        { }
};

struct Node {
    std::string ident;
    std::vector<Port > portdefs;
    std::vector<Comp > compdefs;
    Node() :
        ident(std::string()),
        portdefs(std::vector<Port >()),
        compdefs(std::vector<Comp >())
        { }
};

struct node_avro_json_Union__0__ {
private:
    size_t idx_;
    boost::any value_;
public:
    size_t idx() const { return idx_; }
    LinkType get_LinkType() const;
    void set_LinkType(const LinkType& v);
    Link get_Link() const;
    void set_Link(const Link& v);
    Port get_Port() const;
    void set_Port(const Port& v);
    Comp get_Comp() const;
    void set_Comp(const Comp& v);
    Node get_Node() const;
    void set_Node(const Node& v);
    node_avro_json_Union__0__();
};

inline
LinkType node_avro_json_Union__0__::get_LinkType() const {
    if (idx_ != 0) {
        throw avro::Exception("Invalid type for union");
    }
    return boost::any_cast<LinkType >(value_);
}

inline
void node_avro_json_Union__0__::set_LinkType(const LinkType& v) {
    idx_ = 0;
    value_ = v;
}

inline
Link node_avro_json_Union__0__::get_Link() const {
    if (idx_ != 1) {
        throw avro::Exception("Invalid type for union");
    }
    return boost::any_cast<Link >(value_);
}

inline
void node_avro_json_Union__0__::set_Link(const Link& v) {
    idx_ = 1;
    value_ = v;
}

inline
Port node_avro_json_Union__0__::get_Port() const {
    if (idx_ != 2) {
        throw avro::Exception("Invalid type for union");
    }
    return boost::any_cast<Port >(value_);
}

inline
void node_avro_json_Union__0__::set_Port(const Port& v) {
    idx_ = 2;
    value_ = v;
}

inline
Comp node_avro_json_Union__0__::get_Comp() const {
    if (idx_ != 3) {
        throw avro::Exception("Invalid type for union");
    }
    return boost::any_cast<Comp >(value_);
}

inline
void node_avro_json_Union__0__::set_Comp(const Comp& v) {
    idx_ = 3;
    value_ = v;
}

inline
Node node_avro_json_Union__0__::get_Node() const {
    if (idx_ != 4) {
        throw avro::Exception("Invalid type for union");
    }
    return boost::any_cast<Node >(value_);
}

inline
void node_avro_json_Union__0__::set_Node(const Node& v) {
    idx_ = 4;
    value_ = v;
}

inline node_avro_json_Union__0__::node_avro_json_Union__0__() : idx_(0), value_(LinkType()) { }
}
namespace avro {
template<> struct codec_traits<democfg::LinkType> {
    static void encode(Encoder& e, democfg::LinkType v) {
		if (v > democfg::LinkType::connect)
		{
			std::ostringstream error;
			error << "enum value " << static_cast<unsigned>(v) << " is out of bound for democfg::LinkType and cannot be encoded";
			throw avro::Exception(error.str());
		}
        e.encodeEnum(static_cast<size_t>(v));
    }
    static void decode(Decoder& d, democfg::LinkType& v) {
		size_t index = d.decodeEnum();
		if (index > static_cast<size_t>(democfg::LinkType::connect))
		{
			std::ostringstream error;
			error << "enum value " << index << " is out of bound for democfg::LinkType and cannot be decoded";
			throw avro::Exception(error.str());
		}
        v = static_cast<democfg::LinkType>(index);
    }
};

template<> struct codec_traits<democfg::Link> {
    static void encode(Encoder& e, const democfg::Link& v) {
        avro::encode(e, v.linktype);
        avro::encode(e, v.address);
    }
    static void decode(Decoder& d, democfg::Link& v) {
        if (avro::ResolvingDecoder *rd =
            dynamic_cast<avro::ResolvingDecoder *>(&d)) {
            const std::vector<size_t> fo = rd->fieldOrder();
            for (std::vector<size_t>::const_iterator it = fo.begin();
                it != fo.end(); ++it) {
                switch (*it) {
                case 0:
                    avro::decode(d, v.linktype);
                    break;
                case 1:
                    avro::decode(d, v.address);
                    break;
                default:
                    break;
                }
            }
        } else {
            avro::decode(d, v.linktype);
            avro::decode(d, v.address);
        }
    }
};

template<> struct codec_traits<democfg::Port> {
    static void encode(Encoder& e, const democfg::Port& v) {
        avro::encode(e, v.ident);
        avro::encode(e, v.links);
    }
    static void decode(Decoder& d, democfg::Port& v) {
        if (avro::ResolvingDecoder *rd =
            dynamic_cast<avro::ResolvingDecoder *>(&d)) {
            const std::vector<size_t> fo = rd->fieldOrder();
            for (std::vector<size_t>::const_iterator it = fo.begin();
                it != fo.end(); ++it) {
                switch (*it) {
                case 0:
                    avro::decode(d, v.ident);
                    break;
                case 1:
                    avro::decode(d, v.links);
                    break;
                default:
                    break;
                }
            }
        } else {
            avro::decode(d, v.ident);
            avro::decode(d, v.links);
        }
    }
};

template<> struct codec_traits<democfg::Comp> {
    static void encode(Encoder& e, const democfg::Comp& v) {
        avro::encode(e, v.ident);
        avro::encode(e, v.type_name);
        avro::encode(e, v.portlist);
        avro::encode(e, v.config);
    }
    static void decode(Decoder& d, democfg::Comp& v) {
        if (avro::ResolvingDecoder *rd =
            dynamic_cast<avro::ResolvingDecoder *>(&d)) {
            const std::vector<size_t> fo = rd->fieldOrder();
            for (std::vector<size_t>::const_iterator it = fo.begin();
                it != fo.end(); ++it) {
                switch (*it) {
                case 0:
                    avro::decode(d, v.ident);
                    break;
                case 1:
                    avro::decode(d, v.type_name);
                    break;
                case 2:
                    avro::decode(d, v.portlist);
                    break;
                case 3:
                    avro::decode(d, v.config);
                    break;
                default:
                    break;
                }
            }
        } else {
            avro::decode(d, v.ident);
            avro::decode(d, v.type_name);
            avro::decode(d, v.portlist);
            avro::decode(d, v.config);
        }
    }
};

template<> struct codec_traits<democfg::Node> {
    static void encode(Encoder& e, const democfg::Node& v) {
        avro::encode(e, v.ident);
        avro::encode(e, v.portdefs);
        avro::encode(e, v.compdefs);
    }
    static void decode(Decoder& d, democfg::Node& v) {
        if (avro::ResolvingDecoder *rd =
            dynamic_cast<avro::ResolvingDecoder *>(&d)) {
            const std::vector<size_t> fo = rd->fieldOrder();
            for (std::vector<size_t>::const_iterator it = fo.begin();
                it != fo.end(); ++it) {
                switch (*it) {
                case 0:
                    avro::decode(d, v.ident);
                    break;
                case 1:
                    avro::decode(d, v.portdefs);
                    break;
                case 2:
                    avro::decode(d, v.compdefs);
                    break;
                default:
                    break;
                }
            }
        } else {
            avro::decode(d, v.ident);
            avro::decode(d, v.portdefs);
            avro::decode(d, v.compdefs);
        }
    }
};

template<> struct codec_traits<democfg::node_avro_json_Union__0__> {
    static void encode(Encoder& e, democfg::node_avro_json_Union__0__ v) {
        e.encodeUnionIndex(v.idx());
        switch (v.idx()) {
        case 0:
            avro::encode(e, v.get_LinkType());
            break;
        case 1:
            avro::encode(e, v.get_Link());
            break;
        case 2:
            avro::encode(e, v.get_Port());
            break;
        case 3:
            avro::encode(e, v.get_Comp());
            break;
        case 4:
            avro::encode(e, v.get_Node());
            break;
        }
    }
    static void decode(Decoder& d, democfg::node_avro_json_Union__0__& v) {
        size_t n = d.decodeUnionIndex();
        if (n >= 5) { throw avro::Exception("Union index too big"); }
        switch (n) {
        case 0:
            {
                democfg::LinkType vv;
                avro::decode(d, vv);
                v.set_LinkType(vv);
            }
            break;
        case 1:
            {
                democfg::Link vv;
                avro::decode(d, vv);
                v.set_Link(vv);
            }
            break;
        case 2:
            {
                democfg::Port vv;
                avro::decode(d, vv);
                v.set_Port(vv);
            }
            break;
        case 3:
            {
                democfg::Comp vv;
                avro::decode(d, vv);
                v.set_Comp(vv);
            }
            break;
        case 4:
            {
                democfg::Node vv;
                avro::decode(d, vv);
                v.set_Node(vv);
            }
            break;
        }
    }
};

}
#endif
