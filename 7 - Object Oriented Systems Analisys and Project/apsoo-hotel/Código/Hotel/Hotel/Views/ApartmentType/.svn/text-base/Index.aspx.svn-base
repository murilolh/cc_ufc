<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<IEnumerable<Hotel.Models.ApartmentType>>" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
    Index
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
    <h2>  
        Apartment Types</h2>
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
                        Actions    
                    </th>
                    <th>
                        Name
                    </th>
                    <th>
                        Description
                    </th>
                    <th>
                        Bed
                    </th>
                    <th>
                        Price($/day)
                    </th>
                </tr>
                <% foreach (var item in Model) { %>
                <tr>
                    <td>
                        <%= Html.ActionLink("Edit", "Edit", new { id=item.ID }) %>
                        |
                        <%= Html.ActionLink("Delete", "Delete", new { id = item.ID })%>
                    </td>
                    <td>
                        <%= Html.Encode(item.Name) %>                       
                    </td>
                    <td>
                        <%= Html.Encode(item.Description) %>
                    </td>                    
                    <td>
                        <%= Html.Encode(item.Bed) %>
                    </td>
                    <td>
                        <%= Html.Encode(String.Format("{0,00:F}", item.Price)) %>
                    </td>
                </tr>
                <% } %>
            </table>
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
<asp:Content ID="Content3" ContentPlaceHolderID="JavaScriptContent" runat="server">
</asp:Content>
<asp:Content ID="Content4" ContentPlaceHolderID="CssContent" runat="server">
 <link rel="stylesheet" type="text/css" href="<%= ResolveUrl("~")%>Content/grid.css" />
</asp:Content>
<asp:Content ID="Content5" ContentPlaceHolderID="HeadContent" runat="server">
</asp:Content>
