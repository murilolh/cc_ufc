<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<Hotel.Models.Apartment>" %>

<%@ Import Namespace="Hotel.Controllers" %>
<%@ Import Namespace="Hotel.Models" %>
<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
	Edit
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">

    <h2>Edit</h2>

    <%= Html.ValidationSummary("Edit was unsuccessful. Please correct the errors and try again.") %>

    <% using (Html.BeginForm()) {%>

        <fieldset>
            <legend>Fields</legend>           
            <p>
                <label for="Number">Number:</label>
                <%= Html.TextBox("Number", Model.Number) %>
                <%= Html.ValidationMessage("Number") %>
            </p>
             <p>
                <label for="Floor">Floor:</label>
                <%= Html.TextBox("Floor", Model.Floor) %>
                <%= Html.ValidationMessage("Floor") %>
            </p>
            <p>
                <label for="Type">Type:</label>
                <%= Html.DropDownList("TypeID", ApartmentController.ApartmentTypeSelectList(Model.TypeID))%> 
                <%= Html.ValidationMessage("Type") %>
            </p>
            <p>
                <label for="Status">Status:</label>
                <%= Html.DropDownList("ApartmentStatus", ApartmentController.TypeSelectList(Model.ApartmentStatus))%> 
                <%= Html.ValidationMessage("Status") %>
            </p>
            <p>
                <input type="submit" value="Save" />
            </p>
        </fieldset>

    <% } %>

    <div>
        <%=Html.ActionLink("Back to List", "Index") %>
    </div>

</asp:Content>

<asp:Content ID="Content3" ContentPlaceHolderID="JavaScriptContent" runat="server">
</asp:Content>

<asp:Content ID="Content4" ContentPlaceHolderID="CssContent" runat="server">
</asp:Content>

<asp:Content ID="Content5" ContentPlaceHolderID="HeadContent" runat="server">
</asp:Content>

