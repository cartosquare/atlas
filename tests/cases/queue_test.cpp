#include "catch.hpp"

#include "queue1.hpp"
#include "queue2.hpp"


TEST_CASE("queue", "[queue]") {
    
    SECTION("queue1") {
        atlas::Queue1<std::string> q;
        q.EnQueue("to");
        q.EnQueue("be");
        q.EnQueue("or");
        q.EnQueue("not");
        q.EnQueue("to");
        
        REQUIRE(q.DeQueue() == "to");
        q.EnQueue("be");
        REQUIRE(q.DeQueue() == "be");
    }
    SECTION("queue2") {
        atlas::Queue2<std::string> q;
        q.EnQueue("to");
        q.EnQueue("be");
        q.EnQueue("or");
        q.EnQueue("not");
        q.EnQueue("to");
        
        REQUIRE(q.DeQueue() == "to");
        q.EnQueue("be");
        REQUIRE(q.DeQueue() == "be");
    }
}
