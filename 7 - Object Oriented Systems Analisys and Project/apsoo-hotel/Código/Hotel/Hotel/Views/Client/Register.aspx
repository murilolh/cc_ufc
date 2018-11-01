<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<Hotel.Controllers.ClientEditViewModel>" %>
<%@ Import Namespace="Hotel"%>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
	   <%=Model.IsAdd ? "New Client" : "Edit Client"%>
</asp:Content>

<asp:Content ID="Content4" ContentPlaceHolderID="JavaScriptContent" runat="server">
    <script type="text/javascript" src="<%=ResolveUrl("~")%>Scripts/validacao.js"></script>

    <script type="text/javascript">
        //valida o CPF digitado
        function NewValidarCPF(Objcpf) {
            if (Objcpf.value == "" || Objcpf.value == null) {                
                return;
            }            
            ValidarCPF(Objcpf);
            
        }
    </script>
</asp:Content>
    


<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
    <style>
            .ui-datepicker { 
                  margin-left: 200px;
                  z-index: 1000;
            }
     </style>
     <h2>Create a New Account</h2>
    <p>
        Use the form below to create a new account. 
    </p>
    <p>
        Passwords are required to be a minimum of 8 characters in length.
    </p>    
     

    <% if (Model.HasErrors) {%>
		<span class="validation-summary-errors">
		    <%= Html.ValidationSummary("Action was unsuccessful. Please correct the errors and try again.") %>
		</span>
	<% } %>
	 
	 <% using (Html.BeginForm("Register", "Client", new { clientID = Model.Client.ID })) { %>	
        <fieldset>
            <legend>Fields</legend>            
            <p>
                <label for="Name">Name:</label>
                <%= Html.TextBox("Client.Name", Model.Client.Name, new { @maxlength = "50" })%>
                <%= Html.ValidationMessage("Client.Name")%>
            </p>
            <p>
                <label for="Login">Login:</label>
                <%= Html.TextBox("Client.Login", Model.Client.Login, new { @maxlength = "8" })%>
                <%= Html.ValidationMessage("Client.Login")%>
            </p>
            <p>
                <label for="Password">Password:</label>
                <%= Html.Password("Client.Password", Model.Client.Password, new { @maxlength = "8" })%>
                <%= Html.ValidationMessage("Client.Password")%>
            </p>
            <p>
                <label for="CPF">CPF:</label>
                <%= Html.TextBox("Client.CPF", Model.Client.CPF, new { @onblur = "NewValidarCPF(this)", @onkeypress = "MascaraCPF(this)", @maxlength = "14" })%>
                <%= Html.ValidationMessage("Client.CPF")%>
            </p>
            
            <p>
                <label for="DateOfBirth">Date of Birth:</label>
                <%= Html.TextBox("Client.DateOfBirth", Hotel.StringFormatter.FormatInputDate(Model.Client.DateOfBirth) , new { @class = "with-date-picker"})%>
                <%= Html.ValidationMessage("Client.DateOfBirth")%>
            </p>
            <p>
                <% if (!String.IsNullOrEmpty((String)ViewData["typeView"])) { %>                    
                    <input type="hidden" name="typeView" id="typeView" value="<%=(String)ViewData["typeView"] %>"/>
                <% } %>
                <input type="submit" value="Save" />
            </p>
        </fieldset>        
        <% } %>
</asp:Content>

