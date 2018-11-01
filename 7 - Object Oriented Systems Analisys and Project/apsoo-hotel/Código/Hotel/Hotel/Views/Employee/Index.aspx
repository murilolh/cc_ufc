<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<IEnumerable<Hotel.Models.Employee>>" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
    Index
</asp:Content>
<asp:Content ID="Content4" ContentPlaceHolderID="CssContent" runat="server">
</asp:Content>
<asp:Content ID="Content3" ContentPlaceHolderID="HeadContent" runat="server">
    <link rel="stylesheet" type="text/css" href="<%= ResolveUrl("~")%>Content/grid.css" />
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
    <h2>
        Employees</h2>
    <p>
        <%= Html.ActionLink("Create New", "Create") %>  
    </p>  
    
    <%= Html.ValidationSummary("Action was unsuccessful. Please correct the errors and try again.") %>
    
    <% if (Model != null)
       {%>
    <div id="grid">
        <div id="grid-data">
            <table>
                <tr>
                    <th>
                    </th>
                    <th>
                        Login
                    </th>
                    <th>
                        Name
                    </th>
                    <th>
                        CPF
                    </th>
                    <th>
                        Type
                    </th>
                    <th>
                        DateOfBirth
                    </th>
                </tr>
                <% foreach (var item in Model)
                       { %>
                <tr>
                    <td>
                        <%= Html.ActionLink("Edit", "Edit", new { id = item.ID })%>
                        |
                        <%= Html.ActionLink("Delete", "Delete", new { id = item.ID })%>
                    </td>
                    <td>
                        <%= Html.Encode(item.Login)%>
                    </td>
                    <td>
                        <%= Html.Encode(item.Name)%>
                    </td>
                    <td>
                        <%= Html.Encode(item.CPF)%>
                    </td>
                    <td>
                        <%= Html.Encode(Hotel.Models.EnumExtensions.GetStringValue(item.EmployeeType))%>
                    </td>
                    <td>
                        <%= Html.Encode(Hotel.StringFormatter.FormatInputDate(item.DateOfBirth))%>
                    </td>
                </tr>
                <% } %>
            </table>
        </div>
    </div>
    <% }
       else
       { %>
    There are not employers registered.
    <% }  %>
    
    <br />
	<div>
                <%=Html.ActionLink("Back to Control", "Index", "Control") %> 
             </div> 
</asp:Content>
