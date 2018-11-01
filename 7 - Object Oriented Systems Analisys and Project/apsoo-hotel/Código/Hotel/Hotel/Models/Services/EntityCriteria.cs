using System;
using System.Collections.Generic;
using System.Linq;
using System.Linq.Expressions;
using System.Web;

namespace Hotel.Models.Services
{
	public enum SortDirection
	{
		Asc = 1,
		Desc = 2
	}


	public abstract class EntityCriteria <TEntity>
	{
		private IList<TEntity> _dataSource;

		public string Keyword { get; set; }
		
		public bool UsePaging { get; set; }
		public int PageIndex{ get; set; }
		public int PageSize { get; set; }

		public string SortField { get; set; }
		public SortDirection SortDirection { get; set; }


		public EntityCriteria(IList<TEntity> dataSource)
		{
			_dataSource = dataSource;
		}

        public IList<TEntity> getData() {
            return _dataSource;
        }

        public void setData(IList<TEntity> dataSource)
        {
            this._dataSource = dataSource;
        }
        

		public int GetTotalItemsCount()
		{
			IQueryable<TEntity> query = _dataSource.AsQueryable();
			query = AddQueryConditions(query);

			int totalRows = query.Count();
			return totalRows;
		}


		public List<TEntity> Find()
		{
			IQueryable<TEntity> query = _dataSource.AsQueryable();
			query = AddQueryConditions(query);
			query = AddQuerySorting(query);

			if (this.UsePaging)
				query = AddQueryPaging(query);

			List<TEntity> list = query.ToList();
			return list;
		}
        

		protected virtual IQueryable<TEntity> AddQueryConditions(IQueryable<TEntity> query)
		{
			return query;
		}


		private IQueryable<TEntity> AddQuerySorting(IQueryable<TEntity> query)
		{
			if (String.IsNullOrEmpty(this.SortField))
				return query;

			//Used approach from http://www.singingeels.com/Articles/Self_Sorting_GridView_with_LINQ_Expression_Trees.aspx
			//instead of a long switch statement 
			var param = Expression.Parameter(typeof(TEntity), typeof(TEntity).Name);
			var sortExpression = Expression.Lambda<Func<TEntity, object>>
									(Expression.Convert(Expression.Property(param, this.SortField), typeof(object)), param);

			if (this.SortDirection == SortDirection.Asc)
				query = query.OrderBy(sortExpression);
			else
				query = query.OrderByDescending(sortExpression);

			return query;
		}


		private IQueryable<TEntity> AddQueryPaging(IQueryable<TEntity> query)
		{
			query = query.Skip((this.PageIndex - 1) * this.PageSize)
								.Take(this.PageSize);
			return query;
		}
	}
}
