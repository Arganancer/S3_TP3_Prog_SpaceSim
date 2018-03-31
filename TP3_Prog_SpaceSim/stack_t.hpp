#ifndef STACK_T_HPP
#define STACK_T_HPP
namespace container_t
{
	template <class T>
	class stack_t
	{
		struct Box
		{
			T value;
			Box* previous;
			Box(const T& value, Box* previous) :value(value), previous(previous) {}
		};

		stack_t(const stack_t&);

		//Representation
		Box *first;
		size_t sz;

	public:

		//Constructeur et affectateur
		stack_t();
		~stack_t();
		stack_t& operator=(const stack_t<T>& other); //Actually useful?

		//Accesseur

		//Capacite
		bool empty() const;
		size_t size() const;

		//Fonction generatrice
		void push(const T& value);
		void pop();
		void swap(stack_t&) noexcept;
		T& top();
	};

	template <class T>
	inline stack_t<T>::stack_t(const stack_t& other)
	{
		sz = other.sz;
		first = other.first;
	}

	template <class T>
	inline stack_t<T>::stack_t()
	{
		sz = 0;
		first = nullptr;
	}

	template <class T>
	inline stack_t<T>::~stack_t()
	{
		Box* temp = nullptr;
		while (sz > 0)
		{
			temp = first;
			first = first->previous;
			delete temp;
			--sz;
		}
	}
	template <class T>
	stack_t<T>& stack_t<T>::operator=(const stack_t<T>& other)
	{
		Box* temp = other.first;
		delete first;
		first = temp;
		//sz = other.size();
		return *this;
	}

	template <class T>
	inline T& stack_t<T>::top()
	{
		return first->value;
	}

	template <class T>
	bool stack_t<T>::empty() const
	{
		if (sz == 0)
			return true;
		return false;
	}

	template <class T>
	size_t stack_t<T>::size() const
	{
		return sz;
	}

	template <class T>
	void stack_t<T>::push(const T& value)
	{
		if (sz == 0)
		{
			Box* node = new Box(value, nullptr);
			first = node;
		}
		else
		{
			Box* node = new Box(value, first);
			first = node;
		}
		++sz;
	}

	template <class T>
	void stack_t<T>::pop()
	{
		if (sz > 0)
		{
			Box* temp = first;
			first = first->previous;
			delete temp;
			--sz;
		}
	}

	template <class T>
	inline void stack_t<T>::swap(stack_t& other) noexcept
	{
		std::swap(this->first, other.first);
		std::swap(this->sz, other.sz);
	}

}

#endif