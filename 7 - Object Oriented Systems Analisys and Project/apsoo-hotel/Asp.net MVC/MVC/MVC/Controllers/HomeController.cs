using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using MVC.Models;

namespace MVC.Controllers
{
    [HandleError]
    public class HomeController : Controller
    {
        public ActionResult Index()
        {
            TesteRepository t = new TesteRepository();

            
            ViewData["Message"] = "Welcome to ASP.NET MVC!";

            ViewData["products"] = t.Select().ToList();
            return View();
        }

        public ActionResult About()
        {
            return View();
        }
    }
}
