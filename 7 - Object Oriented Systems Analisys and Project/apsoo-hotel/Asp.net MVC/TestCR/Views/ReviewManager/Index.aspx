<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<ReviewManagerGrid>" %>

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
		
      	function onTabClick(id) {	
      		document.location = "<%= ResolveUrl("~/Edit")%>" + id;
      		      					
			submitForm();			
		}
    </script>

</asp:Content>
<asp:Content ID="CSS" ContentPlaceHolderID="CSSContent" runat="server">
</asp:Content>
<asp:Content ID="Title" ContentPlaceHolderID="TitleContent" runat="server">
    Review Manager
</asp:Content>
<asp:Content ID="Main" ContentPlaceHolderID="MainContent" runat="server">
    <h2>
        Review Manager
    </h2>
    <% using (Html.BeginForm("Index", "ReviewManager", FormMethod.Post)) { %>
    <table style="width: 100%; border: solid 0px;">
        <tr>
            <td style="border: solid 0px; vertical-align: top;">
                <fieldset>
                    <legend>Reviews</legend>
                    <div id="search-form" style="width:100%">
                        <% Html.RenderPartial("_SearchForm", Model.SearchForm); %>
                    </div>
                    <!-- search-form -->
                    <div style="clear: both">
                    </div>
                    <div id="grid" style="width:100%">
                        <% Html.RenderPartial("_Grid", Model); %>
                    </div>
                    <!-- grid -->
                </fieldset>
                <div>
                    [<%= Html.ActionLink("Back to Administration", "Index", "Admin") %>]
                </div>
            </td>
        </tr>
    </table>
    <% } %>
</asp:Content>
