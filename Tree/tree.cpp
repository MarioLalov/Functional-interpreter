#include "tree.h"

NumberNode::NumberNode(float data)
{
    number = data;
}

SyntaxTree::SyntaxTree(std::string &expresion)
{
    std::size_t cnt = expresion.find("->");
    tree_name = expresion.substr(0, cnt);
    root = new FunctionNode(tree_name);

    while (cnt < expresion.size())
    {
        //get type
        std::size_t cur = expresion.find("(");

        if (cur != std::string::npos)
        {
            std::string name = expresion.substr(cnt, cur - cnt);
            //get function from list
            FunctionNode *fun = nullptr;
            //new Node(fun);
        }
    }
}

std::vector<Node *> ListNode::getChildren()
{
    return children;
}

std::vector<Node *> FunctionNode::getChildren()
{
    return children;
}

std::vector<Node *> NumberNode::getChildren()
{
    std::vector<Node *> empty;
    return empty;
}

void SyntaxTree::insertArgs(Node *current, std::queue<float>& arguments)
{
    if (typeid(current).hash_code() == typeid(NumberNode *).hash_code())
    {
        NumberNode *num = dynamic_cast<NumberNode *>(current);
        //assign arguments.pop()
    }

    std::vector<Node*> children = current->getChildren();
    for(std::size_t i = 0; i < children.size(); i++)
    {
        insertArgs(children[i], arguments);
    }

}
