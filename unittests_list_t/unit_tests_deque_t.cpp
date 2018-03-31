#include "stdafx.h"
#include "CppUnitTest.h"
#include "../TP3_Prog_SpaceSim/deque_t.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace unit_tets_space_sim
{
	TEST_CLASS(unittests_deque_t)
	{
	public:
		TEST_METHOD(test_push_back)
		{
			// Setup
			container_t::deque_t<int> deque_test;
			const int values[4]{ 1, 2, 3, 4 };

			// Test methods
			deque_test.push_back(values[0]);
			deque_test.push_back(values[1]);
			deque_test.push_back(values[2]);
			deque_test.push_back(values[3]);

			// Validation
			Assert::AreEqual(values[0], deque_test[0]);
			Assert::AreEqual(values[1], deque_test[1]);
			Assert::AreEqual(values[2], deque_test[2]);
			Assert::AreEqual(values[3], deque_test[3]);
		}

		TEST_METHOD(test_push_front)
		{
			// Setup
			container_t::deque_t<int> deque_test;
			const int values[4]{ 1, 2, 3, 4 };

			// Test methods
			deque_test.push_front(values[0]);
			deque_test.push_front(values[1]);
			deque_test.push_front(values[2]);
			deque_test.push_front(values[3]);

			// Validation
			Assert::AreEqual(deque_test[0], values[3]);
			Assert::AreEqual(deque_test[1], values[2]);
			Assert::AreEqual(deque_test[2], values[1]);
			Assert::AreEqual(deque_test[3], values[0]);
		}

		TEST_METHOD(test_specified_constructor)
		{
			// Setup
			const unsigned long desired_capacity = 5;
			container_t::deque_t<int> deque_test(desired_capacity);

			// Test methods
			const auto actual_capacity = deque_test.capacity();

			// Validation
			Assert::AreEqual(actual_capacity, desired_capacity);
		}

		TEST_METHOD(test_empty_true)
		{
			// Setup
			container_t::deque_t<int> deque_test;
			const auto desired_outcome = true;

			// Test methods
			const auto is_empty = deque_test.empty();

			// Validation
			Assert::AreEqual(is_empty, desired_outcome);
		}

		TEST_METHOD(test_empty_false)
		{
			// Pre-test Setup
			container_t::deque_t<int> deque_test;
			const auto desired_outcome = false;
			deque_test.push_back(0);

			// Test methods
			const auto is_empty = deque_test.empty();

			// Validation
			Assert::AreEqual(is_empty, desired_outcome);
		}

		TEST_METHOD(test_size)
		{
			// Setup
			container_t::deque_t<int> deque_test;
			const int values[4]{ 1, 2, 3, 4 };
			const unsigned long desired_size = 4;
			deque_test.push_front(values[0]);
			deque_test.push_front(values[1]);
			deque_test.push_front(values[2]);
			deque_test.push_front(values[3]);

			// Test methods
			const auto actual_size = deque_test.size();

			// Validation
			Assert::AreEqual(actual_size, desired_size);
		}

		TEST_METHOD(test_size2)
		{
			// Setup
			container_t::deque_t<int> deque_test;
			const unsigned long desired_size = 0;

			// Test methods
			const unsigned long actual_size = deque_test.size();

			// Validation
			Assert::AreEqual(actual_size, desired_size);
		}

		TEST_METHOD(test_cap)
		{
			// Setup
			container_t::deque_t<int> deque_test;
			const int values[4]{ 1, 2, 3, 4 };
			const unsigned long cap_desired_value = 7;
			deque_test.push_front(values[0]);
			deque_test.push_front(values[1]);
			deque_test.push_front(values[2]);
			deque_test.push_front(values[3]);

			// Test methods
			const auto cap_actual_value = deque_test.capacity();

			// Validation
			Assert::AreEqual(cap_actual_value, cap_desired_value);
		}

		TEST_METHOD(test_cap2)
		{
			// Setup
			container_t::deque_t<int> deque_test;
			const unsigned long desired_cap = 0;

			// Test methods
			const unsigned long actual_cap = deque_test.capacity();

			// Validation
			Assert::AreEqual(actual_cap, desired_cap);
		}

		TEST_METHOD(test_push_front_push_back)
		{
			// Setup
			container_t::deque_t<int> deque_test;
			const int values[8]{ 1, 2, 3, 4, 5, 6, 7, 8};
			const unsigned long cap = 15;
			const unsigned long size = 8;

			// Test methods
			deque_test.push_front(values[0]);
			deque_test.push_front(values[1]);
			deque_test.push_front(values[2]);
			deque_test.push_front(values[3]);
			deque_test.push_back(values[4]);
			deque_test.push_back(values[5]);
			deque_test.push_back(values[6]);
			deque_test.push_back(values[7]);

			// Validation
			Assert::AreEqual(deque_test[0], values[3]);
			Assert::AreEqual(deque_test[1], values[2]);
			Assert::AreEqual(deque_test[2], values[1]);
			Assert::AreEqual(deque_test[3], values[0]);
			Assert::AreEqual(deque_test[4], values[4]);
			Assert::AreEqual(deque_test[5], values[5]);
			Assert::AreEqual(deque_test[6], values[6]);
			Assert::AreEqual(deque_test[7], values[7]);
			Assert::AreEqual(deque_test.size(), size);
			Assert::AreEqual(deque_test.capacity(), cap);
		}

		TEST_METHOD(test_pop_front)
		{
			// Setup
			container_t::deque_t<int> deque_test;
			const int values[8]{ 1, 2, 3, 4, 5, 6, 7, 8 };
			const unsigned long cap = 15;
			const unsigned long size = 7;

			deque_test.push_front(values[0]);
			deque_test.push_front(values[1]);
			deque_test.push_front(values[2]);
			deque_test.push_front(values[3]);
			deque_test.push_back(values[4]);
			deque_test.push_back(values[5]);
			deque_test.push_back(values[6]);
			deque_test.push_back(values[7]);

			// Test methods
			deque_test.pop_front();

			// Validation
			Assert::AreEqual(deque_test[0], values[2]);
			Assert::AreEqual(deque_test[1], values[1]);
			Assert::AreEqual(deque_test[2], values[0]);
			Assert::AreEqual(deque_test[3], values[4]);
			Assert::AreEqual(deque_test[4], values[5]);
			Assert::AreEqual(deque_test[5], values[6]);
			Assert::AreEqual(deque_test[6], values[7]);

			Assert::AreEqual(deque_test.size(), size);
			Assert::AreEqual(deque_test.capacity(), cap);
		}

		TEST_METHOD(test_pop_back)
		{
			// Pre-test Setup
			container_t::deque_t<int> deque_test;
			const int values[8]{ 1, 2, 3, 4, 5, 6, 7, 8 };
			const unsigned long cap = 15;
			const unsigned long size = 8;

			deque_test.push_front(values[0]);
			deque_test.push_front(values[1]);
			deque_test.push_front(values[2]);
			deque_test.push_front(values[3]);
			deque_test.push_back(values[4]);
			deque_test.push_back(values[5]);
			deque_test.push_back(values[6]);
			deque_test.push_back(values[7]);

			// Test methods
			deque_test.pop_back();

			// Post-test setup
			deque_test.push_back(values[0]);

			// Validation
			Assert::AreEqual(deque_test[0], values[3]);
			Assert::AreEqual(deque_test[1], values[2]);
			Assert::AreEqual(deque_test[2], values[1]);
			Assert::AreEqual(deque_test[3], values[0]);
			Assert::AreEqual(deque_test[4], values[4]);
			Assert::AreEqual(deque_test[5], values[5]);
			Assert::AreEqual(deque_test[6], values[6]);
			Assert::AreEqual(deque_test[7], values[0]);

			Assert::AreEqual(deque_test.size(), size);
			Assert::AreEqual(deque_test.capacity(), cap);
		}

		TEST_METHOD(test_copy_constructor)
		{
			// Pre-test Setup
			container_t::deque_t<int> deque_test1;
			const int values[4]{ 1, 2, 3, 4 };
			const unsigned long cap = 7;
			const unsigned long size = 4;

			deque_test1.push_front(values[0]);
			deque_test1.push_front(values[1]);
			deque_test1.push_front(values[2]);
			deque_test1.push_front(values[3]);

			// Test methods
			auto deque_test2 = deque_test1;

			// Post-test setup
			// Validation
			Assert::AreEqual(deque_test2[0], values[3]);
			Assert::AreEqual(deque_test2[1], values[2]);
			Assert::AreEqual(deque_test2[2], values[1]);
			Assert::AreEqual(deque_test2[3], values[0]);

			Assert::AreEqual(deque_test1[0], values[3]);
			Assert::AreEqual(deque_test1[1], values[2]);
			Assert::AreEqual(deque_test1[2], values[1]);
			Assert::AreEqual(deque_test1[3], values[0]);

			Assert::AreEqual(deque_test2.empty(), false);
			Assert::AreEqual(deque_test2.size(), size);
			Assert::AreEqual(deque_test2.capacity(), cap);
		}

		TEST_METHOD(test_accessor_operator)
		{
			// Pre-test Setup
			container_t::deque_t<int> deque_test;
			const int values1[4]{ 1, 2, 3, 4 };
			const int values2[4]{ 4, 5, 6, 7 };
			const unsigned long cap = 7;
			const unsigned long size = 4;

			deque_test.push_front(values1[0]);
			deque_test.push_front(values1[1]);
			deque_test.push_front(values1[2]);
			deque_test.push_front(values1[3]);

			// Test methods
			deque_test[0] = values2[0];
			deque_test[1] = values2[1];
			deque_test[2] = values2[2];
			deque_test[3] = values2[3];

			// Post-test setup
			// Validation
			Assert::AreEqual(deque_test[0], values2[0]);
			Assert::AreEqual(deque_test[1], values2[1]);
			Assert::AreEqual(deque_test[2], values2[2]);
			Assert::AreEqual(deque_test[3], values2[3]);

			Assert::AreEqual(deque_test.empty(), false);
			Assert::AreEqual(deque_test.size(), size);
			Assert::AreEqual(deque_test.capacity(), cap);
		}

		TEST_METHOD(test_reserve)
		{
			// Pre-test Setup
			container_t::deque_t<int> deque_test;
			const unsigned long capacity_to_reserve = 97;
			const unsigned long size = 0;

			// Test methods
			deque_test.reserve(capacity_to_reserve);

			// Post-test setup
			const unsigned long actual_capacity = deque_test.capacity();

			// Validation
			Assert::AreEqual(deque_test.empty(), true);
			Assert::AreEqual(deque_test.size(), size);
			Assert::AreEqual(deque_test.capacity(), capacity_to_reserve);
		}

		TEST_METHOD(test_resize)
		{
			// Pre-test Setup
			container_t::deque_t<int> deque_test;
			const int values[6]{ 1, 2, 3, 4, 5, 6 };
			const unsigned long cap = 7;
			const unsigned long desired_size = 4;

			deque_test.push_back(values[0]);
			deque_test.push_back(values[1]);
			deque_test.push_back(values[2]);
			deque_test.push_back(values[3]);
			deque_test.push_back(values[4]);
			deque_test.push_back(values[5]);

			// Test methods
			deque_test.resize(desired_size);

			// Post-test setup
			const unsigned long actual_size = deque_test.size();

			// Validation
			Assert::AreEqual(deque_test[0], values[0]);
			Assert::AreEqual(deque_test[1], values[1]);
			Assert::AreEqual(deque_test[2], values[2]);
			Assert::AreEqual(deque_test[3], values[3]);

			Assert::AreEqual(deque_test.empty(), false);
			Assert::AreEqual(actual_size, desired_size);
			Assert::AreEqual(deque_test.capacity(), cap);
		}

		TEST_METHOD(test_clear)
		{
			// Pre-test Setup
			container_t::deque_t<int> deque_test;
			const int values[6]{ 1, 2, 3, 4, 5, 6 };
			const unsigned long desired_cap = 0;
			const unsigned long desired_size = 0;

			deque_test.push_back(values[0]);
			deque_test.push_back(values[1]);
			deque_test.push_back(values[2]);
			deque_test.push_back(values[3]);
			deque_test.push_back(values[4]);
			deque_test.push_back(values[5]);

			// Test methods
			deque_test.clear();

			// Post-test setup
			// Validation
			Assert::AreEqual(deque_test.empty(), true);
			Assert::AreEqual(deque_test.size(), desired_size);
			Assert::AreEqual(deque_test.capacity(), desired_cap);
		}

		TEST_METHOD(test_swap)
		{
			// Pre-test Setup
			container_t::deque_t<int> deque_test1;
			container_t::deque_t<int> deque_test2;
			const int values1[4]{ 1, 2, 3, 4 };
			const int values2[4]{ 5, 6, 7, 8 };
			const unsigned long cap = 7;
			const unsigned long size = 4;

			deque_test1.push_front(values1[0]);
			deque_test1.push_front(values1[1]);
			deque_test1.push_front(values1[2]);
			deque_test1.push_front(values1[3]);

			deque_test2.push_front(values2[0]);
			deque_test2.push_front(values2[1]);
			deque_test2.push_front(values2[2]);
			deque_test2.push_front(values2[3]);

			// Test methods
			deque_test1.swap(deque_test2);

			// Post-test setup
			// Validation
			Assert::AreEqual(deque_test2[0], values1[3]);
			Assert::AreEqual(deque_test2[1], values1[2]);
			Assert::AreEqual(deque_test2[2], values1[1]);
			Assert::AreEqual(deque_test2[3], values1[0]);
			Assert::AreEqual(deque_test2.empty(), false);
			Assert::AreEqual(deque_test2.size(), size);
			Assert::AreEqual(deque_test2.capacity(), cap);

			Assert::AreEqual(deque_test1[0], values2[3]);
			Assert::AreEqual(deque_test1[1], values2[2]);
			Assert::AreEqual(deque_test1[2], values2[1]);
			Assert::AreEqual(deque_test1[3], values2[0]);
			Assert::AreEqual(deque_test1.empty(), false);
			Assert::AreEqual(deque_test1.size(), size);
			Assert::AreEqual(deque_test1.capacity(), cap);
		}
	};
}