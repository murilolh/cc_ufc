<%@  Control Language="C#" Inherits="System.Web.Mvc.ViewUserControl<ReviewManagerGrid>" %>
<%@ Import Namespace="CodeReview.Web.Services" %>
<%@ Import Namespace="CodeReview.Web" %>
<%@ Import Namespace="CodeReview.Web.Controllers" %>
<%@ Import Namespace="CodeReview.Web.ViewModels.Shared" %>
<%@ Import Namespace="CodeReview.Model.Entities" %>
<%@ Import Namespace="CodeReview.Web.Helpers" %>

<script>
    function rowClick(id, event) {
        if (event.ctrlKey) {
             window.open(resolveUrl('~/ReviewManager/Edit/' + id));            
         } else {
             document.location = resolveUrl('~/ReviewManager/Edit/' + id);            
        }
    }
</script>

<table>
    <tr>               
        <th title="Sort by Developer">
            <%= Model.SortActionLink("Developer", "Developer") %>
        </th>
        <th title="Sort by Reviewer">
            <%= Model.SortActionLink("Reviewer", "Reviewer")%>
        </th>        
        <th title="Sort by Server">
            <%= Model.SortActionLink("Server", "PVobServer")%>
        </th>
        <th title="Sort by PVOB">
            <%= Model.SortActionLink("PVOB", "PVobName")%>
        </th>
        <th title="Sort by Activity">
            <%= Model.SortActionLink("Activity", "Activity")%>
        </th>
        <th title="Sort by Creation date">
            <%= Model.SortActionLink("Creation date", "CreationDate") %>
        </th>
        <th title="Sort by Status">
            <%= Model.SortActionLink("Status", "Status")%>
        </th>
    </tr>
    <% 
	//Can't use Model.Data directly.  Doesn't pick up generic type.								 				
    foreach (ReviewData item in Model.Data) 
    { 
        string css = "pending";
        
        if (item.Status == ReviewStatus.IN_REVIEW)
            css = "inReview";
        else if (item.Status == ReviewStatus.APPROVED)
            css = "approved";
        else if (item.Status == ReviewStatus.REJECTED)
            css = "rejected";
        else if (item.Status == ReviewStatus.DELIVERED)
            css = "delivered";
    %>
    <tr title="Edit Review" class="<%=css%>" onclick="rowClick(<%= item.Id %>, event)" style="cursor: pointer">                  
        <td>
            <%= Html.Encode(item.Developer) %>
        </td>
        <td>
            <%= Html.Encode(item.Reviewer) %>
        </td>
        <td>
            <%= Html.Encode(item.Project.PVobServer) %>
        </td>
        <td>
            <%= Html.Encode(item.Project.PVobName) %>
        </td>
        <td>
            <%= Html.Encode(StringHelper.Resume(item.Activity, 40)) %>
        </td>
        <td style="width: 120px">
            <%= Html.Encode(String.Format("{0:g}", item.CreationDate)) %>
        </td>
        <td style="width: 60px">
            <%= Html.Encode(item.Status.GetStringValue()) %>
        </td>
    </tr>
    <% } %>
</table>


