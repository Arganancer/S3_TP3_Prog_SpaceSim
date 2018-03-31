#ifndef DOUBLE_CHAINED_LIST_H
#define DOUBLE_CHAINED_LIST_H
#include <cstddef>
#include <iterator>

namespace container_t
{
	template <class T>
	class list_t
	{
	public:
		//Constructeur et affectateur
		list_t();
		~list_t();
		list_t& operator=(const list_t<T>&);
		list_t& operator+=(const list_t<T>&);

		//Accesseur
		T& front();
		T& back();
		const T& front() const;
		const T& back() const;

		//Capacite
		bool empty() const;
		size_t size() const;

		//Fonction generatrice
		void push_front(const T& value);
		void pop_front();
		void push_back(const T& value);
		void pop_back();
		void swap(list_t&) noexcept;
		void clear();
		void splice(list_t& x);

	private:
		struct box
		{
			T value;
			box* previous;
			box* next;

			box(const T& value, box* previous, box* next) : value(value), previous(previous), next(next)
			{
			}
		};

		//Representation
		box *first_, *last_;
		size_t sz_;

#pragma region ITERATOR
	public:
		class iterator : public std::iterator<T, T>
		{
		protected:
			friend list_t;
			box* ptr_;
		public:
			// Constructors/Destructors
			explicit iterator(box* ptr) : ptr_(ptr)
			{
			}

			iterator(const iterator& other) { *this = other; }
			~iterator() = default;

			// Affector redefinitions
			iterator& operator=(const iterator& other)
			{
				ptr_ = other.ptr_;
				return *this;
			}

			iterator& operator++()
			{
				ptr_ = ptr_->next;
				return *this;
			} // PreIncrement Iterator
			iterator operator++(int)
			{
				iterator k(*this);
				operator++();
				return k;
			} // Post Increment Iterator
			iterator& operator--()
			{
				ptr_ = ptr_->previous;
				return *this;
			} // Decrement Iterator
			iterator operator--(int)
			{
				iterator k = this;
				ptr_ = ptr_->previous;
				return k;
			} // Post Decrement Iterator
			T& operator*() { return ptr_->value; }
			T& operator->() { return ptr_->value; }
			bool operator==(const iterator& right_iterator) const { return ptr_ == right_iterator.ptr_; }
			bool operator!=(const iterator& right_iterator) const { return ptr_ != right_iterator.ptr_; }
		};
#pragma endregion

		iterator insert(iterator position, const T& value)
		{
			// The container is extended by inserting new elements BEFORE the element at the specified position.
			if (position.ptr_ == first_)
			{
				push_front(value);
				return begin();
			}

			box* temp = new box(value, position.ptr_->previous, position.ptr_);
			position.ptr_->previous->next = temp;
			position.ptr_->previous = temp;
			++sz_;
			return iterator(temp);
		}

		iterator erase(iterator position)
		{
			if (position.ptr_ == first_)
			{
				pop_front();
				return begin();
			}
			if (position.ptr_ == last_)
			{
				pop_back();
				return end();
			}

			box* temp = position.ptr_->next;
			position.ptr_->previous->next = position.ptr_->next; // Link previous to next.
			position.ptr_->next->previous = position.ptr_->previous; // Link next to previous.
			delete position.ptr_;
			--sz_;
			return iterator(temp);
		}

		iterator begin()
		{
			if (sz_ > 0) { return iterator(first_); }
			return end();
		}

		iterator end()
		{
			return iterator(nullptr);
		}
	};

	template <class T>
	list_t<T>::list_t() : sz_(0)
	{
		first_ = last_ = nullptr;
	}

	template <class T>
	list_t<T>::~list_t()
	{
		while (sz_ > 0)
		{
			pop_front();
		}
	}

	template <class T>
	list_t<T>& list_t<T>::operator=(const list_t<T>& other)
	{
		clear();

		// This list becomes other list.
		box* temp = other.first_;
		for (size_t i = 0; i < other.sz_; i++)
		{
			push_back(temp->value);
			temp = temp->next;
		}

		return *this;
	}

	template <class T>
	list_t<T>& list_t<T>::operator+=(const list_t<T>& other)
	{
		// Append the other list to this list:
		box* temp = other.first_;
		for (size_t i = 0; i < other.sz_; i++)
		{
			push_back(temp->value);
			temp = temp->next;
		}

		return *this;
	}

	template <class T>
	T& list_t<T>::front()
	{
		return first_->value;
	}

	template <class T>
	T& list_t<T>::back()
	{
		return last_->value;
	}

	template <class T>
	const T& list_t<T>::front() const
	{
		return first_->value;
	}

	template <class T>
	const T& list_t<T>::back() const
	{
		return last_->value;
	}

	template <class T>
	bool list_t<T>::empty() const // Tested, functions.
	{
		return sz_ == 0 ? true : false;
	}

	template <class T>
	size_t list_t<T>::size() const // Tested, functions.
	{
		return sz_;
	}

	template <class T>
	void list_t<T>::push_front(const T& value)
	{
		if (first_ == nullptr)
		{
			last_ = first_ = new box(value, nullptr, nullptr);
		}
		else if (first_->next == nullptr)
		{
			first_ = new box(value, nullptr, first_);
			last_->previous = first_;
		}
		else
		{
			first_ = new box(value, nullptr, first_);
			first_->next->previous = first_;
		}
		++sz_;
	}

	template <class T>
	void list_t<T>::pop_front()
	{
		if (sz_ > 0)
		{
			if (sz_ == 1)
			{
				delete first_ , last_;
				first_ = last_ = nullptr;
			}
			else if (sz_ == 2)
			{
				delete first_;
				last_->previous = nullptr;
				first_ = last_;
			}
			else
			{
				first_ = first_->next;
				delete first_->previous;
				first_->previous = nullptr;
			}
			--sz_;
		}
	}

	template <class T>
	void list_t<T>::push_back(const T& value)
	{
		if (first_ == nullptr)
		{
			last_ = first_ = new box(value, nullptr, nullptr);
		}
		else if (first_->next == nullptr)
		{
			last_ = new box(value, last_, nullptr);
			first_->next = last_;
		}
		else
		{
			last_ = new box(value, last_, nullptr);
			last_->previous->next = last_;
		}
		++sz_;
	}

	template <class T>
	void list_t<T>::pop_back()
	{
		if (sz_ > 0)
		{
			if (sz_ == 1)
			{
				delete first_ , last_;
				first_ = last_ = nullptr;
			}
			else if (sz_ == 2)
			{
				delete last_;
				first_->next = nullptr;
				last_ = first_;
			}
			else
			{
				last_ = last_->previous;
				delete last_->next;
				last_->next = nullptr;
			}
			--sz_;
		}
	}

	template <class T>
	void list_t<T>::swap(list_t& other) noexcept
	{
		std::swap(first_, other.first_);
		std::swap(last_, other.last_);
		std::swap(sz_, other.sz_);
	}

	template <class T>
	void list_t<T>::clear()
	{
		while (sz_ > 0)
		{
			pop_front();
		}
	}

	template <class T>
	void list_t<T>::splice(list_t& x)
	{
		// Append the other list to this list:
		box* temp = x.first_;
		for (size_t i = 0; i < x.sz_; i++)
		{
			push_back(std::move(temp->value));
			temp = temp->next;
		}

		x.clear();
	}
}

#endif
