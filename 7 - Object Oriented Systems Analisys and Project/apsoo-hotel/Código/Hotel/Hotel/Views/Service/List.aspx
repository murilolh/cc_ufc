<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<ServiceGrid>" %>

<%@ Import Namespace="Hotel"%>
<%@ Import Namespace="Hotel.Models"%>
<%@ Import Namespace="Hotel.Controllers"%>
<%@ Import Namespace="Hotel.ViewModels.Shared"%>

<asp:Content ID="Content1" ContentPlaceHolderID="HeadContent" runat="server">
        
	<script type="text/javascript" src="<%= ResolveUrl("~") %>Scripts/jquery-autocomplete/jquery.autocomplete.js"></script>
	<script type="text/javascript" src="<%= ResolveUrl("~") %>Scripts/jquery.blockUI.js"></script>
	<script type="text/javascript" src="<%= ResolveUrl("~") %>Scripts/grid.js"></script>
	
	<link rel="stylesheet" type="text/css" href="<%= ResolveUrl("~")%>Scripts/jquery-autocomplete/jquery.autocomplete.css"  />
	<link rel="stylesheet" type="text/css" href="<%= ResolveUrl("~")%>Content/grid.css"  />	
	
</asp:Content>


<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">

    <h2>Services</h2>

    <%= Html.ActionLink("Add New", "Add") %>
    
    <% using (Html.BeginForm("List", "Service", FormMethod.Post)) { %>
		
		<div id="search-form">
			<% Html.RenderPartial("_SearchForm", Model.SearchForm); %>
		</div> <!-- search-form -->
			
		<div style="clear: both"></div>
		
		<%= Html.ValidationSummary("Action was unsuccessful. Please correct the errors and try again.") %>		
		<div id="grid">		
			<% Html.RenderPartial("_Grid", Model); %>
		</div>  <!-- grid -->	
	
	<% } %>
				
        <br />
        <div>
            <%=Html.ActionLink("Back to Control", "Index", "Control") %> 
         </div> 
</asp:Content>

