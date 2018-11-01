<%@ Control Language="C#" Inherits="System.Web.Mvc.ViewUserControl<CheckSearchForm>" %>
<%@ Import Namespace="Hotel"%>
<%@ Import Namespace="Hotel.ViewModels.Shared"%>
<%@ Import Namespace="Hotel.Controllers"%>

<table id="advanced-search-fields"> 
	<tr>
	    <td>
			AparmentNumber<br />
			<%= Html.TextBox("SearchForm.AparmentNum", Model.ApartmentNum, new { @style = "width: 100px", @maxlength = "20" })%>
		</td>	
		<td>
			Status<br />
			<%= Html.TextBox("SearchForm.Status", Model.Status, new { @style = "width: 100px", @maxlength = "20" })%>
		</td>		
		
		<td>
			Date Range<br />
			<table id="range">
				<tr>
					<td>
						<%= Html.TextBox("SearchForm.FromDateBegin", Model.ToDateBegin, new { @style = "width: 100px", @maxlength = "15" , @class = "with-date-picker"})%>
						<%= Html.ValidationMessage("SearchForm.FromDateBegin")%>
					</td>
					<td>
						to
					</td>
					<td>
						<%= Html.TextBox("SearchForm.ToDateBegin", Model.FromDateBegin, new { @style = "width: 100px", @maxlength = "15" , @class = "with-date-picker"})%>
						<%= Html.ValidationMessage("SearchForm.ToDateBegin")%>
					</td>
			
				</tr>
			</table>
			
			
		</td>
	</tr>
</table>
			