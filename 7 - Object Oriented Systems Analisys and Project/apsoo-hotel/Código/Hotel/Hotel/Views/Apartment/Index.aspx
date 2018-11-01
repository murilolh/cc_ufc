<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<IEnumerable<Hotel.Models.Apartment>>" %>
<%@ Import Namespace="Hotel.Models" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
	Index
</asp:Content>


<asp:Content ID="Content5" ContentPlaceHolderID="HeadContent" runat="server">
    <link rel="stylesheet" type="text/css" href="<%= ResolveUrl("~")%>Content/grid.css"  />
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">

    <h2>Apartments</h2>
    <p>
        <%= Html.ActionLink("Create New", "Create") %>
    </p>
    
    <%= Html.ValidationSummary("Action was unsuccessful. Please correct the errors and try again.") %>
    
      
    <% if (Model.Count() != null)
       {%>        
        <div id="grid">
               <div id="grid-data">
    <table>
        <tr>
            <th>Actions</th>
            <th>
                Number
            </th>
            <th>
                Floor
            </th>
             <th>
                ApartmentType
            </th>
            <th>
                Status
            </th>
        </tr>

    <% foreach (var item in Model) { %>
    
        <tr>
            <td>
                <%= Html.ActionLink("Edit", "Edit", new { id=item.ID }) %> |
                <%= Html.ActionLink("Delete", "Delete", new { id=item.ID })%>
            </td>
            <td>
                <%= Html.Encode(item.Number) %>
            </td>
            <td>
                <%= Html.Encode(item.Floor) %>
            </td>
            <td>
                <%= Html.Encode(item.ApartmentType.Name) %>
            </td>
            <td>
                <%= Html.Encode(EnumExtensions.GetStringValue(item.ApartmentStatus)) %>
            </td>
        </tr>
    
    <% } %>

    </table>
            </div>
            </div>
    <% }
       else
       { %>
        There are not apartments registered.
    <% }  %>
    
    <br />
        <div>
            <%=Html.ActionLink("Back to Control", "Index", "Control") %> 
         </div> 
    

</asp:Content>

<asp:Content ID="Content3" ContentPlaceHolderID="JavaScriptContent" runat="server">
   
</asp:Content>

<asp:Content ID="Content4" ContentPlaceHolderID="CssContent" runat="server">
</asp:Content>
