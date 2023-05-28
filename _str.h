#pragma once
#include <string.h> 
class _str //класс управления ресурсом 
{
	char* m_pszData;
	int m_nCount;
	friend class Str;	//Дружественный класс или метод
	_str() {//если создается объект и туда не передается строка
		m_pszData = new char[1] {0}; 
		m_nCount = 1; //количество ссылок на эти данные
	}

	_str(const char* p) {//если создается объект и туда передается строка
		m_nCount = 1; 
		m_pszData = new char[strlen(p) + 1]; 
		strcpy_s(m_pszData, strlen(p) + 1, p); //копируем данные
	}
	~_str() { delete[]m_pszData; } //деструктор
	void AddRef() { m_nCount++; } 

	//Удаляет себя
	void Release() { 
		m_nCount--; //уменьшаем количество ссылок
		if (m_nCount == 0) delete this; 
	} //если объектов уже нет, то тогда и данные можно удалять

	friend ostream& operator << (ostream& stream, const _str& str) {
		return stream << str.m_pszData;
	}
};

