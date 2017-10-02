//************************************************/
//* @file  :DataHolder.h
//* @brief :Data���Ǘ�����
//* @date  :2017/09/30
//* @author:K.Yamamoto
//************************************************/
#pragma once
#include <vector>
#include <memory>

template<class T>
class DataHolder 
{
private:
	//Data��ވꗗ
	std::vector<std::unique_ptr<T>> m_DataList;

	bool m_change;
public:
	DataHolder() :m_change(false) {}
	~DataHolder() {}

	//�f�[�^��ǉ�����
	int AddData(std::unique_ptr<T> data) {
		m_DataList.push_back(move(data));
		m_change = true;
		return (int)(m_DataList.size()) - 1;
	}

	//�f�[�^����Ԃ�
	//�������nullptr
	T* GetData(int id) const {
		if (id > (int)(m_DataList.size()) - 1)return nullptr;
		if (0 > id)return nullptr;
		return	m_DataList[id].get();
	}

	// �S�f�[�^�擾
	std::vector<std::unique_ptr<T>>& GetList() {
		return m_DataList;
	}

	int GetContainerSize() const {
		return (int)(m_DataList.size());
	}

	bool ChangeHolderCallBack() {
		if (m_change) {
			m_change = false;
			return true;
		}
		return false;
	}
};
