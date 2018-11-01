<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<MetricGrid>" %>

<%@ Import Namespace="CodeReview.Model.Entities" %>
<%@ Import Namespace="CodeReview.Web.Services" %>
<%@ Import Namespace="CodeReview.Web.Controllers" %>
<%@ Import Namespace="CodeReview.Web.ViewModels.Shared" %>
<%@ Import Namespace="CodeReview" %>
<%@ Import Namespace="CodeReview.Web" %>
<%@ Import Namespace="CodeReview.Metric" %>
<asp:Content ID="JavaScript" ContentPlaceHolderID="JavascriptContent" runat="server">

    <script type="text/javascript" src="<%=ResolveUrl("~/Scripts/jquery-autocomplete/jquery.autocomplete.js")%>"></script>

    <script type="text/javascript" src="<%=ResolveUrl("~/Scripts/jquery.blockUI.js")%>"></script>
    
    <script type="text/javascript" src="<%=ResolveUrl("~/Scripts/qTip/jquery.qtip-1.0.0-rc3.js")%>"></script>

    <script type="text/javascript" src="<%=ResolveUrl("~/Scripts/grid.js")%>"></script>

    <script src="<%=ResolveUrl("~/Scripts/jquery-ui-1.7.2/ui/ui.datepicker.js")%>" type="text/javascript"></script>
    
    <script src="<%=ResolveUrl("~/Scripts/jquery-ui-1.7.2.custom.min.js")%>" type="text/javascript"></script>

    <link href="<%=ResolveUrl("~/Scripts/jquery-ui-1.7.2/themes/redmond/jquery-ui-1.7.2.custom.css")%>"
        rel="stylesheet" type="text/css" />
    <link rel="stylesheet" type="text/css" href="<%=ResolveUrl("~/Scripts/jquery-autocomplete/jquery.autocomplete.css")%>" />
    <link rel="stylesheet" type="text/css" href="<%=ResolveUrl("~/Content/grid.css")%>" />

    <script type="text/javascript">         	
        $(document).ready(function() {
            $(".with-date-picker").datepicker({changeMonth: false, changeYear: false, dateFormat: 'dd/mm/yy'});

			if ($('#status-line').is(':visible')) {
				setTimeout(function() {
					$('#status-line').fadeOut('slow');
				}, 3000);
			}
		}); 
		
        $(document).ready(function() 
        {
            $('#metrics span[tooltip]').each(function()
            {
                $(this).qtip({
                    content: $(this).attr('tooltip'),
                    style: { 
                        name: 'light',
                        tip: {
                            corner: 'bottomLeft',
                            color: '#5c87b2'
                        },
                        border: {
                            width: 1,
                            radius: 4,
                            color: '#5c87b2'
                        },
                    },
                    position: {
                        corner: {
                            target: 'topLeft',
                            tooltip: 'bottomLeft'
                        }
                   }
                });
            });
        });
        
        // return 2- i.e, 1- other browsers
          function findBrowser(){
            var nVer = navigator.appVersion;
            var nAgt = navigator.userAgent;
            var browserName  = navigator.appName;
            var fullVersion  = ''+parseFloat(navigator.appVersion); 
            var majorVersion = parseInt(navigator.appVersion,10);
            var nameOffset,verOffset,ix;

            // In MSIE, the true version is after "MSIE" in userAgent
            if ((verOffset=nAgt.indexOf("MSIE"))!=-1) {
             browserName = "Microsoft Internet Explorer";
             fullVersion = nAgt.substring(verOffset+5);
            }
            // In Chrome, the true version is after "Chrome" 
            else if ((verOffset=nAgt.indexOf("Chrome"))!=-1) {
             browserName = "Chrome";
             fullVersion = nAgt.substring(verOffset+7);
            }
            // In Firefox, the true version is after "Firefox" 
            else if ((verOffset=nAgt.indexOf("Firefox"))!=-1) {
             browserName = "Firefox";
             fullVersion = nAgt.substring(verOffset+8);
            }
            // trim the fullVersion string at semicolon/space if present
            if ((ix=fullVersion.indexOf(";"))!=-1) fullVersion=fullVersion.substring(0,ix);
            if ((ix=fullVersion.indexOf(" "))!=-1) fullVersion=fullVersion.substring(0,ix);

            majorVersion = parseInt(''+fullVersion,10);
            if (isNaN(majorVersion)) {
             fullVersion  = ''+parseFloat(navigator.appVersion); 
             majorVersion = parseInt(navigator.appVersion,10);
            }
            
            if(browserName =="Chrome"){
                if(fullVersion == "4.0.249.78"){
                    return 1;
                    }else{
                        return 2;
                    }
            }else{
               return 1; 
            }
          }
        
          function openDialog(type) {                
            if( document.getElementById("metric").value ==""){
                alert("No metric selected. Please, choose one above.");
                return;
            }
            document.forms[1].target = "_self";  
            if(type == "Generate PDF"){
            document.getElementById("type").value="Generate PDF";            
          
            var browserType=findBrowser();
          
            document.getElementById("dialog").style.visibility="visible";
            jQuery("#dialog").dialog('open');
          
          
             jQuery(document).ready(
                    function() {
                    jQuery("#dialog").dialog({
                        autoOpen: true,
                        resizable: false,
                        height: 180,
                        modal: true,
                        buttons: {
                           'Open in Browser': function() {
                             document.getElementById("pressed").value="Open";
                             var metric=  document.getElementById("metric").value;
                             document.getElementById("dialog").style.visibility="hidden";
                             if(browserType == 1){
                              window.open("/Metric/Report?type=Generate PDF&pressed=Open&metric="+metric+"");
                             }else{
                                document.location = "/Metric/Report?type=Generate PDF&pressed=Open&metric="+metric+"";
                             }
                             jQuery("#dialog").dialog('close');   
                            },
                           'Save to disk': function() {                          
                              document.getElementById("pressed").value="Save";
                              document.getElementById("dialog").style.visibility="hidden";
                              var metric=  document.getElementById("metric").value;
                             document.location = "/Metric/Report?type=Generate PDF&pressed=Save&metric="+metric;
                                         
                             jQuery("#dialog").dialog('close');
                           }
                        }
                    });
                    });
            
            }
            else{
                document.getElementById("type").value="Generate Pie Chart";            

                document.forms[1].submit();
            }
		}
		
      	function onTabClick(id) {	
      		document.location = "<%= ResolveUrl("~/Edit")%>" + id;
		}
		
		function setMetric(metric) {
		    document.getElementById("metric").value = metric;
		}
    </script>

