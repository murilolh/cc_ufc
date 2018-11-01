<%@ Control Language="C#" Inherits="System.Web.Mvc.ViewUserControl<SearchForm>" %>
<%@ Import Namespace="Hotel.ViewModels.Shared"%>
<%@ Import Namespace="Hotel.Controllers"%>

<%= Html.Hidden("SearchForm.IsAdvanced", Model.IsAdvanced) %>
		
<table>
	<tr>
		<td align="right">
			<a href="#" id="advanced-link" <%= Model.IsAdvanced ? "class='hidden'" : ""%>>advanced >></a>
			<a href="#" id="keyword-link" <%= Model.IsAdvanced ? "" : "class='hidden'"%>>keyword >></a>
		</td>
	</tr>
	
	<tr>
		<td>
			<div id="advanced-search" <%= Model.IsAdvanced ? "" : "class='hidden'"%>>
				<table>
					<tr>
						<td>
							<% Html.RenderPartial("_AdvancedSearchForm", Model); %>
						</td>
					</tr>
					<tr>
						<td align="right">
							<input type="submit" id="advanced-search-submit" value="Search" />
						</td>
					</tr>
				</table>		
			</div>
				

			
			<div id="keyword-search" <%= Model.IsAdvanced ? "class='hidden'" : ""%>>
				<table>
					<tr>
						<td>
							<%= Html.TextBox("SearchForm.Keyword", Model.Keyword, new { @style = "width: 100px" , @maxlength ="20"}) %>
						</td>
						<td><input type="submit" id="keyword-search-submit" value="Search" /></td>
					</tr>
				</table>
			</div>
		</td>
	</tr>
</table>
		