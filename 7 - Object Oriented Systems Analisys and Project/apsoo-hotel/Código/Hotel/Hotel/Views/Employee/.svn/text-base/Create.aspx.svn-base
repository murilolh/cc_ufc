<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<Hotel.Models.Employee>" %>

<%@ Import Namespace="Hotel.Controllers" %>
<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
	Create
</asp:Content>


<asp:Content ID="Content4" ContentPlaceHolderID="JavaScriptContent" runat="server">
    <script type="text/javascript" src="<%=ResolveUrl("~")%>Scripts/validacao.js"></script>
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
    <style>
            .ui-datepicker { 
                  margin-left: 200px;
                  z-index: 1000;
            }
     </style>
    <h2>Create</h2>

    <%= Html.ValidationSummary("Create was unsuccessful. Please correct the errors and try again.") %>

    <% using (Html.BeginForm())
       {%>

        <fieldset>
            <legend>Fields</legend>
             <p>
                <label for="Name">Name:</label>
                <%= Html.TextBox("Name", Model.Name, new { @maxlength = "50" })%>
                <%= Html.ValidationMessage("Name") %>
            </p>
            <p>
                <label for="Login">Login:</label>
                <%= Html.TextBox("Login", Model.Login, new { @maxlength = "8" })%>
                <%= Html.ValidationMessage("Login") %>
            </p>
            <p>
                <label for="Password">Password:</label>
                <%= Html.Password("Password", Model.Password, new { @maxlength = "8" })%>
                <%= Html.ValidationMessage("Password") %>
            </p>
            <p>
		        <label for="Type">Type:</label>
			    <%= Html.DropDownList("EmployeeType", EmployeeController.TypeSelectList())%> 
			    <%= Html.ValidationMessage("Type") %>
		    </p>
            <p>
                <label for="CPF">CPF:</label>
                <%= Html.TextBox("CPF", Model.CPF, new { @onblur = "ValidarCPF(this)", @onkeypress= "MascaraCPF(this)", @maxlength = "14" } )%>
                <%= Html.ValidationMessage("CPF") %>
            </p>
            <p>
                <label for="DateOfBirth">DateOfBirth:</label>
                <%= Html.TextBox("DateOfBirth", Hotel.StringFormatter.FormatInputDate(Model.DateOfBirth), new { @class = "with-date-picker" })%>
                <%= Html.ValidationMessage("DateOfBirth") %>
            </p>                        
            <p>
                <input type="submit" value="Create" />
            </p>
        </fieldset>

    <% } %>

    <div>
        <%=Html.ActionLink("Back to Employees", "Index") %>
    </div>

</asp:Content>

<asp:Content ID="Content3" ContentPlaceHolderID="HeadContent" runat="server">
</asp:Content>

