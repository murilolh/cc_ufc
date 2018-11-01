using System.Linq;
using System.Web.Mvc;
using Hotel.Models;
using Hotel.Models.Repository;
using System.Data;
using System;

namespace Hotel.Controllers
{
    public class ApartmentTypeController : Controller
    {
        //
        // GET: /ApatmentType/
        private static IRepository<ApartmentType, hotelEntities> atr;
        private static ApartmentRepository<Apartment, hotelEntities> ar;

        public ApartmentTypeController() {
            atr = new EFRepository<ApartmentType, hotelEntities>();
            ar = new ApartmentRepository<Apartment, hotelEntities>();
        }
        public ActionResult Index()
        {
            
            return View(atr.SelectAll().OrderBy(a => a.Name));
        }

        //
        // GET: /ApatmentType/Details/5

        public ActionResult Details(int id)
        {
            return View();
        }

        //
        // GET: /ApatmentType/Create

        public ActionResult Create()
        {
            ApartmentType ap = new ApartmentType();
            return View(ap);
        } 

        //
        // POST: /ApatmentType/Create

        [AcceptVerbs(HttpVerbs.Post)]
        public ActionResult Create([Bind(Exclude = "ID")] ApartmentType apartType)

        {
            bool isValid = true;

            try
            {
                if (!TryUpdateModel(apartType, "ApartmentType"))
                    isValid = false;

                ValidateApartmentType(apartType);

                if (!ModelState.IsValid || !isValid)
                {
                    TempData["StatusLine"] = "Apartment type " + apartType.Name + " can't be added.";
                    return View("Create", apartType);
                }

                atr.Insert(apartType);
                atr.Context.SaveChanges();

                TempData["StatusLine"] = "Added new apartment type " + apartType.Name + ".";
                return RedirectToAction("Index");
            }
            catch
            {
                TempData["StatusLine"] = "Apartment type " + apartType.Name + " can't be added.";              
                return View("Create", apartType);
            }
        }

        //
        // GET: /ApatmentType/Edit/5
 
        public ActionResult Edit(int id)
        {
            ApartmentType apt = atr.SelectOne(a => a.ID == id);
            return View(apt);
        }

        //
        // POST: /ApatmentType/Edit/5

        [AcceptVerbs(HttpVerbs.Post)]
        public ActionResult Edit(ApartmentType apt, FormCollection collection)
        {            
            try
            {
                bool isValid = true;
                if (!TryUpdateModel(apt, "ApartmentType"))
                    isValid = false;

                ValidateApartmentType(apt);

                if (!ModelState.IsValid || !isValid)
                {
                    TempData["StatusLine"] = "Can't update apartment type " + apt.Name + ".";
                    return View("Edit", apt);
                }

                atr.Update(apt);
                atr.Context.SaveChanges();

                TempData["StatusLine"] = "Updated apartment type " + apt.Name + ".";
 
                return RedirectToAction("Index");
            }
            catch
            {
                TempData["StatusLine"] = "Can't update apartment type " + apt.Name + ".";
                return View("Edit", apt);
            }
        }

        public ActionResult Delete(int id)
        {
            ApartmentType apt = atr.SelectOne(a => a.ID == id);

            try
            {                
                ValidateDeleteApartmentType(apt);

                if (!ModelState.IsValid)
                {
                    TempData["StatusLine"] = "apartment type can't be deleted " + apt.Name + ".";
                    return View("Index", atr.SelectAll().OrderBy(a => a.Name));
                }

                atr.Delete(apt);
                atr.Context.SaveChanges();

                TempData["StatusLine"] = "Deleted apartment type" + apt.Name + ".";
                return View("Index", atr.SelectAll().OrderBy(a => a.Name));
            }
            catch (UpdateException ex)
            {
                ModelState.AddModelError("_FORM", ex.Message);
                TempData["StatusLine"] = "apartment type can't be deleted " + apt.Name + ".";
                return View("Index", atr.SelectAll().OrderBy(a => a.Name));
            }
        }

        private void ValidateApartmentType(ApartmentType aptype)
        {
          if (atr.SelectOne(c => c.Name == aptype.Name && c.ID != aptype.ID) != null)
            ModelState.AddModelError("Name", "There is already registered apartment type with this Name.");            
        }

        private void ValidateDeleteApartmentType(ApartmentType aptype)
        {
            if (ar.SelectOne(a => a.ApartmentType.ID == aptype.ID) != null)
                ModelState.AddModelError("_FORM", "There is registered apartment with this apartment type.");
        }
    }
}
