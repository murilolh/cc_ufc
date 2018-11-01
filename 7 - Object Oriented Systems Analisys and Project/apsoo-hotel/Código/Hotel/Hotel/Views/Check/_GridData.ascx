<%@ Control Language="C#" Inherits="System.Web.Mvc.ViewUserControl<CheckGrid>" %>
<%@ Import Namespace="Hotel"%>
<%@ Import Namespace="Hotel.Models"%>
<%@ Import Namespace="Hotel.Controllers"%>


<table>
	<tr>
		<th>Actions</th>
		<th>
			<%= Model.SortActionLink("Name", "Name")%>
		</th>
		<th>
			<%= Model.SortActionLink("Apartment", "ApartmentNumber")%>
		</th>		
		<th>
			<%= Model.SortActionLink("Status", "Status")%>
		</th>		
		<th>
			<%= Model.SortActionLink("Date Begin", "DateBegin")%>
		</th>
		<th>
			<%= Model.SortActionLink("Date End", "DateEnd")%>
		</th>
		<th>
			<%= Model.SortActionLink("Daily Value", "Value")%>
		</th>
	</tr>

	<%  
		//Can't use Model.Data directly.  Doesn't pick up generic type.
		IList<Check> checks = (IList<Check>)Model.Data;
	    foreach (Check item in checks) { %>
    
		<tr onclick="onClick(<%= item.ID %>)">
			<td>
			    <%= Html.ActionLink("Details", "Details", new { id = item.ID, view = (String)ViewData["view"]})%> |
				<%= Html.ActionLink("Edit", "Edit", new { id = (String)ViewData["typeView"], clientId = item.ID, view = (String)ViewData["view"] })%> |
				<%= Html.ActionLink("Cancel", "Cancel", new { id=item.ID, view=(String)ViewData["view"]}) %> |
				<%= Html.ActionLink("Delete", "Delete", new { id=item.ID, view=(String)ViewData["view"]}) %> 
			</td>
			<td>
				<%= Html.Encode(item.Client.Name) %>
			</td>
			<td>
				<%= Html.Encode(item.Apartment.Number) %>
			</td>		
			<td>
				<%= Html.Encode(EnumExtensions.GetStringValue(item.CheckStatus))%>
			</td>			
			<td>
				<%= Html.Encode(StringFormatter.FormatInputDateTime(item.DateBegin)) %>
			</td>
			<td>
				<%= Html.Encode(StringFormatter.FormatInputDateTime(item.DateEnd)) %>
			</td>
			<td>
				<%= Html.Encode(String.Format("{0:F}", item.Value)) %>
			</td>			
		</tr>
    
	<% } %>
	
</table>
	