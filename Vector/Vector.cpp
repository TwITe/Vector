#include <iostream>
#include <cassert>
#include <cstring>

using namespace std;

//���������, ������� ������������ ��� �������� ������ ������ ��� ������.
int* buffer;

//������� ����������� ��������� � �������. 
unsigned array_size;

//������������ ���������� ��������� � �������.
unsigned capacity;

//������������� �������. 
//����������� ���� ��� ����� ���, ��� ����� �������������� ������. 
void init_array() {
	array_size = 0;
	capacity = 0;
	buffer = new int[array_size];
}

//������������ �������� �������. 
//����������� ���� ��� ����� ���, ��� ������ ��������� ��������������. 
void destroy_array() {
	delete[] buffer;
	buffer = nullptr;
	array_size = 0;
	capacity = 0;
}

//������������ ��������� ����� ������ ��� �������� ������.
void memAlloc() {
	capacity = array_size * 2 + 1;
	int* newBuffer = new int[capacity];
	memcpy(newBuffer, buffer, sizeof(buffer)*array_size);
	delete[] buffer;
	buffer = newBuffer;
}

//���������� ������ �������� � ������.
void add_element(const int& element) {
	if (array_size == capacity) {
		memAlloc();
	}
	buffer[array_size] = element;
	array_size = array_size + 1;
}

//�������� �������� �� �������. 
//������� ���������� true, ���� ������� ��� ������ ���������, ����� - false. 
bool delete_element(const int& element)
{
	bool found = false;
	for (unsigned i = 0; i < array_size; i++)
	{
		if (buffer[i] == element) {
			found = true;
			if (array_size * 2 > capacity) {
				memcpy(buffer + i, buffer + (i + 1), sizeof(int)*(array_size - (i + 1)));
			}
			else if (array_size * 2 == capacity) {
				int* newBuffer = new int[array_size - 1];
				memcpy(newBuffer, buffer, sizeof(int)*i);
				memcpy(newBuffer + i, buffer + (i + 1), sizeof(int)*(array_size - (i + 1)));
				delete[] buffer;
				buffer = newBuffer;
			}
			else if (array_size * 2 < capacity) {
				for (unsigned k = i; k < array_size - 1; i++) {
					buffer[i] = buffer[i + 1];
				}
				buffer[array_size - 1] = 0;
			}
			array_size = array_size - 1;
		}
	}
	return found;
}

//�������� �������� �� ������� �� �������. 
//������� ���������� true, ���� ������� ��� ������ ���������, ����� - false. 
bool delete_element_by_index(const unsigned& index)
{
	bool found = false;
	for (unsigned i = 0; i < array_size; i++)
	{
		if (i == index) {
			found = true;
			int* newBuffer = new int[array_size - 1];
			memcpy(newBuffer, buffer, sizeof(buffer) * i);
			memcpy(newBuffer + i, buffer + (i + 1), sizeof(buffer) * (array_size - (i + 1)));
			delete[] buffer;
			buffer = newBuffer;
			array_size = array_size - 1;
		}
	}
	return found;
}

//����� �������� � �������.
//������� ���������� true, ���� ������� ��� ������ � �������, ����� - false. 
bool find_element(const int& element) {

	for (unsigned i = 0; i < array_size; i++) {
		if (buffer[i] == element) {
			return true;
		}
	}
	return false;
}

//�������� �������� �������� �� ��� �������.
//���� ������ ������������ (������ 0, ��� ������� �������) - ����� ������ ����������
// (� ��������� � ������� ����, ��� ��� ������).
const int& get_element(const unsigned& index) {
	if (index >= array_size) {
		throw std::runtime_error("index is invalid");
	}
	else {
		return buffer[index];
	}
}

//�������� ������� ���������� ��������� � �������. 
unsigned get_array_size() {
	return array_size;
}

//��������� ����� ������ ����������� (��������� ������ ������� �����������).
//������ ����� ������. 
//������ ��� �������� �� ������� ������.

void check_preconditions() {
	assert(array_size == 0);
	assert(array_size == 0);
	assert(buffer == nullptr);
}

void can_init_and_destroy_new_array_test() {
	init_array();
	destroy_array();
	check_preconditions();
}

