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


#ifndef HEAD_AVRO_HPP_1975975583__H_
#define HEAD_AVRO_HPP_1975975583__H_


#include <sstream>
#include "boost/any.hpp"
#include "avro/Specific.hh"
#include "avro/Encoder.hh"
#include "avro/Decoder.hh"

namespace democfg {
struct ConfigHeader {
    std::string impname;
    std::string instname;
    ConfigHeader() :
        impname(std::string()),
        instname(std::string())
        { }
};

struct head_avro_json_Union__0__ {
private:
    size_t idx_;
    boost::any value_;
public:
    size_t idx() const { return idx_; }
    ConfigHeader get_ConfigHeader() const;
    void set_ConfigHeader(const ConfigHeader& v);
    head_avro_json_Union__0__();
};

inline
ConfigHeader head_avro_json_Union__0__::get_ConfigHeader() const {
    if (idx_ != 0) {
        throw avro::Exception("Invalid type for union");
    }
    return boost::any_cast<ConfigHeader >(value_);
}

inline
void head_avro_json_Union__0__::set_ConfigHeader(const ConfigHeader& v) {
    idx_ = 0;
    value_ = v;
}

inline head_avro_json_Union__0__::head_avro_json_Union__0__() : idx_(0), value_(ConfigHeader()) { }
}
namespace avro {
template<> struct codec_traits<democfg::ConfigHeader> {
    static void encode(Encoder& e, const democfg::ConfigHeader& v) {
        avro::encode(e, v.impname);
        avro::encode(e, v.instname);
    }
    static void decode(Decoder& d, democfg::ConfigHeader& v) {
        if (avro::ResolvingDecoder *rd =
            dynamic_cast<avro::ResolvingDecoder *>(&d)) {
            const std::vector<size_t> fo = rd->fieldOrder();
            for (std::vector<size_t>::const_iterator it = fo.begin();
                it != fo.end(); ++it) {
                switch (*it) {
                case 0:
                    avro::decode(d, v.impname);
                    break;
                case 1:
                    avro::decode(d, v.instname);
                    break;
                default:
                    break;
                }
            }
        } else {
            avro::decode(d, v.impname);
            avro::decode(d, v.instname);
        }
    }
};

template<> struct codec_traits<democfg::head_avro_json_Union__0__> {
    static void encode(Encoder& e, democfg::head_avro_json_Union__0__ v) {
        e.encodeUnionIndex(v.idx());
        switch (v.idx()) {
        case 0:
            avro::encode(e, v.get_ConfigHeader());
            break;
        }
    }
    static void decode(Decoder& d, democfg::head_avro_json_Union__0__& v) {
        size_t n = d.decodeUnionIndex();
        if (n >= 1) { throw avro::Exception("Union index too big"); }
        switch (n) {
        case 0:
            {
                democfg::ConfigHeader vv;
                avro::decode(d, vv);
                v.set_ConfigHeader(vv);
            }
            break;
        }
    }
};

}
#endif
