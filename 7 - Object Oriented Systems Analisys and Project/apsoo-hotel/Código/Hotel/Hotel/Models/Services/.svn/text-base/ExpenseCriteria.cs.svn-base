using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using Hotel.Models;

namespace Hotel.Models.Services
{
	public class ExpenseCriteria : EntityCriteria<Expense>
	{
        public DateTime? FromDate { get; set; }
        public DateTime? ToDate { get; set; }
        public string Service { get; set; }
		
		public ExpenseCriteria(IList<Expense> dataSource)
			: base(dataSource)
		{

		}


		protected override IQueryable<Expense> AddQueryConditions(IQueryable<Expense> query)
		{
			if (!String.IsNullOrEmpty(this.Keyword))
			{
				string keyword = this.Keyword;
                query = query.Where(expense => expense.Date.ToString().ContainsCaseInsensitive(keyword)	
                                                || expense.Service.Name.ToString().ContainsCaseInsensitive(keyword));

				return query;
			}


            if (!String.IsNullOrEmpty(this.Service))
                query = query.Where(expense => expense.Service.Name.ToString().ContainsCaseInsensitive(this.Service.ToString()));
            
            if (this.FromDate != null)
                query = query.Where(expense => expense.Date >= this.FromDate);

            if (this.ToDate != null)
                query = query.Where(expense => expense.Date <= this.ToDate);
			return query;
		}
	}
}
