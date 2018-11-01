<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<Hotel.Controllers.ServiceEditViewModel>" %>
<%@ Import Namespace="Hotel"%>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
	   <%=Model.IsAdd ? "New Service" : "Edit Service"%>
</asp:Content>

<asp:Content ID="Content3" ContentPlaceHolderID="JavaScriptContent" runat="server">    
    <script type="text/javascript">
        jQuery(document).ready(function() {
            var value;            
            if (document.getElementById("Service_Price") != null) {
                value = document.getElementById("Service_Price").value;
                if (value == 0)
                    document.getElementById("Service_Price").value = "0,00";
            }
        }); 
    </script>
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">

    <h2><%=Model.IsAdd ? "New Service" : "Edit Service" %></h2>

    <% if (Model.HasErrors) {%>
		<span class="validation-summary-errors">
			Save was unsuccessful. Please correct the errors and try again.
		</span>
	<% } %>

    <% using (Html.BeginForm(Model.IsAdd ? "AddSave" : "EditSave", "Service", new { serviceID = Model.Service.ID }))
		{%>

        <fieldset>
            <legend>Fields</legend>           
            <p>
                <label for="Name">Name:</label>
                <%= Html.TextBox("Service.Name", Model.Service.Name)%>
                <%= Html.ValidationMessage("Service.Name")%>
            </p>            
            <p>
                <label for="Description">Description:</label>
                <%= Html.TextArea("Service.Description", Model.Service.Description)%>
                <%= Html.ValidationMessage("Service.Description")%>
            </p>
            <p>
                <label for="Price">Price($):</label>
                <%= Html.TextBox("Service.Price", String.Format("{0,00:F}", Model.Service.Price))%>
                <%= Html.ValidationMessage("Service.Price")%>
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

