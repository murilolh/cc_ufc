using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using Hotel.Models;

namespace Hotel.Models.Services
{
	public class CheckCriteria : EntityCriteria<Check>
	{
        public DateTime? FromDateBegin { get; set; }
        public DateTime? ToDateBegin { get; set; }
        public int? Status { get; set; }
        public int? AparmentNum { get; set; }
		
		public CheckCriteria(IList<Check> dataSource)
			: base(dataSource)
		{

		}


		protected override IQueryable<Check> AddQueryConditions(IQueryable<Check> query)
		{
			if (!String.IsNullOrEmpty(this.Keyword))
			{
				string keyword = this.Keyword;
                query = query.Where(check => check.DateBegin.ToString().ContainsCaseInsensitive(keyword)	
											      || check.Apartment.Number.ToString().ContainsCaseInsensitive(keyword)	
                                                || check.Status.ToString().ContainsCaseInsensitive(keyword));

				return query;
			}


            if (!String.IsNullOrEmpty(this.Status.ToString()))
                query = query.Where(check => check.Status.ToString().ContainsCaseInsensitive(this.Status.ToString()));
            
            if (this.AparmentNum.HasValue)
                query = query.Where(check => check.Apartment.Number.ToString().ContainsCaseInsensitive(this.AparmentNum.ToString()));

            if (this.FromDateBegin != null)
                query = query.Where(check => check.DateBegin >= this.FromDateBegin);

            if (this.ToDateBegin != null)
                query = query.Where(check => check.DateBegin <= this.ToDateBegin);
			return query;
		}
	}
}
