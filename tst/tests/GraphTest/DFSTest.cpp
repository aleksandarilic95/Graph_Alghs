#include "DFSTest.h"

TEST_F(DFSTest, DFSCountNodes) {
    try{
        m_graph_.DFS(0, dta);
        size_t l_result = dta.get_result();
        EXPECT_EQ(l_result, m_graph_.size());
    }
    catch(...) {
        FAIL() << "No exception was expected";
    }
}

TEST_F(DFSTest, DFSCountNodesIncomplete) {
    
    try{
        m_graph_.DFS(5, dta);
        size_t l_result = dta.get_result();
        EXPECT_NE(l_result, m_graph_.size());
    }
    catch(...) {
        FAIL() << "No exception was expected";
    }
}

TEST_F(DFSTest, DFSBadStartIndex) {
    try{
        m_graph_.DFS(7, dta);
        FAIL() << "Expected std::out_of_range";
    }
    catch(std::out_of_range const& err) {
        EXPECT_EQ(err.what(), std::string("Given index is out of range"));
    }
    catch(...) {
        FAIL() << "Expected std::out_of_range";
    }
}