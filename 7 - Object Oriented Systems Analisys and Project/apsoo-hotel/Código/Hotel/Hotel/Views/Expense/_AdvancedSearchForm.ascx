<%@ Control Language="C#" Inherits="System.Web.Mvc.ViewUserControl<ExpenseSearchForm>" %>
<%@ Import Namespace="Hotel"%>
<%@ Import Namespace="Hotel.ViewModels.Shared"%>
<%@ Import Namespace="Hotel.Controllers"%>

<table id="advanced-search-fields"> 
	<tr>
	    <td>
			Service<br />
			<%= Html.TextBox("SearchForm.Service", Model.Service, new { @style = "width: 100px", @maxlength = "20" })%>
		</td>		
		
		<td>
			Date Range<br />
			<table id="range">
				<tr>
					<td>
						<%= Html.TextBox("SearchForm.FromDate", Model.FromDate, new { @style = "width: 100px", @maxlength = "15" , @class = "with-date-picker"})%>
						<%= Html.ValidationMessage("SearchForm.FromDate")%>
					</td>
					<td>
						to
					</td>
					<td>
						<%= Html.TextBox("SearchForm.ToDate", Model.ToDate, new { @style = "width: 100px", @maxlength = "15" , @class = "with-date-picker"})%>
						<%= Html.ValidationMessage("SearchForm.ToDate")%>
					</td>
			
				</tr>
			</table>
			
			
		</td>
	</tr>
</table>
			