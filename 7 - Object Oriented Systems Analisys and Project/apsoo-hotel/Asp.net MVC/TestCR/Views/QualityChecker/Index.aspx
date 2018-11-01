<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<IEnumerable<CodeReview.Model.Entities.QualityChecker>>" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
    Quality Checkers management
</asp:Content>

<asp:Content ID="Content4" ContentPlaceHolderID="CSSContent" runat="server">
     <link href="<%=ResolveUrl("~/Scripts/jquery-ui-1.7.2/themes/redmond/jquery-ui-1.7.2.custom.css")%>"
        rel="stylesheet" type="text/css" />
</asp:Content>

<asp:Content ID="Content5" ContentPlaceHolderID="JavascriptContent" runat="server">

    <script src="<%=ResolveUrl("~/Scripts/jquery-ui-1.7.2.custom.min.js")%>" type="text/javascript"></script>

    <script type="text/javascript">
        var deleteLink;
        jQuery(document).ready(
            function() {
                jQuery("#dialog").dialog({
                    autoOpen: false,
                    resizable: false,
                    height: 180,
                    modal: true,
                    buttons: {
                        'Delete': function() {
                            jQuery(this).dialog('close');
                            window.location = deleteLink;
                        },
                        Cancel: function() {
                            jQuery(this).dialog('close');
                        }
                    }
                });
                jQuery(".delete").click(function() {
                    jQuery("#dialog").dialog('open');
                    deleteLink = jQuery(this).attr('href');
                    return false;
                });
            }
        );
        
    </script>

</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
    <h2>
        Quality Checkers management</h2>
    <table width="100%">
        <tr>
            <th>
            </th>
            <th>
                Name
            </th>
            <th width="100%">
                Description
            </th>
        </tr>
        <% foreach (var item in Model) { %>
        <tr>
            <td nowrap>
                <%= Html.ActionLink("Edit", "Edit", new { id = item.Id }) %>
                |
                <%= Html.ActionLink("Details", "Details", new { id = item.Id }) %>
                |
                <%= Html.ActionLink("Delete", "Delete", new { id = item.Id }, new { @class = "delete" }) %>
            </td>
            <td nowrap>
                <%= Html.Encode(item.Name) %>
            </td>
            <td>
                <%= Html.Encode(item.Description) %>
            </td>
        </tr>
        <% } %>
    </table>
    <p>
        [<%= Html.ActionLink("Create New", "Create") %>] | [<%=Html.ActionLink("Back to Administration", "Index", "Admin") %>]
    </p>
    <div id="dialog" title="Delete Quality Checker?">
        <p>
            <span class="ui-icon ui-icon-alert" style="float: left; margin: 0 7px 20px 0;"></span>
            The Quality Checker will be deleted. Are you sure?</p>
    </div>
</asp:Content>
