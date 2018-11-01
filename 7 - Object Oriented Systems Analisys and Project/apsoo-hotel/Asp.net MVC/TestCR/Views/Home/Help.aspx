<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage" %>
<asp:Content ID="Content1" ContentPlaceHolderID="HeadContent" runat="server">
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="JavascriptContent" runat="server">
	<script type="text/javascript" src="<%=ResolveUrl("~/Content/syntax_highlighting/sh_main.js")%>"></script>

	<script type="text/javascript">
		function init() {
			sh_highlightDocument('/Content/syntax_highlighting/sh_lang/','.js');
		}
		window.onload = init;
	</script>

</asp:Content>

<asp:Content ID="Content3" ContentPlaceHolderID="CSSContent" runat="server">
<link type="text/css" rel="stylesheet" href="../../Content/syntax_highlighting/sh_css/sh_style.css" />
<style>
    p 
    {
    	text-align:justify;
    }
</style>
</asp:Content>

<asp:Content ID="Content4" ContentPlaceHolderID="TitleContent" runat="server">
	Help
</asp:Content>

<asp:Content ID="Content5" ContentPlaceHolderID="MainContent" runat="server">

    <h2 id="top">Help</h2>
    <h3>Contents</h3>
    <ul>
      <li><a href="#basic_concepts">Basic concepts</a>
        <ul>
          <li><a href="#what_is_code_review">What is code review</a></li>
          <li><a href="#roles">Roles</a></li>
          <li><a href="#review">Review</a>
            <ul>
              <li><a href="#review_statuses">Review statuses</a></li>
            </ul>
          </li>
          <li><a href="#file">File</a>
            <ul>
              <li><a href="#file_statuses">File statuses</a></li>
            </ul>
          </li>
          <li><a href="#quality_checkers">Quality checkers</a></li>
        </ul>
      </li>
    </ul>
    <ul>
      <li><a href="#review_actions">Review actions</a>
        <ul>
          <li><a href="#how_to_request">How to request a review</a></li>
          <li><a href="#how_to_review">How to review a request</a></li>
        </ul>
      </li>
    
      <li><a href="#metrics">Metrics</a>
        <ul>
          <li><a href="#what_is_a_metric">Structure of Code Review Metrics</a></li>
          <li><a href="#initial_metrics">Initial metrics </a></li>
          <li><a href="#create_metric">How to create a new metric</a></li>
          <li><a href="#metric_report">How to generate a metric report</a></li>
        </ul>
      </li>
    </ul>
  <ul>
    <li><a href="#administration">Administration</a>
      <ul>
          <li><a href="#managing_quality_checkers">Managing quality checkers</a></li>
        <li><a href="#managing_reviews">Managing reviews</a></li>
          <li><a href="#configuring_the_database">Configuring the database</a></li>
          <li><a href="#configuring_the_email">Configuring the e-mail</a></li>
      </ul>
    </li>
  </ul>
    <br />
