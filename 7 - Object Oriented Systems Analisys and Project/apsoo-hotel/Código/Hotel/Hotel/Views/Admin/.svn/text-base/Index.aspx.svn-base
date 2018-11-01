<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
	Index
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
    
    <h2>Available Management Queries</h2>     
      <h3 class="item">
        <%= Html.ActionLink("Occupancy rate", "ChartGenerate", "Admin", new { id = "OccupancyRate" }, new { @title = "What is the rate of hotel occupancy on the date X? (In a fit of occupied / total eligible)" })%><br />
        <%= Html.ActionLink("Value Evolution", "ChartGenerate", "Admin", new { id = "ValueEvolution" }, new { @title = "What is the evolution of the amount billed by the hotel for the past three months?" })%><br />
        <%= Html.ActionLink("Search Apartment by Guest", "ChartGenerate", "Admin", new { id = "SearchApartmentByGuest" }, new { @title = "In which apartment is the guest X?" })%><br />
        <%= Html.ActionLink("Best Services", "ChartGenerate", "Admin", new { id = "BestServices" }, new { @title = "What services billed more than the previous month?" })%><br />
      </h3>
     
</asp:Content>

<asp:Content ID="Content3" ContentPlaceHolderID="JavaScriptContent" runat="server">
</asp:Content>

<asp:Content ID="Content4" ContentPlaceHolderID="CssContent" runat="server">
</asp:Content>

<asp:Content ID="Content5" ContentPlaceHolderID="HeadContent" runat="server">
<style type="text/css">
        .item
        {
            height: 42px;
        }
    </style>
</asp:Content>
