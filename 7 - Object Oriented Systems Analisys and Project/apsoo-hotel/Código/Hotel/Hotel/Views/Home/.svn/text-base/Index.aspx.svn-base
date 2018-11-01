<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<Hotel.Models.Inn>" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
	Plaza Caldas Hotel
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">

    <h2>Here Welcome!</h2>
    <div id="text">
        <table style="width: 100%">
            <tr>
                <td style="width: 40%; vertical-align: top">
                   <span style="vertical-align: top; font-size:small" >Comfort and tradition in one place. Come experience the wonderful Hotel Plaza Caldas!                      
                    <%= Html.ActionLink("Register", "Add", "Client", new { id = "ForRegistration" },  new { @title = "Make your registration" }) %> 
                    if you don't have an account yet and make your reservation!. 
                    </span>
                </td>                             
                <td style="width: 60%" align="center">
                 <img alt="logo" src="<%=ResolveUrl("~")%>Content/Images/suite.jpg" 
                     title="Plaza Caldas Hotel" style="height: 300px; width: 400px; text-align: right;"/> 
                </td>
            </tr>
        </table>
    </div>     
</asp:Content>

<asp:Content ID="Content3" ContentPlaceHolderID="HeadContent" runat="server">
</asp:Content>
