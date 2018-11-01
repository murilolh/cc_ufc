<%@ Control Language="C#" Inherits="System.Web.Mvc.ViewUserControl<ClientGrid>" %>
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
			<%= Model.SortActionLink("Login", "Login")%>
		</th>
				
		<th>
			<%= Model.SortActionLink("CPF", "CPF")%>
		</th>
		
		<th>
			<%= Model.SortActionLink("Date of Birth", "DateOfBirth")%>
		</th>
	</tr>

	<% 
		//Can't use Model.Data directly.  Doesn't pick up generic type.
		IList<Client> clients = (IList<Client>)Model.Data;
	    foreach (Client item in clients) { %>
    
		<tr onclick="onRowClick(<%= item.ID %>)">
			<td>
				<%= Html.ActionLink("Edit", "Edit", new { id=item.ID}) %> |
				<%= Html.ActionLink("Delete", "Delete", new { id=item.ID })%>
			</td>

			<td>
				<%= Html.Encode(item.Name) %>
			</td>
			
			<td>
				<%= Html.Encode(item.Login) %>
			</td>
			
			
			<td>
				<%= Html.Encode(item.CPF) %>
			</td>
			
			<td>
				<%= Html.Encode(StringFormatter.FormatInputDate(item.DateOfBirth)) %>
			</td>
		</tr>
    
	<% } %>
	
</table>
	