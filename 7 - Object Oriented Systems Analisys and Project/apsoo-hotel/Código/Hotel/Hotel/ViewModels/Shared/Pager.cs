using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Diagnostics;
using System.Linq;
using System.Web;


namespace Hotel.ViewModels.Shared
{

	public class Pager
	{
		private int _currentPage;
		private int _pageSize;
		private int _totalRows;

		private bool _isVisible;
		private bool _isNavVisible;

		private string _rowStats;

		private int _totalPages;

		private int _firstPage;
		private int _lastPage;
		
		private bool _isFirstPage;
		private bool _isLastPage;

		private int _nextPage;
		private int _previousPage;


		//Properties
		public int CurrentPage
		{
			get { return _currentPage;} 
			set { _currentPage = value;} 
		}

		public int PageSize
		{
			get { return _pageSize;} 
			set { _pageSize = value;} 
		}

		public int TotalRows
		{
			get { return _totalRows; }
			set { _totalRows = value; }
		}

		public bool IsVisible
		{
			get { return _isVisible; }
		}


		public bool IsNavVisible
		{
			get { return _isNavVisible; }
		}
        
		public string RowStats
		{
			get { return _rowStats; }
		}

		public int TotalPages
		{
			get { return _totalPages; }
		}

		public int FirstPage
		{
			get { return _firstPage; }
		}

		public int LastPage
		{
			get { return _lastPage; }
		}

		public bool IsFirstPage
		{
			get { return _isFirstPage; }
		}

		public bool IsLastPage
		{
			get { return _isLastPage; }
		}


		public int PreviousPage
		{
			get
			{
				if (_isFirstPage)
					throw new InvalidOperationException("No previous page when on first page.");
				return _previousPage;
			}
		}


		public int NextPage
		{
			get 
			{
				if (_isLastPage)
					throw new InvalidOperationException("No next page when on last page.");
			
				return _nextPage; 
			}
		}


		public Pager()
		{
			_currentPage = 1;
			_pageSize = 10;
		}


		public Pager(int currentPage, int pageSize, int totalRows)
		{
			Verify.Argument.IsPositive(currentPage, "currentPage");
			Verify.Argument.IsPositive(pageSize, "pageSize");
			Verify.Argument.IsPositiveOrZero(totalRows, "totalRows");

			_currentPage = currentPage;
			_pageSize = pageSize;
			_totalRows = totalRows;
		}


		public void Init(int totalRows)
		{
			Verify.Argument.IsPositiveOrZero(totalRows, "totalRows");
			
			_totalRows = totalRows;

			Init();
		}


		public void Init()
		{
			Verify.Argument.IsPositive(_currentPage, "_currentPage");
			Verify.Argument.IsPositive(_pageSize, "_pageSize");
			Verify.Argument.IsPositiveOrZero(_totalRows, "_totalRows");

			if (_totalRows == 0)
			{
				_totalPages = 0;
				_isVisible = false;

				return;
			}
			
			_isVisible = true;

			_totalPages = CalculateTotalPages(_totalRows, _pageSize);

			//handle a case when user deleted all rows on last page
			if (_currentPage > _totalPages)
				_currentPage = _totalPages;

			_rowStats = GenPagerStats(_totalRows, _currentPage, _pageSize);
			
            InitNav();
		}


		private void InitNav()
		{
			if (_totalPages == 1)
			{
				_isNavVisible = false;
				_firstPage = 1;
				_lastPage = 1;
				_isFirstPage = true;
				_isLastPage = true;

				return;
			}
			else
			{
				_isNavVisible = true;
			}
			

			_firstPage = 1;
			_lastPage = _totalPages;
			
			if (_currentPage == 1)
			{
				_isFirstPage = true;
			}
			else
			{
				_isFirstPage = false;
				_previousPage = _currentPage - 1;
			}

			//Next and last page
			if (_currentPage == _lastPage)
			{
				_isLastPage = true;
			}
			else
			{
				_isLastPage = false;
				_nextPage = _currentPage + 1;
			}
		}


		private int CalculateTotalPages(int totalRows, int pageSize)
		{
			return (int)Math.Ceiling((double)totalRows / (double)pageSize);
		}


		private string GenPagerStats(int totalRows, int currentPage, int pageSize)
		{
			int firstRow = (currentPage - 1) * pageSize + 1;
			int lastRow = Math.Min(firstRow + pageSize - 1, totalRows);

			string stats;
			if (firstRow == lastRow)
				stats = "Row " + firstRow + " of " + totalRows;
			else
				stats = "Rows " + firstRow + "-" + lastRow + " of " + totalRows;

			return stats;
		}


		public void AddToQueryString(NameValueCollection queryString)
		{
			queryString["Pager.CurrentPage"] = this.CurrentPage.ToString();
			queryString["Pager.PageSize"] = this.PageSize.ToString();
		}
	}
}
