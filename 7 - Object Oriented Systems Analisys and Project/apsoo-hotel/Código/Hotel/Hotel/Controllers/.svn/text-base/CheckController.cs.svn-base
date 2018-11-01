using System;
using System.Collections;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Data;
using System.Linq;
using System.Linq.Expressions;
using System.Web;
using System.Web.Mvc;
using Hotel.Models;
using Hotel.Models.Repository;
using Hotel.Models.Services;
using Hotel.ViewModels.Shared;

namespace Hotel.Controllers
{
    public class CheckEditViewModel
    {
        public bool IsAdd { get; set; }
        public bool HasErrors { get; set; }
        public Check Check { get; set; }
    }


    public class CheckSearchForm : SearchForm
    {
        public int? Status { get; set; }
        public DateTime? FromDateBegin { get; set; }
        public DateTime? ToDateBegin { get; set; }
        public int? ApartmentNum { get; set; }
    }


    public class CheckGrid : Grid<Check, CheckSearchForm>
    {
        public CheckGrid()
        {
            this.Pager = new Pager { CurrentPage = 1, PageSize = 5 };
            this.Sorter = new Sorter("DateBegin", SortDirection.Asc);
        }
    }

    public class CheckGridStateService : GridStateService<Check, CheckSearchForm>
    {
        public CheckGridStateService()
            : base("CheckGrid")
        { }
    }


    public class CheckController : Controller
    {
        private CheckService _checkService;
        private CheckGrid _grid;
        private CheckGridStateService _gridStateService;

        private static CheckRepository<Check, hotelEntities> chr;
        private static ExpenseRepository<Expense, hotelEntities> er;
        private static InheritRepository<Client, Person, hotelEntities> cr;
        private static ApartmentRepository<Apartment, hotelEntities> ar;
        private static IRepository<ApartmentType, hotelEntities> atr;

        private static Check previousEntry;
        private static bool dateVerified;
        private static string view;


        public CheckController()
        {
            _checkService = new CheckService();
            _grid = new CheckGrid();
            _gridStateService = new CheckGridStateService();

            chr = new CheckRepository<Check, hotelEntities>();
            er = new ExpenseRepository<Expense, hotelEntities>();
            cr = new InheritRepository<Client, Person, hotelEntities>();
            ar = new ApartmentRepository<Apartment, hotelEntities>();
            atr = new EFRepository<ApartmentType, hotelEntities>();

            previousEntry = null;
            dateVerified = false;
        }

        public ActionResult Index()
        {
            return RedirectToAction("List");
        }
       

        public ActionResult Details(int id, string view)
        {
            Check check = chr.SelectOne(aux => aux.ID == id);

            if (!TryUpdateModel(check, "Check"))
            {
                var viewModel = new CheckEditViewModel
                {
                    IsAdd = false,
                    HasErrors = true,
                    Check = check
                };

                return View("Details", viewModel);
            }
            var model = new CheckEditViewModel { IsAdd = false, Check = check };
            check.Expenses = er.SelectAll().Where(e => e.Check.ID == id).ToList();
            ViewData["view"] = view;
            return View("Details", model);
        }


        public ActionResult _Grid()
        {
            _grid = new CheckGrid();
            
            UpdateGrid();

            return View(_grid);
        }


        public ActionResult List(string id)
        {
            _grid = new CheckGrid();

            if (Utils.IsPostBack())	//In case Javaschript is disabled or user wants to pass parameters in query string
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
            if (String.IsNullOrEmpty(id))
            {
                view = null;
                FillGridData();
            }
            else
            {
                view = id;
                FillGridData(id);
            }

            return View(_grid);
        }



        public void UpdateGrid()
        {
            if (!TryUpdateModel(_grid))
            {
                _grid.Data = new List<Check>();
                return;
            }

            _grid.ProcessAction();

            FillGridData(view);

            if (_grid.Data.Count > 0)
                _gridStateService.Save(_grid);
        }

        private void FillGridData()
        {   
            CheckCriteria criteria = _checkService.CreateCriteria();
            Utils.BindGridToCriteria(_grid, criteria);

            int totalRows = _checkService.GetTotalItemsCount(criteria);
            _grid.Pager.Init(totalRows);

            if (totalRows == 0)
            {
                _grid.Data = new List<Check>();
                return;
            }

            List<Check> checks = _checkService.FindByCriteria(criteria);
            _grid.Data = checks;
        }

