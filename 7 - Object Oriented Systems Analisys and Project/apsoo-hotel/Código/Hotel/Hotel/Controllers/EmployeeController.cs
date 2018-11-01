using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using System.Web.Mvc.Ajax;
using Hotel.Models;
using Hotel.Models.Repository;
using Hotel.Models.Services;
using Hotel.ViewModels.Shared;
using System.Data;
using Microsoft.Web.Mvc.Controls;

namespace Hotel.Controllers
{
    public class EmployeeController : Controller
    {
        private bool isValid;
        InheritRepository<Employee, Person, hotelEntities> er;
        //
        // GET: /Employee/
        public EmployeeController()
        {
            er = new InheritRepository<Employee, Person, hotelEntities>();
            isValid = true;
        }

        public ActionResult Index()
        {
            return View(er.SelectAll().OrderBy(e => e.Name));
        }

        //
        // GET: /Employee/Details/5

        public ActionResult Details(int id)
        {
            return View();
        }

        //
        // GET: /Employee/Create

        public ActionResult Create()
        {
            Employee emp = new Employee();
            return View(emp);
        }

        //
        // POST: /Employee/Create

        [AcceptVerbs(HttpVerbs.Post)]
        public ActionResult Create([Bind(Exclude = "ID")] Employee employee)
        {
            try
            {
                if (!TryUpdateModel(employee, "ApartmentType"))
                    isValid = false;

                ValidateEmployee(employee);

                if (!ModelState.IsValid || !isValid)
                {
                    TempData["StatusLine"] = "employee can't be added " + employee.Name + "."; 
                    return View("Create", employee);
                }

                er.Insert(employee);
                er.SaveChanges();


                TempData["StatusLine"] = "Added new employee " + employee.Name + ".";
                return RedirectToAction("Index");
            }
            catch
            {
                TempData["StatusLine"] = "employee can't be added " + employee.Name + ".";
                return View(employee);
            }
        }

        //
        // GET: /Employee/Edit/5

        public ActionResult Edit(int id)
        {
            Employee emp = er.SelectOne(employee => employee.ID == id);
            return View(emp);
        }

        //
        // POST: /Employee/Edit/5

        [AcceptVerbs(HttpVerbs.Post)]
        public ActionResult Edit(Employee employee, FormCollection collection)
        {

            try
            {
                if (!TryUpdateModel(employee, "ApartmentType"))
                    isValid = false;

                ValidateEmployee(employee);

                if (!ModelState.IsValid || !isValid)
                {
                    TempData["StatusLine"] = "employee can't be added " + employee.Name + ".";
                    return View("Edit", employee);
                }

                er.Update(employee);
                er.Context.SaveChanges();

                TempData["StatusLine"] = "Updated employee " + employee.Name + ".";
                return RedirectToAction("Index");
            }
            catch
            {
                return View(employee);
            }
        }


        public ActionResult Delete(int id)
        {
            Employee emp = er.SelectOne(employee => employee.ID == id);
            try
            {
                ValidateOnDeleteEmployee(emp);

                if (!ModelState.IsValid || !isValid)
                {
                    TempData["StatusLine"] = "employee can't be added " + emp.Name + ".";
                    return RedirectToAction("Index");
                }

                er.Delete(emp);
                er.Context.SaveChanges();

                TempData["StatusLine"] = "Deleted employee " + emp.Name + ".";
                return RedirectToAction("Index");
            }
            catch (UpdateException ex)
            {
                ModelState.AddModelError("_FORM", ex.Message);
                TempData["StatusLine"] = "employee can't be deleted " + emp.Name + ".";
                return RedirectToAction("Index");
            }


        }

        public static SelectList TypeSelectList()
        {
            return new SelectList(EnumExtensions.GetStringValue(typeof(EmployeeType)), "Value");
        }

        private void ValidateEmployee(Employee employee)
        {
            //Validar se já existe empregado com o mesmo CPF

            if (er.SelectOne(c => c.CPF == employee.CPF && c.ID != employee.ID) != null)
                ModelState.AddModelError("CPF", "There is already registered employee with this CPF.");

            //Validar se já existe empregado com o mesmo Login

            if (er.SelectOne(c => c.Login == employee.Login && c.ID != employee.ID) != null)
                ModelState.AddModelError("Login", "There is already registered employee with this Login.");
        }

        private void ValidateOnDeleteEmployee(Employee employee)
        {
            //Validar se existe despesa para esse empregado

           /* if (er.SelectOne(c => c.ID == employee.ID) != null)
                ModelState.AddModelError("_FORM", "There is registered check for this client.");*/
        }
    }
}
