<%@ Control Language="C#" Inherits="System.Web.Mvc.ViewUserControl<ServiceGrid>" %>
<%@ Import Namespace="Hotel"%>
<%@ Import Namespace="Hotel.Models"%>
<%@ Import Namespace="Hotel.Controllers"%>


<table>
	<tr>
		<th></th>
		<th>
			<%= Model.SortActionLink("Name", "Name")%>
		</th>
		
		<th>
			<%= Model.SortActionLink("Description", "Description")%>
		</th>
		
		<th>
			<%= Model.SortActionLink("Price", "Price")%>
		</th>
	</tr>

	<% 
		//Can't use Model.Data directly.  Doesn't pick up generic type.
		IList<Service> services = (IList<Service>)Model.Data;
	    foreach (Service item in services) { %>
    
		<tr onclick="onRowClick(<%= item.ID %>)">
			<td>
				<%= Html.ActionLink("Edit", "Edit", new { id=item.ID}) %> |
				<%= Html.ActionLink("Delete", "Delete", new { id=item.ID })%>
			</td>
			
			<td>
				<%= Html.Encode(item.Name) %>
			</td>
						
			<td>
				<%= Html.Encode(item.Description) %>
			</td>
			
			<td>
				<%= Html.Encode(String.Format("{0,00:F}", item.Price))%>
			</td>
		</tr>
    
	<% } %>
	
</table>
	