        private void FillGridData(string id)
        {
            ViewData["view"] = id;
            CheckCriteria criteria = _checkService.CreateCriteria(id);
            Utils.BindGridToCriteria(_grid, criteria);

            int totalRows = _checkService.GetTotalItemsCount(criteria);
            _grid.Pager.Init(totalRows);

            if (totalRows == 0)
            {
                _grid.Data = new List<Check>();
                return;
            }

            List<Check> checks = _checkService.FindByCriteria(criteria);
            _grid.Data = checks;   
        }


        public ActionResult GetKeywordAutoCompleteData(string q, int limit)
        {
            string keyword = q;
            List<CheckSuggestion> suggestions = _checkService.FindSuggestions(keyword, 10);

            var list = suggestions.Select(suggestion => new
            {
                suggestion.ID,
                Name = suggestion.DateBegin
            });

            return Json(list);
        }


        public ActionResult Add(string id, int? clientid, string view)
        {
            Check check = new Check();
            check.DateBegin = DateTime.Now;
            check.DateEnd = DateTime.Now.AddDays(1);
            check.Value = (double)calcCheckValue(check);
            var viewModel = new CheckEditViewModel { IsAdd = true, Check = check };

            if (clientid != null)
                check.ClientID = (int)clientid;
            check.Client = cr.SelectOne(c => c.ID == (int)clientid);
            ViewData["view"] = view;
            ViewData["Search"] = "";
            if (id.Equals("Reservation") || id.Equals("OnlineReservation"))
            {
                ViewData["typeView"] = id;
                ViewData["apartments"] = availableForReservation(check);
                check.CheckStatus = CheckStatus.RESERVATION_REQUEST;   
            }            
            else
            {
                ViewData["typeView"] = "Check";
                ViewData["apartments"] = ar.SelectWhere(a => a.Status == (int)ApartmentStatus.AVAILABLE);
                check.CheckStatus = CheckStatus.EFFECTED;                
            }
            return View("Edit", viewModel);
        }

        public static double? calcCheckValue(Check check)
        {
            if (check.Apartment != null)
            {
                if (check.Apartment.ApartmentType == null)
                    check.Apartment.ApartmentType = atr.SelectAll().FirstOrDefault();
            }
            else
            {
                check.Apartment = ar.SelectAll().OrderBy(a => a.Status).FirstOrDefault();
            }

            double days = ((DateTime)check.DateEnd - (DateTime)check.DateBegin).TotalDays;
            if (days < 0)
                return 0.0;
            return days * check.Apartment.ApartmentType.Price;
        }

        public static double? calcCheckValue(Check check, DateTime dateBegin, DateTime dateEnd)
        {
            if (check.Apartment != null)
            {
                if (check.Apartment.ApartmentType == null)
                    check.Apartment.ApartmentType = atr.SelectAll().FirstOrDefault();
            }
            else
            {
                check.Apartment = ar.SelectAll().OrderBy(a => a.Status).FirstOrDefault();
            }

            double days = ((DateTime)dateBegin - (DateTime)dateEnd).TotalDays;
            if (days < 0 || check.Apartment == null)
                return 0.0;
            return days * check.Apartment.ApartmentType.Price;
        }

        public ActionResult Cancel(int id, string view)
        {
            Check check = chr.SelectOne(aux => aux.ID == id);

            if (!TryUpdateModel(check, "Check"))
            {
                var viewModel = new CheckEditViewModel
                {
                    IsAdd = false,
                    HasErrors = true,
                    Check = check
                };

                TempData["StatusLine"] = "Can't cancel check.";
                return View("Edit", viewModel);
            }

            try
            {
                if (check.CheckStatus == CheckStatus.FINALIZED)
                {
                    TempData["StatusLine"] = "Can't cancel a finalized check.";
                }
                if (check.CheckStatus == CheckStatus.CANCELLED)
                {
                    TempData["StatusLine"] = "This check is already cancelled.";
                }
                if (check.CheckStatus == CheckStatus.EFFECTED || check.CheckStatus == CheckStatus.RESERVATION_EFFECTED)
                {
                    TempData["StatusLine"] = "You must check out this check first.";
                }
                if (check.CheckStatus == CheckStatus.RESERVATION_REQUEST)
                {
                    check.Apartment.Status = (int)ApartmentStatus.AVAILABLE;
                    check.Status = (int)CheckStatus.CANCELLED;
                    chr.Update(check);
                    chr.Context.SaveChanges();
                    TempData["StatusLine"] = "This check was cancelled.";
                }
            }
            catch (UpdateException ex)
            {
                ModelState.AddModelError("_FORM", ex.Message);
                TempData["StatusLine"] = "Can't cancel check.";
            }

            return RedirectToAction("List/" + view);
        }