<hr />
    <br />
    
    <h2 id="basic_concepts">Basic concepts</h2>
    <h3 id="what_is_code_review">What is code review</h3>
    <p>
        Code review is a worldwide widespread technique that can be employed in order to find defects in the early stages
        of software development, thus helping to improve the software quality. Not only bugs can be detected more easily
        but also other important quality issues as conformance to coding standards, code complexity, etc. may be evaluated
        by the reviewers.    </p>
    <p>
        Additionally, the code review process yields benefits to the people involved. Since the review process constitutes
        a dialog between a software developer and a (generally more experienced) reviewer, there is a constant feedback
        from experienced developers to the newer ones. The experienced developers are also challenged to find the greater
        amount of defects as possible and report them to the developers.</p>
     
     <h3 id="roles">Roles</h3>
     <p> An user may hold one or more of the following roles in Code Review:  Reviewer, Developer, Administrator and Project Manager.</p>
    <p>
      The administrator can
      <a href="#managing_quality_checkers">manage quality checkers</a>, <a href="#configuring_the_database">configure database</a> 
      and <a href="#managing_reviews">manage all reviews</a>. The project manager can only <a href="#managing_reviews">manage reviews</a> of the projects that he or she manages. The reviewer can perform all tasks of <a href="#how_to_review">reviewing a request</a>.
       The developer can see the review attributes without modifying them.</p>
    <h3 id="review">Review</h3>
    <p>The review is the main entity in the code review process. It is composed of the following attributes:</p>
    <ul>
      <li><strong>Project -</strong> The project name preceded by the ClearCase server address and PVOB name.</li>
      <li><strong>Activity -</strong> The ClearCase activity represented by the review.</li>
      <li><strong>Developer -</strong> The developer who requested the review.</li>
      <li><strong>Reviewer -</strong> The reviewer responsible for the review.</li>
      <li><strong>Creation date -</strong> The date and time when the review was created.</li>
      <li><strong>Last change date -</strong> The date and time when the review was last changed.</li>
      <li><strong>Status -</strong> The <a href="#review_statuses">review status</a>.</li>
      <li><strong>Message -</strong> The message written by the developer when he or she requested the review.</li>
      <li><strong>Files -</strong> the file(s) to be reviewed.</li>
      <li><strong>Comment -</strong> a comment that the reviewer can write about the review.</li>
    </ul>
    
    <p>All reviews owned by an user can be found in the Dashboard. If the user owns a review as a reviewer, the review is displayed 
        in My Reviews tab, and if the user owns a review as a developer, the review is displayed in My Requests tab. By clicking in a review, the user can see the review attributes and <a href="#file">files</a>.</p>
  <h4 id="review_statuses">Review statuses</h4>
    <p>A review may have one of 
    the following statuses: pending, in review, approved, rejected or delivered as depicted in the figure below.</p>
    <div style="text-align:center">
	    <img src="<%=ResolveUrl("~/Content/images/review_statuses.png") %>"/>	</div>
  <p> If a review is pending, it means that no work has been 
      done by the reviewer yet. The respective line in Dashboard table will appear in 
      grey color. When a reviewer opens any review file for the first time, the review status is 
      changed to &quot;in review&quot;, and its color in the Dashboard  turns to yellow. If the reviewer
      approves all the files in the review, the review status is changed to &quot;approved&quot; and 
      its color turns to green in the Dashboard. If the reviewer rejects one or more files in
      the review, the review status is changed for &quot;rejected&quot; and its color turns to red.</p>
  <p>A review
      can only be approved or rejected if all files are reviewed. After delivered 
      in Clear Case, the review status is changed to &quot;delivered&quot; and its corresponding color in Dashboard becomes light blue. Only approved reviews 
      may be delivered.</p>
  <h3 id="file">File</h3>
  
    <p>Each file from a review has the following attributes:</p>
    <ul>
      <li><strong>Review -</strong> The review that contains the file.</li>
      <li><strong>Project -</strong> The project name preceded by the ClearCase server address and PVOB name.</li>
      <li><strong>Activity -</strong>The ClearCase activity represented by the review that contains the file.</li>
      <li><strong>Developer -</strong> The developer who requested the review.</li>
      <li><strong>Reviewer -</strong> The reviewer responsible for the review.</li>
      <li><strong>Creation date -</strong> The date and time when the review that contains the file was created.</li>
      <li><strong>Last change date -</strong> The date and time when the file was last changed.</li>
      <li><strong>Status -</strong> The <a href="#file_statuses">file status</a>.</li>
      <li><strong>File path -</strong> The original file path (in the developer's computer).</li>
      <li><strong>Quality checkers -</strong> The list of quality checkers.</li>
      <li><strong>File(s) content -</strong> if the file is new, just the file text is shown. If the file was modified, the differences are shown.</li>
      <li><strong>Line comments - </strong>The comments writtern by the reviewer in the file lines.</li>
      <li><strong>Comment -</strong> A comment that the reviewer can write about the file.</li>
    </ul>
  <p>All review files are showed when clicking on a review link. Filters are available to easy 
        the search of a specific file, and the files are displayed with distinct color according with status,
    improving visualization.</p>
    <div style="text-align:center">
        <img style="width:70%" src="<%=ResolveUrl("~/Content/images/files.png") %>" />    </div>
    <h4 id="file_statuses">File statuses</h4>
    <p>The file statuses may be pending, approved or rejected. If a file was not reviewed, it is
    "pending" and displayed with grey color. If the file was reviewed and approved, the status is changed
    to "approved" and the color turns to green. If the file was reviewed and not approved, the status
    is changed to "rejected" and the color turns to red.</p>
    <h3 id="quality_checkers">Quality checkers</h3>
    <p>Quality checkers are important topics that can help the reviewers to guide the inspection pointing out what aspects of code should be verified. For the developers, the quality checkers are important because they provide an overview of which are the main defects that the reviewers will check in order to approve or reject the file.</p>
    <p>A table containing all the quality checkers appears for every file right above the code. Each quality checker can have a description that is showed when the mouse pointer is over the quality checker name. The reviewer has to check each one marking them as OK, Not OK or N/A (not applicable). 
    The file will only be approved or disapproved if all the quality checker are marked.</p>
    <p>The administrator is able to create, edit and delete quality checkers in the <a href="#managing_quality_checkers">Administration</a> page.</p>
  <h2 id="review_actions">Review actions</h2>
    <h3 id="how_to_request">How to request a review</h3>
    <p>There are two ways to request a new review, both using the client application 
        that must be installed on computer:</p>
    <h4>Clear Case client context menu</h4>
    <p>In the context menu of Clear Case client, on the view directories, will appear a option &quot;LGE 
        Code Review...&#39; after instalation of the client application. This option 
        enables to make review requests for activties from a view.</p>
    <div style="text-align:center">
        <img src='<%=ResolveUrl("~/Content/images/context_menu.png") %>' style="height:30%" />
    </div>
    <p>The client window looks like the peicture below. The informations about the view 
        are shown in the top rigth side. The available activities able to review are listed in the top left side.
        Note that you must be the owner of the view and the user identity is getted by Windows authentication.</p>
    <div style="text-align:center">
        <img src='<%=ResolveUrl("~/Content/images/request_window_01.png") %>' style="height:70%" />
    </div>
    <p>So, the user can select one or more activities and a reviewer for them or one 
        reviewer for each activity and add them in the activity list to review 
        &quot;Activities to Review&quot;. After that, the user may put some message to reviewer(s) 
        and send the request.</p>
    <div style="text-align:center">
        <img src='<%=ResolveUrl("~/Content/images/add_activity.png") %>' style="height:30%" />
    </div>
        <div style="text-align:center">
        <img src='<%=ResolveUrl("~/Content/images/send_request.png") %>' style="height:30%" />
    </div>
        <div style="text-align:center">
        <img src='<%=ResolveUrl("~/Content/images/no_activities.png") %>' style="height:30%" />
    </div>
    <h4>Clear Case delivery trigger</h4>
    <p>
    If the project is configurated to use the Code Review system, all time you try to deliver activities the Code Review Trigger will be executed. 
    This trigger verifies if the activities was reviewed or are in review, if not, the Code Review Client will be openned in the same way that by the context menu, 
    but only with the delivery activities, not all of the view.  
    </p>
    <h3 id="how_to_review">How to review a request</h3>
    <p>The reviews are listed in the Dashboard as shown in the picture below.</p>
  <div style="text-align:center">
        <img style="width:70%" src="<%=ResolveUrl("~/Content/images/DashboardHome.png") %>" />    </div>
    <p>    Selecting a review in the Dashboard takes the user to the review page where there is a  list containing the review files as shown in the picture below. If the review is pending, its stauts will be  changed to &quot;in review&quot;  when the reviewer opens any  file for the first time.</p>
<div style="text-align:center">
        <img style="width:70%" src="<%=ResolveUrl("~/Content/images/review_page.png") %>" />    </div>
    <p>By clicking in one of the files, the reviewer starts a file review 
    where he or she must mark the quality checkers and can optionally write comments.</p>
    <p> The file content is shown in the Diff field (see the image below).</p>
  <div style="text-align:center"> <img src="<%=ResolveUrl("~/Content/images/newDiff.png") %>" /> <br />
        <img src="<%=ResolveUrl("~/Content/images/jumpChanges.png")%>" /> </div>
  <p>It is possible to 
  highlight the code by clicking on the Highlight code link. However, the highlighting process may take a while if there is a large amout of lines currently being displayed. The languages supported are C, C++, C#, CSS, HTML, Java, Javascript, Pascal, PHP, Perl, Properties, Phyton, Ruby, SQL, and XML. If a file is not supported, the Highlight code option will not work and the file content will be shown as normal text.</p>
  <p>It is possible to navigate
  through changes using the navigation buttons located at the bottom of the file contents. All file changes are highlighted: the  added text is marked as green, the changed text is marked as yellow, and the removed text is marked as red.</p>
  <p>Regarding the file content visualization, the user can
    choose how many lines are showed around the changes and how the differences are shown: side by side or inline. In the side by side mode, the previous version of the file  is shown at the left side and the new file content is shown at the right side of the page. In the inline mode, the two file versions are shown as if it was one file and the differences are shown one above the other.</p>
  <p>By clicking on a line number in the file differences, a reviewer can write a comment.
  The reviewer has to select a severity level  for each comment. The possible severities are Information, Warning, and Critical. After choosing the severity and writting the comment, the reviewer has to save the comment. The reviewer can also delete the comments. The developer can only see the reviewer's comments.</p>
  <p>If the current file has already been reviewed, it will be shown link(s) to the older version(s) of it where the reviewer will be able to see the comments that he or she wrote at that time. This feature only works for the reviewer.</p>
  <p>After finishing the file inspection,
    the reviewer must approve or reject the file. A file only can be approved or rejected when all the
    quality checkers are marked. Additionally, the reviewer can write a general comment about the file before he or she approves or rejects the file.</p>
  <p>All files must be reviewed before finishing a review.</p>
  <h2 id="metrics">Metrics</h2>
    <h3 id="what_is_a_metric">Structure of Code Review Metrics</h3>
    <p>Code Review metrics are DLLs that follow the  structure bellow:</p>
    <ul>
      <li>Crystal  Report file;</li>
      <li>Entity  class;</li>
      <li>Main  class that implements the IMetric interface.</li>
    </ul>
    <p>Code Review shows all metrics (DLLs) that are  stored in the bin directory of the web application server.</p>
    <h3 id="initial_metrics">Initial metrics</h3>
    <p>Code Review has some metrics by default. These are the metrics already available:</p>
    <ul>
      <li> <strong>Comments by Severity </strong>- Counts and shows the comments of reviews grouped by severity. </li>
      <li> <strong>Inspection Time </strong>- Counts and shows the reviews grouped by time spent in the inspection process. </li>
      <li> <strong>Pending Time </strong>- Counts and shows the reviews grouped by time spent while their status were &ldquo;pending&rdquo;, that is, the interval between the review request and the start of the inspection process. </li>
      <li> <strong>Quality Checkers Disapproved </strong>- Counts and shows the reviews disapproved quality checkers. </li>
      <li> <strong>Reviews by Developer </strong>- Counts and shows the reviews grouped by developer. </li>
      <li> <strong>Reviews by Reviewer </strong>- Counts and shows the reviews grouped by reviewer. </li>
      <li> <strong>Reviews by Status </strong>- Counts and shows the reviews grouped by status. </li>
      <li> <strong>Total Time </strong>- Counts and shows the reviews grouped by time spent in the code review process. </li>
    </ul>
    <h3 id="create_metric">How to create a new metric</h3>
    <p>To create a new metric, the user must follow the following steps:</p>
    <ul>
        <li>
            <strong>Create a new Project on Visual Studio:</strong>
            <ul >
                <li >
                    Go to File -> New -> Project…
                    <div style="text-align:center"><img  src="<%=ResolveUrl("~/Content/images/newProject.png")%>" /></div>
                </li>
                <li >
                    Choose Visual C# Windows project type and then choose the Class Library template
                     <div style="text-align:center"><img src="<%=ResolveUrl("~/Content/images/classLibrary.png")%>" /></div>
                </li>
                <li >
                    Define the project name and directory and then click OK                </li>
           </ul>     
        </li>
    </ul>
    <ul>
        <li>
           <strong>  Add the Entity Class in the Project</strong>
            <ul>
                <li >
                    Create the entity class that must declare all properties and/or fields that the user wants to use in the report as shown below.
<pre class="sh_cs">
    namespace CodeReview.Metric.Default
    {
        public class ReviewsReport 
        {
            public int Id { get; set; }
            public DateTime CreationDate { get; set; }
            public DateTime LastChangeDate { get; set; }
            public string Developer { get; set; }
            public string Reviewer { get; set; }
            public string Activity { get; set; }
            public string StatusName { get; set; }
        }
    }
</pre>
                </li>
           </ul>     
      </li>
    
       
        <li>
          <strong>    Add Crystal Report file to the project    </strong>  </li>
    </ul>
     <ul>
       <ul>
         <li >
           Create a new item of the Reporting category and then choose the Crystal Report template.
           <div style="text-align:center"><img src="<%=ResolveUrl("~/Content/images/crystal.png")%>" /></div>
              Note: Use as blank Report           </li>
        </ul>
     </ul>
     <ul>
          <li>
            <strong>   Design Crystal Report</strong>
              <ul>
                  <li >
                       Build the solution                  </li>
             </ul>   
             <ul>
                  <li >
                       Define the database fields 
                       <ul>
                           <li>
                              Right click on Database Fields and choose the Database expert option, as shown below.
                              <div style="text-align:center"><img src="<%=ResolveUrl("~/Content/images/designcrystal.png")%>" /></div>
                           </li>
                           <li>
                              Choose “Project Data” and then “.Net Objects” and finally “MetricExample.Entity”, as shown below.
                              <div style="text-align:center"><img src="<%=ResolveUrl("~/Content/images/databaseexport.png")%>" /></div>
                           </li>
                           <li>
                              After that, the user can use all fields of the entity object to design the report, insert groups and add charts. For more details, see <a href="http://download.microsoft.com/download/c/a/1/ca13b7f5-eeaa-409a-84e5-61cac2414361/ASPNET/Demos_CrystalReports_ReportViewer.zip">this movie</a> about Crystal Report.                           </li>
                       </ul>
                  </li>
             </ul>  
          </li>
          </ul>
        
            <ul>
                <li>
                    <strong>  Add references in the project</strong>
                    <ul>
                        <li >
                             CodeReview.Model                        </li>
                        <li>
                             CodeReview.Metric                        </li>
                   </ul>     
                </li>   
            </ul>
            
             <ul>
                <li>
                  <strong>   Develop Main Class</strong>
                    <ul>
                        <li >
                             Create the Main class and implement the IMetric interface, as shown below
 <pre class="sh_cs">
    public class ReviewsByReviewer : IMetric
    {
        public string Name
        {
            get { return "Reviews by Reviewer"; }
        }

        public string Description
        {
            get { return "No description."; }
        }

        public IList<Review> Reviews { get; set; }

        public IList<Element> Elements { ... }

        public IO.MemoryStream ReportStream { ... }
    }
 </pre>
                             <ul>
                                <li>
                                    The Name property determines the name that will be exhibited in the web application.                                </li>
                                <li>
                                    The Description property determines the description that will be exhibited in a tool tip in the web application.                                </li>
                                <li>
                                    The Reviews property determines the list of reviews that will be used to generate the chart and/or the PDF report. This property is set by the search result in the metrics page.                                </li>
                                <li>
                                    The Elements property determines the elements that will be exhibited in the chart. Each Element object has the attributes Name, Value and Color. The following code shows an example of how to list Elements according to the quantity of reviews by developer.
<pre class="sh_cs">
    public IList<Element> Elements
    {
        get
        {
            Dictionary result = new Dictionary();

            foreach (Review review in Reviews)
            {
                if (result.ContainsKey(review.Reviewer))
                {
                    result[review.Reviewer].Value++;
                }
                else
                {
                    result[review.Reviewer] = new Element()
                    {
                        Name = review.Reviewer,
                        Value = 1
                    };
                }
            }

            return new List<Element>(result.Values);
        }
    }
</pre>
                                    </li>
                                <li>
                                    The Report Stream property determines the PDF file stream. The following code is an example of how to create a stream using Crystal Report.
                                    
<pre class="sh_cs">
    public IO.MemoryStream ReportStream
    {
        get
        {
            IList<ReviewsReport> rrs = new List<ReviewsReport>();
            foreach (Review r in Reviews)
            {
                rrs.Add(new ReviewsReport()
                {
                    Activity = Util.Resume(r.Activity,40),
                    Id = r.Id,
                    Reviewer = r.Reviewer,
                    StatusName = r.Status.GetStringValue()
                });
            }

            rrs = rrs.OrderBy(rr => rr.Id).ToList();

            ReportClass report = new ReportReviewsByReviewer();
            report.SetDataSource(rrs);

            return report.ExportToStream(ExportFormatType.PortableDocFormat) as IO.MemoryStream;
        }
    }
</pre>
                                    </li>
                             </ul>
                        </li>
                   </ul>     
                </li>   
            </ul>
    <h3 id="metric_report">How to generate a metric report</h3>
    <p>The metrics page - see figure below - is divided into two main areas: </p>
    <ul>
      <li><strong>Metrics</strong>: shows the list of metrics</li>
      <li><strong>Reviews</strong>: shows the filters and the reviews.</li>
    </ul>
    <p>To generate a metric, the user must choose the  metric, optionally filter the reviews, and finally choose a type of output: Pie  chart or PDF Report.</p>
   <ul><div style="text-align:center"> <img style="width:70%" src="<%=ResolveUrl("~/Content/images/metricsEx.png")%>" /> </div>
     </ul>
    
  <h2 id="administration">Administration</h2>
    <h3 id="managing_quality_checkers">Managing quality checkers</h3>
    <p>The administrator can add a new quality checker, edit or delete the existing ones. When adding a quality checker, the user has to choose a name and a description (both fields are required). </p>
    <p>If a existing quality checker is deleted, the reviews that uses it will still have it. The deleted quality checker will be unavailable only to the reviews created since the quality checker deletion. </p>
    <p>If a new quality checker is added, it will  always be displayed when a reviewer opens a review file. Therefore, this new quality checker will have to be marked by the reviewer even if the file has already been evaluated.</p>
    <h3 id="managing_reviews">Managing reviews</h3>
    <p>The reviews shown in the Review Manager vary according to the user permissions. If the user is an administrator, he or she will be able to see all reviews. If the user is just a project manager, he or she will be able to see only the reviews from the projetc(s) managed by him or her.  Once the user selects a review in the Review Manager, he or she can  modify the reviewer and/or the status . Additionally, the user can see 
        all modifications made in the review by clicking on the Log link.</p>
    <h3 id="configuring_the_database">Configuring the database</h3>
    <p>Only administrators can change database settings. To do it, he or she has to go to the Administrator page and click on 
       Database configuration option. In the database configuration page, the administrator has to fill in all the fields and click on the Test connection or Save button. If the test connection was clicked then the connection will be tested, if it is successfull
       a message appears telling that the connection was sucessfully otherwise the message shows that a connection wasnt be sucessfully tested.
       if the Save button was clicked then the connection will be tested, if the connection was sucessfully tested then it will save otherwise a message appears.</p>
     <h3 id="configuring_the_email">Configuring the e-mail</h3>
    <p>Only administrators can change e-mail settings. To do it, he or she has to go to the Administrator page and click on 
       E-mail configuration option. In the e-mail configuration page, the administrator has to fill in the  required fields: </p>
    <ul>
      <li><strong>From -</strong> The e-mail address that will send the messages.</li>
      <li><strong>From name -</strong> A text that appears on the user's mail box that received the message.</li>
      <li><strong>Server - </strong>The e-mail server address.</li>
    </ul>
    <p>Additionally, he or she can fill in the optional fields: </p>
    <ul>
      <li><strong>Reply To -</strong> The e-mail address that all the messages will be sent.</li>
      <li><strong>Always Cc - </strong> The e-mail address(es)  that will receive a  copy of the e-mail. If more than one e-mail address has to be entered, separate them with semicolons.</li>
      <li><strong>Always Bcc -</strong>  The e-mail address(es)  that will receive a blind copy of the mail. If more than one e-mail address has to be entered, separate them with semicolons.</li>
      <li><strong>User -</strong> The e-mail user name.</li>
      <li><strong>Password -</strong> The e-mail password.</li>
      <li><strong>Subject Prefix -</strong> The text that will appear at the subject of the message followed by the e-mail subject.</li>
      <li><strong>Enable -</strong> If this option is  marked, the action of sending e-mails is activated, otherwise it is disabled.</li>
      <li><strong>Port -</strong> The e-mail  server port.</li>
    </ul>
    <p>and 
      then click on Test or Save email button. If he or she selects the Test button, the entered e-mail configuration will be tested. 
      If he or she selects the Save button, the e-mail configurations will be saved.</p>
      <a href="#" onclick="window.scrollTo(0,0); return false"><img style="display:scroll;position:fixed;bottom:5px;right:5px;float:right" src="<%=ResolveUrl("~/Content/images/top.png")%>" /></a>
</asp:Content>
