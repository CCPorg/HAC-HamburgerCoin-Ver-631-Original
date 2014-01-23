// Copyright (c) 2009-2012 The Bitcoin developers
// Copyright (c) 2011-2012 Litecoin Developers
// Copyright (c) 2013 Elephantcoin Developers
// Copyright (c) 2014 HamburgeCoin Developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "main.h"
#include "uint256.h"

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

	// no checkpoint now, can be added in later releases
    static MapCheckpoints mapCheckpoints =
            boost::assign::map_list_of
(0,   uint256("0x7f90afa3b55baa607333bf801421d88779313ad8e774ef1cb4dcfa2029e2e8c6"))
//(1,   uint256("0x000007a097c5c7d39081c8db0a0bd761f7fe8762986b25176e4e7f530cf060b9"))
//(2,   uint256("0x00000e748deacf131b2938e6897f760e10d1f6cb602e307979016e994f698c74"))
//(3,   uint256("0x0000056774b60b27cc143cc97dc12e8eb46ab6fe173334ab2be575bc1c7034ff"))
//(4,   uint256("0x0000049878b71516dec88ecd2286835b60ec65693f9955270ac7868faab2ab59"))
//(5,   uint256("0x000009c0fe674603a6a87b0d6494b86b6c0068f6963bbb91d6b82726b71b377b"))
//(10,  uint256("0x000003ae896b5536090fac7560503e6723384a3de2d494cfd1c8ef71c2b2fc2b"))
//(20,  uint256("0x00000c80336603397e9dbb0991a5e3593c0f3eb22cdb1631c30d145d20fe05af"))
//(30,  uint256("0x00000e2e1129ee59eaede9e080bf4679bee48f0b7cf32c2344cb290307455c32"))
//(50,  uint256("0x000006e7cd4a604887cd4b674c38ee7cfa1f6f9f7a23fe139b23d46c1709d9c8"))
//(80,  uint256("0x000004753bb4c6478432cf411a596ed71fe47a2bcc08a2a745ccd24c3bbca725"))
//(100, uint256("0x0000001da15b0f22045eab712e20a07b7e8f9cc5ad563072f3b068b43abebe74"))
;


    bool CheckBlock(int nHeight, const uint256& hash)
    {
        if (fTestNet) return true; // Testnet has no checkpoints

        MapCheckpoints::const_iterator i = mapCheckpoints.find(nHeight);
        if (i == mapCheckpoints.end()) return true;
        return hash == i->second;
//return true;
    }

    int GetTotalBlocksEstimate()
    {
        if (fTestNet) return 0;

        return mapCheckpoints.rbegin()->first;
//return 0;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        if (fTestNet) return NULL;

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, mapCheckpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
           return t->second;
//return NULL;
        }
        return NULL;
    }
}
