#include "catch.hpp"
#include "stack1.hpp"
#include "stack2.hpp"

TEST_CASE("stack", "[stack]") {
    
    SECTION("stack1") {
        atlas::Stack1<std::string> s;
        s.Push("to");
        s.Push("be");
        s.Push("or");
        s.Push("not");
        s.Push("to");
        REQUIRE(s.Pop() == "to");
        s.Push("be");
        REQUIRE(s.Pop() == "be");
        REQUIRE(s.Pop() == "not");
        s.Push("that");
        REQUIRE(s.Pop() == "that");
        REQUIRE(s.Pop() == "or");
        REQUIRE(s.Pop() == "be");
    }
    SECTION("stack2") {
        atlas::Stack2<std::string> s;
        s.Push("to");
        s.Push("be");
        s.Push("or");
        s.Push("not");
        s.Push("to");
        REQUIRE(s.Pop() == "to");
        s.Push("be");
        REQUIRE(s.Pop() == "be");
        REQUIRE(s.Pop() == "not");
        s.Push("that");
        REQUIRE(s.Pop() == "that");
        REQUIRE(s.Pop() == "or");
        REQUIRE(s.Pop() == "be");
    }
    
    SECTION("evaluation") {
        atlas::Stack2<int> value_stack;
        atlas::Stack2<char> operator_stack;
        std::string exp = "(1+((2+3)*(4*5))))";
        
        for (size_t i = 0; i < exp.length(); ++i) {
            if (exp[i] == '(') {
                // do nothing
            } else if (exp[i] == '+' || exp[i] == '*') {
                operator_stack.Push(exp[i]);
            } else if (exp[i] == ')') {
                if (!operator_stack.isEmpty()) {
                    char opr = operator_stack.Pop();
                    if (opr == '+') {
                        value_stack.Push(value_stack.Pop() + value_stack.Pop());
                    } else if (opr == '*') {
                        value_stack.Push(value_stack.Pop() * value_stack.Pop());
                    }
                }
                
                
            } else {
                value_stack.Push(std::atoi(&exp[i]));
            }
        }
        
        REQUIRE(value_stack.Pop() == 101);
    }
}


