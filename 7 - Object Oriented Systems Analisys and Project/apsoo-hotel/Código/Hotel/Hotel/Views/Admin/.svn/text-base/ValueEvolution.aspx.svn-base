<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
	Value Evolution
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">

    <h2>Value Evolution</h2>
    <h4>Description: What is the evolution of the amount billed by the hotel for the past three months?</h4>
     <% using (Html.BeginForm("ChartGenerate", "Admin", new { id = (String)ViewData["View"] }))
		{  %>   
        <p>
            <input type="submit" value="View Chart" />
         </p>
         <%} %>
         
         <%if((double[])ViewData["Chart"] != null) { %>  
    <p>
        <div style="text-align: center;">           
                    <%
                        System.Web.UI.DataVisualization.Charting.Chart Chart2 = new System.Web.UI.DataVisualization.Charting.Chart() {
                            Width = 600,
                            Height = 400,
                            RenderType = RenderType.ImageTag,
                            ImageType = ChartImageType.Png,
                            AntiAliasing = AntiAliasingStyles.All,
                            TextAntiAliasingQuality = TextAntiAliasingQuality.High
                        };
                                                
                        Chart2.Palette = ChartColorPalette.BrightPastel;
                        Title t = new Title("Value Evolution", Docking.Top, new System.Drawing.Font("Trebuchet MS", 14, System.Drawing.FontStyle.Bold), System.Drawing.Color.FromArgb(26, 59, 105));
                        Chart2.Titles.Add(t);
                        Chart2.ChartAreas.Add("Series 1");

						// create a couple of series
                        Chart2.Series.Add("Value");
						
                        String[] label = (String[])ViewData["Label"];
                        double[] value = (double[])ViewData["Chart"];
						// add points to series 1
                        for (int i = 2; i > -1; i--)
                            Chart2.Series["Value"].Points.AddXY(label[i],value[i]);
                        
                        Chart2.BorderColor = System.Drawing.Color.FromArgb(26, 59, 105);
                        Chart2.BorderlineDashStyle = ChartDashStyle.Solid;
                        Chart2.BorderWidth = 2;

                        Chart2.BorderSkin.BackGradientStyle = GradientStyle.TopBottom;
                        Chart2.BorderSkin.SkinStyle = BorderSkinStyle.FrameThin6;
                        Chart2.BorderSkin.BackColor = System.Drawing.Color.SlateBlue;
                        Chart2.BorderSkin.BackSecondaryColor = System.Drawing.Color.SteelBlue;

                        
                        Legend legend = Chart2.Legends.Add("Default");
                        legend.Title = "Months";

						// Render chart control
                        Chart2.Page = this;
						HtmlTextWriter writer = new HtmlTextWriter(Page.Response.Output);
						Chart2.RenderControl(writer);
					
                     %>
                     </div>
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
