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

    public class InheritRepository<E, B, C> 

        where E : EntityObject

        where B : EntityObject

        where C : ObjectContext
    {

        /// <summary>

        /// Contexto do Entity Framework

        /// </summary>

        private C context;



        /// <summary>

        /// Contexto do Entity Framework

        /// </summary>

        public C Context
        {

            get { return context; }

            set { context = value; }

        }



        /// <summary>

        /// Retorna o nome do EntitySet do objeto persistente

        /// </summary>

        private string entitySetName;



        /// <summary>

        /// Retorna o nome do EntitySet do objeto persistente

        /// </summary>

        protected string EntitySetName
        {
            
            get
            {

                if (String.IsNullOrEmpty(entitySetName))
                {                    
                    entitySetName = GetEntitySetName(typeof(B).Name);
                }

                return entitySetName;

            }

        }



        /// <summary>

        /// Construtor padrão, sem argumentos. Obtém o contexto do Entity Framework usando o ContextManager.

        /// </summary>

        public InheritRepository()
        {

            // Obtém o contexto

            this.context = ContextManager.GetContext<C>();

        }



        /// <summary>

        /// Insere um novo objeto persistente

        /// </summary>

        /// <param name="entity">Objeto a ser inserido</param>

        public void Insert(E entity)
        {   
            context.AddObject(EntitySetName, entity);
        }



        /// <summary>

        /// Atualiza um objeto existente.

        /// </summary>

        /// <param name="entity">Objeto persistente</param>

        public virtual void Update(E entity)
        {

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



        /// <summary>

        /// Exclui um objeto persistente

        /// </summary>

        /// <param name="entity">Objeto persistente que será excluído</param>

        public void Delete(E entity)
        {

            context.DeleteObject(entity);

        }



        /// <summary>

        /// Retorna um objeto que satisfaça a cláusula passada como parâmetro.

        /// </summary>

        /// <param name="expression">Expressão Lambda da cláusula WHERE</param>

        public E SelectOne(Expression<Func<E, bool>> where)
        {

            return context.CreateQuery<E>(EntitySetName).OfType<E>().Where(where).FirstOrDefault();

        }



        /// <summary>

        /// Salva as alterações no banco de dados.

        /// </summary>

        public void SaveChanges()
        {

            context.SaveChanges();

        }



        /// <summary>

        /// Retorna todos os objetos persistentes.

        /// </summary>

        /// <returns>Coleção com todos os objetos</returns>

        public List<E> SelectAll()
        {

            return context.CreateQuery<E>(EntitySetName).OfType<E>().ToList();

        }



        /// <summary>

        /// Retorna um IQueryable com todos os objetos

        /// </summary>

        /// <returns>IQueryable com todos os objetos</returns>

        public IQueryable<E> QueryAll()
        {

            return context.CreateQuery<E>(EntitySetName).OfType<E>().AsQueryable<E>();

        }



        /// <summary>

        /// Retorna todos os objetos usando paginação.

        /// </summary>

        /// <param name="maximumRows">Quantidade de objetos por página</param>

        /// <param name="startRowIndex">Linha a partir do qual os objetos serão retornados</param>

        /// <returns>Coleção com todos os objetos</returns>

        public List<E> SelectAll(int maximumRows, int startRowIndex)
        {

            return context.CreateQuery<E>(EntitySetName).Skip<E>(startRowIndex).Take(maximumRows).ToList();

        }



        /// <summary>

        /// Retorna um IQueryable com todos os objetos usando paginação

        /// </summary>

        /// <param name="maximumRows">Quantidade de objetos por página</param>

        /// <param name="startRowIndex">Linha a partir do qual os objetos serão retornados</param>

        /// <returns>IQueryable com todos os objetos</returns>

        public IQueryable<E> QueryAll(int maximumRows, int startRowIndex)
        {

            return context.CreateQuery<E>(EntitySetName).Skip<E>(startRowIndex).Take(maximumRows);

        }



        /// <summary>

        /// Retorna todos os objetos que satisfaçam a cláusula passada

        /// </summary>

        /// <param name="where">Expressão Lambda da cláusula WHERE</param>

        public List<E> SelectWhere(Expression<Func<E, bool>> where)
        {

            return context.CreateQuery<E>(EntitySetName).OfType<E>().Where(where).ToList();

        }



        /// <summary>

        /// Retorna todos os objetos que satisfaçam a cláusula passada, usando paginação

        /// </summary>

        /// <param name="where">Expressão Lambda da cláusula WHERE</param>

        /// <param name="maximumRows">Quantidade de objetos por página</param>

        /// <param name="startRowIndex">Linha a partir do qual os objetos serão retornados</param>

        public List<E> SelectWhere(Expression<Func<E, bool>> where, int maximumRows, int startRowIndex)
        {

            return context.CreateQuery<E>(EntitySetName).Where(where)

                          .Skip<E>(startRowIndex).Take(maximumRows).ToList();

        }



        /// <summary>

        /// Retorna o número de objetos

        /// </summary>

        /// <remarks>Para ser usado na configuração da paginação</remarks>

        public int GetCount()
        {

            return context.CreateQuery<E>(EntitySetName).Count();

        }



        /// <summary>

        /// Retorna o número de objetos que satisfaçam a cláusula passada

        /// </summary>

        /// <remarks>Para ser usado na configuração da paginação</remarks>

        public int GetCount(Expression<Func<E, bool>> where)
        {

            return context.CreateQuery<E>(EntitySetName).Where(where).Count();

        }



        /// <summary>

        /// Libera os recursos do Entity Framework.

        /// </summary>

        public void Dispose()
        {

            if (context != null)

                context.Dispose();

        }



        /// <summary>

        /// Retorna o nome do EntitySet, possibilitando a criação de métodos genéricos.

        /// </summary>

        /// <param name="entityTypeName">String com o nome do tipo</param>

        /// <returns>String contendo o EntitySet</returns>

        private string GetEntitySetName(string entityTypeName)
        {

            var container = context.MetadataWorkspace.GetEntityContainer(context.DefaultContainerName, DataSpace.CSpace);

            string entitySetName = (from meta in container.BaseEntitySets

                                    where meta.ElementType.Name == entityTypeName

                                    select meta.Name).FirstOrDefault();

            return entitySetName;

        }



    }



}