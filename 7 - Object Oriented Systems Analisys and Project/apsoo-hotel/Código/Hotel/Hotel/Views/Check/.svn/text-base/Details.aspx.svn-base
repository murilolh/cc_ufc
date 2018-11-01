<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<Hotel.Controllers.CheckEditViewModel>" %>
<%@ Import Namespace="Hotel"%>
<%@ Import Namespace="Hotel.Models.Repository"%>
<%@ Import Namespace="Hotel.Models"%>
<%@ Import Namespace="Hotel.Controllers"%>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">     
	   Check Summary
</asp:Content>

<asp:Content ID="Content3" ContentPlaceHolderID="JavaScriptContent" runat="server">    
    <script type="text/javascript">
        jQuery(document).ready(function() {
            
        });
        
        function newExpense() {
            document.location =  "<%= ResolveUrl("~") %>Expense.aspx/Add/" + <%=Model.Check.ID %>;
        } 
        
        function reverseExpense(id) {
            document.location =  "<%= ResolveUrl("~") %>Expense.aspx/Reverse/" + id;
        } 
        
        function cancelExpense(id) {
            document.location =  "<%= ResolveUrl("~") %>Expense.aspx/Delete/" + id;
        } 
        
        function onClick(id) {
            document.location =  "<%= ResolveUrl("~") %>Check.aspx/Details/" + id; 
        }
        
    </script>
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
    <link rel="stylesheet" type="text/css" href="<%= ResolveUrl("~")%>Content/grid.css"  />	
    <h2>Check Summary</h2>

       <fieldset>
            <legend>Fields</legend>
           
                <label for="Client" >Client: 
                <span  style="font-weight:bold"> <%=Html.Encode(Model.Check.Client.Name)%>  </span>
                </label>
           
                <label for="Apartment Number">Apartment Number:
                <span style="font-weight:bold">  <%=Html.Encode(Model.Check.Apartment.Number)%>   </span>                                            
                </label>
                <label for="Apartment Floor">Apartment Floor:
                <span style="font-weight:bold">  <%=Html.Encode(Model.Check.Apartment.Floor)%>   </span>                                            
                </label>
                <label for="Apartment Type">Apartment Type:
                <span style="font-weight:bold">  <%=Html.Encode(Model.Check.Apartment.ApartmentType.Name)%>   </span>                                            
                </label>
              
             
		        <label for="Status">Status:
			    <span style="font-weight:bold">  <%= Html.Encode(EnumExtensions.GetStringValue(Model.Check.CheckStatus))%> </span>
			    </label>
		     
             
                <label for="DateBegin">Date Begin:
                <span  style="font-weight:bold"> <%= Html.Encode(Hotel.StringFormatter.FormatInputDateTime(Model.Check.DateBegin))%> </span>
                </label>                 
             
             
                <label for="DateEnd">Date End:
                <span  style="font-weight:bold"> <%= Html.Encode(Hotel.StringFormatter.FormatInputDateTime(Model.Check.DateEnd))%> </span>
                </label>
                               
                         
             
                <label for="TimeAmount">Time Amount(Days):
                <span  style="font-weight:bold"> <%= Html.Encode(String.Format("{0:F1}", ((DateTime)Model.Check.DateEnd - (DateTime)Model.Check.DateBegin).TotalDays))%> </span>
                </label>                
             
             
                <label for="Value">Daily Value($):
                <span  style="font-weight:bold"> <%= Html.Encode(String.Format("{0,00:F}", Model.Check.Value))%> </span>
                </label>
                
             
        </fieldset>
        <fieldset>
        <legend>Expenses List</legend>
        <%  
    if (Model.Check.CheckStatus == CheckStatus.EFFECTED || Model.Check.CheckStatus == CheckStatus.RESERVATION_EFFECTED)
    {%>
        <p>
            <input type="button" value="Launch new expense" onclick="newExpense()" /> 
        </p>
           <% } %>
        <div id="grid">
        <div id="grid-data">
         <table>
         <tr>
		        <th>Actions</th>
		        <th>
		            Details
		        </th>
		        <th>
			        Service
		        </th>
		        <th>
			        Date
		        </th>
		        <th>
		            Amount
		        </th>
		        <th>
			        Value
		        </th>
	        </tr>
                
         <% Double total = 0;
            if (Model.Check.Expenses.Count != 0)
            {
                //Can't use Model.Data directly.  Doesn't pick up generic type.
                IList<Expense> expenses = (IList<Expense>)Model.Check.Expenses;
                foreach (Expense item in expenses)
                {   %>           
                             
		        <tr >
		        
			        <td>
			         <%   if (Model.Check.CheckStatus == CheckStatus.EFFECTED || Model.Check.CheckStatus == CheckStatus.RESERVATION_EFFECTED)
                 { %>
			            <a href="#"  onclick="cancelExpense(<%=item.ID %>)">Cancel</a> 	
			            <% }  %>
			            <% ExpenseRepository<Expense,hotelEntities> er = new ExpenseRepository<Expense,hotelEntities>();                    
                            if ((Model.Check.CheckStatus == CheckStatus.EFFECTED || Model.Check.CheckStatus == CheckStatus.RESERVATION_EFFECTED) && item.Value > 0 && 
                                er.SelectWhere(e => e.Value == (-item.Value) && e.Service.ID == item.Service.ID && e.Amount == item.Amount && e.Check.ID == item.Check.ID).ToList().Count() == 0)
                        { %>
				         | <a href="#"  onclick="reverseExpense(<%=item.ID %>)">Reverse </a>				         
				         <% } %>
				          
			        </td>			        
			        <td>
			        <% if (item.Value < 0)
              { %>
                        Expense Reversed.
			            <% } %>
			        </td>
			        <td>
				        <%= Html.Encode(item.Service.Name)%>
			        </td>			       
			        <td>
				        <%= Html.Encode(StringFormatter.FormatInputDateTime(item.Date))%>
			        </td>
			         <td>
				        <%= Html.Encode(item.Amount)%>
			        </td>
			        <td>
				        <%= Html.Encode(String.Format("{0,00:F}", item.Value))%>
			        </td>
		        </tr>               
	        <%  total = total += item.Value;
                } %>        	
	    <% }%>
	    <tr style="background-color:Silver">
			        <td>
				         
			        </td>
			        <td>
			        Expense related to daily apartment
			        </td>
			        <td>
				        Daily Apartment
			        </td>			       
			        <td>
				        <%= Html.Encode(StringFormatter.FormatInputDateTime(DateTime.Today))%>
			        </td>
			        <td>
				        <%= Html.Encode(String.Format("{0:F1}", ((DateTime)Model.Check.DateEnd - (DateTime)Model.Check.DateBegin).TotalDays))%>
			        </td>
			        <td>
				        <%= Html.Encode(String.Format("{0,00:F}", Model.Check.Value))%>
			        </td>
		        </tr>
		        <tr style="background-color:White">
			        <td>
			        </td>
			        <td>
			        </td>
			        <td>
			        </td>
			         <td>
			        </td>
			        <td>				         
			            Total
			        </td>
			        <td>
				        <%= Html.Encode(String.Format("{0,00:F}", total + Model.Check.Value))%>
			        </td>
		        </tr>
		        <tr style="background-color:White">
			        <td>
			        </td>
			        <td>
			        </td>
			        <td>
			        </td>
			         <td>
			        </td>
			        <td>
			        </td>
			        <td>
			     <%   if (Model.Check.CheckStatus == CheckStatus.EFFECTED || Model.Check.CheckStatus == CheckStatus.RESERVATION_EFFECTED) { %>                   
				            <%= Html.ActionLink("Checkout", "Checkout", new { id = Model.Check.ID })%> 
				        <%}
             else if (Model.Check.CheckStatus == CheckStatus.RESERVATION_REQUEST)
             { %>
             <%= Html.ActionLink("Checkin", "Checkin", new { id = Model.Check.ID })%> 
				        <% } %>
			        </td>
		        </tr>
		        
        </table>
	    </div>
	    </div>
        </fieldset>       
        <div>        
            <%=Html.ActionLink("Back to List", "List/" + (String)ViewData["view"])%>
        </div>
       


</asp:Content>

