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
    public class ApartmentController : Controller
    {
        private static ApartmentRepository<Apartment, hotelEntities> ar;
        private static IRepository<ApartmentType, hotelEntities> atr;
        private static CheckRepository<Check, hotelEntities> chr;

        //
        // GET: /Apartment/
        public ApartmentController()
        {
            ar = new ApartmentRepository<Apartment, hotelEntities>();
            atr = new EFRepository<ApartmentType, hotelEntities>();
            chr = new CheckRepository<Check, hotelEntities>();

        }

        public ActionResult Index()
        {   
            return View(ar.SelectAll().OrderBy(a => a.Number));
        }

        //
        // GET: /Apartment/Details/5

        public ActionResult Details(int id)
        {
            return View();
        }

        //
        // GET: /Apartment/Create

        public ActionResult Create()
        {   
            Apartment app = new Apartment();
            return View(app);
        }

        //
        // POST: /Apartment/Create

        [AcceptVerbs(HttpVerbs.Post)]
        public ActionResult Create([Bind(Exclude = "ID")] Apartment apartment)
        {
            bool isValid = true;            
            try
            {
                if (!TryUpdateModel(apartment, "Apartment"))
                    isValid = false;

                ValidateApartment(apartment);

                if (!ModelState.IsValid || !isValid)
                {
                    TempData["StatusLine"] = "apartment can't be added " + apartment.Number + ".";
                    return View("Create", apartment);
                }

                ar.Insert(apartment);
                ar.SaveChanges();


                TempData["StatusLine"] = "Added new apartment " + apartment.Number + "."; 
                return View("Index", ar.SelectAll().OrderBy(a => a.Number));
            }
            catch
            {
                TempData["StatusLine"] = "apartment can't be added " + apartment.Number + "."; 
                return View("Create", apartment);
            }
        }

        //
        // GET: /Apartment/Edit/5

        public ActionResult Edit(int id)
        {
            Apartment apart = ar.SelectOne(apartment => apartment.ID == id);
            apart.TypeID = apart.ApartmentType.ID;          
            return View(apart);
        }

        //
        // POST: /Apartment/Edit/5

        [AcceptVerbs(HttpVerbs.Post)]
        public ActionResult Edit(Apartment apartment, FormCollection collection)
        {
            bool isValid = true;
            try
            {
                if (!TryUpdateModel(apartment, "Apartment"))
                    isValid = false;

                ValidateApartment(apartment);

                if (!ModelState.IsValid || !isValid)
                {
                    TempData["StatusLine"] = "apartment can't be added " + apartment.Number + "."; 
                    return View("Edit", apartment);
                }

                var typeID = apartment.TypeID;
                
                ar.Update(apartment,typeID);
                ar.Context.SaveChanges();

                TempData["StatusLine"] = "Updated apartment " + apartment.Number + ".";
                return View("Index", ar.SelectAll().OrderBy(a => a.Number));
            }
            catch
            {
                TempData["StatusLine"] = "Cant update the apartment " + apartment.Number + ".";
                return View("Edit", apartment);
            }
        }

        public ActionResult Delete(int id)
        {
            Apartment apartment = ar.SelectOne(apart => apart.ID == id);            
            try
            {
                ValidateDeleteApartment(apartment);

                if (!ModelState.IsValid)
                {
                    TempData["StatusLine"] = "apartment can't be deleted " + apartment.Number + ".";
                    return View("Index", ar.SelectAll().OrderBy(a => a.Number));
                }

                ar.Delete(apartment);
                ar.Context.SaveChanges();

                TempData["StatusLine"] = "Deleted apartment " + apartment.Number + ".";
                return View("Index", ar.SelectAll().OrderBy(a => a.Number));
            }
            catch (UpdateException ex)
            {
                TempData["StatusLine"] = "apartment can't be deleted " + apartment.Number + ".";
                ModelState.AddModelError("_FORM", ex.Message);
                return View("Index", ar.SelectAll().OrderBy(a => a.Number));
            }


        }

        private void ValidateApartment(Apartment apt)
        {
            if (ar.SelectOne(c => c.Number == apt.Number && c.Floor == apt.Floor && c.ID != apt.ID) != null)
                ModelState.AddModelError("_FORM", "There is already registered apartment with this number and floor.");
        }

        private void ValidateDeleteApartment(Apartment apt)
        {
            if (chr.SelectOne(a => a.Apartment.ID == apt.ID) != null)
                ModelState.AddModelError("_FORM", "There is registered check with this apartment.");
        }

        public static SelectList TypeSelectList()
        {
            return new SelectList(EnumExtensions.GetStringValue(typeof(ApartmentStatus)), "Value");
        }

        public static SelectList TypeSelectList(Enum value)
        {
            return new SelectList(EnumExtensions.GetStringValue(typeof(ApartmentStatus)), EnumExtensions.GetStringValue(value));
        }

        public static SelectList ApartmentTypeSelectList()
        {   
            atr = new EFRepository<ApartmentType, hotelEntities>();
            return new SelectList(atr.SelectAll().OrderBy(a => a.Name), "ID", "Name");
        }

        public static SelectList ApartmentTypeSelectList(int type)
        {   
            atr = new EFRepository<ApartmentType, hotelEntities>();
            ApartmentType app = atr.SelectOne(c => c.ID == type);
            if (app != null)
            {
                return new SelectList(atr.SelectAll().OrderBy(a => a.Name), "ID", "Name", app.Name);
            }
            else
            {
                return ApartmentController.ApartmentTypeSelectList();
            }

            
        } 
    }
}
