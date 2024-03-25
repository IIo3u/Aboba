#include <iostream>
//4yrka

using namespace std;



// List

template<typename SomeType>
class List
{
private:
	template<typename SomeType>
	class Node
	{
	public:						// ���� �������� ��� ������ �� ������� ����� �� �����, ��:
		Node* PreviousAddress;  // ��� ������ ����� (�.�. ���� � ������ ������)
		Node* NextAddress;		// ��� ������ ������ (�.�. ���� � ����� ������)
		SomeType data;

		Node(SomeType data = SomeType())
		{
			this->data = data;
			this->NextAddress = this->PreviousAddress = nullptr;
		}
	};

	
	Node<SomeType>* Head;	// ������
	Node<SomeType>* Tail; // �����
	int Size;
	void add_first(SomeType data);	// �������������� ���������� ������� ��������

public:
	
	List();
	~List();
	
	void add_on_pos_right(int index, SomeType data); // ��������� �������� ������
	void add_on_pos_left(int index, SomeType data);	 // ��������� �������� �����
	void append(SomeType data);						 // ��������� �������� ������ ���������� �������� (� ����� ������)
	void add_front(SomeType data);					 // ��������� �������� ����� ������� �������� (� ������ ������)
	void pop_element(int index);					 // ������� ������� �� ������� ������
	void pop_top();									 // ������� ��������� (Head) ������� ������
	void pop_low();									 // ������� �������� (Tail) ������� ������
	SomeType& get_low();							 // ������� ������ �� ���� data ��������� ��������
	SomeType& get_top();							 // ������� ������ �� ���� data ���������� ��������
	int get_size() { return Size; };				 // ���������� ������ ������
	SomeType& operator[](int index);				 // �������� �������������� ��� ��������� � ���� data ������ ���������
	

};


template<typename SomeType>
List<SomeType>::~List()
{
	if (this->Size != 0)
	{

		Node<SomeType>* Previous = this->Head;
		Node<SomeType>* Current = nullptr;
		while (Current != nullptr)
		{
			Current = Previous->NextAddress;
			delete Previous;
		}
		delete Current;
	}
}

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


// Matrix

template<typename SomeType>
class CCS_Matrix
{
private:
	
public:
	List<SomeType> Data;
	List<int> LI;
	List<int> LJ;
	int Size;
	CCS_Matrix();								
	void Input(List<SomeType> InputList, int Size);	// ������� �������� �������� � ������
	SomeType get(int i, int j);						// ���������� �������� � ������ ������� � �������� �������
	void set(int i, int j, SomeType data);			// ��������� �������� �������� � ������ ������� � ��������
	int get_size() { return this->Size; }		// ���������� ������ �������
	void Shift();								// �������� �������� ������� �� 1 ������
	
};

template<typename SomeType>
CCS_Matrix<SomeType>::CCS_Matrix()
{
	Size = 0;
};

