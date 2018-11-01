<%@  Control Language="C#" Inherits="System.Web.Mvc.ViewUserControl<IMetric>" %>

<%@ Import Namespace="System.Web.UI.DataVisualization.Charting" %>
<%@ Import Namespace="System.Drawing" %>
<%@ Import Namespace="CodeReview.Metric" %>
<%@ Import Namespace="CodeReview.Model.Entities" %>
<%@ Import Namespace="CodeReview.Web" %>
<%@ Import Namespace="CodeReview.Web.Helpers" %>
<%@ Import Namespace="CodeReview.Web.Services" %>

<link href="<%=ResolveUrl("~/Content/Site.css")%>" rel="stylesheet" type="text/css" />

<div id="image"> 
    <img src="/Content/images/CODEREVIEW_site.png" height="90" alt="LGE Code Review" /> 
</div>
<br />
<div>
 <%  
    IMetric metric = ViewData["metric"] as IMetric;
    ReviewCriteria reviewCriteria = ViewData["reviewCriteria"] as ReviewCriteria;
    metric.Reviews = ViewData["ReviewsForMetrics"] as IList<Review>;
 %>
     <fieldset style="background-color: white;">
        <div style="margin-bottom:5px; ">
            <b>Summary</b>
        </div>
        <div style="margin-bottom:5px; ">
            <b>Metric description:</b> <%= Html.Encode(metric.Description)%>
        </div>
        
        <div style="margin-bottom:5px;">
            <b>Filter used:</b> <%= Html.Encode(reviewCriteria.CriteriaText)%>
        </div>
    </fieldset>
 
   <%  if (metric.Elements.Count() == 0) { %>      
        <script type="text/javascript">
            alert("No data available to generate report. Please choose a valid Filter.");
            document.location = "/Metric/Index";
        </script>
    <% } else {%>    
        <script type="text/javascript" language="JavaScript" src="<%=ResolveUrl("~/Scripts/progress.js")%>">
        </script>  
        
        <%using (Html.BeginForm("GeneratePDF", "Metric", FormMethod.Post)) {%>
            <%if(metric!=null){ %>
                <input type="hidden" name="id" id="id" value="<%=metric.Name%>"/>  
            <%} %>
            <input type="hidden" name="isSave" id="isSave" value="false"/>         
        <% } %>
        
        <script type="text/javascript">
            document.forms[0].submit();
        </script>         
    <% } %>
</div>