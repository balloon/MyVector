#pragma once
//2016-11-22 第一次修改  关于访问内存时的越界检查和初始化时的模板化并添加函数注释
#ifndef _MYVECTOR_H
#define _MYVECTOR_H
#include <memory>
using namespace std;

//为了实现反向迭代器
template<typename Ty> class reverse_pointer;
template<typename Ty> bool operator==(const reverse_pointer<Ty> &left, const reverse_pointer<Ty> &right);
template<typename Ty> bool operator!=(const reverse_pointer<Ty> &left, const reverse_pointer<Ty> &right);
template<typename Ty> bool operator<(const reverse_pointer<Ty> &left, const reverse_pointer<Ty> &right);
template<typename Ty> bool operator>(const reverse_pointer<Ty> &left, const reverse_pointer<Ty> &right);
template<typename Ty>
reverse_pointer<Ty> operator+(const int n,  reverse_pointer<Ty>);
template<typename Ty>
reverse_pointer<Ty> operator-(const int n,  reverse_pointer<Ty>);

template<typename Ty>
class reverse_pointer {
	typedef Ty value;

private:
	value p;
public:
	reverse_pointer() :p(nullptr) {}
	reverse_pointer(value s) :p(s) {}
	reverse_pointer(const reverse_pointer<Ty> &t) :p(t.p) {}
	reverse_pointer<Ty>& operator=(const reverse_pointer<Ty> &t) {
		p = t.p;
		return (*this);
	}
	reverse_pointer<Ty>& operator=(const value &t) {
		p = t;
		return (*this);
	}
	reverse_pointer<Ty>& operator++() {
		--p;
		return (*this);
	}
	reverse_pointer<Ty> operator++(int) {
		auto t = p;
		--p;
		return reverse_pointer<Ty>(t);
	}
	reverse_pointer<Ty>& operator--() {
		++p;
		return (*this);
	}
	reverse_pointer<Ty> operator--(int) {
		auto t = p;
		++p;
		return reverse_pointer<Ty>(t);
	}
	reverse_pointer<Ty> operator+(const int n) {
		return reverse_pointer<Ty>(p - n);
	}
	friend 	reverse_pointer<Ty> operator+(const int n,  reverse_pointer<Ty> t) {
		return reverse_pointer<Ty>(t.p - n);
	}
	reverse_pointer<Ty> operator-(const int n) {
		return reverse_pointer<Ty>(p + n);
	}
	friend reverse_pointer<Ty> operator-(const int n,  reverse_pointer<Ty> t) {
		return reverse_pointer<Ty>(t.p + n);
	}
	reverse_pointer<Ty>& operator+=(const int n) {
		p -= n;
		return (*this);
	}
	reverse_pointer<Ty>& operator-=(const int n) {
		p += n;
		return (*this);
	}
	auto operator*()->decltype(*p) {
		return *p;
	}
	auto operator->() {
		return &*p;
	}
	friend bool operator==(const reverse_pointer<Ty> &left, const reverse_pointer<Ty> &right) {
		if (left.p == right.p)
			return true;
		else
			return false;
	}
	friend bool operator!=(const reverse_pointer<Ty> &left, const reverse_pointer<Ty> &right) {
		if (left == right)
			return false;
		else
			return true;
	}
	friend bool operator<(const reverse_pointer<Ty> &left, const reverse_pointer<Ty> &right) {
		if (left.p < right.p)
			return true;
		else
			return false;
	}
	friend bool operator>(const reverse_pointer<Ty> &left, const reverse_pointer<Ty> &right) {
		if (left < right || left == right)
			return false;
		else
			return true;
	}
};





template<typename T> class MyVector;
template<typename T>
//非成员函数，声明为友元函数
void swap(MyVector<T>&, MyVector<T>&);
template<typename T>
bool operator==(const MyVector<T>&, const MyVector<T>&);
template<typename T>
bool operator!=(const MyVector<T>&, const MyVector<T>&);
template<typename T>
bool operator<(const MyVector<T>&, const MyVector<T>&);
template<typename T>
bool operator>(const MyVector<T>&, const MyVector<T>&);

