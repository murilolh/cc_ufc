<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<Hotel.Controllers.CheckEditViewModel>" %>
<%@ Import Namespace="Hotel"%>
<%@ Import Namespace="Hotel.Models.Repository"%>
<%@ Import Namespace="Hotel.Models"%>
<%@ Import Namespace="Hotel.Controllers"%>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">     
	   <% if (!((String)ViewData["typeView"] == "OnlineReservation"))
       { %>
	   <%=Model.IsAdd ? "New " + (String)ViewData["typeView"] : "Edit " + (String)ViewData["typeView"]%>
	   <% }
       else
       {%>
      New Online Reservation
	   <%} %>
</asp:Content>

<asp:Content ID="Content3" ContentPlaceHolderID="JavaScriptContent" runat="server">    
    <script type="text/javascript" src="<%= ResolveUrl("~") %>Scripts/jquery-autocomplete/jquery.autocomplete.js"></script>
	 <script type="text/javascript" src="<%= ResolveUrl("~") %>Scripts/jquery.blockUI.js"></script>
	    
    <script type="text/javascript">
        jQuery(document).ready(function() {
            $("#Check_Amount").attr("disabled", true);
            $("#Check_Value").attr("disabled", true);
            $("#Check_CheckStatus").attr("disabled", true);             
            
            var value;
           
            if (document.getElementById("Check_Value") != null){               
                value = document.getElementById("Check_Value").value;
                if(value == 0)
                     document.getElementById("Check_Value").value = "0,00";
            }
            
            $("#Search").autocomplete(		   
			 "<%= ResolveUrl("~") %>Client.aspx/GetKeywordAutoCompleteData",
			{
				dataType: 'json',
				parse: function(data) {
					var rows = new Array();

					for (var i = 0; i < data.length; i++) {
						rows[i] = { data: data[i], value: data[i].Name, result: data[i].Name };
					}
					return rows;
				},
				formatItem: function(row, i, n) {
					return row.Name;
				},
				width: 260,
				selectFirst: false
			}
		);  	
			$("#Search").result(function(event, data, formatted) {
			    $("#clientId").val(data.ID);			  			    			    
			    search();
			}
        );
		
            
        });
        
        function selectApartment(id, count, item){               
            var i = 0;
            for (i = 0; i < count; i++){     
                document.getElementById("SelectedApartment_" + i).checked = false;
            }
            document.getElementById("SelectedApartment_" + id).checked = true;
            $("#apartmentId").val(item);
            search();
        }

        function search(){
            $("#isSearch").val(true);			  			    
			document.forms[0].submit();
        }
        
        function searchApartments(){
            search();
        }
        
        function searchClient(){
            search();
        }
        
        function newClient(type) {
            document.location =  "<%= ResolveUrl("~") %>Client.aspx/Add/For" + type;
        }   
        
        function calcValue(){    
           $("#Check_Value").val(<% String.Format("{0:F}", CheckController.calcCheckValue(Model.Check)); %>);
        }  
    </script>
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
    <link rel="stylesheet" type="text/css" href="<%= ResolveUrl("~")%>Content/grid.css"  />
	<link rel="stylesheet" type="text/css" href="<%= ResolveUrl("~")%>Scripts/jquery-autocomplete/jquery.autocomplete.css" />
    <style>
            .ui-datepicker { 
                  margin-left: 200px;
                  z-index: 1000;
            }
     </style>
    <% if (!((String)ViewData["typeView"] == "OnlineReservation"))
       { %>
    <h2><%=Model.IsAdd ? "New " + (String)ViewData["typeView"] : "Edit " + (String)ViewData["typeView"]%></h2>
<% }
       else
       { %>
       <h2>Online Reservation</h2>
<% } %>
    <% if (Model.HasErrors) {%>
		<span class="validation-summary-errors">
			<%= Html.ValidationSummary("Action was unsuccessful. Please correct the errors and try again.") %>				
		</span>
		
	<% } %>

    <% using (Html.BeginForm(Model.IsAdd ? "AddSave" : "EditSave", "Check", new { checkID = Model.Check.ID }))
		{  
           Check check = (Check)ViewData["previousEntry"];
            if (check != null)
            {  %>
            <div id="grid">
        <div id="grid-data">
                <table>
	                <tr>
		                <th>Actions</th>
		                <th>
			                Name
		                </th>
		                <th>
			                Apartment
		                </th>		
		                <th>
			                Status
		                </th>		
		                <th>
			                Date Begin
		                </th>
		                <th>
			                Date End
		                </th>
		                <th>
			                Value
		                </th>
	                </tr>        
		            <tr>
			            <td>
			                <%= Html.ActionLink("Details", "Details", new { id = check.ID, view = (String)ViewData["view"] })%> |
				            <%= Html.ActionLink("Edit", "Edit", new { id = (String)ViewData["typeView"], clientId = check.ID, view = (String)ViewData["view"] })%> 
			            </td>
			            <td>
				            <%= Html.Encode(check.Client.Name) %>
			            </td>
			            <td>
				            <%= Html.Encode(check.Apartment.Number) %>
			            </td>		
			            <td>
				            <%= Html.Encode(EnumExtensions.GetStringValue(check.CheckStatus))%>
			            </td>			
			            <td>
				            <%= Html.Encode(StringFormatter.FormatInputDateTime(check.DateBegin))%>
			            </td>
			            <td>
				            <%= Html.Encode(StringFormatter.FormatInputDateTime(check.DateEnd))%>
			            </td>
			            <td>
				            <%= Html.Encode(String.Format("{0:F}", check.Value))%>
			            </td>
		            </tr>
             </table>
             </div>
	    </div>
          <% } %>
        <fieldset>
            <legend>Fields</legend>            				
			<fieldset> 
			<legend> Client</legend>
			<input type="hidden" id="isSearch" name="isSearch" value="" />
			<input type="hidden" id="clientId" name="clientId" value="<%= Model.Check.Client != null ? Model.Check.Client.ID : 0 %>" />	
			<%if (!((String)ViewData["typeView"] == "OnlineReservation")) { %>
			    <table>
					<tr>					
						<td>	    						    
							<%= Html.TextBox("Search",(String)ViewData["Search"] , new { @style = "width: 100px" , @maxlength ="20"}) %>
						</td>						
						
						<td>
						    <input type="submit" id="search" value="Search Client" onclick="searchClient()"/>
						</td>
						<td>
						    <input type="button" value="Add new Client" onclick="newClient('<%=(String)ViewData["typeView"] %>')" /> 
						</td>
					</tr>					
				</table>
				<% } %>				
                <%  if (Model.Check.Client != null)
                    { %>                                 
                            <table class="grid-data">
	                            <tr>		                   
		                            <th width="280px">
			                            Name 
		                            </th>
		                            <th width="80px">
			                            Login
		                            </th>	
		                            <th width="150px">
			                            CPF
		                            </th>
		                            <th width="100px">
			                            Date of Birth
		                            </th>
		                            <th>
		                            </th>
	                            </tr>	                   		                    
		                            <tr>
			                            <td>
				                            <%= Html.Encode(Model.Check.Client.Name)%>
			                            </td>
			                            <td>
				                            <%= Html.Encode(Model.Check.Client.Login)%>
			                            </td>
			                            <td>
				                            <%= Html.Encode(Model.Check.Client.CPF)%>
			                            </td>
			                            <td>
				                            <%= Html.Encode(StringFormatter.FormatInputDate(Model.Check.Client.DateOfBirth))%>
			                            </td>
			                            <td>
			                                <%= Html.RadioButton("SelectedClient", "" ,true)%>
			                            </td>
		                            </tr>
                        </table>                                            
                  <% }
                    else
                    {%>                    
                        <span class="validation-summary-errors">
                        There is not client selected. Please search or click in "Add New Client"
                     </span>
                     
                  <% } %>      
                  </fieldset>    
            <fieldset> 
            <legend> Apartment </legend>
            <p>
                <label for="DateBegin">Date Begin:</label>
                <%= Html.TextBox("Check.DateBegin", Hotel.StringFormatter.FormatInputDateTime(Model.Check.DateBegin), new { @class = "with-date-time-picker" })%>
                <%= Html.ValidationMessage("Check.DateBegin")%>
            </p>
            <p>
                <label for="Date">Date End:</label>
                <%= Html.TextBox("Check.DateEnd", Hotel.StringFormatter.FormatInputDateTime(Model.Check.DateEnd) , new { @class = "with-date-time-picker"})%>
                <%= Html.ValidationMessage("Check.DateEnd")%> <input type="submit" id="search-apartments" value="Available Apartments" onclick="searchApartments()"/>
            </p> 
            
            <p>             
                   <%  
                       List<Apartment> list = (List<Apartment>)ViewData["apartments"];
                       if (Model.Check.Apartment != null)
                       { 
                           %>
                           <input type="hidden" id="apartmentId" name="apartmentId" value="<%=Model.Check.Apartment.ID %>" />
                           <% if(!list.Contains(Model.Check.Apartment) && (String)ViewData["typeView"] == "Check")
                            list.Add(Model.Check.Apartment);                        
                       }
                       else { %>
                            <input type="hidden" id="apartmentId" name="apartmentId" value="0" />
                      <% }  
                      if (list.Count() > 0)
                      {%>   
                             <table class="grid-data">
                                <tr>
                                    <th width="150px">
                                        Number
                                    </th>
                                    <th width="150px">
                                        Floor
                                    </th>
                                     <th width="150px">
                                        ApartmentType
                                    </th>
                                    <th width="150px">
                                        Daily Value($)
                                    </th>
                                    
                                    <th>                                        
                                    </th>
                                </tr>

                            <% int i = 0;
                                foreach (var item in list)
                               { %>
                                
                                <tr  onclick="selectApartment(<%=i%>, <%=list.Count() %>, <%=item.ID %>)">
                                    <td>
                                        <%= Html.Encode(item.Number)%>
                                    </td>
                                    <td>
                                        <%= Html.Encode(item.Floor)%>
                                    </td>
                                    <td>
                                        <%= Html.Encode(item.ApartmentType.Name)%>
                                    </td>
                                    <td>
                                        <%= Html.Encode(String.Format("{0,00:F}", item.ApartmentType.Price))%>
                                    </td>
                                    <td>
                                    <% if (Model.Check.Apartment.ID == item.ID)
                                       { %>
                                        <%= Html.RadioButton("SelectedApartment_" + i, i,true)%>
                                     <% }
                                       else
                                       { %>
                                        <%= Html.RadioButton("SelectedApartment_" + i, i,false)%>
                                     <% }
                                       i++;%>
                                    </td>
                                </tr>
                                
                                <% } %>
                            </table>                   
                        <% }
                      else
                      {%>
                                                   
                            <span class="validation-summary-errors">
                                There are not available apartment in this date
                            </span>
                       
                      <% } %>
                      
            </p> 
            </fieldset>
                <% if (!Model.IsAdd)
                { %>
                <p>
		            <label for="Status">Status:</label>
			    <%= Html.DropDownList("Check.CheckStatus", CheckController.TypeSelectList(Model.Check.CheckStatus))%> 
			     </p>
			    <% }   
             else
             { %>
			        <%= Html.Hidden("Check.CheckStatus", Model.Check.CheckStatus)%>
			 <% } %>
		                           
            <%  var d = false;
                if (d)
                { %>
            <p>
                <label for="TimeAmount">Time Amount(Days):</label>
                <%= Html.TextBox("Check.Amount", String.Format("{0:F1}", ((DateTime)Model.Check.DateEnd - (DateTime)Model.Check.DateBegin).TotalDays))%>
            </p>
            <% } %>
            <p>
                <label for="Value">Total Value($):</label>
                <%= Html.TextBox("Check.Value", String.Format("{0,00:F}", Model.Check.Value), new { @onclick = "calcValue()" } )%>
            </p>
            <p>
                <% if (("Reservation").Equals((String)ViewData["typeView"]) || ("Check").Equals((String)ViewData["typeView"]) || 
                ("OnlineReservation").Equals((String)ViewData["typeView"]))
                   { %>                 
                    <input type="hidden" id="typeView" name="typeView" value="<%=(String)ViewData["typeView"] %>" />
                <% } %>
                <input type="submit" value="Save" />
            </p>
        </fieldset>

    <% } %>

    <% if (!(("Reservation").Equals((String)ViewData["typeView"]) || 
                ("OnlineReservation").Equals((String)ViewData["typeView"]))) { %>            
        <div>
            <%=Html.ActionLink("Back to List", "List/" + (String)ViewData["view"]) %>
        </div>
    <% } %>

</asp:Content>

