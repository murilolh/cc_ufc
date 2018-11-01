<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<CodeReview.Web.Controllers.DatabaseViewModel>" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
    Database Config
</asp:Content>
<asp:Content ID="Content4" ContentPlaceHolderID="CSSContent" runat="server">
    <style type="text/css">
        fieldset label
        {
            display: block;
        }
    </style>
</asp:Content>
<asp:Content ID="Content3" ContentPlaceHolderID=JavascriptContent runat="server">
    <script type="text/javascript">
        jQuery(document).ready(function() {
            var temp = document.getElementById("Server");
            temp.focus();
            temp.value = temp.value;
        });
    </script>
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
    <h2>Database Configuration</h2>
    
    <%= Html.ValidationSummary("Invalid configuration. Please correct the errors and try again.") %>
    
    <p style="color: Blue; font-weight: bold;">
        <%= Html.Encode(ViewData["SuccessfulResult"]) %>
    </p>
    <p style="color: Red; font-weight: bold;">
        <%= Html.Encode(ViewData["FailResult"]) %>
    </p>
    
    <%using (Html.BeginForm()) {%>
    <div style="width:365px">
    <fieldset>
        <legend>Configuration</legend>
        <p>
            <label for="Server">
                Server:</label>
            <%= Html.TextBox("Server", Model.Server, new { style = "width: 300px"}) %>
            <%= Html.ValidationMessage("Server", "*") %>
        </p>
        <p>
            <label for="Database">
                Database:</label>
            <%= Html.TextBox("Database", Model.Database, new { style = "width: 300px"}) %>
            <%= Html.ValidationMessage("Database", "*") %>
        </p>
        <p>
            <label for="UserID">
                User ID:</label>
            <%= Html.TextBox("UserID", Model.UserID, new { style = "width: 300px"}) %>
            <%= Html.ValidationMessage("UserID", "*") %>
        </p>
       
        <p>
            <label for="Password">
                Password:</label>
            <%= Html.Password("Password", Model.Password, new { style = "width: 300px"}) %>
            <%= Html.ValidationMessage("Password", "*") %>
        </p>   
    </fieldset>
    <p>
        <button name="button" value="test">Test Connection</button>
        <button name="button" value="save">Save</button>
    </p>
    </div>
    <%} %>
     <p>
        [<%=Html.ActionLink("Back to Administration", "Index", "Admin") %>]
    </p>
</asp:Content>
