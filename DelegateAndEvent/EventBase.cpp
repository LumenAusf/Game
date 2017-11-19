
#include "EventBase.h"

class RealIterator: public EventBase::Iterator
{
public:
	RealIterator(EventBase::Node *node);
	virtual bool HasNext() const;
	virtual Delegate& GetNext();

private:
	EventBase::Node *_node;
};

RealIterator::RealIterator(EventBase::Node *node)
: _node(node)
{
}

bool RealIterator::HasNext() const
{
	return (_node) ? true : false;
}

Delegate& RealIterator::GetNext()
{
	Delegate &deleg = _node->_data;
	_node = _node->_next;

	return deleg;
}

void EventBase::Push(const Delegate &data)
{
	Node *node = new Node(data, _head);
	node->_next = _head;
	_head = node;
}

void EventBase::Remove(const Delegate &data)
{
	Node *node = _head, *h = 0;

	while (node != 0)
	{
		if (node->_data != data)
		{
			Node *n = new Node(node->_data, h);
			n->_next = h;
			h = n;
		}

		node = node->_next;
	}

	delete _head;
	_head = h;
}

EventBase::Iterator* EventBase::GetIterator() const
{
	return new RealIterator(_head);
}