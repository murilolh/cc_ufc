using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using System.Web.Routing;
using Microsoft.Web.Mvc.DataAnnotations;

namespace Hotel
{
	// Note: For instructions on enabling IIS6 or IIS7 classic mode, 
	// visit http://go.microsoft.com/?LinkId=9394801

	public class MvcApplication : System.Web.HttpApplication
	{
		public static void RegisterRoutes(RouteCollection routes)
		{
			routes.IgnoreRoute("{resource}.axd/{*pathInfo}");

            routes.MapRoute(
                "Grid",                                              // Route name
                "Check.aspx/List/_Grid",                           // URL with parameters
                new { controller = "Check", action = "_Grid", id = "" }  // Parameter defaults
            );

            routes.MapRoute(
                "List",                                              // Route name
                "Check.aspx/List/{id}",                           // URL with parameters
                new { controller = "Check", action = "List", id = "" }  // Parameter defaults
            );

			routes.MapRoute(
				"Default",                                              // Route name
                "{controller}.aspx/{action}/{id}",                           // URL with parameters
                new { controller = "Account", action = "LogOn", id = "" }  // Parameter defaults
			);

            


            routes.MapRoute(
				"Add",                                              // Route name
                "{controller}.aspx/{action}/{id}",                           // URL with parameters
				new { controller = "Check", action = "Add", id = "" }  // Parameter defaults
			);

            
            routes.MapRoute(
              "Root",
              "",
              new { controller = "Home", action = "Index", id = "" }
            );

		}

		protected void Application_Start()
		{
			RegisterRoutes(RouteTable.Routes);

			ModelBinders.Binders.DefaultBinder = new DataAnnotationsModelBinder();
		}
	}
}