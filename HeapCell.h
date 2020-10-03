#pragma once
class HeapCell
{
private:
	int m_key;
	int m_data;

public:
	HeapCell();
	HeapCell(int key, int data);
	int getKey() const;
	int getData() const;
	void setKey(int key);
	void setData(int data);
};

