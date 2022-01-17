#include "tree.h"

DeclarationManager *DeclarationManager::instance = nullptr;

DeclarationManager::DeclarationManager()
{
}

DeclarationManager *DeclarationManager::getInstance()
{
    if(!instance)
        instance = new DeclarationManager();

    return instance;
}

Node* DeclarationManager::search(std::string& name) const
{
    for(std::size_t i = 0; i < declared_functions.size(); i++)
    {
        if(name == declared_functions[i].first)
        {
            return declared_functions[i].second;
        }
    }

    return nullptr;
}

void DeclarationManager::declare(std::string& expression)
{
    std::size_t end = expression.find("->");
    std::string fun_name = expression.substr(0, end);
    std::size_t begin = end;

    std::vector<Node*> children;

    while(begin < expression.size())
    {
        std::size_t end = expression.find("(");
        std::string in_fun_name = expression.substr(begin, end - begin);

        Node* cur = search(in_fun_name);
        if(cur)
        {
            //throw
        }

        children.push_back(cur);
        

        
    }


}

FunctionNode::FunctionNode(std::string in_name, std::vector<Node *> in_children)
{
    name = in_name;
    children = in_children;
}

NumberNode::NumberNode(float data)
{
    number = data;
}
/*
SyntaxTree::SyntaxTree(std::string &expresion)
{
    std::size_t cnt = expresion.find("->");
    tree_name = expresion.substr(0, cnt);
    root = new FunctionNode(tree_name);

    while (cnt < expresion.size())
    {
        // get type
        std::size_t cur = expresion.find("(");

        if (cur != std::string::npos)
        {
            std::string name = expresion.substr(cnt, cur - cnt);
            // get function from list
            FunctionNode *fun = nullptr;
            // new Node(fun);
        }
    }
}
*/
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

void NumberNode::setValue(float data)
{
    number = data;
}

// fun([1, 2, 3], 3)

/*     fun
      /   \
  [1,2,3]  3
*/