void can_add_elements_to_array_test() {
	init_array();

	for (int i = 0; i < 2000; ++i) {
		add_element(i);
	}

	for (int i = 0; i < 2000; ++i) {
		int current_element = get_element(i);
		assert(current_element == i);
	}

	destroy_array();
	check_preconditions();
}

void cannot_delete_not_existed_element_test() {
	init_array();

	for (int i = 0; i < 2000; ++i) {
		add_element(i);
	}

	assert(delete_element(3000) == false);

	for (int i = 0; i < 2000; ++i) {
		int current_element = get_element(i);
		assert(current_element == i);
	}

	destroy_array();
	check_preconditions();
}

void cannot_delete_not_existed_element_test2() {
	init_array();

	for (int i = 0; i < 2000; ++i) {
		add_element(i);
	}

	assert(delete_element_by_index(3000) == false);

	for (int i = 0; i < 2000; ++i) {
		int current_element = get_element(i);
		assert(current_element == i);
	}

	destroy_array();
	check_preconditions();
}

void can_delete_existed_element_test() {
	init_array();

	for (int i = 0; i < 5; ++i) {
		add_element(i + 2);
	}

	int size_before_removing_element = get_array_size();

	assert(delete_element(3) == true);

	int size_after_removing_element = get_array_size();

	assert(size_after_removing_element + 1 == size_before_removing_element);
	assert(size_after_removing_element == 4);

	assert(get_element(0) == 2);
	assert(get_element(1) == 4);
	assert(get_element(2) == 5);
	assert(get_element(3) == 6);

	destroy_array();
	check_preconditions();
}

void can_delete_existed_element_test2() {
	init_array();

	for (int i = 0; i < 5; ++i) {
		add_element(i + 2);
	}

	int size_before_removing_element = get_array_size();

	assert(delete_element_by_index(3) == true);

	int size_after_removing_element = get_array_size();

	assert(size_after_removing_element + 1 == size_before_removing_element);
	assert(size_after_removing_element == 4);

	assert(get_element(0) == 2);
	assert(get_element(1) == 3);
	assert(get_element(2) == 4);
	assert(get_element(3) == 6);

	assert(find_element(2) == true);
	assert(find_element(3) == true);
	assert(find_element(4) == true);
	assert(find_element(5) == false);
	assert(find_element(6) == true);

	destroy_array();
	check_preconditions();
}

void exception_occurred_when_getiing_element_with_invalid_index_test() {
	init_array();

	for (int i = 0; i < 5; ++i) {
		add_element(i + 2);
	}

	assert(get_element(0) == 2);

	bool has_exception = false;

	try {
		get_element(5);
	}
	catch (...)
	{
		has_exception = true;
	}

	assert(has_exception == true);

	destroy_array();
	check_preconditions();
}

void exception_occurred_when_getiing_element_with_invalid_index_test2() {
	init_array();

	for (int i = 0; i < 5; ++i) {
		add_element(i + 2);
	}

	assert(get_element(0) == 2);

	bool has_exception = false;

	try {
		get_element(-1);
	}
	catch (...)
	{
		has_exception = true;
	}

	assert(has_exception == true);

	destroy_array();
	check_preconditions();
}

void array_size_has_to_decrease_while_elements_were_deleted_test() {
	init_array();

	for (int i = 0; i < 2000; ++i) {
		add_element(i);
	}

	for (int i = 0; i < 2000; ++i) {
		delete_element_by_index(0);
	}

	assert(get_array_size() == 0);
	assert(array_size < 100);

	destroy_array();
	check_preconditions();
}

int main()
{
	can_init_and_destroy_new_array_test();
	can_add_elements_to_array_test();
	cannot_delete_not_existed_element_test();
	cannot_delete_not_existed_element_test2();
	can_delete_existed_element_test();
	can_delete_existed_element_test2();
	exception_occurred_when_getiing_element_with_invalid_index_test();
	exception_occurred_when_getiing_element_with_invalid_index_test2();
	array_size_has_to_decrease_while_elements_were_deleted_test();
	can_init_and_destroy_new_array_test();

	system("PAUSE");
	return 0;
}