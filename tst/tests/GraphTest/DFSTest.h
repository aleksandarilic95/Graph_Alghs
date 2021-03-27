#ifndef DFS_TEST_H
#define DFS_TEST_H

#include "gtest/gtest.h"
#include "Graph/Graph.h"
#include "Algorithms/GBaseAlgorithm.h"

class DFSTest : public ::testing::Test {
protected:
    DFSTest() {
        m_graph_.add_node({0,1,2,3,4,5});
        m_graph_.add_edge(0, 1, 1).add_edge(0, 2, 7).add_edge(0, 3, 6).add_edge(1, 3, 4).add_edge(1, 4, 1).add_edge(2, 5, 2).add_edge(3, 2, 3).add_edge(3, 5, 2).add_edge(4, 3, 2).add_edge(4, 5, 1);
    }

    class DFSTestAlg : public GBaseAlgorithm<int,int> {
    public:
        void current_node_do() {
            m_node_count_++;
        }
        void start() {}
        void end() {}

        size_t get_result() const noexcept { return m_node_count_; }
    private:
        size_t m_node_count_ = 0;
    };

    Graph<int,int> m_graph_;
    DFSTestAlg dta;
};

#endif