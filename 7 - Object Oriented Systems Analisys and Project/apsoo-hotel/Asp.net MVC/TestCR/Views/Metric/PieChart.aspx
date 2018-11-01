<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage" %>

<%@ Import Namespace="System.Web.UI.DataVisualization.Charting" %>
<%@ Import Namespace="System.Drawing" %>
<%@ Import Namespace="CodeReview.Metric" %>
<%@ Import Namespace="CodeReview.Model.Entities" %>
<%@ Import Namespace="CodeReview.Web" %>
<%@ Import Namespace="CodeReview.Web.Helpers" %>
<%@ Import Namespace="CodeReview.Web.Services" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
	Pie Chart
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
   
    <%
    IMetric metric = ViewData["metric"] as IMetric;
    ReviewCriteria reviewCriteria = ViewData["reviewCriteria"] as ReviewCriteria;
    metric.Reviews = ViewData["ReviewsForMetrics"] as IList<Review>;
    %>

    <h2>Pie Chart - <%=metric.Name%></h2>
    
    <fieldset>
        <legend>Summary</legend>
        
        <div style="margin-bottom:5px;">
            <b>Metric description:</b> <%= Html.Encode(metric.Description)%>
        </div>
        
        <div style="margin-bottom:5px;">
            <b>Filter used:</b> <%= Html.Encode(reviewCriteria.CriteriaText)%>
        </div>
    </fieldset>
    
    <br />
    <% if (metric.Elements.Count() == 0) { %>
        <script type="text/javascript">
            alert("No data available to generate graphic. Please choose a valid Filter.");
            document.location = "/Metric/Index";
        </script>
    <% } %>
    <div style="text-align: center;">
        <img src="PieChartPNG/<%=metric.Name%>" />
    </div>
    
    <br />
    
    [<%=Html.ActionLink("Back to Metric", "Index") %>]
</asp:Content>

<asp:Content ID="Content3" ContentPlaceHolderID="JavascriptContent" runat="server">
</asp:Content>

<asp:Content ID="Content4" ContentPlaceHolderID="CSSContent" runat="server">
</asp:Content>

<asp:Content ID="Content5" ContentPlaceHolderID="HeadContent" runat="server">
</asp:Content>
