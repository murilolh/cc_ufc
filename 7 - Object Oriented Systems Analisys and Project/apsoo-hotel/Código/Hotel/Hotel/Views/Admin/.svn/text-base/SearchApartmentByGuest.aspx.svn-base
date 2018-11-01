<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage" %>
<%@ Import Namespace="Hotel.Models" %>
<%@ Import Namespace="Hotel"%>
<%@ Import Namespace="Hotel.Models.Repository"%>
<%@ Import Namespace="Hotel.Controllers"%>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
	SearchApartmentByGuest
</asp:Content>

<asp:Content ID="Content3" ContentPlaceHolderID="JavaScriptContent" runat="server">
    <script type="text/javascript" src="<%= ResolveUrl("~") %>Scripts/jquery-autocomplete/jquery.autocomplete.js"></script>
	 <script type="text/javascript" src="<%= ResolveUrl("~") %>Scripts/jquery.blockUI.js"></script>
	 
	 <script type="text/javascript">
	 jQuery(document).ready(function() {
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
        
        function search(){
            $("#isSearch").val(true);			  			    
			document.forms[0].submit();
        }
        
         function searchClient(){
            search();
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

    <h2>Search Apartment By Guest</h2>
    <div>
    <fieldset>
    <legend> Guest</legend>
    <% using (Html.BeginForm("ChartGenerate", "Admin", new { id = (String)ViewData["View"] }))
       { %>
			    <table>
					<tr>
						<td>
						    <% Client c = (Client)ViewData["Client"]; %>
						    <input type="hidden" id="isSearch" name="isSearch" value="" />						  
						    <input type="hidden" id="clientId" name="clientId" value="<%= c != null ? c.ID : 0 %>"/>
							<%= Html.TextBox("Search",(String)ViewData["Search"] , new { @style = "width: 100px" , @maxlength ="20"}) %>
						</td>
						<td>
						    <input type="submit" id="search" value="Search Guest" onclick="searchClient()"/>
						</td>
					</tr>					
				</table>				
                <%  if ((Client)ViewData["Client"] != null)
                    { 
                       Client client = (Client)ViewData["Client"]; 
                        %>                                 
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
		                                Action
		                            </th>
	                            </tr>	                   		                    
		                            <tr>
			                            <td>
				                            <%= Html.Encode(client.Name)%>
			                            </td>
			                            <td>
				                            <%= Html.Encode(client.Login)%>
			                            </td>
			                            <td>
				                            <%= Html.Encode(client.CPF)%>
			                            </td>
			                                <td>
				                            <%= Html.Encode(StringFormatter.FormatInputDate(client.DateOfBirth))%>
			                            </td>
			                            <td>			                            
                                            <input type="submit" value="Search Apartment" />    
			                            </td>
		                            </tr>
                        </table>                                
                               
                  <%
                    }
                    else
                    {%>                    
                        <span class="validation-summary-errors">
                            There is not client selected
                        </span>                     
                  <% } %>  
                  
                  </fieldset>                   
                  <fieldset> 
                <legend> Apartment Information</legend> 
                   <%  
                       List<Check> list = (List<Check>)ViewData["Checks"];
                       if (list != null && list.Count > 0)
                       {%> 
                      <table class="grid-data" width="100%">
	                    <tr>
		                    <th>
			                    Name
		                    </th>
		                    <th>
			                    Apartment Number
		                    </th>
                            <th>
                                Apartment Floor
                            </th>
                             <th>
                                ApartmentType
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
			                    Daily Value
		                    </th>
	                    </tr>
                        <% 	
                               foreach (Check item in list)
                               { %>
            
		                    <tr>
			                    <td>
				                    <%= Html.Encode(item.Client.Name)%>
			                    </td>
			                    <td>
				                    <%= Html.Encode(item.Apartment.Number)%>
			                    </td>	
			                    <td>
                                    <%= Html.Encode(item.Apartment.Floor)%>
                                </td>
                                <td>
                                    <%= Html.Encode(item.Apartment.ApartmentType.Name)%>
                                </td>
			                    <td>
				                    <%= Html.Encode(EnumExtensions.GetStringValue(item.CheckStatus))%>
			                    </td>			
			                    <td>
				                    <%= Html.Encode(StringFormatter.FormatInputDateTime(item.DateBegin))%>
			                    </td>
			                    <td>
				                    <%= Html.Encode(StringFormatter.FormatInputDateTime(item.DateEnd))%>
			                    </td>
			                    <td>
				                    <%= Html.Encode(String.Format("{0:F}", item.Value))%>
			                    </td>			
		                    </tr>
		                    </table>
	                    <% } %>
	                    <% } 

                       else if (list == null)
                       {%>
                            Select a client to see apartment information
                      <% }
                       else
                       { %>
                            <span class="validation-summary-errors">
                                This client is not hosted now.
                            </span>
                      
                      <% } %>
          
            </fieldset> 
            <%} %>
            <br />
        <div>
            <%=Html.ActionLink("Back to Administration", "Index", "Admin") %> 
         </div>     
</asp:Content>


<asp:Content ID="Content4" ContentPlaceHolderID="CssContent" runat="server">
</asp:Content>

<asp:Content ID="Content5" ContentPlaceHolderID="HeadContent" runat="server">
</asp:Content>