</asp:Content>
<asp:Content ID="CSS" ContentPlaceHolderID="CSSContent" runat="server">
</asp:Content>
<asp:Content ID="Title" ContentPlaceHolderID="TitleContent" runat="server">
    Metrics
</asp:Content>
<asp:Content ID="Main" ContentPlaceHolderID="MainContent" runat="server">
    <h2>
        Metrics
    </h2>
    
    <fieldset id="metrics">
        <legend>Metrics</legend>
        <%        
        int count = 1;
        string selectedMetricName = "";
        foreach (IMetric metric in MetricManager.Metrics) {
        %>
            <span style="white-space: nowrap; line-height:30px; vertical-align:text-top;">
                <input type="radio" name="metric" value="<%=metric.Name%>" id="metric_<%=count%>" onclick="setMetric(this.value);"
                    <%
                    if ((Session.Contents["MetricName"] == null && count == 1) || (Session.Contents["MetricName"] != null && Session.Contents["MetricName"].ToString() == metric.Name)) 
                    {
                        selectedMetricName = metric.Name;
                    %>
                        checked
                    <%  
                    }
                    %>
                />
                <span tooltip="<%=metric.Description%>">
                    <label for="metric_<%=count%>">
                        <%=metric.Name%>
                    </label>
                </span>
            </span>
            &nbsp;
        <%
            count++;
        }
        %>
    </fieldset>
    
    <%using (Html.BeginForm("Status", "Metric", FormMethod.Post)) {%>
        <fieldset>
            <legend>Reviews </legend>
            <div id="search-form">
                <% Html.RenderPartial("_SearchFormNoKeyword", Model.SearchForm); %>
            </div>
            <div style="clear: both">
            </div>
            <div id="grid">
                <% Html.RenderPartial("_Grid", Model); %>
            </div>
        </fieldset>
    <%}%>    
     
   <%using (Html.BeginForm("Report", "Metric", FormMethod.Post)) {%>
        <div style="text-align:right">
            <input type="hidden" name="pressed" id="pressed" value="" />
            <input type="hidden" name="type" id="type" value="" />
            <input type="hidden" name="metric" id="metric" value="<%=selectedMetricName%>"/>            
            <button type="button" name="type" value="Generate Pie Chart" onclick="openDialog('Generate Pie Chart');" style="height: 30px;">
                <img src="<%=ResolveUrl("~/Content/images/chart_pie.png")%>" alt="" align="top"/>
                Generate Pie Chart
            </button>
            <button type="button" name="type" value="Generate PDF" onclick="openDialog('Generate PDF');" style="height: 30px;">
                <img src="<%=ResolveUrl("~/Content/images/pdf.png")%>" alt="" align="top"/>
                Generate PDF
            </button>
        </div>
    <%}%> 
    
    <div id="dialog" style="visibility:hidden" title="Generate PDF">
        <p style="margin-bottom:auto;margin:0px 0px 0px 0px">
            <span class="ui-icon ui-icon-help" style="float: left; margin: 0 7px 20px 0;"></span>
           What would you like to do with the file?</p>
      </div> 
</asp:Content>
