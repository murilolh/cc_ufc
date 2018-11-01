<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<File>" %>

<%@ Import Namespace="CodeReview.Model.Entities" %>
<%@ Import Namespace="CodeReview.Model.Repositories" %>
<%@ Import Namespace="CodeReview.Web.Helpers" %>
<%@ Import Namespace="CodeReview.Web" %>
<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">

    Review
    <%= Model.Review.Id  %>
    - File
    <%= Model.Id %>
   
 
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
<script src="<%=ResolveUrl("~/Scripts/jquery-ui-1.7.2.custom.min.js")%>" type="text/javascript"></script>  
         <script type="text/javascript" src="<%=ResolveUrl("~/Scripts/wordWrap.js")%>"></script>  
        <script type="text/javascript">  
	 	    window.onload = wordWrap;  
	 	</script>  	 	

    <script type="text/javascript">
        //document.body.setAttribute("onload", "jQuery.unblockUI();");
        jQuery.blockUI({ message: '<h2>Loading...</h2>' });
    </script>
    
     <!-- <div class="transparent_class" id="loading" style="float:left; width:700px; height:500px; margin:30px 50px; background-color:#000; border:1px solid black;">  
        Loading... 
    </div> -->

    <h2>
        File
        <%= Model.Id %></h2>
    <fieldset style="display:block">
        <legend>Summary</legend>
       
        <p style="margin-bottom: 5px;">
            <b>Review:</b>
            <%= Html.Encode(Model.Review.Id)%>
            <%  
                   AdminRepository adminRep = new AdminRepository();               
                   ProjectRepository projectRep = new ProjectRepository();   
                   Boolean admin = false;   
                   String isAdmin = Request.Params["isAdmin"] as String;  
                   if ("true".Equals(isAdmin) && (adminRep.IsAdmin(System.Web.HttpContext.Current.User.Identity.Name)    
                                || projectRep.IsProjectManager(System.Web.HttpContext.Current.User.Identity.Name)))   
                       {    
                  admin = true; 
            %>  
                [<a href="<%=ResolveUrl("~/ReviewManager/Log/" + Model.Review.Id + "?file=" + Model.Id) %>">Back to File Log</a>]  
	 	    <%  
	 	        } else {
            %>  
                [<a href="<%=ResolveUrl("~/Review/" + Model.Review.Id) %>">Back to Review</a>]  
	 	    <% } %> 
	 	    <input type="hidden" id="admin" name="admin" value="<%=admin %>" />
	 	</p> 
	 	<p style="margin-bottom: 5px;" class="word-wrap"> 
            <b>Project:</b>
            <%= Html.Encode(Model.Review.Project.PVobServer) %>/<%= Html.Encode(Model.Review.Project.PVobName) %>/<%= Html.Encode(Model.Review.Project.Name) %>
        </p>
        <p style="margin-bottom: 5px;" class="word-wrap">
            <b>Activity:</b>
            <%= Html.Encode(Model.Review.Activity) %>
        </p>
        <p style="margin-bottom: 5px;">
            <b>Developer:</b>
            <%= Html.Encode(Model.Review.Developer) %>
        </p>
        <p style="margin-bottom: 5px;">
            <b>Reviewer:</b>
            <%= Html.Encode(Model.Review.Reviewer) %>
        </p>
        <p style="margin-bottom: 5px;">
            <b>Creation date:</b>
            <%= Html.Encode(StringFormatter.FormatDateTime(Model.CreationDate)) %>
        </p>
        <p style="margin-bottom: 5px;">
            <b>Last change date:</b>
            <%= Html.Encode(StringFormatter.FormatDateTime(Model.LastChangeDate)) %>
        </p>
        <p style="margin-bottom: 5px;">
            <b>Status:</b>
            <%= Html.Encode(Model.Status.GetStringValue()) %>
        </p>
        <p style="margin-bottom: 5px;">
            <b>File path: </b>
            <span title="<%=Html.Encode(Model.Name)%>">
                <%= Html.Encode(StringHelper.Resume(Model.Name, 100, '\\'))%>
            </span>
        </p>
    </fieldset>
    <%
        FileRepository fRepository = new FileRepository();
        FileQualityCheckerRepository fqcRepository = new FileQualityCheckerRepository();
        QualityCheckerRepository qcRepository = QualityCheckerRepository.Instance;
        IList<File> filesOld = fRepository.GetAllFilesByNameReviewAndStatus(Model.Name, Model.Review, FileStatus.OLD_VERSION);
        IList<QualityChecker> qualityCheckers = qcRepository.GetAll();
        bool isReviewer = Page.User.Identity.Name == Model.Review.Reviewer;
        IList<File> actual = fRepository.GetAllFilesByNameReviewAndStatus(Model.Name, Model.Review, FileStatus.PENDING);
        if (actual.Count == 0)
        {
            actual = fRepository.GetAllFilesByNameReviewAndStatus(Model.Name, Model.Review, FileStatus.APPROVED);
            if (actual.Count == 0)
            {
                actual = fRepository.GetAllFilesByNameReviewAndStatus(Model.Name, Model.Review, FileStatus.REJECTED);
            }
        }
        if (filesOld.Count > 0)
        {
    %>
    <fieldset>
        <legend>Other Versions</legend>
        <div style="margin-bottom: 5px;">
            <% foreach (File aux in filesOld)
              {
                  if (aux.Id == Model.Id) { %>
                    - Version
                    <%=aux.WorkVersion%>
                    [ACTUAL SELECTED]<br />
                  <% } else { %>
                       <% if(admin) { %>                       
                        - <a href="<%=ResolveUrl("~/File/Index/" + aux.Id + "?isAdmin=true") %>">Version
                        <%=aux.WorkVersion%></a><br />
                        <% } else { %>
                        - <a href="<%=ResolveUrl("~/File/Index/" + aux.Id) %>">Version
                        <%=aux.WorkVersion%></a><br />
                        <% } %>
                  <% }   
               }
               if (actual[0].Id != Model.Id) { %>
                <% if(admin) { %>
                    - <a href="<%=ResolveUrl("~/File/Index/" + actual[0].Id + "?isAdmin=true") %>">Actual Version                    
                    <%=actual[0].WorkVersion%></a><br />
                   <% } else {%>
                    - <a href="<%=ResolveUrl("~/File/Index/" + actual[0].Id) %>">Actual Version                    
                    <%=actual[0].WorkVersion%></a><br />                   
                   <% } %>
              <% } %>
        </div>
    </fieldset>
    <%} %>
    
    <% Html.BeginForm("Index", "File", FormMethod.Post); %>
    <fieldset id="qualityCheckers">
        <legend>Quality checkers</legend>
        <table>
            <%
                int row = 0;
                int col = 0;
                foreach (QualityChecker qualityChecker in qualityCheckers)
                {
                    if ((qualityChecker.DeletionDate != null && Model.CreationDate.CompareTo(qualityChecker.DeletionDate) > 0) ||
                        (Model.LastChangeDate.CompareTo(qualityChecker.CreationDate) < 0 && (Model.Review.Status == ReviewStatus.DELIVERED || !isReviewer)))
                    {
                        continue;
                    }

                    row++;
                    col++;
                    
                    QualityCheckerStatus qcStatus = QualityCheckerStatus.NULL;
                    if (ViewData["checker_" + qualityChecker.Id] == null)
                    {
                        FileQualityChecker fileQualityChecker = fqcRepository.GetByFileAndQualityChecker(fRepository.GetFileById(Model.Id), qualityChecker);
                        if (fileQualityChecker != null)
                        {
                            qcStatus = fileQualityChecker.Status;
                        }
                    }
                    else
                    {
                        if ("1".Equals(ViewData["checker_" + qualityChecker.Id]))
                        {
                            qcStatus = QualityCheckerStatus.OK;
                        }
                        else if ("2".Equals(ViewData["checker_" + qualityChecker.Id]))
                        {
                            qcStatus = QualityCheckerStatus.NOT_OK;
                        }
                        else if ("3".Equals(ViewData["checker_" + qualityChecker.Id]))
                        {
                            qcStatus = QualityCheckerStatus.NA;
                        }
                    }

                    if ((col - 1) % 3 == 0)
                    {
            %>
            <tr class="<%=row % 2 == 0 ? "qc_item_even" : "qc_item_odd"%>">
                <%
                    }

                    if ((Model.Review.Status != ReviewStatus.DELIVERED && Model.Status != FileStatus.OLD_VERSION) && isReviewer  && !admin)
                    {
                %>
                <td width="33%" style="vertical-align: middle; height: 20px;">
                    <span tooltip="<%=qualityChecker.Description %>" style="cursor: help">
                        <%=qualityChecker.Name%></span>
                </td>
                <td nowrap="nowrap">
                    <input name="checker_<%=qualityChecker.Id%>" value='1' id="OK_<%=qualityChecker.Id%>"
                        type="radio" <%=qcStatus == QualityCheckerStatus.OK ? "checked" : ""%> />
                    <label for="OK_<%=qualityChecker.Id%>">
                        OK</label>
                </td>
                <td nowrap="nowrap">
                    <input name="checker_<%=qualityChecker.Id%>" value='2' id="NotOK_<%=qualityChecker.Id%>"
                        type="radio" <%=qcStatus == QualityCheckerStatus.NOT_OK ? "checked" : ""%> />
                    <label for="NotOK_<%=qualityChecker.Id%>">
                        Not OK</label>
                </td>
                <td nowrap="nowrap">
                    <input name="checker_<%=qualityChecker.Id%>" value='3' id="NA_<%=qualityChecker.Id%>"
                        type="radio" <%=qcStatus == QualityCheckerStatus.NA ? "checked" : ""%> />
                    <label for="NA_<%=qualityChecker.Id%>">
                        N/A</label>
                </td>
                <%
                    }
                    else
                    {
                %>
                <td width="33%" style="vertical-align: middle; height: 20px;">
                    <span tooltip="<%=qualityChecker.Description %>" style="cursor: help">
                        <%=qualityChecker.Name%></span>
                </td>
                <td nowrap="nowrap" class="<%=qcStatus == QualityCheckerStatus.OK ? "qc_status_on" : "qc_status_off"%>">
                    OK
                </td>
                <td nowrap="nowrap" class="<%=qcStatus == QualityCheckerStatus.NOT_OK ? "qc_status_on" : "qc_status_off"%>">
                    Not OK
                </td>
                <td nowrap="nowrap" class="<%=qcStatus == QualityCheckerStatus.NA ? "qc_status_on" : "qc_status_off"%>">
                    N/A
                </td>
                <%
                    }

                    if ((col - 1) % 3 < 2)
                    {
                %>
                <td style="background-color: #FFFFFF;">
                </td>
                <%
                    }

                    if (col % 3 == 0)
                    {
                %>
            </tr>
            <%
                }
                }
            %>
        </table>
    </fieldset>
    <fieldset>
        <legend>Diff</legend>
        <div id="diffOptions" style="margin-bottom: 5px; float: left;">

            Diff view type:
            <input type="radio" name="viewtype" id="sidebyside" value="sideBySide" <%= (ViewData["viewtype"] != null && ViewData["viewtype"].Equals("sidebyside")) ? "" : "checked='checked'" %> onclick="submitIndexForm();"/>
            <label for="sidebyside">
                Side by Side
            </label>
            <input type="radio" name="viewtype" id="inline" value="inLine" <%= (ViewData["viewtype"] != null && ViewData["viewtype"].Equals("inLine")) ? "checked='checked'" : "" %> onclick="submitIndexForm();"/>
            <label for="inline">
                Inline
            </label>
            &nbsp;&nbsp;
           
            <input type="checkbox" name="ignoreEmptyLine" id="ignoreEmptyLine" <%= (ViewData["ignoreEmptyLine"] != null && ViewData["ignoreEmptyLine"].Equals("on")) ? "checked='checked'" : "" %> onchange="submitIndexForm();"/>
            <label for="ignoreEmptyLine">
                Ignore empty lines
            </label>
       
            &nbsp;&nbsp;
            Show
            <select size="1" id="contextSize" name="contextSize" onchange="submitIndexForm();">
                <option <%= (ViewData["contextSize"] != null && ViewData["contextSize"].Equals("1")) ? "selected='selected'" : "" %> >1</option>
                <option <%= (ViewData["contextSize"] != null && ViewData["contextSize"].Equals("2")) ? "selected='selected'" : "" %> >2</option>
                <option <%= (ViewData["contextSize"] != null && ViewData["contextSize"].Equals("5")) ? "selected='selected'" : "" %> >5</option>
                <option <%= (ViewData["contextSize"] != null && ViewData["contextSize"].Equals("10")) ? "selected='selected'" : "" %> >10</option>
                <option <%= (ViewData["contextSize"] != null && ViewData["contextSize"].Equals("25")) ? "selected='selected'" : "" %> >25</option>
                <option <%= (ViewData["contextSize"] != null && ViewData["contextSize"].Equals("50")) ? "selected='selected'" : "" %> >50</option>
                <option <%= (ViewData["contextSize"] != null && ViewData["contextSize"].Equals("100")) ? "selected='selected'" : "" %> >100</option>
                <option <%= (ViewData["contextSize"] != null &&  ViewData["contextSize"].Equals("All")) ? "selected='selected'" : "" %> >All</option>
            </select>
            line(s) around each change

        </div>
        
        &nbsp;&nbsp;

        <div id="highlightCode" style="float: right;">
            <a href="" onclick="sh_highlightDocument('<%=ResolveUrl("/Content/syntax_highlighting/sh_lang/") %>','.js'); return false;">
                Highlight code</a> (this may take a while for big files)<br />
        </div>
        <div id="diffoutput" style="overflow: auto; width: 100%; height: 500px; margin-top: 25px;
            margin-bottom: 10px;">
            <%= ViewData["diff"] %>
        </div>
        <div id="diffNavigation" style="text-align: center;">
            <a id="fc" onclick="firstChange();" class="pageNav">
                <img id="firstchange" src="<%=ResolveUrl("~/Content/images/nav_first_disabled.png")%>" /></a>&nbsp;
            <a id="pc" onclick="prevChange();" class="pageNav">
                <img id="prevchange" src="<%=ResolveUrl("~/Content/images/nav_prev_disabled.png")%>" /></a>&nbsp;
            <span id="anchorActual"></span>&nbsp; <a id="nc" onclick="nextChange();">
                <img id="nextchange" src="<%=ResolveUrl("~/Content/images/nav_next.png")%>" /></a>&nbsp;
            <a id="lc" onclick="lastChange();">
                <img id="lastchange" src="<%=ResolveUrl("~/Content/images/nav_last.png")%>" /></a>
        </div>
    </fieldset>
     <% Html.EndForm(); %>
    <%Html.BeginForm("SaveFile", "File", FormMethod.Post); %>    
    
    <%
    foreach (QualityChecker qualityChecker in qualityCheckers)
    {
        if ((qualityChecker.DeletionDate != null && Model.CreationDate.CompareTo(qualityChecker.DeletionDate) > 0) ||
            (Model.LastChangeDate.CompareTo(qualityChecker.CreationDate) < 0 && (Model.Review.Status == ReviewStatus.DELIVERED || !isReviewer)))
        {
            continue;
        }
    %>
        <input type="hidden" name="checker_<%=qualityChecker.Id%>" value="" id="checker_<%=qualityChecker.Id%>"/>
    <%
    }
    %>
    
    <input type="hidden" name="urlNextFile" id="urlNextFile" value="<%=ViewData["urlNextFile"]%>"/>
    
    <%
        if (Model.Review.Status != ReviewStatus.DELIVERED && Model.Status != FileStatus.OLD_VERSION && Page.User.Identity.Name == Model.Review.Reviewer && !admin)
        {
    %>
    <fieldset>
        <legend>Finish file review</legend>Comment:<br />
        <input type="hidden" name="return" id="return" value="" />
        <input type="hidden" name="fileId" value="<%=Model.Id %>" />
        <textarea name="comment" rows="4" style="width: 100%; font-size: small; font-family: Verdana;"><%= Model.Comment%></textarea>
        <input type="hidden" value="" id="submitButton" name="submitButton" />
        <div style="text-align: right">
            <button type="button" value="Approve" name="submitButton" onclick="validateQualityChecker(1)"
                style="height: 30px;">
                <img src="<%=ResolveUrl("~/Content/images/tick-circle-frame.png")%>" alt="" align="top" />
                Approve
            </button>
            <button type="button" value="Reject" name="submitButton" onclick="validateQualityChecker(2)"
                style="height: 30px;">
                <img src="<%=ResolveUrl("~/Content/images/cross-circle-frame.png")%>" alt="" align="top" />
                Reject
            </button>
        </div>
        <div id="qualityCheckerError" style="display: none;">
            <strong style="color: Red">PLEASE MARK ALL THE QUALITY CHECKERS </strong>
        </div>
    </fieldset>
    <%
        }
        else if (!string.IsNullOrEmpty(Model.Comment))
        {
    %>
    <fieldset>
        <legend>Comment</legend>
        <p>
            <%= Html.Encode(Model.Comment)%>
        </p>

    </fieldset>
    <%}%>
    <%Html.EndForm(); %>

    <script type="text/javascript">
        fireChange();
        //document.getElementById('loading').style["display"] = "none";
        jQuery.unblockUI();
    </script>
      <div id="dialog" style="visibility:hidden" title="Make changes?">
        <p style="margin-bottom:auto;margin:0px 0px 0px 0px">
            <span class="ui-icon ui-icon-alert" style="float: left; margin: 0 7px 20px 0;"></span>
           Do you want to review the next pending file?</p>
      </div>

