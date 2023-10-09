#include <iostream>


using namespace std;



// List

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
		

public:
	
	List();
	void add_first(SomeType data);
	void add_on_pos_right(int index, SomeType data);
	void add_on_pos_left(int index, SomeType data);
	void append(SomeType data);
	void add_front(SomeType data);
	void pop_element(int index);
	void pop_top();
	void pop_low();
	SomeType& get_low();
	SomeType& get_top();
	int get_size() { return Size; };
	SomeType& operator[](int index);
	

};
template<typename SomeType>
void List<SomeType>::add_first(SomeType data)
{
	Tail = new Node<SomeType>(data);
	Head = Tail;
	this->Size++;
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
List<SomeType>::List()
{
	Size = 0;
	Head = Tail = nullptr;

};

template<typename SomeType>
void List<SomeType>::add_on_pos_right(int index, SomeType data) 
{
	if (this->get_size() == 0)
	{
		this->add_first(data);
	}
	else 
	{
		if (index == this->Size-1) 
		{
			this->append(data);
		}
		else
		{
			int counter = 0;
			Node<SomeType>* NewNode = new Node<SomeType>(data);
			Node<SomeType>* Current = this->Head;
			while (index != counter) 
			{
				Current = Current->NextAddress;
				counter++;
			}
			Node<SomeType>* Previous = Current;
			Node<SomeType>* Next = Current->NextAddress;
			Current = NewNode;
			Previous->NextAddress = Current;
			Current->NextAddress = Next;
			Next->PreviousAddress = Current;
			Current->PreviousAddress = Previous;
			this->Size++;
		}
	}
}

template<typename SomeType>
void List<SomeType>::add_on_pos_left(int index, SomeType data) 
{
	if (this->get_size() == 0)
	{
		this->add_first(data);
	}
	else
	{
		if (index == 0)
		{
			this->add_front(data);
		}
		else
		{
			int counter = 0;
			Node<SomeType>* NewNode = new Node<SomeType>(data);
			Node<SomeType>* Current = this->Head;
			while (index != counter)
			{
				Current = Current->NextAddress;
				counter++;
			}
			Node<SomeType>* Next = Current;
			Node<SomeType>* Previous = Current->PreviousAddress;
			Current = NewNode;
			Next->PreviousAddress = Current;
			Current->PreviousAddress = Previous;
			Previous->NextAddress = Current;
			Current->NextAddress = Next;
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
		return;
	}
	else
	{
		this->Tail->NextAddress = new Node<SomeType>(data);
		Node<SomeType>* Buffer = this->Tail;
		this->Tail = this->Tail->NextAddress;
		this->Tail->PreviousAddress = Buffer;
		Size++;
	}
	
}

template<typename SomeType>
void List<SomeType>::add_front(SomeType data)
{
	if (Head == nullptr)
	{
		this->add_first(data);
		return;
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
		Size++;
	}
	
}

template<typename SomeType>
void List<SomeType>::pop_element(int index)
{
	
	if (this->get_size() == 0)
	{
		return;
	}
	if (this->get_size() == 1)
	{
		delete this->Head;
		this->Size--;
		return;
	}
	if (index == this->Size - 1) 
	{
		Node<SomeType>* Current = Tail;
		Current = Current->PreviousAddress;
		this->Tail = Current;
		delete Current->NextAddress;
		Current->NextAddress = nullptr;
		this->Size--;
		return;
	}
	if (index == 0) 
	{
		Node<SomeType>* Current = Head;
		Current = Current->NextAddress;
		this->Head = Current;
		delete Current->PreviousAddress;
		Current->PreviousAddress = nullptr;
		this->Size--;
		return;
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
		this->Size--;
	}
	
}

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
		return this->Head->data;

	}
	else
	{
		if (index == this->Size - 1)
		{
			return this->Tail->data;
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



// Matrix


class CCS_Matrix
{
public:
	List<int> Data;
	List<int> LI;
	List<int> LJ;
	int Size;

	CCS_Matrix();
	void Input(List<int> InputList, int Size);
	int get(int i, int j);
	void set(int i, int j, int data);
	void Shift();
	
};

CCS_Matrix::CCS_Matrix()
{
	Size = 0;
};

void CCS_Matrix::Input(List<int> InputList, int Size) 
{
	int Column_Index = 0;
	int current_stroke = 1;
	int column_start = 0;
	
	for (int column = 0; column < Size; column++) 
	{
		LJ.append(Column_Index);
		for (int number = column; number < InputList.get_size(); number = number + Size) 
		{
			
			if (InputList[number] != 0) 
			{
				Data.append(InputList[number]);
				LI.append(current_stroke);
				Column_Index++;
			}
			current_stroke++;
		}
		current_stroke = 1;
		
	}
	LJ.append(Column_Index);
};

int CCS_Matrix::get(int i, int j) 
{
	
	int AA = 0;
	
	int N1 = LJ[j-1];
	int N2 = LJ[j];
	for (int counter = N1; counter < N2; counter++)
	{	
		if (LI[counter] == i)
		{
			AA = this->Data[counter];
			break;
		}		
	}
	return AA;
}

void CCS_Matrix::set(int i, int j, int data) 
{
	int N1 = LJ[j - 1];
	int N2 = LJ[j];
	bool flag = false;
	for (int counter = N1; counter < N2; counter ++) 
	{
		if (LI[counter] == i) 
		{
			this->Data[counter] = data;
			flag = true;
			return;
		}
	}
	if (flag == false) 
	{
		for (int counter = N1; counter < N2; counter ++) 
		{
			if (LI[counter] > i) 
			{
				LI.add_on_pos_left(counter, i);
				Data.add_on_pos_left(counter, data);
				for (int column = j; column < LJ.get_size(); column++)
				{
					LJ[column] += 1;
				}
				return;
			}
		}
		LI.add_on_pos_left(N2, i);
		Data.add_on_pos_left(N2, data);
		for (int column = j; column < LJ.get_size(); column++) 
		{
			LJ[column] += 1;
		}
	}
	
}

void CCS_Matrix::Shift() 
{
	

}



int main()
{
	

	int size;
	cout << "Enter your matrix size (x*x) : ";
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

	cout << "Your DataList:" << endl;


	for (int i = 0; i < DataList.get_size(); i++)
	{
		cout << DataList[i];
	}

	CCS_Matrix NewMa;
	NewMa.Input(DataList, size);

	cout << endl;
	

	for (int i = 0; i < NewMa.Data.get_size(); i++)
	{
		cout << NewMa.Data[i];
	}

	cout << endl;

	for (int i = 0; i < NewMa.LI.get_size(); i++)
	{
		cout << NewMa.LI[i];
	}

	cout << endl;

	for (int i = 0; i < NewMa.LJ.get_size(); i++)
	{
		cout << NewMa.LJ[i] << ' ';
	}
	
	
	for (int i = 1; i < size + 1; i++ ) 
	{
		for (int j = 1; j < size + 1; j++) 
		{
			NewMa.set(i, j, 3);
		}
	}
	
	
	cout << endl;
	cout << endl;
	
	cout << "Output Matrix:" << endl;
	for (int i = 1; i <= size; i++) 
	{
		for (int j = 1; j <= size; j++) 
		{
			cout << NewMa.get(i, j) << ' ';
		}
		cout << endl;
	}

	
	
}
	
	