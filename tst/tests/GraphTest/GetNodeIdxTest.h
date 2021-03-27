#ifndef GET_NODE_IDX_TEST_H
#define GET_NODE_IDX_TEST_H

#include "gtest/gtest.h"
#include "Graph/Graph.h"

class GetNodeIdxTest : public ::testing::Test {
protected:
    GetNodeIdxTest() {
        m_graph_.add_node({0,1,2,3,4,5});
        m_graph_.add_edge(0, 1, 1).add_edge(0, 2, 7).add_edge(0, 3, 6).add_edge(1, 3, 4).add_edge(1, 4, 1).add_edge(2, 5, 2).add_edge(3, 2, 3).add_edge(3, 5, 2).add_edge(4, 3, 2).add_edge(4, 5, 1);
    }

    Graph<int,int> m_graph_;
};

#endif