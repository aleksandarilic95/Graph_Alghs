#pragma once
template <typename T>
class Node
{
public:
	Node() : m_value_(T()) {}
	Node(T val) : m_value_(val) {}
	Node(const Node<T>& t) = default;
	Node<T>& operator= (const Node<T>& t) = default;

	Node(Node<T>&& t) = default;
	Node<T>& operator= (Node<T>&& t) = default;

	~Node() = default;

	T getValue() const { return m_value_; }

	friend bool operator== (const Node<T>& lhs, const Node<T>& rhs) {
		return lhs.m_value_ == rhs.m_value_;
	}
private:
	T m_value_;
};

