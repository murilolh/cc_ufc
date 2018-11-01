<%@ Control Language="C#" Inherits="System.Web.Mvc.ViewUserControl<IGrid>" %>

<%@ Import Namespace="CodeReview.Web.ViewModels.Shared"%>
<%@ Import Namespace="CodeReview.Web"%>
<%@ Import Namespace="CodeReview.Web.Services"%>
<%@ Import Namespace="CodeReview.Web.Controllers"%>

<% if (Model.Pager.IsNavVisible) { %>
	<table>
		<tr>
			<td>
				<% if (Model.Pager.IsFirstPage) { %>
					<img src="<%= ResolveUrl("~/Content/images/nav_first_disabled.png") %>" />
				<% } else { %>
					<%= Model.PageNavActionLink(ResolveUrl("~/Content/images/nav_first.png"), Model.Pager.FirstPage) %>   
				<% } %>
			</td>
			
			<td>
				<% if ( Model.Pager.IsFirstPage) { %>
					<img src="<%= ResolveUrl("~/Content/images/nav_prev_disabled.png") %>" />
				<% } else { %>
					<%= Model.PageNavActionLink(ResolveUrl("~/Content/images/nav_prev.png"), Model.Pager.PreviousPage) %>
				<% } %>
				</td>
			
			<td nowrap>Page <%= Model.Pager.CurrentPage %> of <%= Model.Pager.TotalPages %></td>
			
			<td>
				<% if (Model.Pager.IsLastPage) { %>
					<img src="<%= ResolveUrl("~/Content/images/nav_next_disabled.png") %>" />
				<% } else { %>
					<%= Model.PageNavActionLink(ResolveUrl("~/Content/images/nav_next.png"), Model.Pager.NextPage) %>
				<% } %>
			</td>
			
			<td>
				<% if (Model.Pager.IsLastPage) { %>
					<img src="<%= ResolveUrl("~/Content/images/nav_last_disabled.png") %>" />
				<% } else { %>
					<%= Model.PageNavActionLink(ResolveUrl("~/Content/images/nav_last.png"), Model.Pager.LastPage) %>  
				<% } %>
			</td>			
		</tr>
	</table>
<% } %>