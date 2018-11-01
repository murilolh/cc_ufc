<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<FileGrid>" %>

<%@ Import Namespace="CodeReview.Model.Entities" %>
<%@ Import Namespace="CodeReview.Model.Repositories" %>
<%@ Import Namespace="CodeReview.Web.Services" %>
<%@ Import Namespace="CodeReview.Web.Controllers" %>
<%@ Import Namespace="CodeReview.Web.ViewModels.Shared" %>
<%@ Import Namespace="CodeReview" %>
<%@ Import Namespace="CodeReview.Web" %>
<asp:Content ID="Content2" ContentPlaceHolderID="JavascriptContent" runat="server">
<style type="text/css">
.wordwrap
{
   -moz-binding: url('~/Scripts/wordwrap.xml#wordwrap');
}
  p
        {
            margin-bottom: 100px;
            line-height: 1.1em;
        }
    
</style>


    <script type="text/javascript" src="<%=ResolveUrl("~/Scripts/jquery-autocomplete/jquery.autocomplete.js")%>"></script>

    <script type="text/javascript" src="<%=ResolveUrl("~/Scripts/jquery.blockUI.js")%>"></script>

    <script type="text/javascript" src="<%=ResolveUrl("~/Scripts/grid.js")%>"></script>

    <script src="<%=ResolveUrl("~/Scripts/jquery-ui-1.7.2/ui/ui.datepicker.js")%>" type="text/javascript"></script>

    <link href="<%=ResolveUrl("~/Scripts/jquery-ui-1.7.2/themes/redmond/jquery-ui-1.7.2.custom.css")%>"
        rel="stylesheet" type="text/css" />
    <link rel="stylesheet" type="text/css" href="<%=ResolveUrl("~/Scripts/jquery-autocomplete/jquery.autocomplete.css")%>" />
    <link rel="stylesheet" type="text/css" href="<%=ResolveUrl("~/Content/grid.css")%>" />

    <script type="text/javascript">
        jQuery(document).ready(function() {
            $(".with-date-picker").datepicker({ changeMonth: false, changeYear: false, dateFormat: 'dd/mm/yy' });

            if ($('#status-line').is(':visible')) {
                setTimeout(function() {
                    $('#status-line').fadeOut('slow');
                }, 3000);
            }
        });
    </script>
</asp:Content>
<asp:Content ID="Content3" ContentPlaceHolderID="TitleContent" runat="server">
    Review
    <%= (ViewData["ReviewData"] as Review).Id %>
</asp:Content>
<asp:Content ID="Content4" ContentPlaceHolderID="MainContent" runat="server" >
    <script type="text/javascript" src="<%=ResolveUrl("~/Scripts/wordWrap.js")%>"></script>
   <script type="text/javascript">
       window.onload = wordWrap;
    
</script>
   
   
    <% Review review = ViewData["ReviewData"] as Review; %>
    <h2>
        Review
        <%=review.Id %></h2>
    <fieldset >
        <legend>Summary</legend>
      
                     <p style="margin-bottom: 5px;" class="word-wrap">
                         <b>Project:</b>
                         <%= Html.Encode(review.Project.PVobServer) %>/<%= Html.Encode(review.Project.PVobName) %>/<%= Html.Encode(review.Project.Name) %>
                    </p>  
                    <p style="margin-bottom: 5px;" class="word-wrap">
                        <b>Activity:</b>
                        <%= Html.Encode(review.Activity) %>
                    </p>            
             
                    <p style="margin-bottom: 5px;">
                        <b>Developer:</b>
                        <%= Html.Encode(review.Developer) %>
                    </p>            
              
                     <p style="margin-bottom: 5px;">
                        <b>Reviewer:</b>
                        <%= Html.Encode(review.Reviewer) %>
                    </p>           
             
                    <p style="margin-bottom: 5px;">
                        <b>Creation date:</b>
                        <%= Html.Encode(StringFormatter.FormatDateTime(review.CreationDate)) %>
                    </p>            
             
                     <p style="margin-bottom: 5px;">
                        <b>Last change date:</b>
                        <%= Html.Encode(StringFormatter.FormatDateTime(review.LastChangeDate)) %>
                    </p>           
               
                     <p style="margin-bottom: 5px;">
                        <b>Status:</b>
                        <%= Html.Encode(review.Status.GetStringValue()) %>
                    </p>           
               
                   <p   style="margin-bottom: 5px;" class="word-wrap"> 
                           <b>Message:</b>
                      
                       <%= Html.Encode(review.Message) %>
                        </p> 
                               
    </fieldset>
    <fieldset>
        <legend>Files</legend>
        <table width="100%">
            <tr>
                <td>
                    <%Html.BeginForm("Index", "Review", FormMethod.Post);%>
                    <div id="search-form" style="width:100%">
                        <% Html.RenderPartial("_SearchForm", Model.SearchForm); %>
                    </div>
                    <div style="clear: both">
                    </div>
                    <div id="grid" style="width:100%">
                        <% Html.RenderPartial("_Grid", Model); %>
                    </div>
                    <%Html.EndForm();%>
                </td>
            </tr>
        </table>
    </fieldset>
    <%
    FileRepository fileRep = new FileRepository();
    IList<File> files = fileRep.GetAllFiles(review.Id);
    bool showButton = true;
    bool existsRejected = false;
    foreach (File filesAux in files) {
        if (filesAux.Status == FileStatus.PENDING) {
            showButton = false;
        } else if (filesAux.Status == FileStatus.REJECTED) {
            existsRejected = true;
        }
    }        
      
    if (showButton)
    { 
        if (review.Status != ReviewStatus.DELIVERED && User.Identity.Name == review.Reviewer)
        {
    %>
    <fieldset>
        <legend>Finish review</legend>Comment:<br />
        <%Html.BeginForm("SaveReview", "Review", FormMethod.Post);%>
        <textarea name="reviewComments" rows="4" style="width: 100%; font-size: small; font-family: Verdana;"><%= Html.Encode(review.Comment)%></textarea>
        <div style="text-align: right">
            <input name="reviewId" type="hidden" value="<%=review.Id %>" />
            <%if (existsRejected) {%>
                <b>The review will be rejected</b>&nbsp;&nbsp;
            <%} else {%>
                <b>The review will be approved</b>&nbsp;&nbsp;
            <%}%>
            
            <button type="submit" value="UpdateReview" style="height: 30px;">
                <img src="<%=ResolveUrl("~/Content/images/flag-finish.png")%>" alt="" align="top"/>
                Finish
            </button>
        </div>
        <%Html.EndForm(); %>
    </fieldset>
    <%
        }
        else if (!string.IsNullOrEmpty(review.Comment))
        {
    %>
    <fieldset>
        <legend>Comment</legend>
        <p>
            <%= Html.Encode(review.Comment)%>
        </p>
    </fieldset>
    <%
        }
    } 
    %>    
        <div>
            <a href="<%=ResolveUrl("~/DashBoard?viewType=MyReviews") %>">[Back to DashBoard]</a>
        </div>            

</asp:Content>
