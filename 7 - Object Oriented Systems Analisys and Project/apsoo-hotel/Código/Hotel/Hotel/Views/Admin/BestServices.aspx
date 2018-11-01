<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage" %>

<%@ Import Namespace="System.Web.UI.DataVisualization.Charting" %>
<%@ Import Namespace="System.Drawing" %>
<%@ Import Namespace="System.Web.UI.WebControls" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
	Best Services
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">

    <h2>Best Services</h2>     
    
    <h4>Description: What services billed more than the previous month?</h4>
    <style>
        .ui-datepicker-calendar {
        display: none;
    }
</style>
     <% using (Html.BeginForm("ChartGenerate", "Admin", new { id = (String)ViewData["View"] }))
		{  %>  
		<p>
            <label for="Month">Month:</label>
            <%= Html.TextBox("Month", (String)ViewData["Month"], new { @class = "with-date-month-picker", @maxlength = "20", @style = "width : 100px" })%>
            <%= Html.ValidationMessage("Month")%>
            <input type="submit" value="View Chart" />
         </p>
         <%} %>
        <p>  
                <%double[] val = (double[])ViewData["Rate"];
                if(val != null && val.Count() > 0) { %>  
            <div style="text-align: center;">           
              <%
                  System.Web.UI.DataVisualization.Charting.Chart Chart1 = new System.Web.UI.DataVisualization.Charting.Chart(){                  
                    Width = 700,
                    Height = 500,
                    RenderType = RenderType.ImageTag,
                    ImageType = ChartImageType.Png,
                    AntiAliasing = AntiAliasingStyles.All,
                    TextAntiAliasingQuality = TextAntiAliasingQuality.High
                    };
                    
                    
                    Chart1.BorderSkin.BackGradientStyle = GradientStyle.TopBottom;
                    Chart1.BorderSkin.SkinStyle = BorderSkinStyle.FrameThin6;
                    Chart1.BorderSkin.BackColor = Color.SlateBlue;
                    Chart1.BorderSkin.BackSecondaryColor = Color.SteelBlue;

                    Legend legend = Chart1.Legends.Add("Default");
                    legend.Title = "Services";
                    legend.TitleAlignment = StringAlignment.Near;
                    legend.Docking = Docking.Bottom;
            
            
                  // Display 3D Pie Chart
                  Chart1.Series.Add("Default");
                  Chart1.Series[0].ChartType = SeriesChartType.Pie;
                  Chart1.Series[0]["PieLabelStyle"] = "Outside";
                  Chart1.ChartAreas.Add(new ChartArea());
                  Chart1.ChartAreas[0].Area3DStyle.Enable3D = true;


                Chart1.Series[0]["CollectedThreshold"] = "1";
                Chart1.Series[0]["CollectedThresholdUsePercent"] = "false";
                Chart1.Series[0]["CollectedSliceExploded"] = "true";
                Chart1.Series[0]["CollectedLabel"] = "Other (#PERCENT)";
                Chart1.Series[0]["CollectedLegendText"] = "Other (#PERCENT)";
                
                Chart1.Series[0].IsValueShownAsLabel = false;
                Chart1.Series[0].LegendText = "#LABEL";
            
                  // Display a Title
                Chart1.Titles.Add("Best Services in " + (String)ViewData["Month"]);
                  
                  string[] values = (string[])ViewData["Values"];

                  // Add Data to Display
                  string[] xValues = values;
                  double[] yValues = (double[])ViewData["Rate"];
                  Chart1.Series[0].Points.DataBindXY(xValues, yValues);

                  // Call Out The Letter "D"                  
                  //Chart1.Series[0].Points[0]["Exploded"] = "true";
                  

                  // Render chart control
                  Chart1.Page = this;
                  HtmlTextWriter writer1 = new HtmlTextWriter(Page.Response.Output);
                  Chart1.RenderControl(writer1);
                %>
                </div>
                <%}
                else if (val == null)
                { %>
                            <span class="validation-summary-errors">
                                You must select a month and click in View Chart
                            </span>
                <% }
                else
                { %>
                            <span class="validation-summary-errors">
                            There is no data available for this month                               
                            </span>
                
                <%} %>
        </p>
        
        <br />
        <div>
            <%=Html.ActionLink("Back to Administration", "Index", "Admin") %> 
         </div> 

</asp:Content>

<asp:Content ID="Content3" ContentPlaceHolderID="JavaScriptContent" runat="server">
</asp:Content>

<asp:Content ID="Content4" ContentPlaceHolderID="CssContent" runat="server">
</asp:Content>

<asp:Content ID="Content5" ContentPlaceHolderID="HeadContent" runat="server">
</asp:Content>