template <typename T> class MyVector {
public:
	//模板类中类型声明
	typedef T value_type;//元素类型

	typedef value_type* iterator;//元素类型指针

	typedef const value_type* const_iterator;//const 元素类型指针

	typedef value_type&       reference;//元素引用

	typedef const value_type& const_reference;//const 元素引用

	typedef std::size_t       size_type;//无符号整型数据，足够保存此种容器类型最大可能容器的大小

	typedef std::ptrdiff_t    difference_type;//带符号的整型数据，足够保存两个迭代器之间的距离
public:
	
	size_type size() const noexcept {
		return first_free - elements;
	}
	size_type capacity()const noexcept {
		return cap - elements;
	}
	const_iterator cbegin() const noexcept {
		return elements;
	}
	iterator begin() const noexcept {
		return elements;
	}
	const_iterator cend() const noexcept {
		return first_free;
	}
	iterator end() const noexcept {
		return first_free;
	}
	reverse_pointer<iterator> rbegin()  const noexcept {
		return reverse_pointer<iterator>(end() - 1);
	}
	const reverse_pointer<iterator> crbegin()  const noexcept {
		return reverse_pointer<iterator>(end() - 1);
	}
	reverse_pointer<iterator> rend() const noexcept {
		return reverse_pointer<iterator>(begin() - 1);
	}
	const reverse_pointer<iterator> crend()  const noexcept {
		return reverse_pointer<iterator>(begin() - 1);
	}
	reference front() const {
		return (*begin());
	}
	reference back() const {
		return *(end() - 1);
	}
	bool empty() const noexcept {
		if (begin() == nullptr)
			return true;
		else
			return false;
	}
	size_type max_size()const noexcept {
		return 1073741823;//我也不知道为什么是这个数字
	}
	//初始化公用构造函数
	MyVector() :elements(nullptr), first_free(nullptr), cap(nullptr) {}
	template<class Iter>
	MyVector(Iter first, Iter last)	:MyVector()
	{
	auto newcapacity = last-first;
	auto newdata = alloc.allocate(newcapacity);
	auto dest = newdata;
	for (size_type i = 0; i != newcapacity; ++i)
	{
		alloc.construct(dest++, *first++);
	}
	elements = newdata;
	first_free = dest;
	cap = first_free;
}

	MyVector(std::initializer_list<T>);

	MyVector(const MyVector<T>&);

	MyVector(int);

	MyVector(int, const T&);

	MyVector<T>& operator=(const MyVector<T> &t);

	void push_back(const T&);


	void swap(MyVector<T>&);


	friend  void swap(MyVector<T> &left, MyVector<T> &right) {
		left.swap(right);
	}

	void assign(iterator, iterator);

	void assign(std::initializer_list<T>&);

	void assign(size_type, const T&);

	friend bool operator==(const MyVector<T> &left, const MyVector<T> &right) {
		if (left.size() == right.size())
		{
			auto leftBeg = left.cbegin(), rightBeg = right.cbegin();
			for (; leftBeg != left.cend() && rightBeg != right.cend(); ++leftBeg, ++rightBeg) {
				if ((*leftBeg) == (*rightBeg))
					continue;
				else
					return false;
			}
			if (leftBeg == left.cend() && rightBeg == right.cend())
				return true;
		}
		else
			return false;
	}
	friend bool operator!=(const MyVector<T> &left, const MyVector<T> &right) {
		if (left == right)
			return false;
		else
			return true;
	}
	friend bool operator<(const MyVector<T> &left, const MyVector<T> &right) {
		if (left.size() < right.size())
			return true;
		else if (left.size() > right.size())
			return false;
		else {
			auto leftBeg = left.cbegin(), rightBeg = right.cbegin();
			for (; leftBeg != left.cend() && rightBeg != right.cend(); ++leftBeg, ++rightBeg) {
				if ((*leftBeg) == (*rightBeg))
					continue;
				else if ((*leftBeg) < (*rightBeg))
					return true;
				else
					return false;
			}
			if (leftBeg == left.cend() && rightBeg == right.cend())
				return false;
		}
	}
	friend bool operator>(const MyVector<T> &left, const MyVector<T> &right) {
		if (left < right || left == right)
			return false;
		else
			return true;
	}
	iterator insert(const_iterator, value_type);
	iterator insert(const_iterator, int, value_type);
	iterator insert(const_iterator, initializer_list<value_type>);
	iterator insert(const_iterator, const_iterator, const_iterator);
	template<typename ...Ty>
	iterator emplace(const_iterator beg, Ty&&...t) {

		if (beg == end())
			emplace_back((t)...);
		if (beg >= begin() && beg < end()) {
			int n = beg - begin();
			chk_n_alloc();

			iterator m_beg = begin() + n;

			T temp2 = *m_beg, temp;

			alloc.destroy(m_beg);
			alloc.construct(m_beg++, _STD forward<Ty>(t)...);
			for (; m_beg != end(); ++m_beg) {
				temp = *m_beg;
				*m_beg = temp2;
				temp2 = temp;
			}
			alloc.construct(first_free++, temp2);
			return (begin() + n);
		}
		else
			return nullptr;
	}
	template<typename ...Ty>
	void emplace_back(Ty&&... t) {

		chk_n_alloc();

		alloc.construct(first_free++, _STD forward<Ty>(t)...);
	}
	reference at(int n) {
		if (!empty())
		{

			if (n >= 0 && n < size())
				return *(begin() + n);
			else
				_DEBUG_ERROR("Out of bounds ");
		}
		else
			_DEBUG_ERROR("MyVector empty ");
	}
	reference operator[](int n) {
		if (!empty())
		{

			if (n >= 0 && n < size())
				return *(begin() + n);
			else
				_DEBUG_ERROR("Out of bounds ");
		}
		else
			_DEBUG_ERROR("MyVector empty ");
	}
	void pop_back() {
		if (empty())
			_DEBUG_ERROR("MyVector empty before pop");
		else {

			alloc.destroy(--first_free);

		}
	}
	void pop_back_n(int n) {
		if (!empty() && (size_type)n <= size()) {
			for (int i = 0; i != n; ++i) {
				pop_back();
			}
		}
		else
			_DEBUG_ERROR("MyVector empty or beyend size");
	}
	void clear() {
		free();
		elements = nullptr;
		first_free = nullptr;
		cap = nullptr;
	}
	void resize(int n) {
		if ((size_type)n < size()) {
			pop_back_n(size() - n);
		}
		else if ((size_type)n > size()) {
			for (int i = 0; i != n; ++i) {
				chk_n_alloc();
				alloc.construct(first_free++);
			}
		}
	}
	void resize(int n, const_reference t) {
		if ((size_type)n < size()) {
			pop_back_n(size() - n);
		}
		else if ((size_type)n > size()) {
			for (int i = 0; i != n; ++i) {
				chk_n_alloc();
				alloc.construct(first_free++, t);
			}
		}
	}
	void shrink_to_fit() {
		if (!empty() && capacity() > size()) {
			auto newcapacity = size();
			auto newdata = alloc.allocate(newcapacity);
			auto dest = newdata;
			auto elem = elements;
			for (size_type i = 0; i != size(); ++i) {
				alloc.construct(dest++, std::move(*elem++));
			}
			free();
			elements = newdata;
			first_free = dest;
			cap = first_free;
			return;
		}
		else
			return;
	}
	void reserve(int n) {
		if ((size_type)n > capacity()) {
			if ((size_type)n < max_size())
			{
				auto newcapacity = n;
				auto newdata = alloc.allocate(newcapacity);
				auto dest = newdata;
				auto elem = elements;
				for (size_type i = 0; i != size(); ++i) {
					alloc.construct(dest++, std::move(*elem++));
				}
				free();
				elements = newdata;
				first_free = dest;
				cap = elements+newcapacity;
			}
		}
	}
	iterator erase(const_iterator);
	iterator erase(const_iterator, const_iterator);
private:
	
	iterator elements;//begin()
	iterator first_free;//end()
	iterator cap;//capacity()
	static std::allocator<T> alloc;
	void chk_n_alloc() {
		if (size() == capacity())
			reallocate();
	}
	//工具函数，被拷贝控制操作使用
	
	void free() {
		if (elements) {
			for (auto p = first_free; p != elements;)
				alloc.destroy(--p);
			alloc.deallocate(elements, cap - elements);
		}
	}
	void reallocate() {
		auto newcapacity =size() ? 2 * size() : 1;
		if (newcapacity > max_size()) {
			_DEBUG_ERROR("MyVector beyend max_size");
		}
		auto newdata = alloc.allocate(newcapacity);
		auto dest = newdata;
		auto elem = elements;
		for (size_type i = 0; i != size(); ++i)
			alloc.construct(dest++, std::move(*elem++));
		free();
		elements = newdata;
		first_free = dest;
		cap = elements + newcapacity;
	}

};

