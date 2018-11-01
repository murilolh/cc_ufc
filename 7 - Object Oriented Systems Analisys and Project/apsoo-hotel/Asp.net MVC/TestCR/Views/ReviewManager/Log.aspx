<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<CodeReview.Model.Entities.Review>" %>

<%@ Import Namespace="CodeReview.Model.Entities" %>
<%@ Import Namespace="CodeReview.Model.Repositories" %>
<%@ Import Namespace="CodeReview.Web" %>
<%@ Import Namespace="CodeReview.Web.Helpers" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
	Review <%= Model.Id %> Log
	
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">

    <h2>Review <%= Model.Id %> Log</h2>
  <script type="text/javascript" src="<%=ResolveUrl("~/Scripts/wordWrap.js")%>"></script>
   <script type="text/javascript">
       window.onload = wordWrap;
    
</script>
    <fieldset>
        <legend>Summary</legend>
        <p style="margin-bottom:5px;">
            <b>Review:</b>
            <%= Html.Encode(Model.Id) %>            
        </p>
        <p style="margin-bottom:5px;">
            <b>Project:</b>
            <%= Html.Encode(Model.Project.PVobServer) %>/<%= Html.Encode(Model.Project.PVobName) %>/<%= Html.Encode(Model.Project.Name) %>            
        </p>
        
        <p style="margin-bottom:5px;">
            <b>Activity:</b>
            <%= Html.Encode(Model.Activity) %>
        </p>

        <p style="margin-bottom:5px;">
            <b>Developer:</b>
            <%= Html.Encode(Model.Developer) %>
        </p>
        
        <p style="margin-bottom:5px;">
            <b>Reviewer:</b>
            <%= Html.Encode(Model.Reviewer) %>
        </p>
        
        <p style="margin-bottom:5px;">
            <b>Creation date:</b>
            <%= Html.Encode(Model.CreationDate) %>
        </p>
        
        <p style="margin-bottom:5px;">
            <b>Status:</b>
            <%= Html.Encode(Model.Status.GetStringValue()) %>
        </p>
        
        <p style="margin-bottom:5px;">
            <b>Last change date:</b>
            <%= Html.Encode(Model.LastChangeDate) %>
        </p>

        <p style="margin-bottom:5px;" class="word-wrap">
            <b>Message:</b>
            <%= Html.Encode(Model.Message) %>
        </p>
        
        <p style="margin-bottom:5px;" >
            <b>Comment:</b>
            <%= Html.Encode(Model.Comment) %>
        </p>
        
        
    </fieldset>
    
    <fieldset>
        <legend>Review History</legend>
        <table style="width:100%;">
            <tr>
                <th width="15%">Date</th>
                <th width="15%">User</th>
                <th width="15%">Reviewer</th>
                <th width="15%">Status</th>
                <th width="40%">Comment</th>
            </tr>
            <%
            IList<ReviewHistory> reviewHistories = new ReviewRepository().GetReviewHistory(Model.Id);
            foreach (ReviewHistory rh in reviewHistories)
            {
            %>
                <tr class="historyItem">
                    <td><%= Html.Encode(StringFormatter.FormatDateTime(rh.Date)) %></td>
                    <td><%= Html.Encode(rh.ChangeUser) %></td>
                    <td><%= Html.Encode(rh.Reviewer) %></td>
                    <td><%= Html.Encode(rh.Status.GetStringValue()) %></td>
                    <td>
                        <%
                        if (rh.AdminComment != null)
                        {
                        %>
                            <b>Admin:</b> <%= Html.Encode(rh.AdminComment) %>
                        <%
                        }
                        else
                        {
                        %>
                            <%= Html.Encode(rh.Comment) %>
                        <%
                        }
                        %>
                    </td>
                </tr>
            <%
            }
            %>
        </table>
    </fieldset>
    
    <fieldset>
        <legend>Files histories</legend>
        <%
        IList<File> reviewFiles = new FileRepository().GetAllFiles(Model.Id);
        foreach (File file in reviewFiles)
        {
        %>
            <p class="trigger"><a href="#" title="<%=Html.Encode(file.Name)%>"><%= Html.Encode(StringHelper.Resume(file.Name, 100, '\\')) %></a></p>
            <div class="toggle_container_<%=file.Id %>">
	            <div class="block">
		            <%
                IList<FileHistory> fileHistories = new FileRepository().GetFileHistory(file.Id);
                if (fileHistories.Count > 0)
                {
                %>
                    <table style="width:100%;">
                        <tr>
                            <th style="width:15%">Date</th>
                            <th style="width:15%">User</th>
                            <th style="width:15%">Status</th>
                            <th style="width:55%">Comment</th>
                        </tr>
                        <%
                        foreach (FileHistory fh in fileHistories)
                        {
                        %>
                            <tr class="historyItem">
                                <td><%= Html.Encode(StringFormatter.FormatDateTime(fh.Date)) %></td>
                                <td><%= Html.Encode(fh.ChangeUser) %></td>
                                <td><%= Html.Encode(fh.Status.GetStringValue()) %></td>
                                <td><%= Html.Encode(fh.Comment) %></td>
                            </tr>
                        <%
                        }
                        %>
                    </table>
                <%
                }
                else
                {
                %>
                    There is no activity for this file.
                <%
                }
                %>
                
                <fieldset>
                    <legend>Quality checkers history</legend>
                    <%
                    IList<FileQualityCheckerHistory> fileQualityCheckerHistories = new FileQualityCheckerRepository().GetFileQualityCheckerHistory(file.Id);
                    if (fileQualityCheckerHistories.Count > 0)
                    {
                    %>
                        <table style="width:100%;">
                            <tr>
                                <th style="width:15%">Date</th>
                                <th style="width:15%">User</th>
                                <th style="width:15%">Quality checker</th>
                                <th style="width:55%">Status</th>
                                </tr>
                            <%
                            foreach (FileQualityCheckerHistory qh in fileQualityCheckerHistories)
                            {
                            %>
                                <tr class="historyItem">
                                    <td><%= Html.Encode(StringFormatter.FormatDateTime(qh.Date)) %></td>
                                    <td><%= Html.Encode(qh.ChangeUser) %></td>
                                    <td><%= Html.Encode(qh.QualityChecker.Name) %></td>
                                    <td><%= Html.Encode(qh.Status.GetStringValue()) %></td>
                                </tr>
                            <%
                            }
                            %>
                        </table>
                    <%
                    }
                    else 
                    {
                    %>
                        There is no quality checker activity for this file.
                    <%
                    }
                    %>
                </fieldset>
                
                
                <fieldset id="lastReview_<%=file.Id %>">
                    <legend>View File Diff</legend>
                    [<a href="<%=ResolveUrl("~/File/Index/" + file.Id + "?isAdmin=true") %>">Last Review</a>] 
                </fieldset>
                
                <fieldset>
                    <legend>Comments history</legend>
                    <%
                    IList<CommentHistory> commentHistories = new CommentRepository().GetCommentHistory(file.Id);
                    if (commentHistories.Count > 0)
                    {
                    %>
                        <table style="width:100%;">
                        <tr>
                            <th style="width:15%">Date</th>
                            <th style="width:15%">User</th>
                            <th style="width:15%">Action</th>
                            <th style="width:10%">Line</th>
                            <th style="width:15%">Severity</th>
                            <th style="width:30%">Comment</th>
                        </tr>
                        <%
                        foreach (CommentHistory ch in commentHistories)
                        {
                        %>
                            <tr class="historyItem">
                                <td><%= Html.Encode(StringFormatter.FormatDateTime(ch.Date)) %></td>
                                <td><%= Html.Encode(ch.ChangeUser) %></td>
                                <td><%= Html.Encode(ch.Action.GetStringValue()) %></td>
                                <td><%= Html.Encode(ch.Line) %></td>
                                <td><%= Html.Encode(ch.Severity) %></td>
                                <td><%= Html.Encode(ch.CommentText) %></td>
                            </tr>
                        <%
                        }
                        %>
                    </table>
                    <%
                    }
                    else 
                    {
                    %>
                        There is no comment activity for this file.
                    <%
                    }
                    %>
                </fieldset>
	            </div>
            </div>
        <%
        }
        %>
    </fieldset>
    
    <p>
        <%
        if (Model.Status != ReviewStatus.DELIVERED)
        {
        %>
            [<%=Html.ActionLink("Edit", "Edit", new { id=Model.Id }) %>] |
        <%
        }
        %>        
        [<%=Html.ActionLink("Back to Review Manager", "Index") %>]
    </p>
