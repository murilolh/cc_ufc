<%@ Control Language="C#" Inherits="System.Web.Mvc.ViewUserControl<DashBoardGrid>" %>
<%@ Import Namespace="CodeReview.Web.ViewModels.Shared" %>
<%@ Import Namespace="CodeReview.Web" %>
<%@ Import Namespace="CodeReview.Web.Services" %>
<%@ Import Namespace="CodeReview.Web.Controllers" %>
 <%=Html.Hidden("TypeView") %>
<%= Html.Hidden("Pager.CurrentPage")%>
<%= Html.Hidden("Sorter.SortField")%>
<%= Html.Hidden("Sorter.SortDirection")%>
<%= Html.Hidden("GridAction") %>
<%= Html.Hidden("SearchForm.GridType") %>

<% if (!ViewData.ModelState.IsValid) {%>
<div class="validation-summary-errors">
    <%--- <strong>Please fix indicated errors.</strong> ---%>
    <strong>Operation was unsuccessful. Please correct the errors and try again.</strong>
</div>
<% } else if (Model.IsEmpty) { %>
<div id="empty-message">
    <br />
    <strong>There are no reviews that match specified criteria.</strong>
</div>
<% } else { %>
<div id="grid-header">
    <table style="width:100%"; cellpadding="0" cellspacing="0">
        <tr>
            <td width="20%" align="left">
                <%= Model.Pager.RowStats %>
            </td>
            <td width="60%" align="center">
                <% Html.RenderPartial("_PagerNav", Model); %>
            </td>
            <td width="20%" align="right">
                <noscript>
                    <input type="submit" id="Submit1" value="refresh" /></noscript>
                <%= Html.DropDownList("Pager.PageSize", Model.PageSizeSelectList())%>
                rows per page
            </td>
        </tr>
    </table>
</div>
<!-- grid-header -->
<div id="grid-data">
    <% Html.RenderPartial("_GridData", Model); %>
</div>
<!-- data -->
<div id="grid-footer">
    <table width="100%" cellpadding="0" cellspacing="0">
        <tr>
            <td align="center">
                <% Html.RenderPartial("_PagerNav", Model); %>
            </td>
        </tr>
    </table>
</div>
<!-- grid-footer -->
<% } %>