        public ActionResult Checkout(int id)
        {

            Check check = chr.SelectOne(aux => aux.ID == id);

            if (!TryUpdateModel(check, "Check"))
            {
                var viewModel = new CheckEditViewModel
                {
                    IsAdd = false,
                    HasErrors = true,
                    Check = check
                };

                TempData["StatusLine"] = "Can't checkout check.";
                return View("Details", viewModel);
            }

            try
            {
                if (check.CheckStatus == CheckStatus.FINALIZED)
                {
                    TempData["StatusLine"] = "This check is already cancelled.";
                }
                if (check.CheckStatus == CheckStatus.CANCELLED)
                {
                    TempData["StatusLine"] = "Can't finalize this check.";
                }
                if (check.CheckStatus == CheckStatus.RESERVATION_REQUEST)
                {
                    TempData["StatusLine"] = "You must effect this check.";
                }
                if (check.CheckStatus == CheckStatus.EFFECTED || check.CheckStatus == CheckStatus.RESERVATION_EFFECTED)
                {
                    check.Apartment.Status = (int)ApartmentStatus.AVAILABLE;
                    check.Status = (int)CheckStatus.FINALIZED;
                    chr.Update(check);
                    chr.Context.SaveChanges();
                    TempData["StatusLine"] = "This check was finalized.";
                }
            }
            catch (UpdateException ex)
            {
                ModelState.AddModelError("_FORM", ex.Message);
                TempData["StatusLine"] = "Can't finalize this check.";
            }

            return RedirectToAction("List/Checkout");
        }

        public ActionResult Checkin(int id)
        {

            Check check = chr.SelectOne(aux => aux.ID == id);

            if (!TryUpdateModel(check, "Check"))
            {
                var viewModel = new CheckEditViewModel
                {
                    IsAdd = false,
                    HasErrors = true,
                    Check = check
                };

                TempData["StatusLine"] = "Can't checkin this check.";
                return View("Details", viewModel);
            }

            try
            {
                if (check.CheckStatus == CheckStatus.FINALIZED)
                {
                    TempData["StatusLine"] = "Can't start a finalized check.";                 
                }
                if (check.CheckStatus == CheckStatus.CANCELLED)
                {
                    TempData["StatusLine"] = "Can't start a cancelled check.";
                }
                if (check.CheckStatus == CheckStatus.EFFECTED || check.CheckStatus == CheckStatus.RESERVATION_EFFECTED) {
                    TempData["StatusLine"] = "This check had already been started.";                
                }
                if (check.CheckStatus == CheckStatus.RESERVATION_REQUEST)
                {                    
                    check.Apartment.Status = (int)ApartmentStatus.BUSY;
                    check.Status = (int)CheckStatus.RESERVATION_EFFECTED;
                    chr.Update(check);
                    chr.Context.SaveChanges();
                    TempData["StatusLine"] = "This check was started.";
                }
            }
            catch (UpdateException ex)
            {
                ModelState.AddModelError("_FORM", ex.Message);
                TempData["StatusLine"] = "Can't start this check.";
            }

            return RedirectToAction("List/Checkin");
        }
        
