<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<CodeReview.Model.Entities.QualityChecker>" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
	Edit
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">

    <h2>Edit Quality Checker</h2>

    <%= Html.ValidationSummary("Edit was unsuccessful. Please correct the errors and try again.") %>

    <% using (Html.BeginForm()) {%>
        <div style="width:365px">
        <fieldset>
            <legend>Fields</legend>
            <p>
                <label for="Name">Name:</label>
                <br />
                <%= Html.TextBox("Name", Model.Name, new { style = "width: 300px"}) %>
                <%= Html.ValidationMessage("Name", "*") %>
            </p>
            <p>
                <label for="Description">Description:</label>
                <br />
                <%= Html.TextArea("Description", Model.Description, new { style = "width: 300px", rows = 10}) %>
                <%= Html.ValidationMessage("Description", "*") %>
            </p>            
        </fieldset>
        <p>
            <input type="submit" value="Save" />
        </p>
        </div>
    <% } %>

    <div>
        [<%=Html.ActionLink("Back to Quality checkers", "Index") %>] 
    </div>

</asp:Content>

