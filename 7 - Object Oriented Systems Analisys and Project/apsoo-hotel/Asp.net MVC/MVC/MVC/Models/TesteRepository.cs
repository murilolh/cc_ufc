using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace MVC.Models
{
    public class TesteRepository
    {
            ericssonEntities mySqlEntities = new ericssonEntities();

            public IQueryable<products> Select()
            {

                var result = from p in mySqlEntities.products

                             select p;

                return result;

            }

            public IQueryable<products> Select(int id)
            {

                var result = from p in Select()

                             where p.id == id

                             select p;

                return result;

            }

            public void Add(products product)
            {

                mySqlEntities.AddToproducts(product);

            }

            public void Delete(products product)
            {

                mySqlEntities.DeleteObject(product);

            }

            public void Save()
            {

                mySqlEntities.SaveChanges();

            }
        }

   
}