        [AcceptVerbs(HttpVerbs.Post)]
        public ActionResult AddSave(FormCollection collection)
        {
            var check = new Check();
            bool isValid = true;
            if (!TryUpdateModel(check, "Check"))
                isValid = false;

            int clientId;

            var apartmentId = int.Parse(Request.Form["apartmentId"]);
            check.Apartment = ar.SelectOne(a => a.ID == apartmentId);

            ViewData["typeView"] = Request.Form["typeView"];
            ViewData["Search"] = Request.Form["Search"];
            check.Value = (double)calcCheckValue(check);
            String view = null;
            if (Request.Form["typeView"].Equals("Reservation"))
            {
                view = "Checkin";
                ViewData["view"] = view;
                ViewData["apartments"] = availableForReservation(check);
                check.CheckStatus = CheckStatus.RESERVATION_REQUEST;
            }
            else if (Request.Form["typeView"].Equals("OnlineReservation"))
            {
                view = "Home";
                ViewData["view"] = view;
                ViewData["apartments"] = availableForReservation(check);
                check.CheckStatus = CheckStatus.RESERVATION_REQUEST;
            }
            else
            {
                view = "Checkout";
                ViewData["view"] = view;
                ViewData["apartments"] = ar.SelectWhere(a => a.Status == (int)ApartmentStatus.AVAILABLE);
                check.CheckStatus = CheckStatus.EFFECTED;
            }

            if (Request.Form["isSearch"].ToString() == "true")
            {
                if (String.IsNullOrEmpty(Request.Form["clientId"]))
                {
                    if (!String.IsNullOrEmpty(Request.Form["Search"])){
                        String name = (String)Request.Form["Search"];
                        check.Client = cr.SelectOne(c => c.Name == name);
                    }
                    clientId = 0;
                }
                else
                {
                    clientId = int.Parse(Request.Form["clientId"]);
                    check.Client = cr.SelectOne(c => c.ID == clientId);
                }
                var viewModel = new CheckEditViewModel { IsAdd = true, Check = check };
                if (!ModelState.IsValid || !isValid)
                {
                    viewModel = new CheckEditViewModel { IsAdd = true, HasErrors = true, Check = check };
                    return View("Edit", viewModel);
                }                
                return View("Edit", viewModel);

            }
            else
            {  
                clientId = int.Parse(Request.Form["clientId"]);
                check.Client = cr.SelectOne(c => c.ID == clientId);

                ValidateCheck(check);

                if (!ModelState.IsValid || !isValid)
                {
                    if (previousEntry != null && !(Request.Form["typeView"].Equals("OnlineReservation")))
                    {
                        ViewData["previousEntry"] = previousEntry;
                    }
                    var viewModel = new CheckEditViewModel
                                        {
                                            IsAdd = true,
                                            HasErrors = true,
                                            Check = check
                                        };
                    TempData["StatusLine"] = "Can't add the check.";
                    return View("Edit", viewModel);
                }

                try
                {                    
                    if (Request.Form["typeView"] == "Check")
                        check.CheckStatus = CheckStatus.EFFECTED;
                    else
                        check.CheckStatus = CheckStatus.RESERVATION_REQUEST;
                    chr.Insert(check);
                    chr.Context.SaveChanges();
                    chr.Context.Connection.Close();

                    Client aux = cr.SelectOne(client => client.ID == check.Client.ID);
                    Apartment aux2 = ar.SelectOne(apart => apart.ID == apartmentId);

                    TempData["StatusLine"] = "Added new " + Request.Form["typeView"].ToLower() + " for " + aux.Name + " in apartment " + aux2.Number + ".";
                }
                catch (UpdateException ex)
                {
                    ModelState.AddModelError("_FORM", ex.Message);
                    TempData["StatusLine"] = "Can't add the check.";
                }

                if (Request.Form["typeView"].Equals("OnlineReservation"))
                {
                    TempData["StatusLine"] = "You added a new reservation!";
                    return RedirectToAction("Index", "Home");
                }

                return RedirectToAction("List/" + view);
            }
        }


        public ActionResult Edit(string id, int? clientId, string view)
        {
            Check check = null;
            if (clientId != null)
                check = chr.SelectOne(aux => aux.ID == (int)clientId);

            if (check.Status == (int)CheckStatus.FINALIZED || check.Status == (int)CheckStatus.CANCELLED)
            {
                TempData["StatusLine"] = "You can't update finished check.";
                return RedirectToAction("List/" + view);
            }

            
            check.ClientID = check.Client.ID;
            check.ApartmentID = check.Apartment.ID;
            check.Value = (double)calcCheckValue(check);

            if (check.Status == (int)CheckStatus.RESERVATION_REQUEST)            
                ViewData["typeView"] = "Reservation";            
            else                
                ViewData["typeView"] = "Check";
            ViewData["Search"] = "";
            ViewData["apartments"] = new List<Apartment>() { check.Apartment };            
            ViewData["view"] = view;
            var viewModel = new CheckEditViewModel { IsAdd = false, Check = check };

            return View(viewModel);
        }


