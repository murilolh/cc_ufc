<%@ Control Language="C#" Inherits="System.Web.Mvc.ViewUserControl<ExpenseGrid>" %>
<%@ Import Namespace="Hotel"%>
<%@ Import Namespace="Hotel.Models"%>
<%@ Import Namespace="Hotel.Controllers"%>


<table>
	<tr>
		<th></th>
		<th>
			<%= Model.SortActionLink("Service", "Service")%>
		</th>
		<th>
			<%= Model.SortActionLink("Date", "Date")%>
		</th>
		<th>
			<%= Model.SortActionLink("Value", "Value")%>
		</th>
	</tr>

	<% 
		//Can't use Model.Data directly.  Doesn't pick up generic type.
		IList<Expense> expenses = (IList<Expense>)Model.Data;
	    foreach (Expense item in expenses) { %>
    
		<tr onclick="onRowClick(<%= item.ID %>)">
			<td>
				<%= Html.ActionLink("Edit", "Edit", new { id=item.ID}) %> |
				<%= Html.ActionLink("Delete", "Delete", new { id=item.ID })%>
			</td>
			<td>
				<%= Html.Encode(item.Service.Name) %>
			</td>
			<td>
				<%= Html.Encode(StringFormatter.FormatInputDateTime(item.Date)) %>
			</td>
			<td>
				<%= Html.Encode(String.Format("{0,00:F}", item.Value)) %>
			</td>
		</tr>
    
	<% } %>
	
</table>
	