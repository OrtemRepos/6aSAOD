#pragma once
#include "_str.h"
#include <stdlib.h>

class Str
{
	_str* m_pStr;
public:
	Str() { m_pStr = new _str; }		//если не копия, то создаем
	Str(const char* p) {		// новый ресурс
		m_pStr = new _str(p);
	}
	Str(const Str& s)
	{
		m_pStr = s.m_pStr; 	// ссылаемся на тот же ресурс
		m_pStr->AddRef(); 	// отмечаем, что сослались
	}

	Str(int num) {
		//чтобы найти размер буфера
		int size = snprintf(nullptr, 0, "%d", num);
		char* buf = new char[size + 1];
		_itoa_s(num, buf, size + 1, 10);
		m_pStr = new _str(buf);

		delete[] (buf);
	}


	//текущий объект - это левый операнд
	//возвращаем в итоге на него ссылку
	Str& operator = (const Str& s) {
		if (this != &s) {
			s.m_pStr->AddRef(); //говорим, что еще один объект ссылается на эти данные
			m_pStr->Release(); //предыдущие уменьшаем на 1 - на эти данные мы больше не ссылаемся
			m_pStr = s.m_pStr; //теперь этот объект ссылается на новые данные
		}
		return *this;
	}

	//при изменении ресурса со объектами на старый ничего не случится
	Str& operator += (const Str& s) {
		int length = len() + s.len();
		if (s.len() != 0) {		// добавление ничего не изменит!
			_str* pstrTmp = new _str; 	// Новый ресурс
			delete[] pstrTmp->m_pszData;

			pstrTmp->m_pszData = new char[length + 1];
			strcpy_s(pstrTmp->m_pszData, length + 1, m_pStr->m_pszData);
			strcat_s(pstrTmp->m_pszData, length + 1, s.m_pStr->m_pszData);

			m_pStr->Release();
			m_pStr = pstrTmp;
		}
		return *this;
	}

	~Str() {
		m_pStr->Release(); 	// Не уничтожаем ресурс!
	}				// Уменьшаем счетчик ссылок!

	int len() const {
		return strlen(m_pStr->m_pszData);
	}

	Str substr(int off, int len) const {
		if (off < 0) off = 0; //если введено отриц число, то смещение будет 0
		if (len <= 0) { //если длина отр или = 0, то возвращаем пустую подстроку
			return Str();
		} //если слишком большая длина, то тогда просто считаем до конца строки 
		else if (len + off > this->len()) {
			len = this->len() - off;
		} 
			int length = len;
			char* pstrTmp = new char[length+1];
			for (int i = 0; i < length; i++) {
				*(pstrTmp + i) = *(m_pStr->m_pszData + off + i);
			}
			*(pstrTmp + length) = '\0';
			Str str = Str(pstrTmp);
			delete[]  (pstrTmp);
			return str;
		
	}


	friend ostream& operator << (ostream& stream, const Str& str) {
		return stream << *str.m_pStr;
	}
};

	