template<typename SomeType>
void CCS_Matrix<SomeType>::Input(List<SomeType> InputList, int Size) 
{
	int Column_Index = 0;
	int current_stroke = 1;
	int column_start = 0;
	this->Size = Size;

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

template<typename SomeType>
SomeType CCS_Matrix<SomeType>::get(int i, int j) 
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

template<typename SomeType>
void CCS_Matrix<SomeType>::set(int i, int j, SomeType data)
{
	int N1 = LJ[j - 1];
	int N2 = LJ[j];
	bool flag;
	if (data == 0)		// ����������� ����, ��� ��� ����� ������� ���������� �� ������� � ������ �������
	{
		if (N1 == N2) // ��� �������� ��� ��������� � ������ ������� ��� � ��� �� �������
		{
			return;
		}
		for (int counter = N1; counter < N2; counter++)
		{
			
			if (LI[counter] == i) // ���� ������ ������� �� ������ ����� ������, �� �� ������� ��� ���������� � ��:
			{
				this->Data.pop_element(counter);
				this->LI.pop_element(counter);
				for (int column = j; column < LJ.get_size(); column++)
				{				
					if (LJ[column] > 0)
					{
						LJ[column] -= 1;
					}					
				}
				return;					
			}			
		}	
		
	}
	if (N1 == N2 && N2 != 0) // ��������, ����� ��� ����� �������� ������� �� ������ ������, �� ��������� � ������� ���:
	{
		Data.add_on_pos_right(N2 - 1, data);
		LI.add_on_pos_right(N2 - 1, i);
		for (int column = j; column < LJ.get_size(); column++)
		{
			LJ[column] += 1;
		}
		return;
	}
	flag = false;
	for (int counter = N1; counter < N2; counter ++)  // ����������� ��������, ����� ��� ����� �������� �������, ������� ��� ����� ��������:
	{
		if (LI[counter] == i) 
		{
			this->Data[counter] = data;
			flag = true;
			return;
		}
	}
	if (flag == false)								// ���� ������ ��� ������� �� ������, ������ �������, ��:
	{
		if (i == this->Size && j == this->Size) 
		{
			LI.add_on_pos_left(N2 - 1, i);
			Data.add_on_pos_left(N2 - 1, data);
			for (int column = j; column < LJ.get_size(); column++) 
			{
				LJ[column] += 1;
			}
			return;
		}
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
	}
}

template<typename SomeType>
void CCS_Matrix<SomeType>::Shift()
{
	int N1 = this->LJ[this->LJ.get_size() - 2];
	int N2 = this->LJ[this->LJ.get_size() - 1];
	int Data_buffer;
	int LI_buffer;
	for (int counter = N2 - 1; counter >= N1; counter--) // ����� �������� ������� �� 1 ������, ��� �����:
	{
		Data_buffer = this->Data.get_low();				 // ����������� �������� ���������� ������� � ������ � ������ Data
		this->Data.add_front(Data_buffer);				
		this->Data.pop_low();

		LI_buffer = this->LI.get_low();					 // ����������� ��������, ����������� �� ���������� � ������ Data, 
														 // ����������� � LI, ����� � ������, � ��������� �� �� 1, ��������, ���
														 // �� ������ ��������� � LI ��������, �������� ������� <= ������� ������� 
		
		if (LI_buffer == this->Size) 
		{
			this->LI.add_front(1);
		}
		else
		{
			this->LI.add_front(LI_buffer + 1);
		}
		this->LI.pop_low();
	}
	int differences_buffer;
	List<int> differences;
	for (int column = this->Size; column > 0; column--)						
	{																		
		differences.add_front(this->LJ[column] - this->LJ[column - 1]);		// ������� � ���� ������� ��������� ������ LJ == ���������� ��������� � �������,
		this->LJ.pop_low();													// ������� ����� ������� ������ �� ���� ������, �������� �������� ����,
	}																		// ����������� ��������� ������� � ������ � ������ ������� ������ LJ
	
	differences_buffer = differences.get_low();
	differences.pop_low();
	differences.add_front(differences_buffer);

	for (int counter = 0; counter < differences.get_size(); counter++) 
	{
		this->LJ.append(this->LJ.get_low() + differences[counter]);
	}
}

int main()
{


	int size;
	cout << "Enter your matrix size (x*x) : ";
	cin >> size;

	List<char> DataList;

	cout << "Input Your Data:" << endl;

	char buffer;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			cin >> buffer;
			//if ((int)buffer - 48 > 9 || (int)buffer - 48 < 0)	//������ �� ������
			//{
			//	cout << "Invalid data input!";
			//	return -1;
			//}
			DataList.append(buffer);
		}

	}
	
	cout << endl;
	cout << "Your DataList:" << endl;


	for (int i = 0; i < DataList.get_size(); i++)
	{
		cout << DataList[i];
	}

	CCS_Matrix<char> NewMa;
	NewMa.Input(DataList, size);

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


	NewMa.Shift();


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
	