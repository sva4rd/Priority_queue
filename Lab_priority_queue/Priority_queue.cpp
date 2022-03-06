#include "Priority_queue.h"

void Priority_queue::Erase()
{
	while (Pop());
	size = { 0,0,0 };
}

void Priority_queue::Clone(const Priority_queue& Q)
{
	QItem* tmp = Q.front;
	for (unsigned i = 0; i < Q.GetSize(); i++)
	{
		Push(tmp->value, tmp->priority);
		tmp = tmp->next;
	}
}

void Priority_queue::move(QItem*& a, QItem*& b)
{
	a = b;
	b = nullptr;
}

Priority_queue::Priority_queue(const Priority_queue& Q)
{
	size = { 0,0,0 };
	Clone(Q);
}

Priority_queue::Priority_queue(Priority_queue&& other) noexcept
{
	move(front, other.front);
	move(rear, other.rear);
	move(rear_high, other.rear_high);
	move(rear_medium, other.rear_medium);
	move(rear_low, other.rear_low);
	size = other.size;
	other.size = { 0,0,0 };
}

Priority_queue::~Priority_queue()
{
	Erase();
}

Priority_queue& Priority_queue::operator = (const Priority_queue& Q)
{
	if (this != &Q) 
	{
		Erase();
		Clone(Q);
	}
	return *this;
}

Priority_queue& Priority_queue::operator=(Priority_queue&& other) noexcept
{
	if (&other == this)
		return *this;
	Erase();
	move(front, other.front);
	move(rear, other.rear);
	move(rear_high, other.rear_high);
	move(rear_medium, other.rear_medium);
	move(rear_low, other.rear_low);
	size = other.size;
	other.size = { 0,0,0 };
	return *this;
}

void Priority_queue::Push(int Ainfo, Priority element_prior)
{
	QItem* tmp = new QItem(Ainfo, element_prior);
	if (this->GetSize() > 0)
	{
		if (element_prior == Priority::high)
		{
			if (rear_high != nullptr && rear_high != rear)
			{
				tmp->next = rear_high->next;
				rear_high->next = tmp;
				rear_high = tmp;
			}

			if (rear_high == nullptr)
			{
				tmp->next = front;
				front = tmp;
				rear_high = tmp;
			}

			if (rear_high == rear)
			{
				rear->next = tmp;
				rear = tmp;
				rear_high = tmp;
			}

			size[0]++;
		}


		if (element_prior == Priority::medium)
		{
			if (rear_medium != rear && rear_medium != nullptr)
			{
				tmp->next = rear_medium->next;
				rear_medium->next = tmp;
				rear_medium = tmp;
			}

			if (rear_medium == nullptr)
			{
				rear_medium = tmp;
				if (rear_high == nullptr)
				{
					tmp->next = front;
					front = tmp;
				}
				else
				{
					tmp->next = rear_high->next;
					rear_high->next = tmp;
				}
			}

			if (rear_medium == rear)
			{
				rear->next = tmp;
				rear = tmp;
				rear_medium = rear;
			}

			size[1]++;
		}


		if (element_prior == Priority::low)
		{
			if (rear_low != rear && rear_low != nullptr)
			{
				tmp->next = rear_low->next;
				rear_low->next = tmp;
				rear_low = tmp;
			}

			if (rear_low == nullptr)
			{
				rear_low = tmp;
				if (rear_medium == nullptr)
				{
					tmp->next = rear_high->next;
					rear_high->next = tmp;
				}
				else
				{
					tmp->next = rear_medium->next;
					rear_medium->next = tmp;
				}
			}

			if (rear_low == rear)
			{
				rear->next = tmp;
				rear = tmp;
				rear_low = tmp;
			}	

			size[2]++;
		}

		if (rear->next == tmp)
			rear = tmp;
	}
	else
	{
		front = tmp;
		rear = tmp;
		if (element_prior == Priority::high)
		{
			rear_high = tmp;
			size[0]++;
			rear_medium = nullptr;
			rear_low = nullptr;
		}
		if (element_prior == Priority::medium)
		{
			rear_medium = tmp;
			size[1]++;
			rear_high = nullptr;
			rear_low = nullptr;
		}
		if (element_prior == Priority::low)
		{
			rear_low = tmp;
			size[2]++;
			rear_medium = nullptr;
			rear_high = nullptr;
		}
	}
}

bool Priority_queue::Pop()
{
	if (this->IsEmpty())
		return false;
	QItem* tmp = front;
	front = front->next;
	delete tmp;
	
	if (size[0] == 0 && size[1] == 0)
	{
		size[2]--;
		if (size[2] == 0)
			rear_low = nullptr;
	}
	if (size[1] != 0 && size[0] == 0)
	{
		size[1]--;
		if (size[1] == 0)
			rear_medium = nullptr;
	}
	if (size[0] != 0)
	{
		size[0]--;
		if (size[0] == 0)
			rear_high = nullptr;
	}

	if (this->IsEmpty())
		rear = nullptr;
	return true;
}

int Priority_queue::GetFirst() const
{
	if (this->IsEmpty())
		throw exception("Невозможно выполнить GetFirst: очередь пуста");//Impossible to execute GetFirst: queue is empty
	
	return front->value;
}

Priority Priority_queue::GetFirstPriority() const
{
	if (this->IsEmpty())
		throw exception("Невозможно выполнить GetFirst: очередь пуста");//Impossible to execute GetFirst: queue is empty

	return front->priority;
}

bool Priority_queue::IsEmpty() const
{
	return (this->GetSize() == 0);
}

unsigned Priority_queue::GetSize(Priority element_prior) const
{
	if (element_prior == Priority::high)
		return size[0];
	if (element_prior == Priority::medium)
		return size[1];
	if (element_prior == Priority::low)
		return size[2];
}

unsigned Priority_queue::GetSize() const
{
	return (size[0] + size[1] + size[2]);
}

void Priority_queue::Browse(void ItemWork(int)) const
{
	if (this->IsEmpty())
		throw exception("Данная очередь пуста!");

	QItem* tmp = front;
	for (unsigned i = 0; i < this->GetSize(); i++)
	{
		ItemWork(tmp->value);
		tmp = tmp->next;
	}
}