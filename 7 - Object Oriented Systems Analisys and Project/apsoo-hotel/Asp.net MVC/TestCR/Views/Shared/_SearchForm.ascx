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
    <tr>
        <td>
            <div id="keyword-search">
                <fieldset id="search" class="collapsed" style="width: 10%;">
                    <legend class="foldable" style="cursor: pointer"><a href="#" id="keyword">Search</a></legend>
                    <table>
                        <tr>
                            <td style="vertical-align: middle;">
                                <%= Html.TextBox("SearchForm.Keyword", Model.Keyword, new { @style = "width: 100px"}) %>
                            </td>
                            <td>
                                <button type="submit" id="keyword-search-submit" value="Search" style="height: -4px;
                                    width: 90px;">
                                    <img src="<%=ResolveUrl("~/Content/images/search.png")%>" align="left" />
                                    Search
                                </button>
                            </td>
                        </tr>
                    </table>
                </fieldset>
            </div>
        </td>
    </tr>
</table>
