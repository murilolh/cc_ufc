<%@ Page Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage" %>

<asp:Content ID="loginTitle" ContentPlaceHolderID="TitleContent" runat="server">
    Log On
</asp:Content>

<asp:Content ID="Content4" ContentPlaceHolderID="CSSContent" runat="server">
    <style type="text/css">
        fieldset label
        {
            display: block;
        }
    </style>
</asp:Content>
<asp:Content ID="JavaScript" ContentPlaceHolderID="JavascriptContent" runat="server">
<script type="text/javascript">
    jQuery(document).ready(function() {        
        var temp = document.getElementById("username");        
        temp.focus();
        temp.value = temp.value;
    });
</script>

   <script type="text/javascript" src="<%=ResolveUrl("~/Scripts/jquery-browser/jquery.browser.js")%>"></script>
            
</asp:Content>
<asp:Content ID="loginContent" ContentPlaceHolderID="MainContent" runat="server">

    <script type="text/javascript">                
        if ( ($.browser.name == "firefox" && $.browser.versionNumber < 3.5) || ($.browser.name == "chrome" && $.browser.versionNumber < 1) ) {
            alert("You are using " + $.browser.name + " " + $.browser.version +"."+
                "\nThis browser version doesn't fully support Code Review." +
                "\n\nSupported browsers: Mozilla Firefox 3.5 or later, Google Chrome 1.0 or later or Internet Explorer 6 or later with Chrome Frame plugin." +
                "\n\nIf you use an earlier version or a different browser, some Code Review features might not work properly.")
        }
    </script>
    
    <h2>Log On</h2>   

    <p>
        Please enter your username and password used in LGESP Intranet.
    </p>
    <%= Html.ValidationSummary("Login was unsuccessful. Please correct the errors and try again.") %>

    <% using (Html.BeginForm()) { %>
        <div>
            <fieldset>
                <legend>Account Information</legend>
                <p>
                    <label for="username">Username:</label>
                    <%= Html.TextBox("username") %>
                    <%= Html.ValidationMessage("username") %>
                </p>
                <p>
                    <label for="password">Password:</label>
                    <%= Html.Password("password") %>
                    <%= Html.ValidationMessage("password") %>
                </p>
                <p>
                    <%= Html.CheckBox("rememberMe") %> <label class="inline" for="rememberMe">Remember me?</label>
                </p>
                <p>
                    <input type="submit" value="Log On" />
                </p>
            </fieldset>
        </div>
    <% } %>
</asp:Content>
