<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<DashBoardGrid>" %>

<%@ Import Namespace="CodeReview.Model.Entities" %>
<%@ Import Namespace="CodeReview.Web.Services" %>
<%@ Import Namespace="CodeReview.Web.Controllers" %>
<%@ Import Namespace="CodeReview.Web.ViewModels.Shared" %>
<%@ Import Namespace="CodeReview" %>
<%@ Import Namespace="CodeReview.Web" %>
<asp:Content ID="JavaScript" ContentPlaceHolderID="JavascriptContent" runat="server">

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
            $(".with-date-picker").datepicker({changeMonth: false, changeYear: false, dateFormat: 'dd/mm/yy'});

			if ($('#status-line').is(':visible')) {
				setTimeout(function() {
					$('#status-line').fadeOut('slow');
				}, 3000);
			}
		}); 
		
      	function onTabClick(view) {       	    
      	    document.location = "<%= ResolveUrl("~/DashBoard")%>" + "/" + view;
		}
    </script>

</asp:Content>
<asp:Content ID="CSS" ContentPlaceHolderID="CSSContent" runat="server">
</asp:Content>
<asp:Content ID="Title" ContentPlaceHolderID="TitleContent" runat="server">
    DashBoard
</asp:Content>
<asp:Content ID="Main" ContentPlaceHolderID="MainContent" runat="server">
    <h2>
        Dashboard
    </h2>      
    <%= Html.ValidationSummary("Operation was unsuccessful. Please correct the errors and try again.") %> 
    <% using (Html.BeginForm("Index", "DashBoard", FormMethod.Post)) { %>            
    <table id="dashboard">
        <tr>
            <td rowspan="1" nowrap>
                <fieldset style="cursor: default;">
                    <legend>My Status </legend>
                    <% 
                       List<int> myReviewsData = ViewData["MyReviewsData"] as List<int>; 
                       List<int> myRequestsData = ViewData["MyRequestsData"] as List<int>;                    
                    %>
                    <dl id="MyStatusList">
                        <dt>
                            <h4>
                                Last update:
                                <%=Html.Encode(ViewData["DateOfLastUpdate"])%></h4>
                        </dt>
                        <dt>
                            <h4>
                                My Reviews</h4>
                        </dt>
                        <ul>
                            <li>Pending:
                                <%=Html.Encode(myReviewsData.ElementAt(0))%>
                            </li>
                            <li>In Review:
                                <%=Html.Encode(myReviewsData.ElementAt(1))%>
                            </li>
                            <li>Approved:
                                <%=Html.Encode(myReviewsData.ElementAt(2))%>
                            </li>
                            <li>Rejected:
                                <%=Html.Encode(myReviewsData.ElementAt(3))%>
                            </li>
                            <li>Delivered:
                                <%=Html.Encode(myReviewsData.ElementAt(4))%>
                            </li>
                        </ul>
                        <dt>
                            <h4>
                                My Requests</h4>
                        </dt>
                        <ul>
                            <li>Pending:
                                <%=Html.Encode(myRequestsData.ElementAt(0))%>
                            </li>
                            <li>In Review:
                                <%=Html.Encode(myRequestsData.ElementAt(1))%>
                            </li>
                            <li>Approved:
                                <%=Html.Encode(myRequestsData.ElementAt(2))%>
                            </li>
                            <li>Rejected:
                                <%=Html.Encode(myRequestsData.ElementAt(3))%>
                            </li>
                            <li>Delivered:
                                <%=Html.Encode(myRequestsData.ElementAt(4))%>
                            </li>
                        </ul>
                    </dl>
                </fieldset>
            </td>            
            <td rowspan="1">
                <fieldset>
                    <legend>Requests and Reviews </legend>
                    <div id="menubuttons">
                        <ul id="buttons">
                            <li><a style="cursor: pointer; <%= !"MyRequests".Equals((string)ViewData["viewType"]) ? 
                                    "background-color: #a6e2a6;": "" %>" onclick="onTabClick('MyReviews')">My Reviews</a> </li>
                            <li><a style="cursor: pointer; <%= "MyRequests".Equals((string)ViewData["viewType"]) ? 
                                    "background-color: #a6e2a6;": "" %>" onclick="onTabClick('MyRequests')">My Requests</a> </li>
                        </ul>
                    </div>
                    <br />
                    <div id="search-form">
                        <% Html.RenderPartial("_SearchForm", Model.SearchForm); %>
                    </div>
                    <!-- search-form -->
                    <div style="clear: both">
                    </div>
                    <div id="grid">
                        <% Html.RenderPartial("_Grid", Model); %>
                    </div>
                    <!-- grid -->
                </fieldset>
            </td>
        </tr>
    </table>
    <% } %>
</asp:Content>

