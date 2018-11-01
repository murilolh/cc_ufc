<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<Hotel.Models.ApartmentType>" %>

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
                <label for="Name">Name:</label>
                <%= Html.TextBox("Name", Model.Name) %>
                <%= Html.ValidationMessage("Name")%>
            </p>
            <p>
                <label for="Description">Description:</label>
                <%= Html.TextArea("Description", Model.Description) %>
                <%= Html.ValidationMessage("Description")%>
            </p>                        
            <p>
                <label for="Bed">Bed:</label>
                <%= Html.TextBox("Bed", Model.Bed) %>
                <%= Html.ValidationMessage("Bed")%>
            </p>            
            <p>
                <label for="Price">Price($/day):</label>
                <%= Html.TextBox("Price", String.Format("{0,00:F}",Model.Price))%>
                <%= Html.ValidationMessage("Price")%>
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

