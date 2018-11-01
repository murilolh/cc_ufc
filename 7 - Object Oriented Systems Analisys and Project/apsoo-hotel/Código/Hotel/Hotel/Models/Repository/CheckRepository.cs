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

    public class CheckRepository<E, C> : EFRepository<E,C>

        where E : EntityObject

        where C : ObjectContext
    {

        private InheritRepository<Client, Person, hotelEntities> cr = new InheritRepository<Client, Person, hotelEntities>();
        private ApartmentRepository<Apartment,hotelEntities> ar = new ApartmentRepository<Apartment,hotelEntities>();
         private static IRepository<ApartmentType, hotelEntities> atr = new EFRepository<ApartmentType, hotelEntities>();

        /// <summary>

        /// Contexto do Entity Framework

        /// </summary>

        public void Insert(Check check)
        {   
            if (check.CheckStatus == CheckStatus.EFFECTED || check.CheckStatus == CheckStatus.RESERVATION_EFFECTED)
                check.Apartment.Status = (int)ApartmentStatus.BUSY;
            else if (check.CheckStatus == CheckStatus.CANCELLED || check.CheckStatus == CheckStatus.FINALIZED)
                check.Apartment.Status = (int)ApartmentStatus.AVAILABLE;

            ar.Update(check.Apartment, check.Apartment.ApartmentType.ID);
            context.AddObject(EntitySetName, check);
        }

        public List<Check> SelectAll()
        {
            List<Check> list = context.CreateQuery<Check>(EntitySetName).ToList();

            int id;
            int num;
            foreach (Check item in list) {
                if (item != null)
                {
                    id = (int)item.ClientReference.EntityKey.EntityKeyValues[0].Value;
                    item.Client = cr.SelectOne(c => c.ID == id);
                    num = (int)item.ApartmentReference.EntityKey.EntityKeyValues[0].Value;
                    item.Apartment = ar.SelectOne(a => a.ID == num);
                }
            }

            context.Connection.Close();

            return list;

        }

         public List<Check> SelectWhere(Expression<Func<Check, bool>> where){
            List<Check> list = context.CreateQuery<Check>(EntitySetName).Where(where).ToList();

            int id;
            int num;
            foreach (Check item in list)
            {
                if (item != null)
                {
                    id = (int)item.ClientReference.EntityKey.EntityKeyValues[0].Value;
                    item.Client = cr.SelectOne(c => c.ID == id);
                    num = (int)item.ApartmentReference.EntityKey.EntityKeyValues[0].Value;
                    item.Apartment = ar.SelectOne(a => a.ID == num);
                }
            }

            context.Connection.Close();

            return list;

        } 

        public Check SelectOne(Expression<Func<Check, bool>> where)
        {
            Check check = context.CreateQuery<Check>(EntitySetName).Where(where).FirstOrDefault();
            if (check != null)
            {
                int id = (int)check.ClientReference.EntityKey.EntityKeyValues[0].Value;
                check.Client = cr.SelectOne(c => c.ID == id);
                int num = (int)check.ApartmentReference.EntityKey.EntityKeyValues[0].Value;
                check.Apartment = ar.SelectOne(a => a.ID == num);
            }
            context.Connection.Close();
            return check;
        }

        public virtual void Update(Check check)
        {
            Check entity = context.CreateQuery<Check>(EntitySetName).Where(c => c.ID == check.ID).FirstOrDefault();

            entity.DateBegin = check.DateBegin;
            entity.DateEnd = check.DateEnd;
            entity.Status = check.Status;
            entity.Value = check.Value;
            entity.Client = check.Client;            
            entity.Apartment = check.Apartment;            
           
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
                        
                        if(check.CheckStatus == CheckStatus.EFFECTED || check.CheckStatus == CheckStatus.RESERVATION_EFFECTED)
                            check.Apartment.Status = (int)ApartmentStatus.BUSY;
                        else if(check.CheckStatus == CheckStatus.CANCELLED || check.CheckStatus == CheckStatus.FINALIZED)
                            check.Apartment.Status = (int)ApartmentStatus.AVAILABLE;
                        ar.Update(entity.Apartment, entity.Apartment.ApartmentType.ID);
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