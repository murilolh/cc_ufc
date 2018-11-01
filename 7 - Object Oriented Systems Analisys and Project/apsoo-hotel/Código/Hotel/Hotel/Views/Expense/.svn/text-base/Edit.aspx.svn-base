<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<Hotel.Controllers.ExpenseEditViewModel>" %>
<%@ Import Namespace="Hotel"%>
<%@ Import Namespace="Hotel.Models.Repository"%>
<%@ Import Namespace="Hotel.Models"%>
<%@ Import Namespace="Hotel.Controllers"%>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">     
	   <%=Model.IsAdd ? "New " + (String)ViewData["typeView"] : "Edit " + (String)ViewData["typeView"]%>
</asp:Content>

<asp:Content ID="Content3" ContentPlaceHolderID="JavaScriptContent" runat="server">    
    <script type="text/javascript">
        jQuery(document).ready(function() {
            document.getElementById("Expense_Value").disabled = true;
            
            var value;
           
            if (document.getElementById("Expense_Value") != null){               
                value = document.getElementById("Expense_Value").value;
                if(value == 0)
                     document.getElementById("Expense_Value").value = "0,00";
            }
        });

        function newService(type) {
            document.location =  "<%= ResolveUrl("~") %>Service.aspx/Add/For" + type;
        }        
        
    </script>
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">

    <h2><%=Model.IsAdd ? "New Expense" : "Edit Expense"%></h2>

    <% if (Model.HasErrors) {%>
		<span class="validation-summary-errors">
			<%= Html.ValidationSummary("Action was unsuccessful. Please correct the errors and try again.") %>
		</span>
	<% } %>

    <% using (Html.BeginForm(Model.IsAdd ? "AddSave" : "EditSave", "Expense", new { expenseID = Model.Expense.ID }))
		{  %>

        <fieldset>
            <legend>Fields</legend>
            <p> 
                <label for="Service">Service: 
                <%=Html.DropDownList("Expense.ServiceID", ExpenseController.ServiceSelectList(Model.Expense.ServiceID))%>                                
                <%= Html.ValidationMessage("Expense.Service")%> </label>
            </p> 
           
            <p>
                <label for="Date">Date :</label>
                <%= Html.TextBox("Expense.Date", Hotel.StringFormatter.FormatInputDateTime(Model.Expense.Date) , new { @class = "with-date-time-picker"})%>
                <%= Html.ValidationMessage("Expense.Date")%>
            </p>
            <p>
                <%= Html.Hidden("Expense.CheckID", Model.Expense.CheckID)%>
            </p>
            <p>
                <label for="Amount">Amount:</label>
                <%= Html.TextBox("Expense.Amount", Model.Expense.Amount)%>
                <%= Html.ValidationMessage("Expense.Amount")%>
            </p>
            <p>
                <label for="Value">Value($):</label>
                <%= Html.TextBox("Expense.Value", String.Format("{0,00:F}",Model.Expense.Value))%>
                <%= Html.ValidationMessage("Expense.Value")%>
            </p>
            <p>
                <input type="submit" value="Save" />
            </p>
        </fieldset>

    <% } %>
    <div>
        <%=Html.ActionLink("Back to Check Details", "Details/" + Model.Expense.CheckID, "Check") %>
    </div>
</asp:Content>

