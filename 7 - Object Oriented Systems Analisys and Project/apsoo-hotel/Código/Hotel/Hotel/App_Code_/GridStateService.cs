using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;


using Hotel.ViewModels.Shared;

namespace Hotel
{

	public class GridStateService<TEntity, TSearchForm>  where TSearchForm: SearchForm, new()
	{
		class GridState
		{
			public int CurrentPage;
			public int PageSize;

			public Sorter Sorter;
			public TSearchForm SearchForm;
		}

		private string _key;

		public GridStateService(string key)
		{
			_key = key;
		}

		public void Save(Grid<TEntity, TSearchForm> grid)
		{
			GridState state = new GridState
			                  	{
									CurrentPage = grid.Pager.CurrentPage,
									PageSize = grid.Pager.PageSize,
									Sorter = grid.Sorter,
									SearchForm = grid.SearchForm
			                  	};

			HttpContext.Current.Session[_key] = state;
		}


		public bool TryLoad(Grid<TEntity, TSearchForm> grid)
		{
			if (this.Exists(_key))
			{
				this.Load(grid);
				return true;
			}

			return false;
		}


		public void Load(Grid<TEntity, TSearchForm> grid)
		{
			if (HttpContext.Current.Session[_key] == null)
				throw new InvalidOperationException("Grid state is not in session.");

			GridState state = (GridState)HttpContext.Current.Session[_key];

			grid.Pager.CurrentPage = state.CurrentPage;
			grid.Pager.PageSize = state.PageSize;
			grid.Sorter = state.Sorter;
			grid.SearchForm = state.SearchForm;

		}


		private bool Exists(string key)
		{
			if (HttpContext.Current.Session[key] == null)
				return false;

			return true;
		}

	}
}
