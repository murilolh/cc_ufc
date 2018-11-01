<%@ Control Language="C#" Inherits="System.Web.Mvc.ViewUserControl<SearchForm>" %>
<%@ Import Namespace="CodeReview.Web.ViewModels.Shared" %>
<%@ Import Namespace="CodeReview.Web.Controllers" %>
<%= Html.Hidden("SearchForm.IsAdvanced", Model.IsAdvanced) %>
<table style="width: 100%;" cellpadding="0" cellspacing="0">
    <tr>
        <td>
            <div id="advanced-search">
                <fieldset id="filters">
                    <legend class="foldable" style="cursor: pointer"><a href="#" id="advanced">Filters</a>
                    </legend>
                    <% Html.RenderPartial("_AdvancedSearchForm", Model); %>
                </fieldset>
            </div>
        </td>
    </tr>
</table>