</asp:Content>
<asp:Content ID="Content3" ContentPlaceHolderID="JavascriptContent" runat="server">
    <script type="text/javascript" src="<%=ResolveUrl("~/Content/syntax_highlighting/sh_main.js")%>" ></script>
    <script type="text/javascript" src="<%=ResolveUrl("~/Scripts/jquery.blockUI.js")%>" ></script>
    <script type="text/javascript" src="<%=ResolveUrl("~/Scripts/qTip/jquery.qtip-1.0.0-rc3.js")%>" ></script>
    <script type="text/javascript" src="<%=ResolveUrl("~/Scripts/jquery-ui-1.7.2.custom.min.js")%>" ></script>

    <script type="text/javascript">
 
        jQuery(document).ready(function()
        {
            jQuery('#qualityCheckers span[tooltip]').each(function()
            {
                jQuery(this).qtip({
                    content: jQuery(this).attr('tooltip'),
                    style: {
                        name: 'light',
                        tip: {
                            corner: 'bottomLeft',
                            color: '#5c87b2'
                        },
                        border: {
                            width: 1,
                            radius: 4,
                            color: '#5c87b2'
                        },
                    },
                    position: {
                        corner: {
                            target: 'topRight',
                            tooltip: 'bottomLeft'
                        }
                   }
                });
            });
        });
 
        <%
        if (Model.Review.Status != ReviewStatus.DELIVERED && Model.Status != FileStatus.OLD_VERSION && Page.User.Identity.Name == Model.Review.Reviewer)
        {
            QualityCheckerRepository qualityCheckerRepository = QualityCheckerRepository.Instance;
            IList<QualityChecker> qualityCheckers = qualityCheckerRepository.GetAll();
        %>
           
           
            function validateQualityChecker(type) {
            document.getElementById("dialog").style.visibility="visible";
            jQuery("#dialog").dialog('open');
         
                var value;
                <%
                foreach (QualityChecker qc in qualityCheckers)
                {
                    if (qc.DeletionDate == null || Model.CreationDate.CompareTo(qc.DeletionDate) <= 0)
                    {
                %>
                        if (!document.getElementById('OK_<%=qc.Id%>').checked &&
                            !document.getElementById('NotOK_<%=qc.Id%>').checked &&
                            !document.getElementById('NA_<%=qc.Id%>').checked)
                        {
                            document.getElementById("qualityCheckerError").style["display"] = "";
                            jQuery("#qualityCheckerError").effect("pulsate");
                            document.getElementById("dialog").style.visibility="hidden";
                            return;
                        } else {
                            document.getElementById('checker_<%=qc.Id%>').value = 
                                document.getElementById('OK_<%=qc.Id%>').checked ? 1 :
                                document.getElementById('NotOK_<%=qc.Id%>').checked ? 2 : 
                                document.getElementById('NA_<%=qc.Id%>').checked ? 3 : 0;
                        }
                <%
                    }
                }
                FileRepository fRepository = new FileRepository();
                IList<File> allFiles = fRepository.GetAllFiles(Model.Review.Id, false);
                bool isPending = false;
                foreach (File fileAux in allFiles)
                {
                    if (fileAux.Status == FileStatus.PENDING && fileAux.Id != Model.Id)
                    {
                        %> value = document.getElementById("urlNextFile");
                        value.value = <%=fileAux.Id%>
                        <%
                        isPending = true;
                        break;
                    }
                }%>
                
                 if(type==1){
                    document.getElementById("submitButton").value="Approve";
                }else{
                    document.getElementById("submitButton").value="Reject";
                }<%
                 if (!isPending)
                {%>
                    document.getElementById("dialog").style.visibility="hidden";
                    document.getElementById("return").value="no";
                    document.forms[1].submit();
                <%
               
                }
                else {%>
               
               
         
               jQuery(document).ready(
                function() {
                jQuery("#dialog").dialog({
                    autoOpen: true,
                    resizable: false,
                    height: 180,
                    modal: true,
                    buttons: {
                       'Yes': function() {
                         document.getElementById("return").value="yes";
                         document.getElementById("dialog").style.visibility="hidden";
                         document.forms[1].submit();
                        },
                       'No': function() {
                          document.getElementById("return").value="no";
                          document.getElementById("dialog").style.visibility="hidden";
                          document.forms[1].submit();
                       }
                    }
                });
                });
                                                             
                <%
                }
                %>


            }
        <%
        }
        %>    
        
        function submitIndexForm(){
            //jQuery.blockUI({ message: '<img src="../../Content/images/busy.gif" /><h2>Loading...</h2>' });            
            if(admin.value == "True"){                
                document.forms[0].action = document.forms[0].action + "?isAdmin=true";
            }            
            document.forms[0].submit()
        } 

        function saveComment(line) {
            var commentSeverity = document.getElementsByName("commentSeverity_" + line);           
            var severityId = 0;
            if (commentSeverity[commentSeverity.length - 3].checked) { // Critical
                severityId = 1;
            } else if (commentSeverity[commentSeverity.length - 2].checked) { // Warning
                severityId = 2;
            } else if (commentSeverity[commentSeverity.length - 1].checked) { // Information
                severityId = 3;
            }
           
            if (severityId == 0) {
                alert("Choose severity.");
                return;
            }
           
            var commentText = document.getElementsByName("commentText_" + line);
            commentText = commentText[commentText.length - 1].value;
             
            var auxText = commentText;
             
             //trim completo
            function trim(str) {
                return str.replace(/^\s+|\s+$/g,"");
            }
               
            if(trim(auxText).length == 0)
            {
                alert("Write a comment");
                return;
            }
           
            jQuery('#comment_'+line).block({ message: 'Saving comment...' });
            jQuery.post('<%= ResolveUrl("~/Comment/SaveComment") %>',
                {
                    fileId: <%=Model.Id %>, line: line,
                    severityId: severityId, commentText: commentText
                },
                function(data) {
                    if (eval(data) == "success") {
                        if (severityId == 1) {
                            document.getElementById("line_" + line).className = "withComment_critical";
                        } else if (severityId == 2) {
                            document.getElementById("line_" + line).className = "withComment_warning";
                        } else if (severityId == 3) {
                            document.getElementById("line_" + line).className = "withComment_information";
                        }
                        jQuery("#line_" + line).qtip("hide");
                    }
                    jQuery('#comment_'+line).unblock();
                }, "Json");
        }
       
        function deleteComment(line) {
            jQuery('#comment_'+line).block({ message: 'Deleting comment...' });
           
            jQuery.post('<%= ResolveUrl("~/Comment/DeleteComment") %>',
                { fileId: <%=Model.Id %>, line: line },
                function(data) {
                    if (eval(data) == "success") {
                        document.getElementById("line_" + line).className = "link";
                        jQuery("#line_" + line).qtip("hide");
                       
                        var commentSeverity = document.getElementsByName("commentSeverity_" + line);
                       
                        // Critical
                        commentSeverity[commentSeverity.length - 3].checked = false;
                       
                        // Warning
                        commentSeverity[commentSeverity.length - 2].checked = false;
                       
                        // Information
                        commentSeverity[commentSeverity.length - 1].checked = false;
                       
                        var commentText = document.getElementsByName("commentText_" + line);
                        commentText = commentText[commentText.length - 1];
                        commentText.value = "";
                    }
                    jQuery('#comment_'+line).unblock();
                }, "Json");
        }
        
        var balloonsLoaded = new Array();
	       
        function loadBalloon(lineNumber) {           
            var isLoaded = jQuery.inArray(lineNumber, balloonsLoaded);
           
            if (isLoaded == -1) {
           
                balloonsLoaded.push(lineNumber);
               
                var time = new Date().getTime();
                jQuery('#line_'+lineNumber).qtip(
                    {
                        content: {
                            text:
                                '<div id="comment_'+lineNumber+'">' +
                                <%
                                if (Model.Review.Status != ReviewStatus.DELIVERED && Model.Status != FileStatus.OLD_VERSION && User.Identity.Name == Model.Review.Reviewer)
                                {
                                %>
                                    '<p class="comment">' +
                                        '<b>Severity:</b> ' +
                                        <%
                                        IList<Severity> severities = new SeverityRepository().GetAllSeverities();
                                        foreach (Severity s in severities)
                                        {
                                        %>
                                            '<input type="radio" name="commentSeverity_' + lineNumber + '" id="commentSeverity_' + lineNumber + '_<%= s.Id %>_' + time + '" value="<%= s.Id %>" />' +
                                            '<label for="commentSeverity_' + lineNumber + '_<%= s.Id %>_' + time + '"><%= s.Name %></label>' +
                                        <%
                                        }
                                        %>
                                    '</p>' +
                                    '<p class="comment">' +
                                        '<b>Comment:</b><br/> ' +
                                        '<textarea name="commentText_' + lineNumber + '" rows="6" class="comment" style="width: 99%;"></textarea>' +
                                    '</p>' +

                                    '<input type="button" value="Save" onclick="saveComment(' + lineNumber + ');" />' +
                                    '<input type="button" value="Delete" onclick="deleteComment(' + lineNumber + ');" />'
                                <%
                                }
                                else
                                {
                                %>                           
                                    '<p class="comment">' +
                                        '<b>Severity:</b> ' +
                                        '<span name="commentSeverity_' + lineNumber + '" class="comment"></span>' +
                                    '</p>' +
                                    '<p class="comment">' +
                                        '<b>Comment:</b><br/> ' +
                                        '<textarea name="commentText_' + lineNumber + '" rows="6" class="comment" style="width: 99%;" readonly></textarea>' +
                                    '</p>'
                                <%
                                }
                                %>
                                + '</div>'
                            ,
                            title: {
                                text: 'Comment for line ' + lineNumber,
                                button: '<span id="closeButton">[X]</span>'
                            }
                        },
                        style: {
                            name: 'light',
                            tip: {
                                corner: 'bottomLeft',
                                color: '#5c87b2'
                            },
                            border: {
                                width: 1,
                                radius: 4,
                                color: '#5c87b2'
                            },
                            width: 300
                        },
                        position: {
                            corner: {
                                target: 'rightMiddle',
                                tooltip: 'bottomLeft'
                            },
                            adjust: {
                                screen: true
                            }
                        },
                        show: {
                            when: 'click',
                            solo: true
                        },
                        hide: 'inactive',
                        api: {
                            beforeShow: function(event)
                            {
                                showBalloon(lineNumber);
                            }
                        }
                    });
            }           
        }
        
        function showBalloon(line) {
            var th = document.getElementById("line_"+line);
            if (th != null)
            {
                var thClass = th.getAttribute("class");
                if (thClass != null)
                {
                    if (thClass.indexOf("withComment") > -1)
                    {
                        jQuery('#comment_'+line).block({ message: 'Loading comment...' });
                       
                        jQuery.post('<%= ResolveUrl("~/Comment/GetComment") %>',
                        { fileId: <%=Model.Id %>, line: line },
                        function(data) {
                            var comment = $(eval("[" + data + "]"))[0];
                           
                            var commentSeverity = document.getElementsByName("commentSeverity_" + line);           
                           
                            var commentText = document.getElementsByName("commentText_" + line);
                            commentText = commentText[commentText.length - 1];
                           
                            <%
                            if (Model.Review.Status != ReviewStatus.DELIVERED && Model.Status != FileStatus.OLD_VERSION && User.Identity.Name == Model.Review.Reviewer)
                            {
                            %>
                                // Critical
                                commentSeverity[commentSeverity.length - 3].checked = (comment.SeverityId == 1);
                               
                                // Warning
                                commentSeverity[commentSeverity.length - 2].checked = (comment.SeverityId == 2);
                               
                                // Information
                                commentSeverity[commentSeverity.length - 1].checked = (comment.SeverityId == 3);
                            <%
                            }
                            else
                            {                 
                            %>
                                commentSeverity = commentSeverity[commentSeverity.length - 1];
                                commentSeverity.innerHTML = comment.SeverityName;
                            <%
                            }
                            %>
                           
                            commentText.value = comment.CommentText;                                 
                            jQuery('#comment_'+line).unblock();
                        }, "Json");                       
                    }
                }
            }
        }
         
        //Diff navigation
        var anchorCount = <%=ViewData["anchorCount"] %>;
         
        //Diff navigation
        var anchorActual = 0;
        function firstChange() {
            anchorActual = 1;
            fireChange();
        }

        function prevChange() {
            anchorActual--;
            if (anchorActual < 1)
                anchorActual = 1;
            fireChange();
        }

        function nextChange() {
            anchorActual++;
            if (anchorActual > anchorCount)
                anchorActual = anchorCount;
            fireChange();
        }

        function lastChange() {
            anchorActual = anchorCount;
            fireChange();
        }

       function fireChange() {
            if (anchorActual >= 1 && anchorActual <= anchorCount) {
                document.location = "#change_" + anchorActual;
                if (anchorActual == anchorCount) {           
                    document.getElementById("lastchange").setAttribute("src", "<%=ResolveUrl("~/Content/images/nav_last_disabled.png")%>");                                             
                    document.getElementById("nextchange").setAttribute("src", "<%=ResolveUrl("~/Content/images/nav_next_disabled.png")%>");   
                    document.getElementById("lc").className = document.getElementById("nc").className = 'pageNav';                 
                } else {
                    document.getElementById("lastchange").setAttribute("src", "<%=ResolveUrl("~/Content/images/nav_last.png")%>");             
                    document.getElementById("nextchange").setAttribute("src", "<%=ResolveUrl("~/Content/images/nav_next.png")%>");
                    document.getElementById("lc").className = document.getElementById("nc").className = '';               
                }
                       
                if (anchorActual == 1) {
                    document.getElementById("firstchange").setAttribute("src", "<%=ResolveUrl("~/Content/images/nav_first_disabled.png")%>");             
                    document.getElementById("prevchange").setAttribute("src", "<%=ResolveUrl("~/Content/images/nav_prev_disabled.png")%>");
                    document.getElementById("fc").className = document.getElementById("pc").className = 'pageNav';
                } else {
                    document.getElementById("firstchange").setAttribute("src", "<%=ResolveUrl("~/Content/images/nav_first.png")%>");             
                    document.getElementById("prevchange").setAttribute("src", "<%=ResolveUrl("~/Content/images/nav_prev.png")%>");
                    document.getElementById("fc").className = document.getElementById("pc").className = '';
                }
            }
           
            if (anchorActual == 0) {
                if(anchorCount == 1)
                    jQuery("#anchorActual").text("Navigate through " + anchorCount + " change");
                else               
                    jQuery("#anchorActual").text("Navigate through " + anchorCount + " changes");
            } else {
                jQuery("#anchorActual").text("Change " + anchorActual + " of " + anchorCount);
            }
        }
    </script>

