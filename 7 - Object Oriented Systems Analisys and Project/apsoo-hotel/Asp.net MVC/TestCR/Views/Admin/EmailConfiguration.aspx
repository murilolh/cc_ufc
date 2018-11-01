<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<CodeReview.Web.Controllers.EmailViewModel>" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
    Email Configuration
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
    <h2>
        E-mail Configuration</h2>
    <%= Html.ValidationSummary("Invalid configuration. Please correct the errors and try again.") %>
    <p style="color: Blue; font-weight: bold;">
        <%= Html.Encode(ViewData["SuccessfulResult"]) %>
    </p>
    <p style="color: Red; font-weight: bold;">
        <%= Html.Encode(ViewData["FailResult"]) %>
    </p>
    <%using (Html.BeginForm()) {%>
    <div style="width:380px">
    <fieldset>
        <legend>Configuration</legend>
        <p>
            <%=Html.CheckBox("Enable", Model.Enable)%>
            <label for="Enable" style="display: inline">
                Enable SMTP:</label>
        </p>
        <fieldset>
            <legend>Required fields</legend>
            <p>
                <label for="Server">
                    Server</label>
                <%= Html.TextBox("Server", Model.Server, new { style = "width: 300px"})%>
                <%= Html.ValidationMessage("Server", "*")%>
            </p>
            <p>
                <label for="From">
                    From</label>
                <%= Html.TextBox("From", Model.From, new { style = "width: 300px"})%>
                <%= Html.ValidationMessage("From", "*")%>
            </p>
            <p>
                <label for="FromName">
                    From Name</label>
                <%= Html.TextBox("FromName", Model.FromName, new { style = "width: 300px"})%>
                <%= Html.ValidationMessage("FromName", "*")%>
            </p>
        </fieldset>
        <fieldset>
            <legend>Optional fields</legend>
            <p>
                <label for="Port">
                    Port</label>
                <%= Html.TextBox("Port", Model.Port, new { style = "width: 50px"})%>
                <%= Html.ValidationMessage("Port", "*")%>
            </p>
            <p>
                <label for="User">
                    User</label>
                <%= Html.TextBox("User", Model.User, new { style = "width: 300px"})%>
            </p>
            <p>
                <label for="Password">
                    Password</label>
                <%= Html.Password("Password", Model.Password, new { style = "width: 300px"})%>
            </p>
            <p>
                <label for="ReplyTo">
                    Reply To</label>
                <%= Html.TextBox("ReplyTo", Model.ReplyTo, new { style = "width: 300px"})%>
            </p>
            <p>
                <label for="AlwaysCc">
                    Always Cc</label>
                <%= Html.TextArea("AlwaysCc", Model.AlwaysCc, new { style = "width: 300px"})%>
            </p>
            <p>
                <label for="AlwaysBcc">
                    Always Bcc</label>
                <%= Html.TextArea("AlwaysBcc", Model.AlwaysBcc, new { style = "width: 300px"})%>
            </p>
            <p>
                <label for="SubjectPrefix">
                    Subject Prefix</label>
                <%= Html.TextBox("SubjectPrefix", Model.SubjectPrefix, new { style = "width: 300px"})%>
            </p>
        </fieldset>        
    </fieldset>
    <p>
        <button name="button" value="test">
            Test configuration</button>
        <button name="button" value="save">
            Save</button>
    </p>
    </div>
    <%} %>
    <p>
        [<%=Html.ActionLink("Back to Administration", "Index", "Admin") %>]
    </p>
</asp:Content>
