<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage" %>
<%@ Import Namespace="CodeReview.Model.Repositories" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
    Administration
</asp:Content>
<asp:Content ID="Content3" ContentPlaceHolderID="JavascriptContent" runat="server">
</asp:Content>
<asp:Content ID="Content4" ContentPlaceHolderID="CSSContent" runat="server">
    <style type="text/css">
        /* TAB MENU   
----------------------------------------------------------*/
        ul#list
        {            
            padding: 0 0 2px;
            position: relative;
            margin: 0;
            text-align: left;
        }
        ul#list li
        {
            display: list-item;
            list-style: none;
        }
        ul#list li#greeting
        {
            padding: 10px 20px;
            font-weight: bold;
            text-decoration: none;
            line-height: 2.8em;
            color: #fff;
        }
        ul#list li a
        {
            padding: 10px 20px;
            font-weight: bold;
            text-decoration: none;
            line-height: 2.8em;            
            color: #034af3;
        }
        ul#list li a:hover
        {
            background-color: #fff;
            text-decoration: none;
        }
        ul#list li a:active
        {            
            text-decoration: none;
        }
        ul#list li.selected a
        {
            background-color: #fff;
            color: #000;
        }
    </style>
</asp:Content>
<asp:Content ID="Content5" ContentPlaceHolderID="HeadContent" runat="server">
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
    <h2>
        Administration</h2>
    <div>
        <fieldset>
            <legend>Available Actions</legend>
            <div>
                <ul id="list">
                    <%
                    if (new AdminRepository().IsAdmin(Page.User.Identity.Name))
                    {
                    %>
                        <li>
                            <%= Html.ActionLink("Quality checkers", "Index", "QualityChecker") %>
                        </li>
                        <li>
                            <%= Html.ActionLink("Database configuration", "DatabaseConfiguration", "Admin")%>
                        </li>
                        <li>
                            <%= Html.ActionLink("E-mail configuration", "EmailConfiguration", "Admin")%>
                        </li>
                    <%
                    }
                    %>
                    <li>
                        <%= Html.ActionLink("Review Manager", "Index", "ReviewManager")%>
                    </li>
                </ul>
            </div>
        </fieldset>
    </div>
</asp:Content>
