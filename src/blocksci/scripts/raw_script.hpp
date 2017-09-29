//
//  raw_script.hpp
//  blocksci
//
//  Created by Harry Kalodner on 9/28/17.
//

#ifndef raw_script_hpp
#define raw_script_hpp

#include <blocksci/scripts/script_type.hpp>
#include <blocksci/bitcoin_uint256.hpp>

#include <boost/functional/hash.hpp>

#include <stdio.h>

namespace blocksci {
    struct RawScript {
        uint160 hash;
        ScriptType::Enum type;
        
        bool operator==(const RawScript& other) const {
            return type == other.type && hash == other.hash;
        }
    };
}

namespace std {
    template <>
    struct hash<blocksci::RawScript> {
    public:
        size_t operator()(const blocksci::RawScript &b) const {
            std::size_t seed = 123945432;
            hash<decltype(b.hash)> hasher1;
            hash<decltype(b.type)> hasher2;
            seed ^= hasher1(b.hash) + 0x9e3779b9 + (seed<<6) + (seed>>2);
            seed ^= hasher2(b.type) + 0x9e3779b9 + (seed<<6) + (seed>>2);
            return seed;
        }
    };
}

#endif /* raw_script_hpp */