        [AcceptVerbs(HttpVerbs.Post)]
        public ActionResult EditSave(int checkID)
        {
            Check check = chr.SelectOne(aux => aux.ID == checkID);
            
                bool isValid = true;
                if (!TryUpdateModel(check, "Check"))
                    isValid = false;

                int clientId;
                int apartmentId = int.Parse(Request.Form["apartmentId"]);
                check.Apartment = ar.SelectOne(a => a.ID == apartmentId);

                ViewData["typeView"] = Request.Form["typeView"];
                ViewData["Search"] = Request.Form["Search"];
                check.Value = (double)calcCheckValue(check);
                ViewData["apartments"] = availableForReservation(check);

                if (Request.Form["isSearch"].ToString() == "true")
                {
                    if (String.IsNullOrEmpty(Request.Form["clientId"]))
                    {
                        if (!String.IsNullOrEmpty(Request.Form["Search"]))
                        {
                            String name = (String)Request.Form["Search"];
                            check.Client = cr.SelectOne(c => c.Name == name);
                        }
                        clientId = 0;
                    }
                    else
                    {
                        clientId = int.Parse(Request.Form["clientId"]);
                        check.Client = cr.SelectOne(c => c.ID == clientId);
                    }
                    var viewModel = new CheckEditViewModel { IsAdd = true, Check = check };
                    return View("Edit", viewModel);
                }
                else
                {
                    clientId = int.Parse(Request.Form["clientId"]);
                    check.Client = cr.SelectOne(c => c.ID == clientId);

                    ValidateCheck(check);

                    if (!ModelState.IsValid || !isValid)
                    {
                        if (previousEntry != null)
                        {
                            ViewData["previousEntry"] = previousEntry;
                        }
                        check.Value = (double)calcCheckValue(check);
                        var viewModel = new CheckEditViewModel
                                            {
                                                IsAdd = false,
                                                HasErrors = true,
                                                Check = check
                                            };
                        TempData["StatusLine"] = "Can't update check.";
                        return View("Edit", viewModel);
                    }

                    try
                    {
                        check.Value = (double)calcCheckValue(check);
                        chr.Update(check);
                        chr.Context.SaveChanges();
                        chr.SaveChanges();

                        Client aux = cr.SelectOne(client => client.ID == clientId);
                        Apartment aux2 = ar.SelectOne(apart => apart.ID == apartmentId);


                        TempData["StatusLine"] = "Updated check for " + aux.Name + " in apartment " + aux2.Number + ".";


                    }
                    catch (UpdateException ex)
                    {
                        ModelState.AddModelError("_FORM", ex.Message);
                        TempData["StatusLine"] = "Can't update check.";
                    }

                    return RedirectToAction("List");
                }
        }


        public ActionResult Delete(int id, string view)
        {

            Check check = chr.SelectOne(aux => aux.ID == id);

            if (!TryUpdateModel(check, "Check"))
            {
                var viewModel = new CheckEditViewModel
                {
                    IsAdd = false,
                    HasErrors = true,
                    Check = check
                };

                TempData["StatusLine"] = "Can't delete check.";
                return View("Edit", viewModel);

            }

            try            
            {
                Check ch = chr.SelectOne(c => c.Apartment.ID == check.Apartment.ID &&
                                               c.ID != check.ID &&
                                               (c.Status == (int)CheckStatus.EFFECTED ||
                                                c.Status == (int)CheckStatus.RESERVATION_EFFECTED)); 
                if(ch == null){                
                    check.Apartment.Status = (int)ApartmentStatus.AVAILABLE;
                }
                
                chr.Delete(check);
                chr.Context.SaveChanges();

                TempData["StatusLine"] = "Deleted check.";
            }
            catch (UpdateException ex)
            {
                ModelState.AddModelError("_FORM", ex.Message);
                TempData["StatusLine"] = "Can't delete check.";
            }

            return RedirectToAction("List/" + view);
        }

        public static SelectList TypeSelectList()
        {
            return new SelectList(EnumExtensions.GetStringValue(typeof(CheckStatus)), "Value");
        }

        public static SelectList TypeSelectList(Enum value)
        {
            return new SelectList(EnumExtensions.GetStringValue(typeof(CheckStatus)), EnumExtensions.GetStringValue(value));
        }

        public static SelectList ApartmentSelectList()
        {
            return new SelectList(ar.SelectAll().OrderBy(a => a.Number).Distinct(new Hotel.Utils.ApartmentComparer("Number")), "ID", "Number");
        }

        public static SelectList ApartmentSelectList(int apartID)
        {
            Apartment apart = ar.SelectOne(a => a.ID == apartID);
            if (apart != null)
            {
                return new SelectList(ar.SelectAll().OrderBy(a => a.Number).Distinct(new Hotel.Utils.ApartmentComparer("Number")), "ID", "Number", apart.Number);
            }
            else
            {
                return CheckController.ApartmentSelectList();
            }
        }

        public static SelectList ApartmentFloorSelectList()
        {
            return new SelectList(ar.SelectAll().OrderBy(a => a.Floor).Distinct(new Hotel.Utils.ApartmentComparer("Floor")), "ID", "Floor");
        }

