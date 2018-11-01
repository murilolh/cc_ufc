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
using Hotel.Models.Services;
using Hotel.Models.Repository;
using System.Data;
using System.ComponentModel.DataAnnotations;

namespace Hotel.Controllers
{
    public class ClientEditViewModel
    {
        public bool IsAdd { get; set; }
        public bool HasErrors { get; set; }
        public Client Client { get; set; }
    }


    public class ClientSearchForm : SearchForm
    {
        public string Name { get; set; }
        public string Login { get; set; }
        public string CPF { get; set; }

    }


    public class ClientGrid : Grid<Client, ClientSearchForm>
    {  
        public ClientGrid()
        {
            this.Pager = new Pager { CurrentPage = 1, PageSize = 5 };
            this.Sorter = new Sorter("Name", SortDirection.Asc);
        }
    }

    public class ClientGridStateService : GridStateService<Client, ClientSearchForm>
    {
        public ClientGridStateService()
            : base("ClientGrid")
        { }
    }


    public class ClientController : Controller
    {
        private ClientService _clientService;
        private ClientGrid _grid;
        private ClientGridStateService _gridStateService;

        private InheritRepository<Client, Person, hotelEntities> cr;
        private CheckRepository<Check, hotelEntities> chr;

        public ClientController()
        {
            _clientService = new ClientService();
            _grid = new ClientGrid();
            _gridStateService = new ClientGridStateService();

            cr = new InheritRepository<Client, Person, hotelEntities>();
            chr = new CheckRepository<Check, hotelEntities>();
        }


        public ActionResult Index()
        {
            
            return RedirectToAction("List");
        }


        public ActionResult _Grid()
        {
            _grid = new ClientGrid();

            UpdateGrid();

            return View(_grid);
        }

        public ActionResult List()
        {
            _grid = new ClientGrid();

            if (Utils.IsPostBack())	//In case Javascript is disabled or user wants to pass parameters in query string
            {
                UpdateGrid();

                return View(_grid);
            }

            if (_gridStateService.TryLoad(_grid))
            {
                //code to use if you would like query string to include grid filters, etc...
                //string url = _grid.GetUrl();
                //Response.Redirect(url);
            }

            FillGridData();

            return View(_grid);
        }



        public void UpdateGrid()
        {
            if (!TryUpdateModel(_grid))
            {
                _grid.Data = cr.SelectAll().ToList();
                return;
            }

            _grid.ProcessAction();

            FillGridData();

            if (_grid.Data.Count > 0)
                _gridStateService.Save(_grid);
        }


        private void FillGridData()
        {
            ClientCriteria criteria = _clientService.CreateCriteria();
            Utils.BindGridToCriteria(_grid, criteria);

            int totalRows = _clientService.GetTotalItemsCount(criteria);
            _grid.Pager.Init(totalRows);

            if (totalRows == 0)
            {
                _grid.Data = cr.SelectAll().ToList();
                return;
            }

            List<Client> clients = _clientService.FindByCriteria(criteria);
            _grid.Data = clients;
        }


        public ActionResult GetKeywordAutoCompleteData(string q, int limit)
        {
            string keyword = q;
            List<ClientSuggestion> suggestions = _clientService.FindSuggestions(keyword, 10);

            var list = suggestions.Select(suggestion => new
            {
                suggestion.ID,
                Name = suggestion.Name
            });

            return Json(list);
        }


        public ActionResult Add(string id)
        {
            Client client = new Client();
            var viewModel = new ClientEditViewModel { IsAdd = true, Client = client };

            if (id.Equals("ForReservation")) 
                ViewData["typeView"] = "ForReservation";            
            else if (id.Equals("ForCheck"))
                ViewData["typeView"] = "ForCheck";
            else if (id.Equals("ForRegistration"))
            {
                ViewData["typeView"] = "ForRegistration";
                return View("Register", viewModel);
            }
            
            return View("Edit", viewModel);
        }

        [AcceptVerbs(HttpVerbs.Post)]
        public ActionResult Register(FormCollection collection)
        {
            var client = new Client();
            bool isValid = true;
            if (!TryUpdateModel(client, "Client"))
                isValid = false;

            // verify business logic validation
            ValidateClient(client);

            if (!ModelState.IsValid || !isValid)
            {
                var viewModel = new ClientEditViewModel
                {
                    IsAdd = true,
                    HasErrors = true,
                    Client = client
                };
                TempData["StatusLine"] = "You can't be registered. Correct errors and try again";
                return View("Register", viewModel);
            }

            try
            {
                cr.Insert(client);
                cr.Context.SaveChanges();
                TempData["StatusLine"] = "You were successfully registered"; 
            }
            catch (UpdateException ex)
            {
                ModelState.AddModelError("_FORM", ex.Message);
                TempData["StatusLine"] = "You can't be registered. Correct errors and try again";
            }

            Client cli = cr.SelectOne(c => c.Login == client.Login);
            AccountController acc = new AccountController();
            acc.ClientLogOn(cli.Login, true);
            return RedirectToAction("Index", "Home");
        }


