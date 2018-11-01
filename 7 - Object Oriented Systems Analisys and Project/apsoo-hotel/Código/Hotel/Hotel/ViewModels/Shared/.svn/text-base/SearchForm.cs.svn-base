using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Linq;
using System.Web;

namespace Hotel.ViewModels.Shared
{
	public class SearchForm 
	{
		//Properties
		public bool IsAdvanced { get; set; }
		public string Keyword { get; set; }


		public virtual void AddToQueryString(NameValueCollection queryString)
		{
			queryString["SearchForm.IsAdvanced"] = this.IsAdvanced.ToString();
			queryString["SearchForm.Keyword"] = this.Keyword;

			//Add custom properties using reflection.  If it is not sufficient
			//override the AddToQueryString in derived class
			Utils.BindObjectToQueryString(this, queryString, "SearchForm");
		}
	}
}
