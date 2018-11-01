<%@ Page Language="C#" MasterPageFile="~/Views/Shared/Site.Master" %>

<asp:Content ID="aboutTitle" ContentPlaceHolderID="TitleContent" runat="server">
    About
</asp:Content>

<asp:Content ID="aboutContent" ContentPlaceHolderID="MainContent" runat="server">
    <h2>About LGE Code Review</h2>
 
    <p>  
        Diff provided by <a target=_blank href="http://snowtide.com/jsdifflib">jsdifflib</a>.<br />
        Syntax highlighting provided by <a target=_blank href="http://shjs.sourceforge.net">SHJS</a>.<br />
        Inline comments and tooltips provided by <a target=_blank href="http://craigsworks.com/projects/qtip">qTip</a>.
    </p>
    
    <div style="text-align:center">
        <a href="http://www.lge.com" target=_blank>
            <img src="<%=ResolveUrl("~/Content/images/logoLG.png") %>"/>
        </a>
        
        <a href="http://www.ufc.br" target=_blank>
            <img src="<%=ResolveUrl("~/Content/images/LOGO_UFC_INGL_peq.png") %>" />
        </a>
        
        <a href="http://www.great.ufc.br" target=_blank>
            <img src="<%=ResolveUrl("~/Content/images/LOGO_GREAT_INGL_peq.png") %>" />
        </a>
    </div>
    
</asp:Content>
