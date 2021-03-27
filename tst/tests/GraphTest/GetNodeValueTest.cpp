#include "GetNodeValueTest.h"

TEST_F(GetNodeValueTest, GetNodeValueTestOutOfBounds) {
    try{
        int l_node_value = m_graph_.get_node_value(6);
        FAIL() << "Expected std::out_of_range";
    }
    catch(std::out_of_range const& err) {
        EXPECT_EQ(err.what(), std::string("Given index is out of range"));
    }
    catch(...) {
        FAIL() << "Expected std::out_of_range";
    }
}

TEST_F(GetNodeValueTest, GetNodeValueTestInBounds) {
    try{
        int l_node_value = m_graph_.get_node_value(3);
        EXPECT_EQ(l_node_value, 3);
    }
    catch(...) {
        FAIL() << "Expected no exceptions";
    }
}