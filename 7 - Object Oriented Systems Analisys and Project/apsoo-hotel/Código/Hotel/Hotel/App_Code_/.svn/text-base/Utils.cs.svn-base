using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Linq;
using System.Reflection;
using System.Web;
using Hotel.Models;
using Hotel.ViewModels.Shared;
using Hotel.Models.Services;

namespace Hotel
{
	public static class Utils
	{
		public static void BindObjectToQueryString(object obj, NameValueCollection queryString, string objPrefix)
		{
			Type objType = obj.GetType();

			PropertyInfo[] properties = objType.GetProperties(BindingFlags.Instance | BindingFlags.Public | BindingFlags.DeclaredOnly);
			foreach (PropertyInfo property in properties)
			{
				if (property.CanRead && property.CanWrite)
				{
					object value = property.GetValue(obj, null);
					if (value != null)
						queryString[objPrefix + "." + property.Name] =value.ToString();
				}
			}
		}


		public static void BindGridToCriteria<TEntity, TSearchForm>(Grid<TEntity, TSearchForm> grid, EntityCriteria<TEntity> criteria) where TSearchForm : SearchForm, new()
		{
            criteria.UsePaging = true;
			criteria.PageIndex = grid.Pager.CurrentPage;
			criteria.PageSize = grid.Pager.PageSize;

			criteria.SortField = grid.Sorter.SortField;
			criteria.SortDirection = grid.Sorter.SortDirection;

			if (!grid.SearchForm.IsAdvanced)
			{
				criteria.Keyword = grid.SearchForm.Keyword;
				return;
			}

			//Copy advanced search properties
			TSearchForm searchForm = grid.SearchForm;
			Type fromType = searchForm.GetType();
			Type toType = criteria.GetType();

			PropertyInfo[] properties = fromType.GetProperties(BindingFlags.Instance | BindingFlags.Public | BindingFlags.DeclaredOnly);
			foreach (PropertyInfo fromProperty in properties)
			{
				object value = fromProperty.GetValue(searchForm, null);
				if (value != null)
				{
					PropertyInfo toProperty = toType.GetProperty(fromProperty.Name);
					toProperty.SetValue(criteria, value, null);
				}
			}
		}



		public static bool IsPostBack()
		{
			HttpRequest request=HttpContext.Current.Request;
			
			if (request.RequestType == "POST"
					||  request.QueryString.Count > 0)
			  	return true;
			  
			return false;
		}

        public class ApartmentComparer : IEqualityComparer<Apartment>
        {
            private string type;
            public ApartmentComparer(String type)
            {
                this.type = type;
            }
            public bool Equals(Apartment x, Apartment y)
            {
                switch (type) {
                    case "Number": 
                            return x.Number == y.Number;
                    case "Floor": 
                            return x.Floor == y.Floor;
                    default: 
                        return false;
                }
            }

            public int GetHashCode(Apartment obj)
            {
                switch (type)
                {
                    case "Number":
                        return obj.Number.GetHashCode();
                    case "Floor":
                        return obj.Floor.GetHashCode();
                    default:
                        return 0;
                }
            }
        }

	}
}
