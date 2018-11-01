<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<CodeReview.Web.Controllers.ReviewManagerViewModel>" %>

<%@ Import Namespace="CodeReview.Model.Entities" %>
<%@ Import Namespace="CodeReview.Model.Repositories" %>
<%@ Import Namespace="CodeReview.UsersFacade" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
    Edit Review <%=Model.Review.Id %>
</asp:Content>

<asp:Content ID="Content4" ContentPlaceHolderID="CSSContent" runat="server">
    <link href="<%=ResolveUrl("~/Scripts/jquery-ui-1.7.2/themes/redmond/jquery-ui-1.7.2.custom.css")%>"
        rel="stylesheet" type="text/css" />
    <style type="text/css">
        fieldset label
        {
            display: block;
        }
        p
        {
            margin-bottom: 100px;
            line-height: 1.1em;
        }
    </style>
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
                        'Change': function() {
                            document.submitForm.submit();
                        },
                        Cancel: function() {
                            jQuery(this).dialog('close');
                        }
                    }
                });
                jQuery("form#submitForm").submit(function() {
                    jQuery("#dialog").dialog('open');
                    return false;
                });
            }
        );
        
    </script>

</asp:Content>
    
<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
    <h2>Edit Review <%=Model.Review.Id %></h2>
        <script type="text/javascript" src="<%=ResolveUrl("~/Scripts/wordWrap.js")%>"></script>
   <script type="text/javascript">
       window.onload = wordWrap;
    
</script>
   
    
    <%= Html.ValidationSummary("Edit was unsuccessful. Please correct the errors and try again.") %>
    
   
        <fieldset >
            <legend>Summary</legend>
                     <p style="margin-bottom: 5px;" class="word-wrap">
                        <b>Project:</b>
                         <%= Html.Encode(Model.Review.Project.PVobServer) %>/<%= Html.Encode(Model.Review.Project.PVobName) %>/<%= Html.Encode(Model.Review.Project.Name) %>
                     </p>
                     <p style="margin-bottom: 5px;" class="word-wrap">
                        <b>Activity:</b>
                       <%= Html.Encode(Model.Review.Activity) %>
                    </p>            
                    <p style="margin-bottom: 5px;">
                        <b>Developer:</b>
                      <%= Html.Encode(Model.Review.Developer) %>
                    </p>            
                    <p style="margin-bottom: 5px;">
                        <b>Reviewer:</b>
                              <%= Html.Encode(Model.Review.Reviewer) %>
                    </p>           
                    <p style="margin-bottom: 5px;">
                        <b>Creation date:</b>
                       <%= Html.Encode(Model.Review.CreationDate) %>
                    </p>            
                    <p style="margin-bottom: 5px;">
                       <b>Status:</b>
                         <%= Html.Encode(Model.Review.Status.GetStringValue()) %>
                    </p>           
                    <p style="margin-bottom: 5px;">
                        <b>Last change date:</b>
                        <%= Html.Encode(Model.Review.LastChangeDate) %>
                    </p>           
                    <p style="margin-bottom: 5px;" class="word-wrap"> 
                        <b>Message:</b>
                    
                       <%= Html.Encode(Model.Review.Message) %>
                       </p>
                               
        </fieldset>
         <% using (Html.BeginForm("Edit", "ReviewManager", FormMethod.Post, new {id = "submitForm", name = "submitForm"})) {%>    
        <fieldset>
            <legend>Change</legend>
                <% if (Model.Review.Status == ReviewStatus.DELIVERED) { %>
                    <strong style="color: Red">This review has already been delivered. It can not be edited.</strong>
                <% } else { %>
                    
                        <%
                        if (Model.Review.Status != ReviewStatus.APPROVED && Model.Review.Status != ReviewStatus.REJECTED)
                        {
                        %>
                            <p>
                                <label for="Reviewer">Reviewer:</label>
                                <%= Html.DropDownList("Reviewer", ViewData["reviewers"] as SelectList, new { style="width:200px"})%>
                                <%= Html.ValidationMessage("Reviewer", "*") %>
                            </p>
                        <%
                        }
                        else
                        {
                        %>
                            <input type="hidden" name="Reviewer" value="<%=Model.Review.Reviewer %>" />
                        <%
                        }
                        %>
                        
                    <p>
                        <label>Status:</label>
                        <%foreach (var radioButton in ViewData["status"] as SelectList) { %>
                            <%= Html.RadioButton("Status", radioButton.Value, radioButton.Selected, new {id = radioButton.Value}) %>
                            <label for="<%= radioButton.Value%>" style="display:inline"><%= radioButton.Text %></label>
                        <%} %>
                        <%= Html.ValidationMessage("Status", "*") %>   
                    </p>     
                    <p>    
                        <label for="Comment">Comment:</label>
                        <%= Html.TextArea("Comment", "", new { style="width:400px", rows="8"})%>
                        <%= Html.ValidationMessage("Comment", "*") %>
                    </p>
                    <input type="submit" value="Save Changes"/>
                <% } %>
        </fieldset>
    <% } %>
    <p> 
        [<%= Html.ActionLink("Log", "Log", new { id=Model.Review.Id }) %>] |         
        [<%=Html.ActionLink("Back to Review Manager", "Index") %>] 
    </p>
     <div id="dialog" title="Make changes?">
        <p>
            <span class="ui-icon ui-icon-alert" style="float: left; margin: 0 7px 20px 0;"></span>
            The Review will be changed. Are you sure?</p>
    </div>
</asp:Content>
