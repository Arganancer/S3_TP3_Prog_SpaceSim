#include "stdafx.h"
#include "CppUnitTest.h"
#include "../TP3_Prog_SpaceSim/stack_t.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace unit_tets_space_sim
{
	////Constructeur et affectateur
	//stack_t(); Testé
	//~stack_t(); Testé
	////stack_t& operator=(const stack_t<T>&); 

	////Accesseur

	////Capacite
	//bool empty() const; Testé
	//size_t size() const; testé

	////Fonction generatrice
	//void push(const T& value); testé
	//void pop(); testé
	//void swap(stack_t&) noexcept; testé
	//T& top(); testé par les autres tests

	TEST_CLASS(unittests_stack_t)
	{
	public:
		TEST_METHOD(test_stack_push)
		{
			// Setup
			container_t::stack_t<int> stack_test;
			const auto value_to_check = 4;
			// Test methods
			stack_test.push(1);
			stack_test.push(2);
			stack_test.push(3);
			stack_test.push(value_to_check);
			const auto front = stack_test.top();
			// Validation
			Assert::AreEqual(front, value_to_check);
		}
		TEST_METHOD(test_push2)
		{
			// Setup
			container_t::stack_t<int> stack_test;
			const auto value_to_check = 4;
			// Test methods
			stack_test.push(1);
			stack_test.push(2);
			stack_test.push(value_to_check);
			stack_test.push(3);
			const auto front = stack_test.top();
			// Validation
			Assert::AreNotEqual(front, value_to_check);
		}
		TEST_METHOD(test_pop_it)
		{
			// Setup
			container_t::stack_t<int> stack_test;
			const auto value_to_check = 4;
			// Test methods
			stack_test.push(1);
			stack_test.push(2);
			stack_test.push(value_to_check);
			stack_test.push(3);
			stack_test.pop();
			const auto front = stack_test.top();
			// Validation
			Assert::AreEqual(front, value_to_check);
		}
		TEST_METHOD(test_pop_it2)
		{
			// Setup
			container_t::stack_t<int> stack_test;
			const auto value_to_check = 4;
			// Test methods
			stack_test.push(1);
			stack_test.push(2);
			stack_test.push(3);
			stack_test.push(value_to_check);
			stack_test.pop();
			const auto front = stack_test.top();
			// Validation
			Assert::AreNotEqual(front, value_to_check);
		}
		TEST_METHOD(test_empty)
		{
			// Setup
			container_t::stack_t<int> stack_test;
			// Test methods
			stack_test.push(1);
			stack_test.pop();
			// Validation
			Assert::IsTrue(stack_test.empty());
		}
		TEST_METHOD(test_empty2)
		{
			// Setup
			container_t::stack_t<int> stack_test;
			// Test methods
			//none
			// Validation
			Assert::IsTrue(stack_test.empty());
		}
		TEST_METHOD(test_size)
		{
			// Setup
			container_t::stack_t<int> stack_test;
			const size_t value_to_check = 4;
			// Test methods
			stack_test.push(1);
			stack_test.push(2);
			stack_test.push(3);
			stack_test.push(4);
			const auto size = stack_test.size();
			// Validation
			Assert::AreEqual(size, value_to_check);
		}
		TEST_METHOD(test_size2)
		{
			// Setup
			container_t::stack_t<int> stack_test;
			const size_t value_to_check = 0;
			// Test methods
			const auto size = stack_test.size();
			// Validation
			Assert::AreEqual(size, value_to_check);
		}
		TEST_METHOD(test_swap_stacks)
		{
			// Setup
			container_t::stack_t<int> stack_test;
			container_t::stack_t<int> stack_test2;
			const auto value_to_check = 4;
			// Test methods
			stack_test2.push(1);
			stack_test2.push(2);
			stack_test2.push(3);
			stack_test2.push(value_to_check);

			stack_test.swap(stack_test2);
			const auto front = stack_test.top();
			// Validation
			Assert::AreEqual(front, value_to_check);
		}
		TEST_METHOD(test_swap_stacks2)
		{
			// Setup
			container_t::stack_t<int> stack_test;
			container_t::stack_t<int> stack_test2;
			const auto value_to_check = 4;
			// Test methods
			stack_test2.push(1);
			stack_test2.push(2);
			stack_test2.push(3);
			stack_test2.push(5);

			stack_test.push(value_to_check);
			stack_test.swap(stack_test2);

			const auto front = stack_test2.top();
			// Validation
			Assert::AreEqual(front, value_to_check);
		}
		TEST_METHOD(test_op_egal)
		{
			// Setup
			container_t::stack_t<int> stack_test;
			container_t::stack_t<int> stack_test2;
			const auto value_to_check = 4;
			// Test methods
			stack_test2.push(1);
			stack_test2.push(2);
			stack_test2.push(3);
			stack_test2.push(value_to_check);

			stack_test = stack_test2;

			const auto front = stack_test.top();
			// Validation
			Assert::AreEqual(front, value_to_check);
		}
	};
}