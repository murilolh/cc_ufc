using System;
using System.Collections;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Linq;
using System.Linq.Expressions;
using System.Web;
using System.Web.Mvc;
using Hotel.Models;
using Hotel.ViewModels.Shared;
using Hotel.Models.Repository;
using Hotel.Models.Services;
using System.ComponentModel.DataAnnotations;
using System.Data;

namespace Hotel.Controllers
{
	public class ServiceEditViewModel
	{
		public bool IsAdd { get; set; }
		public bool HasErrors { get; set; }
		public Service Service { get; set; }
	}


    public class ServiceSearchForm : SearchForm
	{
		public string Name { get; set; }
		public string Description { get; set; }

		public double? FromPrice { get; set; }
		public double? ToPrice { get; set; }
	}


	public class ServiceGrid : Grid<Service, ServiceSearchForm>
	{
        public ServiceGrid()
		{
			this.Pager = new Pager { CurrentPage = 1, PageSize = 5 };
			this.Sorter = new Sorter("Name", SortDirection.Asc);
		}
	}

	public class ServiceGridStateService : GridStateService<Service, ServiceSearchForm>
	{
        public ServiceGridStateService()
            : base("ServiceGrid")
		{
		}
	}
	 

	public class ServiceController : Controller
	{ 
        //variaveis utilizadas para funcionalidades do grid (estado, ordenação, paginação e busca)
		private ServiceService _serviceService;
        private ServiceGrid _grid;
        private ServiceGridStateService _gridStateService;
        
        //usado para acesso aos dados
        private IRepository<Service, hotelEntities> sr;
    
		public ServiceController()
		{             
			_serviceService=new ServiceService();
            _grid = new ServiceGrid();
            _gridStateService = new ServiceGridStateService();

            sr = new EFRepository<Service, hotelEntities>();
		}


		public ActionResult Index()
		{
			return RedirectToAction("List");
		}


		public ActionResult _Grid()
		{
			_grid = new ServiceGrid();

			UpdateGrid();

			return View(_grid);
		}


		public ActionResult List()
		{
            _grid = new ServiceGrid();

			if (Utils.IsPostBack())	//In case Javascript is disabled or user wants to pass parameters in query string
			{
				UpdateGrid();

				return View(_grid);
			}

			_gridStateService.TryLoad(_grid);

			FillGridData();

			return View(_grid);
		}


		public void UpdateGrid()
		{
			if (!TryUpdateModel(_grid))
			{
				_grid.Data = new List<Service>();
				return;
			}

			_grid.ProcessAction();

			FillGridData();

			if (_grid.Data.Count > 0)
				_gridStateService.Save(_grid);
		}


        private void FillGridData()
        {
        	ServiceCriteria criteria = _serviceService.CreateCriteria();
        	Utils.BindGridToCriteria(_grid, criteria);

            int totalRows = _serviceService.GetTotalItemsCount(criteria);
			_grid.Pager.Init(totalRows);

			if (totalRows == 0)
			{
				_grid.Data = new List<Service>();
				return;
			}

            List<Service> services = _serviceService.FindByCriteria(criteria);
        	_grid.Data = services;
        }


		public ActionResult GetKeywordAutoCompleteData(string q, int limit)
		{
			string keyword = q;
            List<ServiceSuggestion> suggestions = _serviceService.FindSuggestions(keyword, 10);

			var list = suggestions.Select(suggestion => new
			                                            	{
			                                            		suggestion.ID,
			                                            		Name = suggestion.Name
															});

			return Json(list);
		}


		public ActionResult Add()
		{
			Service service = new Service();
	
			var viewModel = new ServiceEditViewModel { IsAdd = true, Service = service };
			return View("Edit", viewModel);
		}


		[AcceptVerbs(HttpVerbs.Post)]
		public ActionResult AddSave()
		{
			var service = new Service();

            bool isValid = true;
            
            if (!TryUpdateModel(service, "Service"))
                isValid = false;

            if (!ModelState.IsValid || !isValid)
            {
				var viewModel = new ServiceEditViewModel
				                	{
				                		IsAdd = true,
				                		HasErrors = true,
										Service = service 
									};
                TempData["StatusLine"] = "Service " + service.Name + " can't be added.";
				return View("Create", viewModel);
			}
            
            try
            {
                sr.Insert(service);
                sr.Context.SaveChanges();
                TempData["StatusLine"] = "Add new service " + service.Name + ".";
            }
            catch (UpdateException ex) {
                ModelState.AddModelError("_FORM", ex.Message);
                TempData["StatusLine"] = "Service " + service.Name + " can't be added.";
            }
			return RedirectToAction("List");
		}


		public ActionResult Edit(int id)
		{
			Service service = _serviceService.GetByID(id);

			var viewModel = new ServiceEditViewModel { IsAdd = false, Service = service };
			
			return View(viewModel);
		}


		[AcceptVerbs(HttpVerbs.Post)]
		public ActionResult EditSave(int serviceID)
		{
            bool isValid = true;
            Service service = _serviceService.GetByID(serviceID);

            if (!TryUpdateModel(service, "Service"))
                isValid = false;

            try
            {
                ValidateService(service);

                if (!ModelState.IsValid || !isValid)
                {
                    var viewModel = new ServiceEditViewModel
                    {
                        IsAdd = false,
                        HasErrors = true,
                        Service = service
                    };

                    TempData["StatusLine"] = "Service " + service.Name + " can't be updated."; 
                    return View("Edit", viewModel);
                }


                sr.Update(service);
                sr.Context.SaveChanges();

                TempData["StatusLine"] = "Updated service " + service.Name + ".";
            }
            catch (UpdateException ex) {
                ModelState.AddModelError("_FORM", ex.Message);
                TempData["StatusLine"] = "Service " + service.Name + " can't be updated."; 
            }
			
			return RedirectToAction("List");
		}


		public ActionResult Delete(int id)
		{            
            Service service = sr.SelectOne(aux => aux.ID == id);

            try
            {
                sr.Delete(service);
                sr.Context.SaveChanges();
                TempData["StatusLine"] = "Deleted service " + service.Name + ".";
            }
            catch (UpdateException ex) {
                ModelState.AddModelError("_FORM", ex.Message);
                TempData["StatusLine"] = "Service " + service.Name + " can't be added.";
            }            
			return RedirectToAction("List");
		}

        private void ValidateService(Service service)
        {
            //Validar se já existe empregado com o mesmo Nome

            if (sr.SelectOne(c => c.Name == service.Name && c.ID != service.ID) != null)
                ModelState.AddModelError("Name", "There is already registered service with this name.");
        }
	}
}
