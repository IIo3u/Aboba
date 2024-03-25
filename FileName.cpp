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
	public:						// Если выложить все ячейки по адресам слева на право, то:
		Node* PreviousAddress;  // Это ссылка влево (т.е. ведёт в начало списка)
		Node* NextAddress;		// Это ссылка вправо (т.е. ведёт в конец списка)
		SomeType data;

		Node(SomeType data = SomeType())
		{
			this->data = data;
			this->NextAddress = this->PreviousAddress = nullptr;
		}
	};

	
	Node<SomeType>* Head;	// Начало
	Node<SomeType>* Tail; // Конец
	int Size;
	void add_first(SomeType data);	// Инициализирует добавление первого элемента

public:
	
	List();
	~List();
	
	void add_on_pos_right(int index, SomeType data); // Добавляет значение справа
	void add_on_pos_left(int index, SomeType data);	 // Добавляет значение слева
	void append(SomeType data);						 // Добавляет значение правее последнего элемента (в конец списка)
	void add_front(SomeType data);					 // Добавляет значение левее первого элемента (в начало списка)
	void pop_element(int index);					 // Удаляет элемент по нужному адресу
	void pop_top();									 // Удаляет Начальный (Head) элемент списка
	void pop_low();									 // Удаляет Конечный (Tail) элемент списка
	SomeType& get_low();							 // Передаёт ссылку на поле data Конечного элемента
	SomeType& get_top();							 // Передаёт ссылку на поле data Начального элемента
	int get_size() { return Size; };				 // Возвращает размер списка
	SomeType& operator[](int index);				 // Оператор индексирования для обращения к полю data нужных элементов
	

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
	void Input(List<SomeType> InputList, int Size);	// Передаёт введённые значения в объект
	SomeType get(int i, int j);						// Возвращает значение в нужных строках и столбцах матрицы
	void set(int i, int j, SomeType data);			// Позволяет поменять значение в нужных строках и столбцах
	int get_size() { return this->Size; }		// Возвращает размер матрицы
	void Shift();								// Сдвигает элементы матрицы на 1 вправо
	
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
	if (data == 0)		// Равносильно тому, что нам нужно удалить информацию из матрицы в данной позиции
	{
		if (N1 == N2) // Это означает что элементов в данном столбце так и так не имеется
		{
			return;
		}
		for (int counter = N1; counter < N2; counter++)
		{
			
			if (LI[counter] == i) // Если нужный элемент на нужном месте найден, то мы удаляем всю информацию о нём:
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
	if (N1 == N2 && N2 != 0) // Ситуация, когда нам нужно добавить элемент на нужную строку, но элементов в столбце нет:
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
	for (int counter = N1; counter < N2; counter ++)  // Стандартная ситуация, когда нам нужно поменять элемент, который уже имеет значение:
	{
		if (LI[counter] == i) 
		{
			this->Data[counter] = data;
			flag = true;
			return;
		}
	}
	if (flag == false)								// Если нужный нам элемент не найден, тоесть нулевой, то:
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
	for (int counter = N2 - 1; counter >= N1; counter--) // Чтобы сдвинуть матрицу на 1 вправо, нам нужно:
	{
		Data_buffer = this->Data.get_low();				 // Переместить элементы последнего столбца в начало в списке Data
		this->Data.add_front(Data_buffer);				
		this->Data.pop_low();

		LI_buffer = this->LI.get_low();					 // Переместить элементы, указывающие на информацию в списке Data, 
														 // находящиеся в LI, также в начало, и увеличить их на 1, учитывая, что
														 // мы должны добавлять в LI элементы, значение которых <= размера матрицы 
		
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
		differences.add_front(this->LJ[column] - this->LJ[column - 1]);		// Разница в двух крайних элементах списка LJ == количеству элементов в столбце,
		this->LJ.pop_low();													// поэтому проще создать список из этих разниц, добавить значения туда,
	}																		// переставить последний элемент в начало и заново собрать список LJ
	
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
			//if ((int)buffer - 48 > 9 || (int)buffer - 48 < 0)	//Защита от дурака
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
	