<%@ Control Language="C#" Inherits="System.Web.Mvc.ViewUserControl<FileGrid>" %>
<%@ Import Namespace="CodeReview.Web.Services" %>
<%@ Import Namespace="CodeReview.Web" %>
<%@ Import Namespace="CodeReview.Web.Controllers" %>
<%@ Import Namespace="CodeReview.Web.ViewModels.Shared" %>
<%@ Import Namespace="CodeReview.Model.Entities" %>
<%@ Import Namespace="CodeReview.Web.Helpers" %>

<script src="<%=ResolveUrl("~/Scripts/jquery-ui-1.7.2.custom.min.js")%>" type="text/javascript"></script>

<script>
    function rowClick(id, event) {
        if (event.ctrlKey) {
            window.open(resolveUrl('~/File/Index/' + id));
        } else {
            document.location = resolveUrl('~/File/Index/' + id);
        }
    }

    var fileId;
    var countApproved = 0;
    jQuery(document).ready(
        function() {
            jQuery("#dialog").dialog({
                autoOpen: false,
                resizable: false,
                height: 180,
                modal: true,
                buttons: {
                    'Approve': function() {
                        jQuery(this).dialog('close');
                        jQuery.post('<%= ResolveUrl("~/File/QuickApprove") %>',
                        {
                            fileId: fileId
                        },
                        function(data) {
                            if (eval(data) == "success") {
                                $('#row_file_' + fileId)[0].className = "approved";
                                $('#status_file_' + fileId)[0].textContent = "Approved";
                                $('#quickApprove_' + fileId)[0].innerHTML = "";
                                countApproved++;

                                if ($('.quickApprove').length == countApproved)
                                    window.location.reload();
                            }
                        }, "Json");
                    },
                    Cancel: function() {
                        jQuery(this).dialog('close');
                    }
                }
            });
            jQuery(".quickApprove").click(function() {
                jQuery("#dialog").dialog('open');
                fileId = jQuery(this).attr('fileId');
                return false;
            });
        }
    );
</script>

<table>
    <tr>
        <th title="Sort by Name">
            <%= Model.SortActionLink("Name", "Name")%>
        </th>
         <th title="Sort by Last change">
            <%= Model.SortActionLink("Last change", "LastChangeDate")%>
        </th>
        <th title="Sort by Status">
            <%= Model.SortActionLink("Status", "Status")%>
        </th>
        <th title=""></th>
    </tr>
    <% 
    foreach (FileData file in Model.Data)  
    {
        string css = "pending";
        
        if (file.Status == FileStatus.APPROVED)
            css = "approved";
        else if (file.Status == FileStatus.REJECTED)
            css = "rejected";
        else if (file.Status == FileStatus.OLD_VERSION)
            css = "oldVersion";
    %>
        <tr class="<%=css%>" style="cursor: pointer;" id="row_file_<%= file.Id %>">
            <td title="View File" onclick="rowClick(<%= file.Id %>, event)">
                <%= Html.Encode(StringHelper.Resume(file.Name, 100, '\\')) %>
                
            </td>
            <td title="View File" onclick="rowClick(<%= file.Id %>, event)" style="width: 120px">
                <%= Html.Encode(StringFormatter.FormatDateTime(file.LastChangeDate)) %>
            </td>
            <td title="View File" onclick="rowClick(<%= file.Id %>, event)" style="width: 80px">
                <span id="status_file_<%= file.Id %>">
                    <%= Html.Encode(file.Status.GetStringValue()) %>
                </span>
            </td>
            <td align="center" style="width: 20px">
                <%if (file.Status == FileStatus.PENDING && Page.User.Identity.Name == file.Review.Reviewer) {%>
                    <div title="Quick Approve" id="quickApprove_<%= file.Id %>" class="quickApprove" fileId="<%= file.Id %>">
                        <img src="<%=ResolveUrl("~/Content/images/tick-circle-frame.png")%>" />
                    </div>
                <%}%>
            </td>
        </tr>
    <%
    }
    %>
</table>

<div id="dialog" title="Quick Approve?">
    <p>
        <span class="ui-icon ui-icon-alert" style="float: left; margin: 0 7px 20px 0;"></span>
        The file will be approved. Are you sure?</p>
</div>