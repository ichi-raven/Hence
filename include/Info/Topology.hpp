/*****************************************************************//**
 * @file   Topology.hpp
 * @brief  Topology列挙型のヘッダファイル
 * 
 * @author ichi-raven
 * @date   March 2023
 *********************************************************************/
#ifndef HENCE_INFO_TOPOLOGY_HPP_
#define HENCE_INFO_TOPOLOGY_HPP_

namespace Hence
{
    enum class Topology
    {
        PointList = 0,
        LineList = 1,
        LineStrip = 2,
        TriangleList = 3,
        TriangleStrip = 4,
        TriangleFan = 5,
        LineListWithAdjacency = 6,
        LineStripWithAdjacency = 7,
        TriangleListWithAdjacency = 8,
        TriangleStripWithAdjacency = 9,
        PatchList = 10,
    };
}

#endif
