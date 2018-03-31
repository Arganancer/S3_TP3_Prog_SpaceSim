#ifndef DEQUE_T_HPP
#define DEQUE_T_HPP

//À faire: Rajouter un head qui est essentiellement e début du queue. Retravailler la fonction. Pour avoir le début: tab[(idx+head) % cap]. 
//[head + size - 1] % cap pour l'operateur crochet.

namespace container_t
{
	template <class T>
	class deque_t
	{
	public:
		using size_type = unsigned long;

		// CONSTRUCTORS/DESTRUCTORS and AFFECTORS
		explicit deque_t(size_t cap = 0);
		deque_t(const deque_t& other);
		~deque_t();
		deque_t& operator=(const deque_t& other);

		// ACCESSORS
		T& operator[](size_t idx);

		// CAPACITY
		bool empty() const;
		size_type size() const;
		size_type capacity() const;

		// MUTATORS
		void push_back(const T& value);
		void pop_back();
		void push_front(const T& value);
		void pop_front();
		void reserve(size_type new_cap);
		void resize(size_type new_size);
		void clear();
		void swap(deque_t& other);

	private:
		T *tab_;
		size_type nb_elem_;
		size_type cap_;
		size_type head_;
	};

	template <class T>
	deque_t<T>::deque_t(size_t cap) :
		nb_elem_(0),
		cap_(cap),
		head_(0)
	{
		tab_ = new T[cap];
		reserve(cap);
	}

	template <class T>
	deque_t<T>::deque_t(const deque_t& other):
		nb_elem_(0),
		cap_(0),
		head_(0)
	{
		tab_ = new T[0];
		*this = other;
	}

	template <class T>
	deque_t<T>::~deque_t()
	{
		clear();
	}

	template <class T>
	deque_t<T>& deque_t<T>::operator=(const deque_t& other)
	{
		resize(other.cap_);
		head_ = other.head_;
		nb_elem_ = other.nb_elem_;

		for (size_type i = 0; i < other.cap_; ++i)
			tab_[i] = other.tab_[i];

		return *this;
	}

	template <class T>
	void deque_t<T>::swap(deque_t& other)
	{
		std::swap(this->cap_, other.cap_);
		std::swap(this->tab_, other.tab_);
		std::swap(this->head_, other.head_);
		std::swap(this->nb_elem_, other.nb_elem_);
	}

	template <class T>
	T& deque_t<T>::operator[](size_t idx)
	{
		return tab_[(idx + head_) % cap_];
	}

	template <class T>
	bool deque_t<T>::empty() const
	{
		return nb_elem_ == 0;
	}

	template <class T>
	typename deque_t<T>::size_type deque_t<T>::size() const
	{
		return nb_elem_;
	}

	template <class T>
	void deque_t<T>::reserve(size_type new_cap)
	{
		if (cap_ < new_cap)
		{
			auto tmp = tab_;
			tab_ = new T[new_cap];

			size_type i = 0;

			for (; i < nb_elem_; ++i)
				tab_[i] = tmp[(head_ + i) % cap_];

			for (; i < new_cap; ++i)
				tab_[i] = T();

			cap_ = new_cap;
			head_ = 0;
		}
	}

	template <class T>
	typename deque_t<T>::size_type deque_t<T>::capacity() const
	{
		return cap_;
	}

	template <class T>
	void deque_t<T>::clear()
	{
		nb_elem_ = 0;
		cap_ = 0;
		delete[] tab_;
		tab_ = nullptr;
	}

	template <class T>
	void deque_t<T>::push_back(const T& value)
	{
		if (nb_elem_ == cap_)
		{
			reserve(2 * cap_ + 1);
		}
		tab_[(head_ + nb_elem_) % cap_] = value;
		nb_elem_++;
	}

	template <class T>
	void deque_t<T>::pop_back()
	{
		nb_elem_--;
		tab_[(head_ + nb_elem_) % cap_] = T();
	}

	template <class T>
	void deque_t<T>::push_front(const T& value)
	{
		if (nb_elem_ == cap_)
			reserve(2 * cap_ + 1);

		if (head_ == 0)
			head_ = cap_ - 1;
		else
			head_ -= 1;
		tab_[head_] = value;

		nb_elem_++;
	}

	template <class T>
	void deque_t<T>::pop_front()
	{
		tab_[(head_) % cap_] = T();
		head_ = (head_ + 1) % cap_;

		nb_elem_--;
	}

	template <class T>
	void deque_t<T>::resize(size_type new_size)
	{
		reserve(new_size);

		if (new_size < nb_elem_)
		{
			for (size_type i = new_size; i < nb_elem_; ++i)
				tab_[i] = T();

			nb_elem_ = new_size;
		}
	}
}
#endif