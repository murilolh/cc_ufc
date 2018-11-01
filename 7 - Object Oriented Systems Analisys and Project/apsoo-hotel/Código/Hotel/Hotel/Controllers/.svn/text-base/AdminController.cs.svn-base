using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using System.Web.Mvc.Ajax;
using Hotel.Models;
using Hotel.Models.Repository;

namespace Hotel.Controllers
{
    public class AdminController : Controller
    {
        //
        // GET: /Admin/
        private static InheritRepository<Client, Person, hotelEntities> cr = new InheritRepository<Client, Person, hotelEntities>();
        private static CheckRepository<Check, hotelEntities> chr = new CheckRepository<Check, hotelEntities>();
        private static IRepository<Service, hotelEntities> sr = new EFRepository<Service, hotelEntities>();
        private static ExpenseRepository<Expense, hotelEntities> er = new ExpenseRepository<Expense, hotelEntities>();
        private static ApartmentRepository<Apartment, hotelEntities> ar = new ApartmentRepository<Apartment, hotelEntities>();

        public AdminController()
        {
            cr = new InheritRepository<Client, Person, hotelEntities>();
            chr = new CheckRepository<Check, hotelEntities>();
            sr = new EFRepository<Service, hotelEntities>();
            er = new ExpenseRepository<Expense, hotelEntities>();
            ar = new ApartmentRepository<Apartment, hotelEntities>();
        }

        public ActionResult Index()
        {
            return View();
        }

        public ActionResult ChartGenerate(string id)
        {
            ViewData["Date"] = DateTime.Today;
            ViewData["Month"] = DateTime.Today.Month + "/" + DateTime.Today.Year;
            ViewData["View"] = id;
            return View(id);
        }

        [AcceptVerbs(HttpVerbs.Post)]
        public ActionResult ChartGenerate(string id, FormCollection formCollection)
        {

            String name;

            switch (id)
            {
                case "OccupancyRate":
                    ViewData["Date"] = DateTime.Parse(Request.Form["Date"]);
                    ViewData["View"] = "OccupancyRate";
                    ViewData["Rate"] = getOccupancyRate((DateTime)ViewData["Date"]);
                    return View("OccupancyRate");
                case "ValueEvolution":
                    setValueEvolution();
                    ViewData["View"] = "ValueEvolution";
                    return View("ValueEvolution");
                case "SearchApartmentByGuest":
                    ViewData["Search"] = Request.Form["Search"];
                    var clientId = 0;
                    if (Request.Form["isSearch"].ToString() == "true")
                    {
                        if (!String.IsNullOrEmpty(Request.Form["Search"]))
                        {
                            name = (String)Request.Form["Search"];
                            ViewData["Client"] = cr.SelectOne(c => c.Name == name);
                        }
                        else
                        {
                            clientId = int.Parse(Request.Form["clientId"]);
                            ViewData["Client"] = cr.SelectOne(c => c.ID == clientId);
                        }
                    }
                    else
                    {
                        clientId = int.Parse(Request.Form["clientId"]);
                        ViewData["Client"] = cr.SelectOne(c => c.ID == clientId);
                        ViewData["Checks"] = chr.SelectWhere(c => c.Client.ID == clientId && c.DateBegin <= DateTime.Now && c.DateEnd >= DateTime.Now
                                                && (c.Status == (int)CheckStatus.RESERVATION_EFFECTED || c.Status == (int)CheckStatus.EFFECTED));
                    }
                    ViewData["View"] = "SearchApartmentByGuest";
                    return View("SearchApartmentByGuest");
                case "BestServices":
                    ViewData["Month"] = Request.Form["Month"];
                    string[] campos = Request.Form["Month"].Split('/');
                    ViewData["View"] = "BestServices";
                    ViewData["Rate"] = getBestServices(campos);
                    return View("BestServices");
                default:
                    return View("Error");
            }
        }

        public double[] getOccupancyRate(DateTime date)
        {
            List<Check> list = chr.SelectWhere(c => c.DateBegin.Day <= date.Day && c.DateEnd.Value.Day >= date.Day
                                                 && (c.DateBegin.Month == date.Month || c.DateEnd.Value.Month == date.Month)
                                                 && (c.DateBegin.Year == date.Year || c.DateEnd.Value.Year == date.Year));
            List<Apartment> apt = new List<Apartment>();
            foreach (Check item in list)
            {
                if (!apt.Contains(item.Apartment) && (item.Status == (int)CheckStatus.EFFECTED || item.Status == (int)CheckStatus.RESERVATION_EFFECTED))
                    apt.Add(item.Apartment);
            }
            string[] values;
            double[] rate;
            int tot = ar.SelectAll().Count();
            if (tot > 0)
            {
                rate = new double[] { (double)apt.Count / (double)tot * 100.0, 100 - (double)apt.Count / (double)tot * 100 };
                values = new string[] { apt.Count.ToString(), (tot - apt.Count).ToString(), tot.ToString() };
            }
            else
            {
                rate = new double[] { 0 };
                values = new string[] { null };
            }

            ViewData["Values"] = values;
            return rate;
        }


        public double[] getBestServices(string[] data)
        {
            int m = int.Parse(data[0]);
            int y = int.Parse(data[1]);
            List<Expense> list = er.SelectWhere(e => e.Date.Value.Month == m && e.Date.Value.Year == y);
            List<Expense> aux = new List<Expense>();
            foreach (Expense item in list)
            {

                if (aux.Where(e => e.Service.Name == item.Service.Name).Count() > 0)
                {
                    Expense exp = aux.Where(e => e.Service.Name == item.Service.Name).First();
                    aux.Remove(exp);
                    exp.Amount = exp.Amount + item.Amount;
                    exp.Value = exp.Value + item.Value;
                    aux.Add(exp);
                }
                else
                {
                    aux.Add(item);
                }
            }

            aux.OrderBy(c => c.Value);
            aux.RemoveAll(c => c.Value <= 0);

            string[] names = new string[aux.Count];
            double[] rate = new double[aux.Count];
            for (int i = 0; i < names.Length; i++)
            {
                names[i] = aux[i].Service.Name + " - $" + String.Format("{0,00:F}", aux[i].Value) + " (#PERCENT)";
                rate[i] = aux[i].Value;
            }

            ViewData["Values"] = names;
            return rate;
        }

        public void setValueEvolution()
        {
            double[] value = { 0, 0, 0 };
            int[] months = new int[3];
            String[] label = new String[3];
            months[0] = DateTime.Today.Month;
            if (months[0] == 1)
            {
                months[0] = 12;
                label[0] = "12/" + DateTime.Today.AddYears(-1).Year.ToString();
            }
            else
            {
                label[0] = months[0].ToString() + "/" + DateTime.Today.Year.ToString();
            }

            for (int i = 1; i < 3; i++)
            {
                if (months[i - 1] == 1)
                {
                    months[i] = 12;
                    label[i] = "12/" + DateTime.Today.AddYears(-1).Year.ToString();
                }
                else
                {
                    months[i] = months[i - 1] - 1;
                    label[i] = months[i] + "/" + DateTime.Today.Year.ToString();
                }
            }
            ViewData["Label"] = label;

            int month;
            for (int i = 0; i < 3; i++)
            {
                month = months[i];
                List<Check> list = chr.SelectWhere(c => c.DateEnd.Value.Month == month && c.Status == (int)CheckStatus.FINALIZED);
                foreach (Check item in list)
                {
                    value[i] = value[i] + item.Value;
                }
            }
            ViewData["Chart"] = value;
        }
    }
}
