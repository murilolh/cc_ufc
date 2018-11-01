 using System;
 using System.Collections.Generic;
 using System.Linq;
 using System.Linq.Expressions;

namespace Hotel.Models.Repository

    {

        /// <summary>

        /// Interface para a implementação do padrão Repository usando o Entity Framework.

       /// </summary> 

       /// <typeparam name="E">Tipo do objeto persistente</typeparam>

       /// <typeparam name="C">Tipo do contexto do Entity Framework</typeparam>
   
       public interface IRepository<E, C>

       {

           /// <summary>

           /// Contexto do Entity Framework

           /// </summary>

           C Context { get; set; }

    

           /// <summary>

           /// Inserção

           /// </summary>

           void Insert(E entity);

    

           /// <summary>

           /// Atualização

           /// </summary>

           void Update(E entity);

    

           /// <summary>

           /// Exclusão

           /// </summary>

           void Delete(E entity);

    

           /// <summary>

           /// Retorna o objeto que satisfaça a cláusula passada como argumento (cláusula WHERE)

           /// </summary>

           E SelectOne(Expression<Func<E, bool>> where);

    

           /// <summary>

           /// Retorna todos os objetos de um tipo

           /// </summary>

           List<E> SelectAll();

    

           /// <summary>

           /// Retorna os objetos usando paginação

           /// </summary>

           List<E> SelectAll(int maximumRows, int startRowIndex);

    

           /// <summary>

           /// Retorna todos os objetos que satisfaçam a cláusula passada

           /// </summary>

           /// <param name="where">Cláusula WHERE</param>

           List<E> SelectWhere(Expression<Func<E, bool>> where);

    

           /// <summary>

           /// Retorna os objetos que satisfaçam a cláusula passada, usando paginação

           /// </summary>

           /// <param name="where">Cláusula WHERE</param>

           List<E> SelectWhere(Expression<Func<E, bool>> where, int maximumRows, int startRowIndex);

    

           /// <summary>

           /// Retorna um objeto IQueryable, possibilitando formar queries usando expressões Lambda

           /// </summary>

           IQueryable<E> QueryAll();

    

           /// <summary>

           /// Retorna um IQueryable com os objetos usando paginação

           /// </summary>

           IQueryable<E> QueryAll(int maximumRows, int startRowIndex);

    

           /// <summary>

           /// Retorna a quantidade de objetos persistentes.

           /// </summary>

           int GetCount();

    

           /// <summary>

           /// Retorna a quantidade de objetos persistentes que satisfaçam a cláusula WHERE

           /// </summary>

           int GetCount(Expression<Func<E, bool>> where);

       }

   }