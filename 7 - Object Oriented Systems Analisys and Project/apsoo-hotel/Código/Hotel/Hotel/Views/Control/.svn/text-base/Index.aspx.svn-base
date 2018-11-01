<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage" %>

<%@ Import Namespace="Hotel.Models" %>
<%@ Import Namespace="Hotel.Models.Repository" %>

<script runat="server">

    protected void Page_Load(object sender, EventArgs e)
    {

    }
</script>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
	    Control and Maintenance of the System
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">

    <h2>Available Actions</h2>     
      <h3 class="item">
        <%= Html.ActionLink("Maintain Checks", "Index", "Check")%><br />
        <%= Html.ActionLink("Maintain Clients", "Index", "Client")%><br />
        <%= Html.ActionLink("Maintain Services", "Index", "Service")%><br />
        <%= Html.ActionLink("Maintain Apartments", "Index", "Apartment")%><br />
        <%= Html.ActionLink("Maintain Apartment Types", "Index", "ApartmentType")%><br />
      </h3>
      <br />
      <br />
    
            
       <%  InheritRepository<Employee,Person,hotelEntities> er = new InheritRepository<Employee,Person,hotelEntities>();
           try
           {
               Employee emp = er.SelectOne(e => e.Login == HttpContext.Current.User.Identity.Name && e.Type == (int)EmployeeType.MANAGER);
               if (emp != null && !String.IsNullOrEmpty(HttpContext.Current.User.Identity.Name))
               { %> 
        <h2>Manager Actions</h2> 
        <h3  class="item">
            <%= Html.ActionLink("Manage Employees", "Index", "Employee")%>
        <% }
           } 
           catch (Exception ex)
           {

           }%>
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
