using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using Hotel.Models;

namespace Hotel.Models.Services
{
	public class ClientCriteria : EntityCriteria<Client>
	{	
		public string Name { get; set; }
		public string Login { get; set; }
		public string CPF { get; set; }

		
		public ClientCriteria(IList<Client> dataSource)
			: base(dataSource)
		{

		}


		protected override IQueryable<Client> AddQueryConditions(IQueryable<Client> query)
		{
			if (!String.IsNullOrEmpty(this.Keyword))
			{
				string keyword = this.Keyword;
				query = query.Where(client => client.Name.ContainsCaseInsensitive(keyword)
												|| client.Login.ContainsCaseInsensitive(keyword)
                                                || client.CPF.ContainsCaseInsensitive(keyword));

				return query;
			}
	

			if (!String.IsNullOrEmpty(this.Name))
				query = query.Where(client => client.Name.ContainsCaseInsensitive(this.Name));

			if (!String.IsNullOrEmpty(this.Login))
				query = query.Where(client => client.Login.ContainsCaseInsensitive(this.Login));

			if (!String.IsNullOrEmpty(this.CPF))
				query = query.Where(client => client.CPF.ContainsCaseInsensitive(this.CPF));
            			
			return query;
		}
	}
}
