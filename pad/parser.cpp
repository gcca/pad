#include "parser.hpp"

namespace pad::parser {

Node::Node(const tokenizer::Token &token) : token_(token) {}

Node *Node::parent() const { return parent_; }

const std::vector<std::unique_ptr<Node>> &Node::children() const {
  return children_;
}

const tokenizer::Token &Node::token() const { return token_; }

void Node::AddChild(std::unique_ptr<Node> child) {
  child->parent_ = this;
  children_.push_back(std::move(child));
}

NodeId::NodeId(const tokenizer::Token &token) : Node(token) {}

std::unique_ptr<Node> NodeId::Eval() const {
  return std::make_unique<NodeId>(token());
}

std::string NodeId::ToString() const { return std::string(token().text()); }

std::string Parse(const std::vector<tokenizer::Token> &tokens) {
  std::string result;
  for (const auto &token : tokens) {
    NodeId node(token);
    if (!result.empty()) result += " ";
    result += std::to_string(node);
  }
  return result;
}

} // namespace pad::parser
