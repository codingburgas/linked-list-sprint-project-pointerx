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

	};

}
