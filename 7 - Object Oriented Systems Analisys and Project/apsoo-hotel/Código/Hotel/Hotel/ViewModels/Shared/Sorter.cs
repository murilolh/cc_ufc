using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Linq;
using System.Web;
using Hotel.Models;
using Hotel.Models.Services;

namespace Hotel.ViewModels.Shared
{

	public class Sorter
	{
		//Properties
		public string SortField { get; set;}
		public SortDirection SortDirection { get; set; }

		public Sorter()
		{
			this.SortDirection = SortDirection.Asc;
		}


		public Sorter(string sortField, SortDirection sortDirection)
		{
			Verify.Argument.IsNotEmpty(sortField, "sortField");
			Verify.Argument.IsNotEmpty(sortField, "sortDirection");

			this.SortField = sortField;
			this.SortDirection = sortDirection;
		}


		public void AddToQueryString(NameValueCollection queryString)
		{
			queryString["Sorter.SortField"] = this.SortField;
			queryString["Sorter.SortDirection"] = this.SortDirection.ToString();
		}
	}
}