</asp:Content>

<asp:Content ID="Content3" ContentPlaceHolderID="JavascriptContent" runat="server">
    <script type="text/javascript">
        $(document).ready(function() {
            //http://www.sohtanaka.com/web-design/easy-toggle-jquery-tutorial/
            //Hide (Collapse) the toggle containers on load
            <%
            IList<File> reviewFiles = new FileRepository().GetAllFiles(Model.Id);
            foreach (File file in reviewFiles)
            {
            %>            
                $(".toggle_container_<%=file.Id %>").hide();
                
                 //Switch the "Open" and "Close" state per click
                $("p.trigger").toggle(function() {
                    $(this).addClass("active");
                }, function() {
                    $(this).removeClass("active");
                });

                //Slide up and down on click
                $("p.trigger").click(function() {
                    $(this).next(".toggle_container_<%=file.Id %>").slideToggle("slow");
                });
            <% 
            }                       
            String diffViewed = Request.Params["file"] as String;
            if(!String.IsNullOrEmpty(diffViewed)) 
            {             
            %>               
               $(".toggle_container_<%=diffViewed%>").show();              
               document.location = "/ReviewManager/Log/<%=Model.Id%>?file=<%=diffViewed%>#lastReview_<%=diffViewed%>";
            <% 
            } 
            %>
        });
    </script>
</asp:Content>

<asp:Content ID="Content4" ContentPlaceHolderID="CSSContent" runat="server">
<style type="text/css">
    table td {
		padding: 5px;   
		border: solid 1px #e8eef4;
	}
    table tr.historyItem {
		background: #FFFFFF none repeat scroll 0 0;
	}
	table tr.historyItem:hover {
		background: #D7DDE3 none repeat scroll 0 0;
	}
	
	p.trigger {
	    padding: 0 0 0 15px;
	    background: url("<%= ResolveUrl("~/Content/images/collapsed.png")%>") no-repeat;
    }
    
    p.trigger a 
    {
    	text-decoration:none;
    }
    
    p.active 
    {
    	background: url("<%= ResolveUrl("~/Content/images/expanded.png")%>") no-repeat;
    }
	 fieldset label
        {
            display: block;
        }
 p
        {
            margin-bottom: 100px;
            line-height: 1.1em;
        }
    .toggle_container {
	    margin: 0 0 5px;
	    padding: 0;
	    overflow: hidden;
	    clear: both;
    }
    
    .toggle_container .block {
	    padding: 20px;
    }
</style>
</asp:Content>

<asp:Content ID="Content5" ContentPlaceHolderID="HeadContent" runat="server">
</asp:Content>