template<typename T> std::allocator<T> MyVector<T>::alloc;


template<typename T>
MyVector<T>::MyVector(std::initializer_list<T> li) :MyVector() {
	auto newcapacity = li.size();
	auto newdata = alloc.allocate(newcapacity);
	auto dest = newdata;
	for (auto beg = li.begin(); beg != li.end();) {
		alloc.construct(dest++, *beg++);
	}
	elements = newdata;
	first_free = dest;
	cap = first_free;
}
template<typename T>
MyVector<T>::MyVector(const MyVector<T> &t) :MyVector() {
	auto newcapacity = t.size();
	auto newdata = alloc.allocate(newcapacity);
	auto dest = newdata;
	for (auto beg = t.begin(); beg != t.end(); ) {
		alloc.construct(dest++, *beg++);
	}
	elements = newdata;
	first_free = dest;
	cap = first_free;
}
template<typename T>
MyVector<T>::MyVector(int n):MyVector() {
	auto newcapacity = n;
	auto newdata = alloc.allocate(newcapacity);
	auto dest = newdata;
	for (size_type i = 0; i != n; ++i) {
		alloc.construct(dest++);
	}
	elements = newdata;
	first_free = dest;
	cap = first_free;

}
template<typename T>
MyVector<T>::MyVector(int n, const T &t):MyVector() {
	
	elements= alloc.allocate(n);
	first_free = uninitialized_fill_n(elements, n, t);
	cap = first_free;
}
template<typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector<T> &t) {
	if (&t == this)
	{
		return *this;
	}
	if (begin())
		free();
	elements = alloc.allocate(t.size());
	first_free = uninitialized_copy(t.begin(), t.end(), elements);
	cap = first_free;
	return (*this);
}
template<typename T>
void MyVector<T>::push_back(const T &m) {
	chk_n_alloc();
	alloc.construct(first_free++, m);
}
template<typename T>
void MyVector<T>::swap(MyVector<T> &t) {
	auto m_elements =begin();
	auto m_first_free =end();
	auto m_cap = cap;
	elements = t.begin();
	first_free = t.end();
	cap = t.cap;
	t.elements = m_elements;
	t.first_free = m_first_free;
	t.cap = m_cap;
}

