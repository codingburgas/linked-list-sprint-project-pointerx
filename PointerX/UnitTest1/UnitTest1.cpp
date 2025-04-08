#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(Class1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			//Arrange
			Node* head = new Node{ {"2025-05-01", "Initial Title", "Initial Topic"}, nullptr };

			//Act
			addEventSorted(head);
		
			//Assert
			Assert::AreEqual("2025-05-01", head->data.date.c_str());


		}

		TEST_METHOD(TestMethod3)
		{
			Node* head = new Node{ {"2025-05-01", "Initial Title", "Initial Topic"}, nullptr };

			printAllEvents(head);

			Assert::AreEqual("2025-05-01", head->data.date.c_str());


		}
	};

	TEST_CLASS(class2)
	{
	public:

		TEST_METHOD(TestMethod2)
		{
			Node* head = new Node{ {"2025-05-01", "Initial Title", "Initial Topic"}, nullptr };
			addEventSorted(head);

		}

		TEST_METHOD(TestMethod4)
		{
			Node* head = new Node{ {"2025-05-01", "Initial Title", "Initial Topic"}, nullptr };
			deleteEvent(head);

			Assert::AreEqual("2025-05-01", head->data.date.c_str());
		}

		TEST_METHOD(TestMethod5)
		{
			Node* head = new Node{ {"2025-05-01", "Initial Title", "Initial Topic"}, nullptr };
			editEvent(head);

			Assert::AreEqual("2025-05-01", head->data.date.c_str());
		}
	};

}