        public static SelectList ApartmentFloorSelectList(int apartID)
        {
            Apartment apart = ar.SelectOne(a => a.ID == apartID);
            if (apart != null)
            {
                return new SelectList(ar.SelectAll().OrderBy(a => a.Floor).Distinct(new Hotel.Utils.ApartmentComparer("Floor")), "ID", "Floor", apart.Floor);
            }
            else
            {
                return CheckController.ApartmentFloorSelectList();
            }
        }

        public static SelectList ClientSelectList()
        {
            return new SelectList(cr.SelectAll().OrderBy(a => a.Name), "ID", "Name");
        }

        public static SelectList ClientSelectList(int clientID)
        {
            Client client = cr.SelectOne(c => c.ID == clientID);
            if (client != null)
            {
                return new SelectList(cr.SelectAll().OrderBy(a => a.Name), "ID", "Name", client.Name);
            }
            else
            {
                return CheckController.ClientSelectList();
            }
        }



        private void ValidateCheck(Check check)
        {
            if (!dateVerified)
            {
                ValidateDate(check);
                dateVerified = false;
            }

            if (check.Client == null)
                ModelState.AddModelError("_FORM", "There is not client selected");

            if (check.Apartment == null)
                ModelState.AddModelError("_FORM", "There is not apartment selected");


            //Validar se a data inicial é maior ou igual a data de hoje

            var apartID = check.Apartment.ID;
            var dateBegin = check.DateBegin;
            var dateEnd = check.DateEnd;
            
            //fazer a busca por qualquer reserva deste apartamento na data especificada            
            Check chk = chr.SelectOne(c => c.Apartment.ID == apartID && (c.Status != (int)CheckStatus.CANCELLED && c.Status != (int)CheckStatus.FINALIZED) && c.ID != check.ID && ((c.DateBegin <= dateBegin && c.DateEnd >= dateEnd) ||
                                                                                     (c.DateBegin >= dateBegin && c.DateBegin < dateEnd) ||
                                                                                     (c.DateEnd > dateBegin && c.DateEnd <= dateEnd)));
            if (chk != null)
            {
                previousEntry = chk;
                ModelState.AddModelError("_FORM", "A entry for this apartment already exists on this date.");
            }


        }

        public Check hasCheck(Check check) {
            Check chk = chr.SelectOne(c => c.Apartment.ID == check.Apartment.ID && (c.Status == (int)CheckStatus.CANCELLED || c.Status == (int)CheckStatus.FINALIZED) && c.ID != check.ID && ((c.DateBegin <= check.DateBegin && c.DateEnd >= check.DateEnd) ||
                                                                                         (c.DateBegin >= check.DateBegin && c.DateBegin < check.DateEnd) ||
                                                                                         (c.DateEnd > check.DateBegin && c.DateEnd <= check.DateEnd)));
            return check;
        }

        private void ValidateDate(Check check)
        {
            var apartID = check.Apartment.ID;
            var dateBegin = check.DateBegin;
            var dateEnd = check.DateEnd;

            if (dateBegin.CompareTo(DateTime.Today) < 0)
                ModelState.AddModelError("_FORM", "The begin date is less than the today date.");

            //Validar se a data final é maior ou igual á data inicial

            if (dateBegin.CompareTo(dateEnd) > 0)
                ModelState.AddModelError("_FORM", "The begin date is greater than the end date.");
        }

        public List<Apartment> availableForReservation(Check check)
        {
            ValidateDate(check);
            dateVerified = true;
            var dateBegin = check.DateBegin;
            var dateEnd = check.DateEnd;

            List<Check> ch = chr.SelectWhere(c => c.ID != check.ID && ((c.DateBegin <= dateBegin && c.DateEnd >= dateEnd) ||
                                                                                     (c.DateBegin >= dateBegin && c.DateBegin < dateEnd) ||
                                                                                     (c.DateEnd > dateBegin && c.DateEnd <= dateEnd)) && (c.Status==(int)CheckStatus.RESERVATION_EFFECTED || c.Status==(int)CheckStatus.EFFECTED || c.Status==(int)CheckStatus.RESERVATION_REQUEST));
            List<Apartment> list = ar.SelectAll();
            foreach (Check item in ch) {
                if(list.Contains(item.Apartment))
                    list.Remove(item.Apartment);
            }
            return list.OrderBy(a => a.Number).ToList();
        }
    }
}
