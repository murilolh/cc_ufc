using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using Hotel.Models;

namespace Hotel.Models.Services
{
	public class ServiceCriteria : EntityCriteria<Service>
	{	
		public string Name { get; set; }		
		public string Description { get; set; }
		
		public double? FromPrice { get; set; }
		public double? ToPrice { get; set; }

		
		public ServiceCriteria(IList<Service> dataSource)
			: base(dataSource)
		{

		}


		protected override IQueryable<Service> AddQueryConditions(IQueryable<Service> query)
		{
			if (!String.IsNullOrEmpty(this.Keyword))
			{
				string keyword = this.Keyword;
				query = query.Where(service => service.Name.ContainsCaseInsensitive(keyword)												
												|| (service.Description != null && service.Description.ContainsCaseInsensitive(keyword)));

				return query;
			}
	

			if (!String.IsNullOrEmpty(this.Name))
				query = query.Where(service => service.Name.ContainsCaseInsensitive(this.Name));

			if (!String.IsNullOrEmpty(this.Description))
				query = query.Where(service => service.Description.ContainsCaseInsensitive(this.Description));

			if (this.FromPrice.HasValue)
				query = query.Where(service => service.Price >= this.FromPrice.Value);

			if (this.ToPrice.HasValue)
				query = query.Where(service => service.Price <= this.ToPrice.Value);

			return query;
		}
	}
}