</asp:Content>
<asp:Content ID="Content4" ContentPlaceHolderID="CSSContent" runat="server">
    <link href="<%=ResolveUrl("~/Content/review.css")%>" rel="stylesheet" type="text/css" />
   
    <link href="<%=ResolveUrl("~/Scripts/jquery-ui-1.7.2/themes/redmond/jquery-ui-1.7.2.custom.css")%>"
        rel="stylesheet" type="text/css" />
       
    <!-- Syntax highlight -->
    <link type="text/css" rel="stylesheet" href="<%=ResolveUrl("~/Content/syntax_highlighting/sh_css/sh_style.css")%>" />
   
    <!-- Diff -->
    <link rel="stylesheet" type="text/css" href="<%=ResolveUrl("~/Content/diff/diffview.css")%>" />
   
    <style type="text/css">
        p
        {
            margin-bottom: 100px;
            line-height: 1.1em;
        }
   
        #diffNavigation a.pageNav
        {
            cursor: default;                       
        }
   
        #qualityCheckers p
        {
            margin: 0px 0px 3px 0px;
            font-family: Verdana;
            font-size: x-small;
        }
        .title
        {
            margin: 0px 0px 3px 0px;
            font-size: small;
            font-family: Verdana;
            font-weight: bolder;
        }
        .comment
        {
            margin: 0px 0px 3px 0px;
            font-family: Verdana;
            font-size: x-small;
        }
        
        .transparent_class {
	        filter:alpha(opacity=50);
	        -moz-opacity:0.5;
	        -khtml-opacity: 0.5;
	        opacity: 0.5;
        }
        .wordwrap  
        {  
            -moz-binding: url('~/Scripts/wordwrap.xml#wordwrap');  
        }       
    </style>
</asp:Content>
<asp:Content ID="Content5" ContentPlaceHolderID="HeadContent" runat="server">
</asp:Content>