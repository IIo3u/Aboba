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
	void add_on_pos(int index, SomeType data);
	void append(SomeType data);
	void add_front(SomeType data);
	void pop_element(int index);
	SomeType& get_low();
	SomeType& get_top();
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
void List<SomeType>::add_on_pos(int index, SomeType data) 
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
			counter++;
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

template<typename SomeType>
void List<SomeType>::append(SomeType data)
{	
	if (this->Tail == nullptr)
	{
		Tail = new Node<SomeType>(data);
		Head = Tail;
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
		Tail = new Node<SomeType>(data);
		Head = Tail;
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
		Size--;
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
	int get(int k, int m);
	void set(int k, int m, int value);
	void Shift();
	
	
};

CCS_Matrix::CCS_Matrix()
{
	Size = 0;
};


void CCS_Matrix::Input(List<int> InputList, int Size) 
{
	int Column_Index = 0;
	int current_stroke = 0;
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
		current_stroke = 0;
		
	}
	LJ.append(Column_Index);
};

int CCS_Matrix::get(int k, int m) 
{
	
	int AA = 0;
	int i = k - 1;
	int j = m - 1;
	int N1 = LJ[j];
	int N2 = LJ[j + 1];
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

void CCS_Matrix::set(int k, int m, int value) 
{
	int i = k - 1;
	int j = m - 1;
	int N1 = LJ[j];
	int N2 = LJ[j + 1];
	bool flag = false;
	for (int counter = N1; counter < N2; counter++)
	{
		if (LI[counter] == i)
		{
			this->Data[counter] = value;
			flag = true;
			break;
		}
	}
	if (flag == false) 
	{
		
		for (int counter = N1; counter < N2; counter++) 
		{
			if (i > LI[counter])
			{
				continue;
			}
			else 
			{
				Data.add_on_pos(counter - 1, value);
				LI.add_on_pos(counter - 1, i);
			}
		}
		for (int column = j + 1; column < LJ.get_size(); column++) 
		{
			LJ[column] += 1;
		}
	}
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

	cout << endl;
	

	NewMa.set(1,2, 3);

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

	cout << endl;
	cout << endl;
	cout << "Changed Matrix:" << endl;
	for (int i = 1; i <= size; i++)
	{
		for (int j = 1; j <= size; j++)
		{
			cout << NewMa.get(i, j) << ' ';
		}
		cout << endl;
	}

	

	
	




}
	
	