#pragma once
#include "_str.h"
#include <stdlib.h>

class Str
{
	_str* m_pStr;
public:
	Str() { m_pStr = new _str; }		//���� �� �����, �� �������
	Str(const char* p) {		// ����� ������
		m_pStr = new _str(p);
	}
	Str(const Str& s)
	{
		m_pStr = s.m_pStr; 	// ��������� �� ��� �� ������
		m_pStr->AddRef(); 	// ��������, ��� ���������
	}

	Str(int num) {
		//����� ����� ������ ������
		int size = snprintf(nullptr, 0, "%d", num);
		char* buf = new char[size + 1];
		_itoa_s(num, buf, size + 1, 10);
		m_pStr = new _str(buf);

		delete[] (buf);
	}


	//������� ������ - ��� ����� �������
	//���������� � ����� �� ���� ������
	Str& operator = (const Str& s) {
		if (this != &s) {
			s.m_pStr->AddRef(); //�������, ��� ��� ���� ������ ��������� �� ��� ������
			m_pStr->Release(); //���������� ��������� �� 1 - �� ��� ������ �� ������ �� ���������
			m_pStr = s.m_pStr; //������ ���� ������ ��������� �� ����� ������
		}
		return *this;
	}

	//��� ��������� ������� �� ��������� �� ������ ������ �� ��������
	Str& operator += (const Str& s) {
		int length = len() + s.len();
		if (s.len() != 0) {		// ���������� ������ �� �������!
			_str* pstrTmp = new _str; 	// ����� ������
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
		m_pStr->Release(); 	// �� ���������� ������!
	}				// ��������� ������� ������!

	int len() const {
		return strlen(m_pStr->m_pszData);
	}

	Str substr(int off, int len) const {
		if (off < 0) off = 0; //���� ������� ����� �����, �� �������� ����� 0
		if (len <= 0) { //���� ����� ��� ��� = 0, �� ���������� ������ ���������
			return Str();
		} //���� ������� ������� �����, �� ����� ������ ������� �� ����� ������ 
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

	

