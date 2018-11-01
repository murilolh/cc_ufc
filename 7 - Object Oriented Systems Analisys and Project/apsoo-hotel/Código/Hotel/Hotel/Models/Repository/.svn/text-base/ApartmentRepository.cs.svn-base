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

    public class ApartmentRepository<E, C> : EFRepository<E, C>, IDisposable

        where E : EntityObject

        where C : ObjectContext
    {
        private IRepository<ApartmentType, hotelEntities> atr = new EFRepository<ApartmentType, hotelEntities>();


        public void Insert(Apartment apartment)
        {
            ApartmentType type = atr.SelectOne(t => t.ID == apartment.TypeID);
            apartment.ApartmentType = type;
            context.AddObject(EntitySetName, apartment);
        }

        public List<Apartment> SelectAll()
        {
            List<Apartment> list = context.CreateQuery<Apartment>(EntitySetName).ToList();

            int id;          
            foreach (Apartment item in list)
            {
                if (item != null)
                {
                    id = (int)item.ApartmentTypeReference.EntityKey.EntityKeyValues[0].Value;
                    item.ApartmentType = atr.SelectOne(c => c.ID == id);
                }
            }

            context.Connection.Close();
            return list;

        }

        public List<Apartment> SelectWhere(Expression<Func<Apartment, bool>> where) {
             List<Apartment> list = context.CreateQuery<Apartment>(EntitySetName).Where(where).ToList();
             int id;
             foreach (Apartment item in list)
             {
                 if (item != null)
                 {
                     id = (int)item.ApartmentTypeReference.EntityKey.EntityKeyValues[0].Value;
                     item.ApartmentType = atr.SelectOne(c => c.ID == id);
                 }
             }

             context.Connection.Close();
             return list;

        }

        public Apartment SelectOne(Expression<Func<Apartment, bool>> where)
        {
            Apartment apartment = context.CreateQuery<Apartment>(EntitySetName).Where(where).FirstOrDefault();
            if (apartment != null)
            {
                int id = (int)apartment.ApartmentTypeReference.EntityKey.EntityKeyValues[0].Value;
                apartment.ApartmentType = atr.SelectOne(c => c.ID == id);
                return apartment;
            }
            else {
                return null;
            }
        }

        public virtual void Update(Apartment apt, int typeID)
        {   
            Apartment entity = context.CreateQuery<Apartment>(EntitySetName).Where(a => a.ID == apt.ID).FirstOrDefault();

            entity.Number = apt.Number;
            entity.Floor = apt.Floor;
            entity.Status = apt.Status;
            entity.ApartmentTypeReference.EntityKey = atr.SelectOne(c => c.ID == typeID).EntityKey;

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