#pragma once
#include <iostream>
#include <vector>
using namespace std;

enum class Priority { low , medium , high };

class Priority_queue
{
private:
	struct QItem
	{
		int value;
		Priority priority;
		QItem* next;
		QItem(int Avalue, Priority element_prior) : value(Avalue), priority(element_prior), next(nullptr) {}
	};
	vector<int>size;
	QItem* front, * rear;
	QItem* rear_low, * rear_medium, * rear_high;

	void Erase();
	void Clone(const Priority_queue&);
	void move(QItem*&, QItem*&);

public:
	Priority_queue() : size({ 0,0,0 }), front(nullptr), rear(nullptr), rear_low(NULL), rear_medium(nullptr), rear_high(nullptr) {};

	Priority_queue(const Priority_queue&);
	Priority_queue(Priority_queue&&) noexcept;

	Priority_queue& operator = (const Priority_queue&);
	Priority_queue& operator = (Priority_queue&&) noexcept;

	~Priority_queue();

	void Push(int AInfo, Priority element_prior);
	bool Pop();
	int GetFirst() const;
	Priority GetFirstPriority() const;
	bool IsEmpty()const;
	unsigned GetSize() const;
	unsigned GetSize(Priority element_prior) const;

	void Browse(void ItemWork(int)) const;
};