<%@ Control Language="C#" Inherits="System.Web.Mvc.ViewUserControl<IGrid>" %>
<%@ Import Namespace="Hotel.Controllers"%>
<%@ Import Namespace="Hotel.Models"%>
<%@ Import Namespace="Hotel.ViewModels.Shared"%>

<% if (Model.Pager.IsNavVisible) { %>
	<table>
		<tr>
			<td>
				<% if (Model.Pager.IsFirstPage) { %>
					<span class="disabled"><%= Html.Encode("<<") %></span>
				<% } else { %>
					<%= Model.PageNavActionLink("<<", Model.Pager.FirstPage) %>   
				<% } %>
			</td>
			
			<td>
				<% if ( Model.Pager.IsFirstPage) { %>
					<span class="disabled"><%= Html.Encode("<") %></span>
				<% } else { %>
					<%= Model.PageNavActionLink("<", Model.Pager.PreviousPage) %>
				<% } %>
				</td>
			
			<td>Page <%= Model.Pager.CurrentPage %> of <%= Model.Pager.TotalPages %></td>
			
			<td>
				<% if (Model.Pager.IsLastPage) { %>
					<span class="disabled"><%= Html.Encode(">") %></span>
				<% } else { %>
					<%= Model.PageNavActionLink(">", Model.Pager.NextPage) %>
				<% } %>
			</td>
			
			<td>
				<% if (Model.Pager.IsLastPage) { %>
					<span class="disabled"><%= Html.Encode(">>") %></span>
				<% } else { %>
					<%= Model.PageNavActionLink(">>", Model.Pager.LastPage) %>  
				<% } %>
			</td>
			
		</tr>
	</table>
<% } %>