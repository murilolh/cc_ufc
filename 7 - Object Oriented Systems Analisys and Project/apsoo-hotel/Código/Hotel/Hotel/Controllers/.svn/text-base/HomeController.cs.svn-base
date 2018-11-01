using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using Hotel.Models.Repository;
using Hotel.Models;
using System.Web.UI.DataVisualization.Charting;
using System.Drawing;
using System.Web.UI.WebControls;
using System.IO;

namespace Hotel.Controllers
{
    [HandleError]
    public class HomeController : Controller
    {
        public ActionResult Index()
        {
            Chart chart = new Chart();            
            chart.BackColor = Color.Transparent;
            chart.Width = Unit.Pixel(250);
            chart.Height = Unit.Pixel(100);

            Series series1 = new Series("Series1");
            series1.ChartArea = "ca1";
            series1.ChartType = SeriesChartType.Pie;
            series1.Font = new Font("Verdana", 8.25f, FontStyle.Regular);
            series1.Points.Add(new DataPoint
            {
                AxisLabel = "Value1",
                YValues = new double[] { 10 }
            });
            series1.Points.Add(new DataPoint
            {
                AxisLabel = "Value2",
                YValues = new double[] { 20 }
            });
            chart.Series.Add(series1);

            ChartArea ca1 = new ChartArea("ca1");
            ca1.BackColor = Color.Transparent;
            chart.ChartAreas.Add(ca1);

            if (false)
            {
                using (var ms = new MemoryStream())
                {
                    chart.SaveImage(ms, ChartImageFormat.Png);
                    ms.Seek(0, SeekOrigin.Begin);

                    return File(ms.ToArray(), "image/png", "mychart.png");
                }
            }
            else
            {
                IRepository<Inn, hotelEntities> hr = new EFRepository<Inn, hotelEntities>();
                Inn hotel = hr.SelectAll().First();
                return View(hotel);
            }
        }
    }
}
