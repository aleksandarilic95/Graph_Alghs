#include "GetNodeIdxTest.h"

TEST_F(GetNodeIdxTest, GetNodeNotFound) {
    int l_node_idx = m_graph_.get_node_idx(6);
    EXPECT_EQ(l_node_idx, -1);
};

TEST_F(GetNodeIdxTest, GetNodeFound) {
    int l_node_idx = m_graph_.get_node_idx(3);
    EXPECT_EQ(l_node_idx, 3);
};