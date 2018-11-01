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
    public class ExpenseEditViewModel
    {
        public bool IsAdd { get; set; }
        public bool HasErrors { get; set; }
        public Expense Expense { get; set; }
    }


    public class ExpenseSearchForm : SearchForm
    {
        public string Service { get; set; }
        public DateTime? FromDate { get; set; }
        public DateTime? ToDate { get; set; }
    }


    public class ExpenseGrid : Grid<Expense, ExpenseSearchForm>
    {
        public ExpenseGrid()
        {
            this.Pager = new Pager { CurrentPage = 1, PageSize = 5 };
            this.Sorter = new Sorter("Date", SortDirection.Asc);
        }
    }

    public class ExpenseGridStateService : GridStateService<Expense, ExpenseSearchForm>
    {
        public ExpenseGridStateService()
            : base("ExpenseGrid")
        { }
    }


    public class ExpenseController : Controller
    {
        private ExpenseService _expenseService;
        private ExpenseGrid _grid;
        private ExpenseGridStateService _gridStateService;

        private static ExpenseRepository<Expense, hotelEntities> chr;
        private static IRepository<Service, hotelEntities> sr;
        private static CheckRepository<Check, hotelEntities> cr;

        private bool isValid;

        public ExpenseController()
        {
            _expenseService = new ExpenseService();
            _grid = new ExpenseGrid();
            _gridStateService = new ExpenseGridStateService();

            chr = new ExpenseRepository<Expense, hotelEntities>();
            sr = new EFRepository<Service, hotelEntities>();
            cr = new CheckRepository<Check, hotelEntities>();

        }

        public ActionResult Index()
        {
            
            return RedirectToAction("List");
        }


        public ActionResult _Grid()
        {
            _grid = new ExpenseGrid();

            UpdateGrid();

            return View(_grid);
        }


        public ActionResult List()
        {
            _grid = new ExpenseGrid();

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

            FillGridData();

            return View(_grid);
        }



        public void UpdateGrid()
        {
            if (!TryUpdateModel(_grid))
            {
                _grid.Data = new List<Expense>();
                return;
            }

            _grid.ProcessAction();

            FillGridData();

            if (_grid.Data.Count > 0)
                _gridStateService.Save(_grid);
        }


        private void FillGridData()
        {
            ExpenseCriteria criteria = _expenseService.CreateCriteria();
            Utils.BindGridToCriteria(_grid, criteria);

            int totalRows = _expenseService.GetTotalItemsCount(criteria);
            _grid.Pager.Init(totalRows);

            if (totalRows == 0)
            {
                _grid.Data = new List<Expense>();
                return;
            }

            List<Expense> expenses = _expenseService.FindByCriteria(criteria);
            _grid.Data = expenses;
        }


        public ActionResult GetKeywordAutoCompleteData(string q, int limit)
        {
            string keyword = q;
            List<ExpenseSuggestion> suggestions = _expenseService.FindSuggestions(keyword, 10);

            var list = suggestions.Select(suggestion => new
            {
                suggestion.ID,
                Name = suggestion.Date
            });

            return Json(list);
        }


        public ActionResult Add(string id)
        {
            int ID = int.Parse(id);
            Expense expense = new Expense();
            expense.Check = cr.SelectOne(c => c.ID == ID);
            expense.CheckID = ID;
            expense.Date = DateTime.Now;
            expense.Amount = 1;
            expense.Service = sr.SelectAll().OrderBy(a => a.Name).First();
            expense.Value = expense.Amount * expense.Service.Price;
            var viewModel = new ExpenseEditViewModel { IsAdd = true, Expense = expense };
            return View("Edit", viewModel);
        }

        private Double calcExpenseValue(Expense expense)
        {
            return 0;
        }


        [AcceptVerbs(HttpVerbs.Post)]
        public ActionResult AddSave([Bind(Exclude = "ID")] Expense expense)
        {
            isValid = true;
            if (!TryUpdateModel(expense, "Expense"))
                isValid = false;
            expense.Check = cr.SelectOne(c => c.ID == expense.CheckID);
            ValidateExpense(expense);

            if (!ModelState.IsValid || !isValid)
            {
                var viewModel = new ExpenseEditViewModel
                {
                    IsAdd = true,
                    HasErrors = true,
                    Expense = expense
                };
                TempData["StatusLine"] = "Can't add the expense.";
                return View("Edit", viewModel);
            }
            try
            {
                var serviceId = expense.ServiceID;
                var checkId = expense.CheckID;

                chr.Insert(expense, serviceId, checkId);
                chr.Context.SaveChanges();

                Service aux = sr.SelectOne(service => service.ID == serviceId);
                Check aux2 = cr.SelectOne(apart => apart.ID == checkId);

                TempData["StatusLine"] = "Added new expense of service " + aux.Name + " in check.";
            }
            catch (UpdateException ex)
            {
                ModelState.AddModelError("_FORM", ex.Message);
                TempData["StatusLine"] = "Can't add the expense.";
            }
            
            return RedirectToAction("Details/" + expense.CheckID, "Check");
        }


        public ActionResult Edit(int id)
        {
            Expense expense = chr.SelectOne(aux => aux.ID == id);
            expense.ServiceID = expense.Service.ID;
            expense.CheckID = expense.Check.ID;
            expense.Value = expense.Amount * expense.Service.Price;

            var viewModel = new ExpenseEditViewModel { IsAdd = false, Expense = expense };
            return View(viewModel);
        }


        [AcceptVerbs(HttpVerbs.Post)]
        public ActionResult EditSave(int expenseID)
        {
            Expense expense = chr.SelectOne(aux => aux.ID == expenseID);

            isValid = true;
            if (!TryUpdateModel(expense, "Expense"))
                isValid = false;

            ValidateExpense(expense);

            if (!ModelState.IsValid || !isValid)
            {
                var viewModel = new ExpenseEditViewModel
                {
                    IsAdd = false,
                    HasErrors = true,
                    Expense = expense
                };
                TempData["StatusLine"] = "Can't add the expense.";
                return View("Edit", viewModel);
            }
            try
            {
                var serviceId = expense.ServiceID;
                var checkID = expense.CheckID;

                chr.Update(expense, serviceId, checkID);
                chr.Context.SaveChanges();
                chr.SaveChanges();

                Service aux = sr.SelectOne(service => service.ID == serviceId);
                Check aux2 = cr.SelectOne(apart => apart.ID == checkID);


                TempData["StatusLine"] = "Updated expense of service " + aux.Name + " in check.";


            }
            catch (UpdateException ex)
            {
                ModelState.AddModelError("_FORM", ex.Message);
                TempData["StatusLine"] = "Can't update expense.";
            }

            return RedirectToAction("List");
        }


        public ActionResult Delete(int id)
        {

            Expense expense = chr.SelectOne(aux => aux.ID == id);

            if (!TryUpdateModel(expense, "Expense"))
            {
                var viewModel = new ExpenseEditViewModel
                {
                    IsAdd = false,
                    HasErrors = true,
                    Expense = expense
                };

                TempData["StatusLine"] = "Can't cancel expense.";
                return View("Edit", viewModel);
            }

            int checkId = expense.Check.ID;
            try
            {
               
                chr.Delete(expense);
                chr.Context.SaveChanges();

                TempData["StatusLine"] = "Cancelled expense.";
            }
            catch (UpdateException ex)
            {
                ModelState.AddModelError("_FORM", ex.Message);
                TempData["StatusLine"] = "Can't cancel expense.";
            }            
            return RedirectToAction("Details/" + checkId, "Check");
        }

        public ActionResult Reverse(int id)
        {
            Expense expense = chr.SelectOne(aux => aux.ID == id);

            if (!TryUpdateModel(expense, "Expense"))
            {
                var viewModel = new ExpenseEditViewModel
                {
                    IsAdd = false,
                    HasErrors = true,
                    Expense = expense
                };

                TempData["StatusLine"] = "Can't reverse expense.";
                return RedirectToAction("Details/" + expense.Check.ID, "Check");
            }

            int checkId = expense.Check.ID; 
            try
            {
                Expense exp = new Expense();              
                exp.Amount = expense.Amount;
                exp.Date = DateTime.Today;

                var serviceId = expense.Service.ID;

                chr.Reverse(exp, serviceId, checkId);
                chr.Context.SaveChanges();
                
                TempData["StatusLine"] = "Reversed expense.";
            }
            catch (UpdateException ex)
            {
                ModelState.AddModelError("_FORM", ex.Message);
                TempData["StatusLine"] = "Can't reverse expense.";
            }
            return RedirectToAction("Details/" + checkId, "Check");
        }

        public static SelectList ServiceSelectList()
        {
            return new SelectList(sr.SelectAll().OrderBy(a => a.Name), "ID", "Name");
        }

        public static SelectList ServiceSelectList(int serviceID)
        {
            Service service = sr.SelectOne(c => c.ID == serviceID);
            if (service != null)
            {
                return new SelectList(sr.SelectAll().OrderBy(a => a.Name), "ID", "Name", service.Name);
            }
            else
            {
                return ExpenseController.ServiceSelectList();
            }
        }

        private void ValidateExpense(Expense expense)
        {
            //Validar se a data é diferente da data atual
            var date = (DateTime)expense.Date;
            if (date.CompareTo(DateTime.Today) < 0)
                ModelState.AddModelError("Expense.Date", "The expense date is less than the today date.");

            if (date.CompareTo(expense.Check.DateBegin) < 0)
                ModelState.AddModelError("Expense.Date", "The expense date is less than the check begin");

            if (date.CompareTo(expense.Check.DateEnd) > 0)
                ModelState.AddModelError("Expense.Date", "The expense date is greater than the check end");
        }
    }
}
