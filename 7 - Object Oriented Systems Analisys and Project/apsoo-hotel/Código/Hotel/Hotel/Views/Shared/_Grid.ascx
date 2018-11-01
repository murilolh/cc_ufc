<%@ Control Language="C#" Inherits="System.Web.Mvc.ViewUserControl<IGrid>" %>
<%@ Import Namespace="Hotel.ViewModels.Shared"%>
<%@ Import Namespace="Hotel"%>
<%@ Import Namespace="Hotel.Models"%>
<%@ Import Namespace="Hotel.Controllers"%>


<%= Html.Hidden("Pager.CurrentPage")%>
		
<%= Html.Hidden("Sorter.SortField")%>
<%= Html.Hidden("Sorter.SortDirection")%>

<%= Html.Hidden("GridAction") %>


<% if (!ViewData.ModelState.IsValid && !ViewData.ModelState.Keys.Contains("_FORM")) {%>
	<div class="validation-summary-errors">
		<strong>Please fix indicated errors.</strong> 
	</div>
<% } else if (Model.IsEmpty) { %>
	<div id="empty-message">
		<strong>There are no itens that match specified criteria.</strong> 
	</div>
<% } else { %>
	

	<div id="grid-header">
		<div id="row-stats">
			<%= Model.Pager.RowStats %>
		</div>
		
		<div class="pager-nav">			
			<% Html.RenderPartial("_PagerNav", Model); %>
		</div>
		
		<div style="clear: both"></div>
	</div> <!-- grid-header -->
	
				
	<div id="grid-data">
		<% Html.RenderPartial("_GridData", Model); %>
	</div> <!-- data -->
	
	<div id="grid-footer">
		<div id="page-size-div">
			<noscript><input type="submit" id="refresh-button" value="refresh" /></noscript>
			<%= Html.DropDownList("Pager.PageSize", Model.PageSizeSelectList())%> rows per page
		</div>
		
		<div class="pager-nav">			
			<% Html.RenderPartial("_PagerNav", Model); %>
		</div>
		
		<div style="clear: both;"/>
	</div>

<% } %>