        [AcceptVerbs(HttpVerbs.Post)]
        public ActionResult AddSave(FormCollection collection)
        {
            var client = new Client();
            bool isValid = true;
            if (!TryUpdateModel(client, "Client"))
                isValid = false;

            // verify business logic validation
            ValidateClient(client);

            if (!ModelState.IsValid || !isValid)
            {
                var viewModel = new ClientEditViewModel
                {
                    IsAdd = true,
                    HasErrors = true,
                    Client = client
                };
                TempData["StatusLine"] = "Client " + client.Name + " can't be added.";
                return View("Edit", viewModel);
            }

            try
            {
                cr.Insert(client);
                cr.Context.SaveChanges();
                TempData["StatusLine"] = "Added new client " + client.Name + ".";
            }
            catch (UpdateException ex)
            {
                ModelState.AddModelError("_FORM", ex.Message);
                TempData["StatusLine"] = "Client " + client.Name + " can't be added.";
            }

            Client cli = cr.SelectOne(c => c.Login == client.Login);

            if (cli == null)
            {
                TempData["StatusLine"] = "Try search the client or add again.";
                cli = new Client();
                cli.ID = 0;
            }

            if (Request.Form["typeView"] == "ForCheck") {
                return RedirectToAction("Add/Check?clientid=" + cli.ID, "Check");

            }
            else if (Request.Form["typeView"] == "ForReservation")
            {
                return RedirectToAction("Add/Reservation?clientid=" + cli.ID, "Check");
            }
            else if (Request.Form["typeView"] == "ForRegistration")
            {
                TempData["StatusLine"] = "You were successfully registered";
                return RedirectToAction("LogOn/" + cli.Login + "?password=" + cli.Password, "Account");
            }
            return RedirectToAction("List");
        }


        public ActionResult Edit(int id)
        {
            Client client = _clientService.GetByID(id);

            var viewModel = new ClientEditViewModel { IsAdd = false, Client = client };

            return View(viewModel);
        }

        [AcceptVerbs(HttpVerbs.Post)]
        public ActionResult EditSave(int clientID)
        {
            Client client = _clientService.GetByID(clientID);
            bool isValid = true;

            if (!TryUpdateModel(client, "Client"))
                isValid = false;
            
            // verify business logic validation
            ValidateClient(client);

            if (!ModelState.IsValid || !isValid)
            {
                var viewModel = new ClientEditViewModel
                {
                    IsAdd = false,
                    HasErrors = true,
                    Client = client
                };

                TempData["StatusLine"] = "Client " + client.Name + " can't be updated.";
                return View("Edit", viewModel);
            }

            try
            {
                cr.Update(client);
                cr.Context.SaveChanges();

                TempData["StatusLine"] = "Updated client " + client.Name + ".";
            }
            catch (UpdateException ex)
            {
                ModelState.AddModelError("_FORM", ex.Message);
                TempData["StatusLine"] = "Client " + client.Name + " can't be updated.";
            }
            return RedirectToAction("List");
        }


        public ActionResult Delete(int id)
        {

            Client client = cr.SelectOne(aux => aux.ID == id);

            ValidateOnDeleteClient(client);

            if (!ModelState.IsValid)
            {
                TempData["StatusLine"] = "Client " + client.Name + " can't be deleted.";
                return RedirectToAction("List");
            }
            try
            {   
                cr.Delete(client);
                cr.Context.SaveChanges();

                TempData["StatusLine"] = "Deleted client " + client.Name + ".";
            }
            catch (UpdateException ex)
            {
                ModelState.AddModelError("_FORM", ex.Message);
                TempData["StatusLine"] = "Client " + client.Name + " can't be deleted.";
            }

            return RedirectToAction("List");
        }


        private void ValidateClient(Client client)
        {
            //Validar se já existe cliente com o mesmo CPF

            if (cr.SelectOne(c => c.CPF == client.CPF && c.ID != client.ID) != null)
                ModelState.AddModelError("Client.CPF", "There is already registered client with this CPF.");

            //Validar se já existe cliente com o mesmo Login

            if (cr.SelectOne(c => c.Login == client.Login && c.ID != client.ID) != null)
                ModelState.AddModelError("Client.Login", "There is already registered client with this Login.");
        }

        private void ValidateOnDeleteClient(Client client)
        {
            //Validar se existe check para esse cliente

            if (chr.SelectOne(c => c.Client.ID == client.ID) != null)
                ModelState.AddModelError("_FORM", "There is registered check for this client.");
        }
    }
}