template<typename T>
void MyVector<T>::assign(iterator p1, iterator p2) {
	if (begin())
		free();
	elements = alloc.allocate(p2-p1);
	first_free = uninitialized_copy(p1, p2, elements);
	cap = first_free;
	
}
template<typename T>
void MyVector<T>::assign(std::initializer_list<T> &t) {
	if (begin())
		free();
	elements = alloc.allocate(t.size());
	first_free = uninitialized_copy(t.begin(), t.end(), elements);
	cap = first_free;
}
template<typename T>
void MyVector<T>::assign(size_type n, const T &t) {
	if (begin())
		free();
	elements = alloc.allocate(n);
	first_free = uninitialized_fill_n(elements, n, t);
	cap = first_free;
}
template<typename T>
T* MyVector<T>::insert(const_iterator beg, value_type t) {
	
	value_type temp,temp2 = t;
	int n = beg - begin();
	iterator m_beg = const_cast<iterator> (beg);
	if (beg >= begin() && beg <= end()) {
		for (; m_beg != end(); ++m_beg)
		{


			temp = *m_beg;
			*m_beg = temp2;
			temp2 = temp;
		}
		chk_n_alloc();
		alloc.construct(first_free++, temp2);
		return (begin()+n);
	}
	else
		return nullptr;
}
template<typename T>
T* MyVector<T>::insert(const_iterator beg, int n, value_type t) {
	
	iterator m_beg =const_cast<iterator> (beg); int lenght = beg - begin();
	if (beg >= begin() && beg <= end()) {
		for (int i = 0; i != n; ++i) {
			m_beg = insert(m_beg, t);
		}
		return (begin() + lenght + n);
	}
	else
		return nullptr;
}
template<typename T>
T* MyVector<T>::insert(const_iterator beg, initializer_list<value_type> li) {
	iterator m_beg = const_cast<iterator> (beg);
	if (beg >= begin() && beg <= end()) {
		for (auto li_end = li.end()-1; li_end >= li.begin(); --li_end) {
			m_beg = insert(m_beg, *li_end);
		}
		return(begin());
	}
	else
		return nullptr;
}
template<typename T>
T* MyVector<T>::insert(const_iterator beg, const_iterator left, const_iterator right) {
	if (right - left) {
		iterator p = new value_type[right - left];
		for (int i = 0; i != right - left;++i) {
			p[i] = *(left + i);
		}
		
			iterator m_beg = const_cast<iterator> (beg);
			if (beg >= begin() && beg <= end()) {
				for (iterator end = p + (right - left - 1); end >= p; --end) {
					m_beg = insert(m_beg, *end);
				}
				delete[] p;
				return(begin());
			}
			else
				return nullptr;
	}
	else
		return nullptr;
}
template<typename T>
T* MyVector<T>::erase(const_iterator beg) {
	if (!empty()) {
		if (beg >= begin() && beg < end()) {
			auto m_beg = const_cast<iterator>(beg);
			for (; m_beg!=end()-1; ++m_beg) {
				*m_beg = *(m_beg + 1);
			}
			alloc.destroy(--first_free);
			return const_cast<iterator>(beg);
		}
		else
			_DEBUG_ERROR("iterator is not find");
	}
	else
		_DEBUG_ERROR("MyVector empty ");
}
template<typename T>
T* MyVector<T>::erase(const_iterator left, const_iterator right) {
	if (!empty()) {
		if (left >= begin() && left<end() && right>left&&right <= end()) {
			auto n = right - left;
			iterator t;
			for (int i = 0; i != n; ++i) {
				t=erase(left + i);
			}
			return t;
		}
	
	}
	else
		_DEBUG_ERROR("MyVector empty ");
}
#endif