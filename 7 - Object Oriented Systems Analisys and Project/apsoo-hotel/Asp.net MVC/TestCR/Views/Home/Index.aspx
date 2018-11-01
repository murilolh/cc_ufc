<%@ Page Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage" %>
<%@ Import Namespace="CodeReview.Model.Utils" %>

<asp:Content ID="indexTitle" ContentPlaceHolderID="TitleContent" runat="server">
    Home Page    
</asp:Content>

<asp:Content ID="indexContent" ContentPlaceHolderID="MainContent" runat="server">

    <%if(DatabaseHelper.IsDatabaseConfigurated() == false) { %>
        <h2 style="text-align:center; color:Red">This is probably the first access on LGE Code Review, so the database must be configurated.</h2>
        <p style="text-align:center">
            <%=Html.ActionLink("[Configure database]", "DatabaseConfig", "Admin") %>
        </p>
    <%} %>

    <table>
        <tr>
          <td style="vertical-align: top">
              <p>LGE Code Review provides an efficient way to perform code review.
               Your team will improve software quality and will deliver more 
               reliably software. </p>
                <p>The essence of LGE Code Review tool is an author receiving feedback on his or her
                 changes and the tool supports comments at the level of entire reviews,
                  whole files and specific source lines. </p>
                <p>LGE Code Review provides multiple features to help your team to get the best of 
                code review process:</p>
            
                <ul>
                <li>Simple workflow;</li>
                <li>Clear Case integration;</li>
                <li>Checklist-based reviews;</li>
                <li>Roles Management (developer, reviewer and admin);</li>
                <li>Search filters and table ordering by columns;</li>
                <li>E-mail notifications;</li>
                <li>Inline, file and review comments;</li>
                <li>Syntax highlighting for a wide variety of languages;</li>
                <li>And much more.</li>
                </ul>                        
            <p>
                With LGE Code Review tool handling your code review process, your team
                will deliver higher quality software faster and more reliably. 
            </p>
            <p>Get started!</p>
        
            <div style="color:#F22;background-color:#FEE;border-color:#F00;border-width:thin;border-style:dashed;">
                Supported browsers: Mozilla Firefox 3.5 or later, Google Chrome 1.0 or later or Internet Explorer 6 or later with Chrome Frame plugin. 
                <br />
                If you use an earlier version or a different browser, some Code Review features might not work properly.
            </div>  
          </td>  
          <td>
          <img width=700 src="<%=ResolveUrl("~/Content/images/DashboardHome.png") %>" />
          
          <br /> <br /><br /><br /> 
            <img width=550 src="<%=ResolveUrl("~/Content/images/newDiff.png") %>" />
          </td>
        </tr>
    </table>
    
    <div>
        
    </div>   
    <div id="placeholder"></div>
</asp:Content>
