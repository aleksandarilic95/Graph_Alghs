#pragma once
template <typename T>
class Node
{
public:
	Node() : _val(T()) {}
	Node(T val) : _val(val) {}
	Node(const Node<T>& t) = default;
	Node<T>& operator= (const Node<T>& t) = default;

	Node(Node<T>&& t) = default;
	Node<T>& operator= (Node<T>&& t) = default;

	~Node() = default;

	T getValue() const { return _val; }

	friend bool operator== (const Node<T>& lhs, const Node<T>& rhs) {
		return lhs._val == rhs._val;
	}
private:
	T _val;
};

