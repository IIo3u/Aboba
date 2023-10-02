#include <iostream>


using namespace std;

template<typename SomeType>
class List
{
private:
	template<typename SomeType>
	class Node
	{
	public:
		Node* PreviousAddress;
		Node* NextAddress;
		SomeType data;

		Node(SomeType data = SomeType())
		{
			this->data = data;
			this->NextAddress = this->PreviousAddress = nullptr;
		}
	};

	
	Node<SomeType>* Head;
	Node<SomeType>* Tail;
	int Size;

	void add_first(SomeType data);
	void pop_low();
	void pop_top();
	

public:
	SomeType& get_low();
	SomeType& get_top();
	List();
	void add_on_position(int index, SomeType data);
	void append(SomeType data);
	void add_front(SomeType data);
	void pop_element(int index);
	void pop_element(Node<SomeType>* data);
	int get_size() { return Size; };
	SomeType& operator[](int index);
	

};

template<typename SomeType>
List<SomeType>::List()
{
	Size = 0;
	Head = Tail = nullptr;

};

template<typename SomeType>
void List<SomeType>::add_first(SomeType data)
{
	Tail = new Node<SomeType>(data);
	Head = Tail;
}

template<typename SomeType>
void List<SomeType>::add_on_position(int index, SomeType data) 
{
	if (index == 0) 
	{
		this->add_front(data);
	}
	else 
	{
		if (index == this->Size)

		{
			this->append(data);
		}
		else
		{

			int counter = 0;
			Node<SomeType>* NewNode = new Node<SomeType>;
			NewNode->data = data;
			Node<SomeType>* Current = this->Head;
			Node<SomeType>* Previous = nullptr;
			Node<SomeType>* Next = nullptr;
			while (counter != index)
			{
				Current = Current->NextAddress;
			}
			Next = Current->NextAddress;
			Previous = Current;
			Current = NewNode;
			Current->NextAddress = Next;
			Current->PreviousAddress = Previous;
			Previous->NextAddress = Current;
			Next->PreviousAddress = Current;
			this->Size++;
		}
	}
}

template<typename SomeType>
void List<SomeType>::append(SomeType data)
{	
	if (this->Tail == nullptr)
	{
		this->add_first(data);
	}
	else
	{
		Node<SomeType>* Previous;
		Node<SomeType>* Current = this->Tail;
		Current->NextAddress = new Node<SomeType>(data);
		Previous = Current;
		Current = Current->NextAddress;
		Current->PreviousAddress = Previous;
		this->Tail = Current;
	}
	Size++;
}

template<typename SomeType>
void List<SomeType>::add_front(SomeType data)
{
	if (Head == nullptr)
	{
		this->add_first(data);
	}
	else
	{
		Node<SomeType>* Next;
		Node<SomeType>* Current = this->Head;
		Current->PreviousAddress = new Node<SomeType>(data);
		Next = Current;
		Current = Current->PreviousAddress;
		Current->NextAddress = Next;
		this->Head = Current;
	}
	Size++;
}

template<typename SomeType>
void List<SomeType>::pop_element(int index)
{
	
	if (this->get_size() == 0)
	{
		cout << "This list has no elements!\n";
		return;
	}
	if (this->get_size() == 1)
	{
		delete this->Head;
		this->Size--;
		return;
	}
	if (index == this->Size) 
	{
		this->pop_low();
		return;
	}
	if (index == 0) 
	{
		this->pop_top();
	}
	else 
	{
		int counter = 0;
		Node<SomeType>* Previous = nullptr;
		Node<SomeType>* Current = Head;
		Node<SomeType>* Next = nullptr;
		while (counter != index)
		{
			Current = Current->NextAddress;
			counter++;
		}
		Previous = Current->PreviousAddress;
		Next = Current->NextAddress;
		if (Previous != nullptr)
		{
			Previous->NextAddress = Next;
		}

		if (Next != nullptr)
		{
			Next->PreviousAddress = Previous;
		}
		delete Current;
		Size--;
	}
	
}

