using System;
using System.Collections;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Linq;
using System.Linq.Expressions;
using System.Reflection;
using System.Web;
using System.Web.Mvc;
using Hotel.Models;
using Hotel.Models.Services;

namespace Hotel.ViewModels.Shared
{
	public enum GridAction
	{
		None=0,
		GoToPage,
		ChangePageSize,
		Sort,
		KeywordSearch,
		AdvancedSearch
	}

	[Serializable]
	public class Grid<TEntity, TSearchForm> : IGrid where  TSearchForm : SearchForm, new()
	{
		private Pager _pager;
		private Sorter _sorter;
		private TSearchForm _searchForm;
    
		private IList<TEntity> _data;
		private GridAction _gridAction;
		
		//Properties
		public Pager Pager
		{
			get { return _pager; }
			set { _pager = value; } 
		}

		public Sorter Sorter
		{
			get { return _sorter; }
			set { _sorter = value; } 
		}

		public TSearchForm SearchForm
		{
			get { return _searchForm; }
			set { _searchForm = value; }
		}


		public IList<TEntity> Data
		{ 
			get { return _data; }
			set { _data = value; } 
		}


		public GridAction GridAction
		{
			get { return _gridAction; }
			set { _gridAction = value; }
		}


		public bool IsEmpty
		{
			get 
			{
				return (_data.Count() == 0);
			}
		}

		public HttpRequest Request
		{
			get
			{
				return HttpContext.Current.Request;
			}
		}


		public Grid()
		{
			_pager = new Pager();
			_sorter = new Sorter();
			_searchForm = new TSearchForm();
		}


		public Grid(Pager pager, Sorter sorter) : this()
		{
			Verify.Argument.IsNotNull(pager, "pager");
			Verify.Argument.IsNotNull(sorter, "sorter");

			_pager = pager;
			_sorter = sorter;
		}


		public void ProcessAction()
		{
			//Javascript disabled or using query string
			if (this.Request.RequestType == "GET")
			{
				if (Request.QueryString["advanced-search-submit"] != null)
					this.GridAction = GridAction.AdvancedSearch;

				if (Request.QueryString["keyword-search-submit"] != null)
					this.GridAction = GridAction.KeywordSearch;
			}


			if (_gridAction == GridAction.ChangePageSize
				|| _gridAction == GridAction.Sort
				|| _gridAction == GridAction.KeywordSearch
				|| _gridAction == GridAction.AdvancedSearch)
				_pager.CurrentPage = 1;

			_gridAction = GridAction.None;
		}


		public SelectList PageSizeSelectList()
		{
			var pageSizes = new List<string> { "1", "2", "5", "10", "100" };
			return new SelectList(pageSizes, "Value");
		}

		//Cache query string for subsequent requests
		private NameValueCollection _queryString;

		private NameValueCollection GetQueryString()
		{
			return GetQueryString(false);
		}


		private NameValueCollection GetQueryString(bool cached)
		{
			NameValueCollection queryString;
			if (cached && _queryString != null)
			{
				queryString = new NameValueCollection(_queryString);
				return queryString;
			}

			queryString = new NameValueCollection();
			
			this.Pager.AddToQueryString(queryString);
			this.Sorter.AddToQueryString(queryString);
			this.SearchForm.AddToQueryString(queryString);

			if (cached)
			{
				//Cache it and return copy
				_queryString = queryString;
				queryString = new NameValueCollection(_queryString);
			}

			return queryString;
		}


		public string PageNavActionLink(string linkText, int page)
		{
			var queryString = GetQueryString(true);
			queryString["Pager.CurrentPage"] = page.ToString();
			queryString["GridAction"] = GridAction.GoToPage.ToString();

			string url = GenUrl(HttpContext.Current.Request.Path, queryString);
			string onClick = "goToPage(" + page + "); return false;";


			string link = "";
			link += "<a href=\"" + url + "\" onclick=\"" + onClick + "\">"; 
			link += HttpContext.Current.Server.HtmlEncode(linkText) ;
			link += "</a>";

			return link;
		}


		private string GenUrl(string pageUrl, NameValueCollection queryString)
		{
			string url = pageUrl;
			if (queryString.Count == 0)
				return url;

			for (int count = 0; count < queryString.Count; count++ )
			{
				string key = queryString.Keys[count];
				string value = queryString[key];

				if (count==0)
					url += "?";
				else
					url += "&";

				url += key + "=" + HttpContext.Current.Server.UrlEncode(value);
			}

			return url;
		}


		public string GetUrl()
		{
			var queryString = GetQueryString(true);
			string url = GenUrl(HttpContext.Current.Request.Path, queryString);
			return url;
		}


		public string SortActionLink(string linkText, string sortField)
		{
			var queryString = GetQueryString();
			queryString["Pager.CurrentPage"] = "1";
			queryString["GridAction"] = GridAction.Sort.ToString();

			string onClick = "";
			if (_sorter.SortField == sortField && _sorter.SortDirection == SortDirection.Asc)
			{
				onClick = "sort('" + sortField + "', 'Desc'); return false;";
				queryString["Sorter.SortDirection"] = SortDirection.Desc.ToString();
			}
			else
			{
				onClick = "sort('" + sortField + "', 'Asc'); return false;";

				queryString["Sorter.SortField"] = sortField;
				queryString["Sorter.SortDirection"] = SortDirection.Asc.ToString();
			}

			string cssClass = GetSortLinkCssClass(sortField);
			string url = GenUrl(HttpContext.Current.Request.Path, queryString);

			string link = "";
			link += "<a class=\"" + cssClass + "\" href=\"" + url + "\" onclick=\"" + onClick + "\">";
			link += HttpContext.Current.Server.HtmlEncode(linkText);
			link += "</a>";

			return link;
		}


		private string GetSortLinkCssClass(string sortField)
		{
			if (_sorter.SortField != sortField)
				return "";

			if (Sorter.SortDirection == SortDirection.Asc)
				return "asc";

			return "desc";
		}


	}
}
