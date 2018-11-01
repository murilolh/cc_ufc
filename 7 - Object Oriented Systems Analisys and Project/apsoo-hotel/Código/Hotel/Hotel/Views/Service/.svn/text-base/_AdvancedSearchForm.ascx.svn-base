<%@ Control Language="C#" Inherits="System.Web.Mvc.ViewUserControl<ServiceSearchForm>" %>
<%@ Import Namespace="Hotel"%>
<%@ Import Namespace="Hotel.ViewModels.Shared"%>
<%@ Import Namespace="Hotel.Controllers"%>

<table id="advanced-search-fields"> 
	<tr>
		<td>
			Name<br />
			<%= Html.TextBox("SearchForm.Name", Model.Name, new { @style = "width: 100px", @maxlength = "20" })%>
		</td>		
		<td>
			Description<br />
			<%= Html.TextBox("SearchForm.Description", Model.Description, new { @style = "width: 100px", @maxlength = "20" })%>
		</td>
		
		<td>
			Price Range<br />
			<table id="range">
				<tr>
					<td>
						<%= Html.TextBox("SearchForm.FromPrice", Model.ToPrice, new { @style = "width: 100px", @maxlength = "15" })%>
						<%= Html.ValidationMessage("SearchForm.FromPrice")%>
					</td>
					<td>
						to
					</td>
					<td>
						<%= Html.TextBox("SearchForm.ToPrice", Model.FromPrice, new { @style = "width: 100px", @maxlength = "15" })%>
						<%= Html.ValidationMessage("SearchForm.ToPrice", "Invalid price.")%>
					</td>
			
				</tr>
			</table>
			
			
		</td>
	</tr>
</table>
			