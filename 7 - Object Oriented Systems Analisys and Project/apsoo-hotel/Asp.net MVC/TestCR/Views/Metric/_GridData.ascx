<%@  Control Language="C#" Inherits="System.Web.Mvc.ViewUserControl<MetricGrid>" %>
<%@ Import Namespace="CodeReview.Web.Services" %>
<%@ Import Namespace="CodeReview.Web" %>
<%@ Import Namespace="CodeReview.Web.Controllers" %>
<%@ Import Namespace="CodeReview.Web.Helpers" %>
<%@ Import Namespace="CodeReview.Web.ViewModels.Shared" %>
<%@ Import Namespace="CodeReview.Model.Entities" %>
<table>
    <tr>
        <th>
            <%= Model.SortActionLink("Developer", "Developer") %>
        </th>
        <th>
            <%= Model.SortActionLink("Reviewer", "Reviewer")%>
        </th>        
        <th>
            <%= Model.SortActionLink("Server", "PVobServer")%>
        </th>
        <th>
            <%= Model.SortActionLink("PVOB", "PVobName")%>
        </th>
        <th>
            <%= Model.SortActionLink("Project", "ProjectName")%>
        </th>
        <th>
            <%= Model.SortActionLink("Activity", "Activity")%>
        </th>
        <th>
            <%= Model.SortActionLink("Creation date", "CreationDate")%>
        </th>
        <th>
            <%= Model.SortActionLink("Last change", "LastChangeDate")%>
        </th>
        <th>
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
    <tr class="<%=css%>">
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
            <%= Html.Encode(item.Project.Name) %>
        </td>
        <td>
            <%= Html.Encode(StringHelper.Resume(item.Activity, 40)) %>
        </td>
        <td style="width: 120px">
            <%= Html.Encode(String.Format("{0:g}", item.CreationDate)) %>
        </td>
        <td style="width: 120px">
            <%= Html.Encode(String.Format("{0:g}", item.LastChangeDate)) %>
        </td>
        <td style="width: 60px">
            <%= Html.Encode(item.Status.GetStringValue()) %>
        </td>
    </tr>
    <% } %>
</table>


