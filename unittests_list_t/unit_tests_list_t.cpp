#include "stdafx.h"
#include "CppUnitTest.h"
#include "../TP3_Prog_SpaceSim/list_t.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace unit_tets_space_sim
{		
	TEST_CLASS(unittests_list_t)
	{
	public:
		TEST_METHOD(test_push_front_and_front_int)
		{
			// Setup
			container_t::list_t<int> list_test;
			const auto value_to_check = 4;
			// Test methods
			list_test.push_front(1);
			list_test.push_front(2);
			list_test.push_front(3);
			list_test.push_front(value_to_check);
			const auto front = list_test.front();
			// Validation
			Assert::AreEqual(front, value_to_check);
		}

		TEST_METHOD(test_iterator_begin_and_dereference)
		{
			// Setup
			container_t::list_t<int> list_test;
			const auto value_to_check = 4;
			list_test.push_front(1);
			list_test.push_front(2);
			list_test.push_front(3);
			list_test.push_front(value_to_check);
			// Test methods
			auto it = list_test.begin();
			// Validation
			Assert::AreEqual(*it, value_to_check);
		}

		TEST_METHOD(test_iterator_end_and_increment)
		{
			auto i = 1;
			// Setup
			container_t::list_t<int> list_test;
			list_test.push_front(4);
			list_test.push_front(3);
			list_test.push_front(2);
			list_test.push_front(1);
			// Test methods
			auto it = list_test.begin();
			auto nb_of_loops = 0;
			// Validation
			for (; it != list_test.end(); ++i, ++it)
			{
				++nb_of_loops;
			}
			Assert::AreEqual(4, nb_of_loops);
		}

		TEST_METHOD(test_iterator_end2)
		{
			// Setup
			container_t::list_t<int> list_test;
			// Test methods
			auto it = list_test.begin();
			// Validation
			for (; it != list_test.end(); ++it)
			{
				Assert::AreEqual(*it, 0);
			}
		}

		TEST_METHOD(test_push_front2)
		{
			// Pre-test Setup
			container_t::list_t<int> list_test;
			int nb_to_push_front[4]{ 1, 2, 3, 4 };

			// Test methods
			list_test.push_front(nb_to_push_front[3]);
			list_test.push_front(nb_to_push_front[2]);
			list_test.push_front(nb_to_push_front[1]);
			list_test.push_front(nb_to_push_front[0]);

			// Post-test setup
			auto it = list_test.begin();
			auto counter = 0;

			// Validation
			for (; it != list_test.end(); counter++, ++it)
			{
				Assert::AreEqual(*it, nb_to_push_front[counter]);
			}
		}

		TEST_METHOD(test_push_back)
		{
			// Pre-test Setup
			container_t::list_t<int> list_test;
			int nb_to_push_back[4]{ 1, 2, 3, 4 };

			// Test methods
			list_test.push_back(nb_to_push_back[0]);
			list_test.push_back(nb_to_push_back[1]);
			list_test.push_back(nb_to_push_back[2]);
			list_test.push_back(nb_to_push_back[3]);

			// Post-test setup
			auto it = list_test.begin();
			auto counter = 0;

			// Validation
			for (; it != list_test.end(); counter++, ++it)
			{
				Assert::AreEqual(*it, nb_to_push_back[counter]);
			}
		}

		TEST_METHOD(test_insert)
		{
			// Pre-test Setup
			container_t::list_t<int> list_test;
			int nb_to_push_back[7]{ 1, 10, 11, 12, 2, 3, 4,};

			list_test.push_back(nb_to_push_back[0]);
			list_test.push_back(nb_to_push_back[4]);
			list_test.push_back(nb_to_push_back[5]);
			list_test.push_back(nb_to_push_back[6]);

			auto it = list_test.begin();
			++it;

			// Test methods
			list_test.insert(it, 12);
			it = list_test.begin();
			++it;
			list_test.insert(it, 11);
			it = list_test.begin();
			++it;
			list_test.insert(it, 10);

			// Post-test setup
			it = list_test.begin();
			auto counter = 0;

			// Validation
			for (; it != list_test.end(); counter++, ++it)
			{
				Assert::AreEqual(*it, nb_to_push_back[counter]);
			}
		}

		TEST_METHOD(test_insert2)
		{
			// Pre-test Setup
			container_t::list_t<int> list_test;
			int nbs_to_insert[7]{ 1, 10, 11, 12, 2, 3, 4 };


			// Test methods
			for (auto i = 0; i < 7; i++)
			{
				const auto it = list_test.begin();
				list_test.insert(it, nbs_to_insert[i]);
			}

			// Post-test setup
			auto counter = 6;

			// Validation
			for (auto it = list_test.begin(); it != list_test.end(); --counter, ++it)
			{
				Assert::AreEqual(*it, nbs_to_insert[counter]);
			}
		}

		TEST_METHOD(test_insert3)
		{
			// Pre-test Setup
			container_t::list_t<int> list_test;
			int nbs_to_insert[7]{ 1, 10, 11, 12, 2, 3, 4 };

			auto counter = 1;

			const auto it1 = list_test.begin();
			list_test.insert(it1, nbs_to_insert[0]);

			while (list_test.size() < 7)
			{
				// Test methods
				for (auto it = list_test.begin(); it != list_test.end();)
				{
					const auto temp_it = it++;
					if (it == list_test.end())
					{
						list_test.insert(temp_it, nbs_to_insert[counter]);
						++counter;
					}
				}
			}

			// Post-test setup
			auto it = list_test.begin();

			// Insertion: 10, 11, 12, 2, 3, 4, 1
			// Validation
			Assert::AreEqual(*it, nbs_to_insert[1]), ++it;
			Assert::AreEqual(*it, nbs_to_insert[2]), ++it;
			Assert::AreEqual(*it, nbs_to_insert[3]), ++it;
			Assert::AreEqual(*it, nbs_to_insert[4]), ++it;
			Assert::AreEqual(*it, nbs_to_insert[5]), ++it;
			Assert::AreEqual(*it, nbs_to_insert[6]), ++it;
			Assert::AreEqual(*it, nbs_to_insert[0]);
		}

		TEST_METHOD(test_back)
		{
			// Pre-test Setup
			container_t::list_t<int> list_test;
			int nb_to_push_back[4]{ 1, 2, 3, 4 };
			list_test.push_back(nb_to_push_back[0]);
			list_test.push_back(nb_to_push_back[1]);
			list_test.push_back(nb_to_push_back[2]);
			list_test.push_back(nb_to_push_back[3]);

			// Test methods
			// Post-test setup
			// Validation
			Assert::AreEqual(4, list_test.back());
		}

		TEST_METHOD(test_empty_true)
		{
			// Pre-test Setup
			container_t::list_t<int> list_test;

			// Test methods
			// Post-test setup
			// Validation
			Assert::AreEqual(true, list_test.empty());
		}

		TEST_METHOD(test_empty_false)
		{
			// Pre-test Setup
			container_t::list_t<int> list_test;
			list_test.push_back(1);
			// Test methods
			// Post-test setup
			// Validation
			Assert::AreEqual(false, list_test.empty());
		}

		TEST_METHOD(test_equal_operator)
		{
			// Pre-test Setup
			container_t::list_t<int> list_test;
			container_t::list_t<int> list_test2;
			int nb_to_push_back[4]{ 1, 2, 3, 4, };

			list_test.push_back(nb_to_push_back[0]);
			list_test.push_back(nb_to_push_back[1]);
			list_test.push_back(nb_to_push_back[2]);
			list_test.push_back(nb_to_push_back[3]);

			// Test methods
			list_test2 = list_test;

			// Post-test setup
			auto it = list_test2.begin();

			// Validation
			Assert::AreEqual(*it, nb_to_push_back[0]), ++it;
			Assert::AreEqual(*it, nb_to_push_back[1]), ++it;
			Assert::AreEqual(*it, nb_to_push_back[2]), ++it;
			Assert::AreEqual(*it, nb_to_push_back[3]);
		}

		TEST_METHOD(test_iterator_decrement)
		{
			// Pre-test Setup
			container_t::list_t<int> list_test;
			int nb_to_push_back[4]{ 1, 2, 3, 4, };

			list_test.push_back(nb_to_push_back[0]);
			list_test.push_back(nb_to_push_back[1]);
			list_test.push_back(nb_to_push_back[2]);
			list_test.push_back(nb_to_push_back[3]);

			auto it = list_test.begin();

			// Test methods
			// Post-test setup
			// Validation
			Assert::AreEqual(*it, nb_to_push_back[0]), ++it;
			Assert::AreEqual(*it, nb_to_push_back[1]), ++it;
			Assert::AreEqual(*it, nb_to_push_back[2]), ++it;
			Assert::AreEqual(*it, nb_to_push_back[3]), --it;
			Assert::AreEqual(*it, nb_to_push_back[2]), --it;
			Assert::AreEqual(*it, nb_to_push_back[1]), --it;
			Assert::AreEqual(*it, nb_to_push_back[0]);
		}

		TEST_METHOD(test_size)
		{
			// Pre-test Setup
			container_t::list_t<int> list_test;
			int nb_to_push_back[4]{ 1, 2, 3, 4, };

			list_test.push_back(nb_to_push_back[0]);
			list_test.push_back(nb_to_push_back[1]);
			list_test.push_back(nb_to_push_back[2]);
			list_test.push_back(nb_to_push_back[3]);

			const size_t size = 4;

			// Test methods
			// Post-test setup
			// Validation
			Assert::AreEqual(size, list_test.size());
		}

		TEST_METHOD(test_pop_front)
		{
			// Pre-test Setup
			container_t::list_t<int> list_test;
			int nb_to_push_back[4]{ 1, 2, 3, 4, };

			list_test.push_back(nb_to_push_back[0]);
			list_test.push_back(nb_to_push_back[1]);
			list_test.push_back(nb_to_push_back[2]);
			list_test.push_back(nb_to_push_back[3]);

			const size_t size = 3;

			// Test methods
			list_test.pop_front();

			// Post-test setup
			auto it = list_test.begin();

			// Validation
			Assert::AreEqual(size, list_test.size());
			Assert::AreEqual(*it, nb_to_push_back[1]), ++it;
			Assert::AreEqual(*it, nb_to_push_back[2]), ++it;
			Assert::AreEqual(*it, nb_to_push_back[3]);
		}

		TEST_METHOD(test_pop_front2)
		{
			// Pre-test Setup
			container_t::list_t<int> list_test;
			int nb_to_push_back[4]{ 1, 2, 3, 4, };

			list_test.push_back(nb_to_push_back[0]);
			list_test.push_back(nb_to_push_back[1]);
			list_test.push_back(nb_to_push_back[2]);
			list_test.push_back(nb_to_push_back[3]);

			const size_t size = 0;

			// Test methods
			list_test.pop_front();
			list_test.pop_front();
			list_test.pop_front();
			list_test.pop_front();

			// Post-test setup
			// Validation
			Assert::AreEqual(size, list_test.size());
		}

		TEST_METHOD(test_pop_back)
		{
			// Pre-test Setup
			container_t::list_t<int> list_test;
			int nb_to_push_back[4]{ 1, 2, 3, 4, };

			list_test.push_back(nb_to_push_back[0]);
			list_test.push_back(nb_to_push_back[1]);
			list_test.push_back(nb_to_push_back[2]);
			list_test.push_back(nb_to_push_back[3]);

			const size_t size = 3;

			// Test methods
			list_test.pop_back();

			// Post-test setup
			auto it = list_test.begin();

			// Validation
			Assert::AreEqual(size, list_test.size());
			Assert::AreEqual(*it, nb_to_push_back[0]), ++it;
			Assert::AreEqual(*it, nb_to_push_back[1]), ++it;
			Assert::AreEqual(*it, nb_to_push_back[2]);
		}

		TEST_METHOD(test_pop_back2)
		{
			// Pre-test Setup
			container_t::list_t<int> list_test;
			int nb_to_push_back[4]{ 1, 2, 3, 4, };

			list_test.push_back(nb_to_push_back[0]);
			list_test.push_back(nb_to_push_back[1]);
			list_test.push_back(nb_to_push_back[2]);
			list_test.push_back(nb_to_push_back[3]);

			const size_t size = 0;

			// Test methods
			list_test.pop_back();
			list_test.pop_back();
			list_test.pop_back();
			list_test.pop_back();

			// Post-test setup
			// Validation
			Assert::AreEqual(size, list_test.size());
		}

		TEST_METHOD(test_swap)
		{
			// Pre-test Setup
			int nb_to_push_back1[4]{ 1, 2, 3, 4, };
			container_t::list_t<int> list_test1;
			const size_t size1 = 4;
			list_test1.push_back(nb_to_push_back1[0]);
			list_test1.push_back(nb_to_push_back1[1]);
			list_test1.push_back(nb_to_push_back1[2]);
			list_test1.push_back(nb_to_push_back1[3]);

			int nb_to_push_back2[5]{ 5, 6, 7, 8, 9, };
			container_t::list_t<int> list_test2;
			const size_t size2 = 5;
			list_test2.push_back(nb_to_push_back2[0]);
			list_test2.push_back(nb_to_push_back2[1]);
			list_test2.push_back(nb_to_push_back2[2]);
			list_test2.push_back(nb_to_push_back2[3]);
			list_test2.push_back(nb_to_push_back2[4]);

			// Test methods
			list_test2.swap(list_test1);

			// Post-test setup
			auto it1 = list_test1.begin();
			auto it2 = list_test2.begin();

			// Validation
			Assert::AreEqual(size1, list_test2.size());
			Assert::AreEqual(*it2, nb_to_push_back1[0]), ++it2;
			Assert::AreEqual(*it2, nb_to_push_back1[1]), ++it2;
			Assert::AreEqual(*it2, nb_to_push_back1[2]), ++it2;
			Assert::AreEqual(*it2, nb_to_push_back1[3]);

			Assert::AreEqual(size2, list_test1.size());
			Assert::AreEqual(*it1, nb_to_push_back2[0]), ++it1;
			Assert::AreEqual(*it1, nb_to_push_back2[1]), ++it1;
			Assert::AreEqual(*it1, nb_to_push_back2[2]), ++it1;
			Assert::AreEqual(*it1, nb_to_push_back2[3]), ++it1;
			Assert::AreEqual(*it1, nb_to_push_back2[4]);
		}

		TEST_METHOD(test_iterator_equal_operator)
		{
			// Pre-test Setup
			container_t::list_t<int> list_test;
			int nb_to_push_back[2]{ 1, 2, };

			list_test.push_back(nb_to_push_back[0]);
			list_test.push_back(nb_to_push_back[1]);

			const auto it1 = list_test.begin();
			const auto it2 = list_test.begin();
			auto it3 = list_test.begin();
			auto it4 = list_test.begin();
			const auto it5 = list_test.end();

			++it3;
			++it4;

			// Test methods
			const auto are_equal1 = it1 == it2;
			const auto are_equal2 = it3 == it4;
			const auto are_not_equal1 = it1 == it3;
			const auto are_not_equal2 = it1 == it5;

			// Post-test setup
			// Validation
			Assert::AreEqual(true, are_equal1);
			Assert::AreEqual(true, are_equal2);
			Assert::AreEqual(false, are_not_equal1);
			Assert::AreEqual(false, are_not_equal2);
		}

		TEST_METHOD(test_iterator_not_equal_operator)
		{
			// Pre-test Setup
			container_t::list_t<int> list_test;
			int nb_to_push_back[2]{ 1, 2, };

			list_test.push_back(nb_to_push_back[0]);
			list_test.push_back(nb_to_push_back[1]);

			const auto it1 = list_test.begin();
			const auto it2 = list_test.begin();
			auto it3 = list_test.begin();
			auto it4 = list_test.begin();
			const auto it5 = list_test.end();

			++it3;
			++it4;

			// Test methods
			const auto are_equal1 = it1 != it2;
			const auto are_equal2 = it3 != it4;
			const auto are_not_equal1 = it1 != it3;
			const auto are_not_equal2 = it1 != it5;

			// Post-test setup
			// Validation
			Assert::AreEqual(false, are_equal1);
			Assert::AreEqual(false, are_equal2);
			Assert::AreEqual(true, are_not_equal1);
			Assert::AreEqual(true, are_not_equal2);
		}

		TEST_METHOD(test_erase)
		{
			// Pre-test Setup
			container_t::list_t<int> list_test;
			const size_t size = 3;
			int nb_to_push_back[4]{ 1, 2, 3, 4};

			list_test.push_back(nb_to_push_back[0]);
			list_test.push_back(nb_to_push_back[1]);
			list_test.push_back(nb_to_push_back[2]);
			list_test.push_back(nb_to_push_back[3]);

			auto it = list_test.begin();
			++it;

			// Test methods
			list_test.erase(it);

			// Post-test setup
			it = list_test.begin();

			// Validation
			Assert::AreEqual(size, list_test.size());
			Assert::AreEqual(nb_to_push_back[0], *it), ++it;
			Assert::AreEqual(nb_to_push_back[2], *it), ++it;
			Assert::AreEqual(nb_to_push_back[3], *it);
		}

		TEST_METHOD(test_erase2)
		{
			// Pre-test Setup
			container_t::list_t<int> list_test;
			const size_t size = 0;
			int nb_to_push_back[4]{ 1, 2, 3, 4 };

			list_test.push_back(nb_to_push_back[0]);
			list_test.push_back(nb_to_push_back[1]);
			list_test.push_back(nb_to_push_back[2]);
			list_test.push_back(nb_to_push_back[3]);

			// Test methods
			for(auto it = list_test.begin();it != list_test.end();)
			{
				it = list_test.erase(it);
			}

			// Post-test setup
			// Validation
			Assert::AreEqual(size, list_test.size());
		}

		TEST_METHOD(test_erase_returned_iterator)
		{
			// Pre-test Setup
			container_t::list_t<int> list_test;
			int nb_to_push_back[3]{ 1, 2, 3 };

			list_test.push_back(nb_to_push_back[0]);
			list_test.push_back(nb_to_push_back[1]);
			list_test.push_back(nb_to_push_back[2]);

			auto it = list_test.begin();
			++it;

			// Test methods
			it = list_test.erase(it);

			// Post-test setup
			// Validation
			Assert::AreEqual(nb_to_push_back[2], *it);
		}

		TEST_METHOD(test_insert_returned_iterator)
		{
			// Pre-test Setup
			container_t::list_t<int> list_test;
			int nb_to_push_back[3]{ 1, 2, 3 };
			const auto nb_to_insert = 22;

			list_test.push_back(nb_to_push_back[0]);
			list_test.push_back(nb_to_push_back[1]);
			list_test.push_back(nb_to_push_back[2]);

			auto it = list_test.begin();
			++it;

			// Test methods
			it = list_test.insert(it, nb_to_insert);

			// Post-test setup
			// Validation
			Assert::AreEqual(nb_to_insert, *it);
		}

		// Test class to test list dereferencing and accessing class methods.
		class test
		{
		public:
			explicit test(int i)
			{
				value_ = i;
			}

			int get_value() const
			{
				return value_;
			}

		private:
			int value_;
		};

		TEST_METHOD(test_derefeferencing_class_method_accessing)
		{
			// Pre-test Setup
			container_t::list_t<test*> list_test;
			list_test.push_back(new test(1));
			list_test.push_back(new test(2));
			list_test.push_back(new test(3));

			auto it = list_test.begin();

			// Test methods
			int nbs[3];
			for (auto i = 0; it != list_test.end(); ++it, ++i)
			{
				nbs[i] = it->get_value();
			}
			// Post-test setup
			it = list_test.begin();

			// Validation
			Assert::AreEqual(nbs[0], it->get_value()), ++it;
			Assert::AreEqual(nbs[1], it->get_value()), ++it;
			Assert::AreEqual(nbs[2], it->get_value());
		}

		TEST_METHOD(test_operator_append)
		{
			// Pre-test Setup
			int nb_to_push_back[7]{ 1, 2, 3, 4, 5, 6, 7};
			container_t::list_t<test*> list_test1;
			list_test1.push_back(new test(nb_to_push_back[0]));
			list_test1.push_back(new test(nb_to_push_back[1]));
			list_test1.push_back(new test(nb_to_push_back[2]));

			container_t::list_t<test*> list_test2;
			list_test2.push_back(new test(nb_to_push_back[3]));
			list_test2.push_back(new test(nb_to_push_back[4]));
			list_test2.push_back(new test(nb_to_push_back[5]));
			list_test2.push_back(new test(nb_to_push_back[6]));

			// Test methods
			list_test1 += list_test2;

			// Post-test setup
			auto it = list_test1.begin();
			auto it2 = list_test2.begin();

			// Validation
			Assert::AreEqual(nb_to_push_back[0], it->get_value()), ++it;
			Assert::AreEqual(nb_to_push_back[1], it->get_value()), ++it;
			Assert::AreEqual(nb_to_push_back[2], it->get_value()), ++it;
			Assert::AreEqual(nb_to_push_back[3], it->get_value()), ++it;
			Assert::AreEqual(nb_to_push_back[4], it->get_value()), ++it;
			Assert::AreEqual(nb_to_push_back[5], it->get_value()), ++it;
			Assert::AreEqual(nb_to_push_back[6], it->get_value());

			Assert::AreEqual(nb_to_push_back[3], it2->get_value()), ++it2;
			Assert::AreEqual(nb_to_push_back[4], it2->get_value()), ++it2;
			Assert::AreEqual(nb_to_push_back[5], it2->get_value()), ++it2;
			Assert::AreEqual(nb_to_push_back[6], it2->get_value());
		}

		TEST_METHOD(test_clear)
		{
			// Pre-test Setup
			const size_t empty = 0;
			int nb_to_push_back[3]{ 1, 2, 3 };
			container_t::list_t<test*> list_test1;
			list_test1.push_back(new test(nb_to_push_back[0]));
			list_test1.push_back(new test(nb_to_push_back[1]));
			list_test1.push_back(new test(nb_to_push_back[2]));

			// Test methods
			list_test1.clear();

			// Post-test setup
			// Validation
			Assert::AreEqual(empty, list_test1.size());
		}

		TEST_METHOD(test_splice)
		{
			// Pre-test Setup
			const size_t size1 = 7;
			const size_t size2 = 0;

			int nb_to_push_back[7]{ 1, 2, 3, 4, 5, 6, 7};
			container_t::list_t<test*> list_test1;
			list_test1.push_back(new test(nb_to_push_back[0]));
			list_test1.push_back(new test(nb_to_push_back[1]));
			list_test1.push_back(new test(nb_to_push_back[2]));

			container_t::list_t<test*> list_test2;
			list_test2.push_back(new test(nb_to_push_back[3]));
			list_test2.push_back(new test(nb_to_push_back[4]));
			list_test2.push_back(new test(nb_to_push_back[5]));
			list_test2.push_back(new test(nb_to_push_back[6]));

			// Test methods
			list_test1.splice(list_test2);

			// Post-test setup
			// Validation
			Assert::AreEqual(size1, list_test1.size());
			Assert::AreEqual(size2, list_test2.size());
		}
	};
}