#pragma once

#include "tokenizer.hpp"

#include <memory>
#include <string>
#include <vector>

namespace pad::parser {

class Node {
public:
  virtual ~Node() = default;

  Node(const Node &) = delete;
  Node(Node &&) = delete;
  Node &operator=(const Node &) = delete;
  Node &operator=(Node &&) = delete;

  [[nodiscard]] virtual std::unique_ptr<Node> Eval() const = 0;
  [[nodiscard]] virtual std::string ToString() const = 0;

  Node *parent() const;
  const std::vector<std::unique_ptr<Node>> &children() const;
  const tokenizer::Token &token() const;

  void AddChild(std::unique_ptr<Node> child);

protected:
  explicit Node(const tokenizer::Token &token);

private:
  Node *parent_ = nullptr;
  std::vector<std::unique_ptr<Node>> children_;
  const tokenizer::Token &token_;
};

class NodeId : public Node {
public:
  explicit NodeId(const tokenizer::Token &token);

  [[nodiscard]] std::unique_ptr<Node> Eval() const override;
  [[nodiscard]] std::string ToString() const override;
};

[[nodiscard]] std::string Parse(const std::vector<tokenizer::Token> &tokens);

} // namespace pad::parser

namespace std {
inline string to_string(const pad::parser::Node &node) {
  return node.ToString();
}
} // namespace std