template<typename SomeType>
void List<SomeType>::pop_element(Node<SomeType>* Data)
{
	if (this->get_size() == 0)
	{
		cout << "This list has no elements!\n";
		return;

		if (this->get_size() == 1)
		{
			delete this->Head;
			this->Size--;
			return;
		}
	}
	Node<SomeType>* Previous = nullptr;
	Node<SomeType>* Current = Data;
	Node<SomeType>* Next = nullptr;
	Previous = Current->PreviousAddress;
	Next = Current->NextAddress;
	if (Previous != nullptr)
	{
		Previous->NextAddress = Next;
	}

	if (Next != nullptr)
	{
		Next->PreviousAddress = Previous;
	};
	delete Current;
	Size--;
}

template<typename SomeType>
void List<SomeType>::pop_top()
{
	if (this->get_size() == 0)
	{
		cout << "This list has no elements!\n";
		return;
	}
	if (this->get_size() == 1)
	{
		delete this->Head;
		this->Size--;
		return;
	}
	Node<SomeType>* Current = Head;
	Current = Current->NextAddress;
	this->Head = Current;
	delete Current->PreviousAddress;
	Current->PreviousAddress = nullptr;
	this->Size--;
};

template<typename SomeType>
void List<SomeType>::pop_low()
{
	if (this->get_size() == 0)
	{
		cout << "This list has no elements!\n";
		return;
	}
	if (this->get_size() == 1)
	{
		delete this->Tail;
		this->Size--;
		return;

	}
	Node<SomeType>* Current = Tail;
	Current = Current->PreviousAddress;
	this->Tail = Current;
	delete Current->NextAddress;
	Current->NextAddress = nullptr;
	this->Size--;
};

template<typename SomeType>
SomeType& List<SomeType>::get_low()
{
	return this->Tail->data;
};

template<typename SomeType>
SomeType& List<SomeType>::get_top()
{
	return this->Head->data;
};

template<typename SomeType>
SomeType& List<SomeType>::operator[](int index)
{
	if (index == 0)
	{
		return this->get_top();

	}
	else
	{
		if (index == this->Size - 1)
		{
			return this->get_low();
		}
		else
		{
			int counter = 0;
			Node<SomeType>* Current = this->Head;
			while (Current != nullptr)
			{
				if (counter == index)
				{
					return Current->data;
				}
				Current = Current->NextAddress;
				counter++;
			}
		}
		
	}
};

template<typename SomeType>
List<SomeType>& Copy(List<SomeType>* OldList)
{
	List<SomeType>* NewList = new List<SomeType>;
	for (int i = 0; i < OldList.get_size(); i++)
	{
		NewList->append(OldList.get_low());
	}
}


template<typename SomeType>
class Matrix
{
public:
	List<SomeType> Data;
	int Size;

	Matrix();
	


	
	
	
};

template<typename SomeType>
Matrix<SomeType>::Matrix()
{
	Data;
	Size = 0;

};

int main()
{
	int size;
	cout << "Enter your matrix size: ";
	cin >> size;

	List<int> DataList;

	cout << "Input Your Data:" << endl;

	char buffer;
	for (int i = 0; i < size; i++) 
	{
		for (int j = 0; j < size; j++) 
		{
			cin >> buffer;
			DataList.append((int)buffer - 48);
		}
		cout << endl;
	}

	

	
	Matrix<int> NewMa;
	NewMa.Data = DataList;
	
	cout << "Your DataList: ";
	for (int i = 0; i < size*size; i++) 
	{
		cout << NewMa.Data[i] << ' ';
	}











	/*List<int>* firstRow = new List<int>;
	firstRow->append(13);
	List<List<int>*> Matrix;
	Matrix.append(firstRow);
	int c = 13;

	cout << Matrix[0]->get_top();
	*/




}
	
	