using System;
using System.Collections.Generic;
using System.Data;
using System.Data.Metadata.Edm;
using System.Data.Objects;
using System.Data.Objects.DataClasses;
using System.Linq;
using System.Linq.Expressions;
using Hotel.Models.Context;
using Hotel.Models.Repository;


namespace Hotel.Models.Repository
{



    /// <summary>

    /// Repositório genérico para o Entity Framework com as operações mais comuns de persistência, como inserção, atualização,

    /// exclusão e seleção.

    /// </summary>

    /// <typeparam name="E">Tipo do objeto a ser persistido</typeparam>

    /// <typeparam name="C">Tipo do contexto</typeparam>

    public class ExpenseRepository<E, C> : EFRepository<E,C>

        where E : EntityObject

        where C : ObjectContext
    {

        private IRepository<Service, hotelEntities> cr = new EFRepository<Service,hotelEntities>();
        private CheckRepository<Check,hotelEntities> ar = new CheckRepository<Check,hotelEntities>();

        /// <summary>

        /// Contexto do Entity Framework

        /// </summary>

        public void Insert(Expense expense, int serviceID, int checkID)
        {               
            Service service = cr.SelectOne(c => c.ID == serviceID);
            Check apart = ar.SelectOne(a => a.ID == checkID);
            expense.Service = service;
            expense.Check = apart;
            expense.Value = expense.Amount * expense.Service.Price;            
            context.AddObject(EntitySetName, expense);
            context.Connection.Close();
        }

        public void Reverse(Expense expense, int serviceID, int checkID)
        {
            Service service = cr.SelectOne(c => c.ID == serviceID);
            Check apart = ar.SelectOne(a => a.ID == checkID);
            expense.Service = service;
            expense.Check = apart;
            expense.Value = expense.Amount * -expense.Service.Price;
            context.AddObject(EntitySetName, expense);
            context.Connection.Close();
        }

        public List<Expense> SelectAll()
        {
            List<Expense> list = context.CreateQuery<Expense>(EntitySetName).ToList();

            int id;
            int num;
            foreach (Expense item in list) {
                if (item != null)
                {
                    id = (int)item.ServiceReference.EntityKey.EntityKeyValues[0].Value;
                    item.Service = cr.SelectOne(c => c.ID == id);
                    num = (int)item.CheckReference.EntityKey.EntityKeyValues[0].Value;
                    item.Check = ar.SelectOne(a => a.ID == num);
                }
            }

            context.Connection.Close();

            return list;

        }

        public List<Expense> SelectWhere(Expression<Func<Expense, bool>> where)
        {

            List<Expense> list = context.CreateQuery<Expense>(EntitySetName).Where(where).ToList();

            int id;
            int num;
            foreach (Expense item in list)
            {
                if (item != null)
                {
                    id = (int)item.ServiceReference.EntityKey.EntityKeyValues[0].Value;
                    item.Service = cr.SelectOne(c => c.ID == id);
                    num = (int)item.CheckReference.EntityKey.EntityKeyValues[0].Value;
                    item.Check = ar.SelectOne(a => a.ID == num);
                }
            }

            context.Connection.Close();

            return list;

        }

        public Expense SelectOne(Expression<Func<Expense, bool>> where)
        {
            Expense expense = context.CreateQuery<Expense>(EntitySetName).Where(where).FirstOrDefault();
            if (expense != null)
            {
                int id = (int)expense.ServiceReference.EntityKey.EntityKeyValues[0].Value;
                expense.Service = cr.SelectOne(c => c.ID == id);
                int num = (int)expense.CheckReference.EntityKey.EntityKeyValues[0].Value;
                expense.Check = ar.SelectOne(a => a.ID == num);
            }
            context.Connection.Close();
            return expense;
        }

        public virtual void Update(Expense expense, int serviceID, int checkID)
        {
            Expense entity = context.CreateQuery<Expense>(EntitySetName).Where(c => c.ID == expense.ID).FirstOrDefault();

            entity.Date = expense.Date;            
            entity.Amount = expense.Amount;
           
            entity.Service.EntityKey = cr.SelectOne(c => c.ID == serviceID).EntityKey;
            entity.Check.EntityKey =  ar.SelectOne(a => a.ID == checkID).EntityKey;

            entity.Value = entity.Amount * entity.Service.Price;

            EntityKey key;

            object originalItem;

            if (entity.EntityKey == null)

                // Obtém o entity key do objeto que será atualizado

                key = Context.CreateEntityKey(EntitySetName, entity);

            else

                key = entity.EntityKey;

            try
            {

                // Obtém o objeto original

                if (Context.TryGetObjectByKey(key, out originalItem))
                {

                    if (originalItem is EntityObject &&

                        ((EntityObject)originalItem).EntityState != EntityState.Added)
                    {
                        // Autaliza o objeto
                        context.ApplyPropertyChanges(key.EntitySetName, entity);

                        context.Connection.Close();

                    }

                }

            }

            catch (Exception ex)
            {

                throw ex;

            }
        }
    }
}