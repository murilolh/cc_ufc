using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using Hotel.Models.Repository;

namespace Hotel.Models.Services
{
	public class ServiceService
	{
        private List<Service> Services {
            get
            {
                IRepository<Service, hotelEntities> sr = new EFRepository<Service, hotelEntities>();
                return sr.SelectAll().OrderBy(s => s.Name).ToList();
            }        
        }

		public Service GetByID(int serviceID)
		{
			return this.Services.AsQueryable().First(service => service.ID == serviceID);
		}


		public IQueryable<Service> GetQueryable()
		{
			return this.Services.AsQueryable();
		}


		public void Add(Service service)
		{
			this.Services.Add(service);
		}


		public void Update(Service service)
		{            
		}

		public ServiceCriteria CreateCriteria()
		{
			return new ServiceCriteria(this.Services);
		}


		public int GetTotalItemsCount(ServiceCriteria criteria)
		{
			return criteria.GetTotalItemsCount();
		}


		public List<Service> FindByCriteria(ServiceCriteria criteria)
		{
			return criteria.Find();
		}


		public List<ServiceSuggestion> FindSuggestions(string keyword, int max)
		{
			IQueryable<Service> query = this.GetQueryable();
			query = query.Where(service => service.Name.ToLower().StartsWith(keyword))
							.Take(max)
							.OrderBy(service => service.Name);

			var list = query.Select(service => new ServiceSuggestion
													{
														ID = service.ID,
														Name = service.Name													
													})
													.ToList();

			return list;
		}
	}
}
