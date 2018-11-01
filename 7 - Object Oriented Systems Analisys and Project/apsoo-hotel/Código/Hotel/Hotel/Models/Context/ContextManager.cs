using System.Web;
using System.Data.Objects;


    namespace Hotel.Models.Context

    {

        /// <summary>

        /// Classe gerenciadora do contexto do Entity Framework. Utiliza generics para determinar em tempo de execução o 

        /// tipo do contexto e Reflection para instanciar o tipo genérico. Armazena o contexto no HttpContext, de modo que 

        /// não seja necessário instanciar o contexto nas próximas chamadas dentro da requisição web.

       /// </summary>

       public sealed class ContextManager

       {

           /// <summary>

           /// Construtor privado, não será possível instanciar a classe usando new

           /// </summary>

           private ContextManager()

           {

           }

    

           /// <summary>

           /// Obtém o contexto do Entity Framework usando generics.

           /// </summary>

           /// <typeparam name="T">Tipo do contexto do Entity Framework (deve herdar de ObjectContext)</typeparam>

           /// <returns>Contexto do Entity Framework</returns>

           public static T GetContext<T>()

               where T : ObjectContext

           {

               string ocKey = "ocm_" + HttpContext.Current.GetHashCode().ToString("x");

               if (HttpContext.Current != null)

               {

                   if (!HttpContext.Current.Items.Contains(ocKey))

                   {

                       // Instancia o contexto através de Reflection

                       T ctx = typeof(T).GetConstructor(System.Type.EmptyTypes).Invoke(System.Type.EmptyTypes) as T;

                       // Armazena na requisição

                       HttpContext.Current.Items.Add(ocKey, ctx);

                   }

                   return HttpContext.Current.Items[ocKey] as T;

               }

               else

                   // Caso a aplicação não seja web, instancia e retorna o contexto.

                   return typeof(T).GetConstructor(System.Type.EmptyTypes).Invoke(System.Type.EmptyTypes) as T;

               

           }

    

       }

   }