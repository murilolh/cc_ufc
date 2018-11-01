<%@ Control Language="C#" Inherits="System.Web.Mvc.ViewUserControl<FileSearchForm>" %>
<%@ Import Namespace="CodeReview.Web" %>
<%@ Import Namespace="CodeReview.Web.ViewModels.Shared" %>
<%@ Import Namespace="CodeReview.Web.Controllers" %>

<script type="text/javascript">
    function onStatusSelect(checkBox) {
        if (checkBox.checked)
            $("#SearchForm_Status").val($("#SearchForm_Status").val() + ($("#SearchForm_Status").val().length > 0 ? ";" : "") + checkBox.value);
        else {
            $("#SearchForm_Status").val($("#SearchForm_Status").val().replace(";" + checkBox.value, ""));
            $("#SearchForm_Status").val($("#SearchForm_Status").val().replace(checkBox.value, ""));
        }

        $("#SearchForm_Status").val($("#SearchForm_Status").val().replace(";;", ";"));

        $("#GridAction").val("AdvancedSearch");
        $("#SearchForm_IsAdvanced").val(true);
        submitFormWithAjax();
        return false;
    } 
</script>

<table id="advanced-search-fields">
    <tr>
        <td colspan="6">
            <div id="status-search">
                <table>
                    <tr>
                        <th>
                            Filter by Status:
                        </th>
                        <td>
                            <input id="CheckboxPending"  type="checkbox" value="Pending" onclick="onStatusSelect(this)" <%=Model.Status != null && Model.Status.ContainsCaseInsensitive("Pending") ? "checked" : "" %>/>
                            <label for="CheckboxPending">
                                Pending
                            </label>
                        </td>
                        <td>
                            <input id="CheckboxApproved" type="checkbox" value="Approved" onclick="onStatusSelect(this)" <%=Model.Status != null && Model.Status.ContainsCaseInsensitive("Approved") ? "checked" : "" %>/>
                            <label for="CheckboxApproved">
                                Approved
                            </label>
                        </td>
                        <td>
                            <input id="CheckboxRejected" type="checkbox" value="Rejected" onclick="onStatusSelect(this)" <%=Model.Status != null && Model.Status.ContainsCaseInsensitive("Rejected") ? "checked" : "" %>/>
                            <label for="CheckboxRejected">
                                Rejected
                            </label>
                        </td>
                    </tr>
                </table>
            </div>
        </td>
    </tr>
    <tr>
        <td>
            Name<br />
            <%= Html.TextBox("SearchForm.Name", Model.Name, new { @style = "width: 100%"})%>
        </td>
        <%= Html.Hidden("SearchForm.Status", Model.Status )%>
        <td>
            Last change<br />
            <table id="date-of-creation-range">
                <tr>
                    <td>
                        <%= Html.TextBox("SearchForm.FromDateOfLastChange", StringFormatter.FormatInputDate(Model.FromDateOfLastChange), new { @style = "width: 100%", @class = "with-date-picker" })%>
                        <%= Html.ValidationMessage("SearchForm.FromDateOfLastChange", "Invalid date.")%>
                    </td>
                    <td style="vertical-align: middle">
                        &nbsp;to&nbsp;
                    </td>
                    <td>
                        <%= Html.TextBox("SearchForm.ToDateOfLastChange", StringFormatter.FormatInputDate(Model.ToDateOfLastChange), new { @style = "width: 100%", @class = "with-date-picker" })%>
                        <%= Html.ValidationMessage("SearchForm.ToDateOfLastChange", "Invalid date.")%>
                    </td>
                </tr>
            </table>
        </td>
        <td>
            <button type="submit" id="advanced-search-submit" value="Search" style="height: -4px;
                width: 90px;">
                <img src="<%=ResolveUrl("~/Content/images/search.png")%>" alt="" align="left" />
                Search
            </button>
        </td>
    </tr>
</table>
