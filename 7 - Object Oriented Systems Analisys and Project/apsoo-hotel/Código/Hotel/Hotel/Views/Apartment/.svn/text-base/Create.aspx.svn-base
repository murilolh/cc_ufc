<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<Hotel.Models.Apartment>" %>

<%@ Import Namespace="Hotel.Controllers" %>
<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
	Create
</asp:Content>


<asp:Content ID="Content3" ContentPlaceHolderID="JavaScriptContent" runat="server">  
    <script type="text/javascript">
        jQuery(document).ready(function() {
        var value = document.getElementById("Floor").value;
        if (value == 0)
            document.getElementById("Floor").value = "";
        
        value = document.getElementById("Number").value;
        if (value == 0)            
            document.getElementById("Number").value = "";
        });
    </script>
</asp:Content>


<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">

    <h2>Create</h2>

    <%= Html.ValidationSummary("Create was unsuccessful. Please correct the errors and try again.") %>

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
                <%= Html.DropDownList("ApartmentStatus", ApartmentController.TypeSelectList())%> 
                <%= Html.ValidationMessage("Status") %>
            </p>
            <p>
                <input type="submit" value="Create" />
            </p>
        </fieldset>

    <% } %>

    <div>
        <%=Html.ActionLink("Back to List", "Index") %>
    </div>

</asp:Content>

<asp:Content ID="Content4" ContentPlaceHolderID="CssContent" runat="server">
</asp:Content>

<asp:Content ID="Content5" ContentPlaceHolderID="HeadContent" runat="server">
</asp:Content>

