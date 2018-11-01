using System;
using System.Text;
using System.Collections.Generic;
using System.Linq;

using Hotel;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using Hotel.ViewModels.Shared;

namespace Hotel.Tests.ViewModels.Shared
{
	/// <summary>
	/// Summary description for UnitTest1
	/// </summary>
	[TestClass]
	public class PagerTest
	{
		public PagerTest()
		{
			//
			// TODO: Add constructor logic here
			//
		}

		private TestContext testContextInstance;

		/// <summary>
		///Gets or sets the test context which provides
		///information about and functionality for the current test run.
		///</summary>
		public TestContext TestContext
		{
			get
			{
				return testContextInstance;
			}
			set
			{
				testContextInstance = value;
			}
		}

		#region Additional test attributes
		//
		// You can use the following additional attributes as you write your tests:
		//
		// Use ClassInitialize to run code before running the first test in the class
		// [ClassInitialize()]
		// public static void MyClassInitialize(TestContext testContext) { }
		//
		// Use ClassCleanup to run code after all tests in a class have run
		// [ClassCleanup()]
		// public static void MyClassCleanup() { }
		//
		// Use TestInitialize to run code before running each test 
		// [TestInitialize()]
		// public void MyTestInitialize() { }
		//
		// Use TestCleanup to run code after each test has run
		// [TestCleanup()]
		// public void MyTestCleanup() { }
		//
		#endregion



		private void AssertConstructorArgumentOutOfRange(int currentPage, int pageSize, int totalRows, string argumentName)
		{
			try
			{
				Pager pager = CreateAndInitPager(currentPage, pageSize, totalRows);
			}
			catch (ArgumentOutOfRangeException e)
			{
				Assert.AreEqual(e.ParamName, argumentName);
				return;
			}

			Assert.Fail("Expected exception for argument " + argumentName + ".");
		}


		[TestMethod]
		public void Construct_With_Invalid_Args_Throws()
		{
			AssertConstructorArgumentOutOfRange(-1, 10, 20, "currentPage");
			AssertConstructorArgumentOutOfRange(0, 10, 20, "currentPage");

			AssertConstructorArgumentOutOfRange(1, 0, 20, "pageSize");
			AssertConstructorArgumentOutOfRange(1, -5, 20, "pageSize");

			AssertConstructorArgumentOutOfRange(1, 10, -1, "totalRows");
		}


		private Pager CreateAndInitPager(int currentPage, int pageSize, int totalRows)
		{
			var pager = new Pager(currentPage, pageSize, totalRows);
			pager.Init();

			return pager;
		}

		[TestMethod]
		public void Pager_Not_Be_Visible_If_TotalRows_Zero()
		{
			var pager = CreateAndInitPager(1, 10, 0);
			Assert.IsFalse(pager.IsVisible);
		}

		[TestMethod]
		public void Nav_Not_Visible_If_One_Page()
		{
			var pager = CreateAndInitPager(1, 10, 5);
			Assert.IsFalse(pager.IsNavVisible);
		}


		[TestMethod]
		public void Nav_Visible_If_More_Then_One_Page()
		{
			var pager = CreateAndInitPager(1, 10, 15);
			Assert.IsTrue(pager.IsNavVisible);

		}

		[TestMethod]
		public void Test_RowStats()
		{
			var pager = CreateAndInitPager(1, 10, 5);
			Assert.AreEqual("Rows 1-5 of 5", pager.RowStats);

			pager = CreateAndInitPager(1, 10, 15);
			Assert.AreEqual("Rows 1-10 of 15", pager.RowStats);

			pager = CreateAndInitPager(1, 1, 5);
			Assert.AreEqual("Row 1 of 5", pager.RowStats);
		}


		[TestMethod]
		public void Test_FirstLast_For_One_Incomplete_Page()
		{
			var pager = CreateAndInitPager(1, 10, 5);

			Assert.AreEqual(1, pager.TotalPages);
			Assert.AreEqual(1, pager.FirstPage);
			Assert.AreEqual(1, pager.LastPage);

			Assert.IsTrue(pager.IsFirstPage);
			Assert.IsTrue(pager.IsLastPage);
		}


		[TestMethod]
		public void Test_FirstLast_For_One_Complete_Page()
		{
			var pager = CreateAndInitPager(1, 10, 10);

			Assert.AreEqual(1, pager.TotalPages);
			Assert.AreEqual(1, pager.FirstPage);
			Assert.AreEqual(1, pager.LastPage);

			Assert.IsTrue(pager.IsFirstPage);
			Assert.IsTrue(pager.IsLastPage);

		}

		[TestMethod]
		public void Test_FirstLast_For_Two_Pages_Second_Incomplete()
		{
			var pager = CreateAndInitPager(1, 10, 15);

			Assert.AreEqual(2, pager.TotalPages);

			Assert.AreEqual(1, pager.FirstPage);
			Assert.AreEqual(2, pager.LastPage);

			Assert.IsTrue(pager.IsFirstPage);
			Assert.IsFalse(pager.IsLastPage);

		}

		[TestMethod]
		public void Test_FirstLast_For_Two_Complete_Pages()
		{
			var pager = CreateAndInitPager(1, 10, 20);

			Assert.AreEqual(2, pager.TotalPages);

			Assert.AreEqual(1, pager.FirstPage);
			Assert.AreEqual(2, pager.LastPage);

			Assert.IsTrue(pager.IsFirstPage);
			Assert.IsFalse(pager.IsLastPage);
		}




		[TestMethod]
		[ExpectedException(typeof(InvalidOperationException), "No previous page when on first page.")]
		public void PreviousPage_Throws_If_On_First_Page()
		{
			var pager = CreateAndInitPager(1, 10, 25);
			
			int prevPage=pager.PreviousPage;
		}


		[TestMethod]
		[ExpectedException(typeof(InvalidOperationException), "No previous page when on first page.")]
		public void NextPage_Throws_If_On_Last_Page()
		{
			var pager = CreateAndInitPager(3, 10, 25);

			int nextPage = pager.NextPage;
		}


		[TestMethod]
		public void Test_PrevNext_For_Three_Pages_With_First_Page_Selected()
		{
			var pager = CreateAndInitPager(1, 10, 25);

			Assert.AreEqual(2, pager.NextPage);
		}

		[TestMethod]
		public void Test_PrevNext_For_Three_Pages_With_Second_Page_Selected()
		{
			var pager = CreateAndInitPager(2, 10, 25);

			Assert.AreEqual(1, pager.PreviousPage);
			Assert.AreEqual(3, pager.NextPage);
		}


		[TestMethod]
		public void Test_PrevNext_For_Three_Pages_With_Third_Page_Selected()
		{
			var pager = CreateAndInitPager(3, 10, 25);

			Assert.AreEqual(2, pager.PreviousPage);
		}
	}


}
