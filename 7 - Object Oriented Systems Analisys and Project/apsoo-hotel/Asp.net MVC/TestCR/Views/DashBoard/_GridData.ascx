<%@ Control Language="C#" Inherits="System.Web.Mvc.ViewUserControl<DashBoardGrid>" %>
<%@ Import Namespace="CodeReview.Web.Services" %>
<%@ Import Namespace="CodeReview.Web" %>
<%@ Import Namespace="CodeReview.Web.Controllers" %>
<%@ Import Namespace="CodeReview.Web.ViewModels.Shared" %>
<%@ Import Namespace="CodeReview.Model.Entities" %>
<%@ Import Namespace="CodeReview.Web.Helpers" %>

<script>
    function rowClick(id, event) {
        if (event.ctrlKey) {
            window.open(resolveUrl('~/Review/' + id));
        } else {
            document.location = resolveUrl('~/Review/' + id);
        }
    }
</script>

<table>
    <tr>
        <% if ((string)ViewData["viewType"] == "MyReviews") 
           { %>
            <th title="Sort by Developer">
               <%= Model.SortActionLink("Developer", "Developer") %>
            </th>
        <% } else { %>
            <th title="Sort by Reviewer">
               <%= Model.SortActionLink("Reviewer", "Reviewer")%>
            </th>
        <% } %>
    
        <th title="Sort by Server">
            <%= Model.SortActionLink("Server", "PVobServer")%>
        </th>
        <th title="Sort by PVOB">
            <%= Model.SortActionLink("PVOB", "PVobName")%>
        </th>
        <th title="Sort by Activity">
            <%= Model.SortActionLink("Activity", "Activity")%>
        </th>
        <th title="Sort by Last change">
            <%= Model.SortActionLink("Last change", "LastChangeDate")%>
        </th>
        <th title="Sort by Status">
            <%= Model.SortActionLink("Status", "Status")%>
        </th>
    </tr>
    
    <% 
	//Can't use Model.Data directly.  Doesn't pick up generic type.								 				
    foreach (ReviewData review in Model.Data) 
    { 
        string css = "pending";
        
        if (review.Status == ReviewStatus.IN_REVIEW)
            css = "inReview";
        else if (review.Status == ReviewStatus.APPROVED)
            css = "approved";
        else if (review.Status == ReviewStatus.REJECTED)
            css = "rejected";
        else if (review.Status == ReviewStatus.DELIVERED)
            css = "delivered";
    %>
        <tr title="View Review" class="<%=css%>" onclick="rowClick(<%= review.Id %>, event)" style="cursor: pointer">
            <% if ((string)ViewData["viewType"] == "MyReviews") { %>
                <td>
                    <%= Html.Encode(review.Developer) %>
                </td>
            <% } else { %>
                <td>
                    <%= Html.Encode(review.Reviewer) %>
                </td>
            <% } %>
            
            <td>
                <%= Html.Encode(review.Project.PVobServer) %>
            </td>
            <td>
                <%= Html.Encode(review.Project.PVobName) %>
            </td>
            <td>
                 <%= Html.Encode(StringHelper.Resume(review.Activity, 40)) %>
            </td>
            <td style="width: 120px">
                <%= Html.Encode(StringFormatter.FormatDateTime(review.LastChangeDate)) %>
            </td>
            <td style="width: 80px">
                <%= Html.Encode(review.StatusName) %>
            </td>
        </tr>
    <% } %>
</table>