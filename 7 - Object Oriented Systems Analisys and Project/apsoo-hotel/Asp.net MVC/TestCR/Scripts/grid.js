var keywordEnterDown = false;

function goToPage(pageIndex) {
    $("#Pager_CurrentPage").val(pageIndex);
    $("#GridAction").val("GoToPage");
    submitForm();
}

function sort(sortField, sortDirection) {
    $("#GridAction").val("Sort");

    $("#Sorter_SortField").val(sortField);
    $("#Sorter_SortDirection").val(sortDirection);

    submitForm();
}

function setcursor(objectId) {
    var temp = document.getElementById(objectId);
    temp.focus();
    temp.value = temp.value;
}

function verifySearchFields() {

    switch ($("#SearchForm_GridType").val()) {
        case "DashBoard":
            if ($("#TypeView").val() == "MyReviews")
                setcursor("SearchForm_Developer");
            else
                setcursor("SearchForm_Reviewer");
            break;
        case "Review":
            setcursor("SearchForm_Name");
            break;
        case "ReviewManager":
            setcursor("SearchForm_Developer");
            break;
        case "Metric":
            setcursor("SearchForm_Developer");
            break;
    }

    if ($("#SearchForm_IsAdvanced").val() == "True" || $("#SearchForm_IsAdvanced").val() == "true") {       
        if ($("#SearchForm_ToDateOfLastChange").val() != null && $("#SearchForm_ToDateOfLastChange").val() != "") {
            setcursor("advanced-search-submit");            
        }
        if ($("#SearchForm_FromDateOfLastChange").val() != null && $("#SearchForm_FromDateOfLastChange").val() != "") {
            setcursor("advanced-search-submit");
        }
        if ($("#SearchForm_ToDateOfCreation").val() != null && $("#SearchForm_ToDateOfCreation").val() != "") {
            setcursor("advanced-search-submit");
        }
        if ($("#SearchForm_FromDateOfCreation").val() != null && $("#SearchForm_FromDateOfCreation").val() != "") {
            setcursor("advanced-search-submit");
        }
        if ($("#SearchForm_Project").val() != null && $("#SearchForm_Project").val() != "") {
            setcursor("SearchForm_Project");
        }
        if ($("#SearchForm_Activity").val() != null && $("#SearchForm_Activity").val() != "") {
            setcursor("SearchForm_Activity");
        }
        if ($("#SearchForm_PVobName").val() != null && $("#SearchForm_PVobName").val() != "") {
            setcursor("SearchForm_PVobName");
        }
        if ($("#SearchForm_PVobServer").val() != null && $("#SearchForm_PVobServer").val() != "") {
            setcursor("SearchForm_PVobServer");
        }
        if ($("#SearchForm_Reviewer").val() != null && $("#SearchForm_Reviewer").val() != "") {
            setcursor("SearchForm_Reviewer");
        }
        if ($("#SearchForm_Developer").val() != null && $("#SearchForm_Developer").val() != "") {
            setcursor("SearchForm_Developer");
        }
        if ($("#SearchForm_Name").val() != null && $("#SearchForm_Name").val() != "") {
            setcursor("SearchForm_Name");
        }
    }
    else {
        setcursor("SearchForm_Keyword");
    }
}

function submitForm() {
    var form = $("#grid").parents("form:first");
    form.submit();
}

function submitFormWithAjax() {
    if ($("#GridAction").val() != "GoToPage") {
        if (!keywordEnterDown) {
            $("#GridAction").val("AdvancedSearch");
            $("#SearchForm_IsAdvanced").val(true);

        } else {
            $("#GridAction").val("KeywordSearch");
            $("#SearchForm_IsAdvanced").val(false);
        }

        keywordEnterDown = false;
    }

    var form = $("#grid").parents("form:first");
    var formData = form.serialize();

    block();



    $.ajax({
        type: "POST",
        url: "_Grid",
        data: formData,
        success: function(newHtml) {
            setTimeout(function() {
                $("#grid").html(newHtml);

                initGrid();
                unblock();
            }, 400);
        },

        error: function(request, textStatus, errorThrown) {
            unblock();
        }
    });

    verifySearchFields();
}

function block() {
    $('#grid #grid-data').block({
        message: '<div class="blockUI-message">Processing...</div>',
        css: { border: 'none', width: 'auto' },
        overlayCSS: { backgroundColor: '#C0C0C0' }
    });

}

function unblock() {
    $('#grid #grid-data').unblock();

}

function initGrid() {
    //Alternative table colors
    $("#grid #grid-data table tr:even").addClass("alt");

    //On mouse over in table row
    $("#grid #grid-data table tr").bind("mouseover mouseout", function() {
        $(this).toggleClass("over");
    });

    $("#Pager_PageSize").change(function() {

        $("#GridAction").val("ChangePageSize");

        submitForm();
    });
}

//Autocomplete and Search Features

jQuery(document).ready(function() {
    initGrid();

    verifySearchFields();

    $("#grid").parents("form:first").submit(function() {
        //if ($("#GridAction").val() == "AdvancedSearch")
        //	return true;

        submitFormWithAjax();
        return false;
    });

    $("#search-form #keyword").click(function() {
        if ($("#search").toggleClass().val() == "") {
            $("#search").toggleClass("collapsed");
            setcursor("SearchForm_Keyword");
        }
        else {
            $("#search").toggleClass("");
        }
    });

    $("#search-form #advanced").click(function() {
        if ($("#filters").toggleClass().val() == "") {
            $("#filters").toggleClass("collapsed");
            verifySearchFields();
        }
        else {
            $("#filters").toggleClass("");
        }
    });

    $("#keyword-search-submit").click(function() {
        keywordEnterDown = true;
        $("#GridAction").val("KeywordSearch");
        $("#SearchForm_IsAdvanced").val(false);
    });

    $("#advanced-search-submit").click(function() {
        if (!keywordEnterDown) {
            $("#GridAction").val("AdvancedSearch");
            $("#SearchForm_IsAdvanced").val(true);

        } else {
            $("#GridAction").val("KeywordSearch");
            $("#SearchForm_IsAdvanced").val(false);
        }

        keywordEnterDown = false;
    });

    $("#SearchForm_Name").keydown(function(event) {
        $("#SearchForm_Name").focus(false);
    });

    $("#SearchForm_Developer").keydown(function(event) {
        $("#SearchForm_Developer").focus(false);
    });

    $("#SearchForm_Reviewer").keydown(function(event) {
        $("#SearchForm_Reviewer").focus(false);
    });


    $("#SearchForm_Keyword").keydown(function(event) {
        if (event.keyCode == 13) {
            keywordEnterDown = true;
        }
    });

    $("#SearchForm_Keyword").result(function(event, data, formatted) {
        keywordEnterDown = true;
        submitForm();
    });

    $("#SearchForm_Developer").result(function(event, data, formatted) {
        $("#GridAction").val("AdvancedSearch");
        $("#SearchForm_IsAdvanced").val(true);
        submitForm();
    });

    $("#SearchForm_Reviewer").result(function(event, data, formatted) {
        $("#GridAction").val("AdvancedSearch");
        $("#SearchForm_IsAdvanced").val(true);
        submitForm();
    });

    $("#SearchForm_Activity").result(function(event, data, formatted) {
        $("#GridAction").val("AdvancedSearch");
        $("#SearchForm_IsAdvanced").val(true);
        submitForm();
    });

    $("#SearchForm_PVobServer").result(function(event, data, formatted) {
        $("#GridAction").val("AdvancedSearch");
        $("#SearchForm_IsAdvanced").val(true);
        submitForm();
    });

    $("#SearchForm_PVobName").result(function(event, data, formatted) {
        $("#GridAction").val("AdvancedSearch");
        $("#SearchForm_IsAdvanced").val(true);
        submitForm();
    });

    $("#SearchForm_Project").result(function(event, data, formatted) {
        $("#GridAction").val("AdvancedSearch");
        $("#SearchForm_IsAdvanced").val(true);
        submitForm();
    });

    $("#SearchForm_Name").result(function(event, data, formatted) {
        $("#GridAction").val("AdvancedSearch");
        $("#SearchForm_IsAdvanced").val(true);
        submitForm();
    });

    $("#SearchForm_Keyword").autocomplete(
			resolveUrl("~/" + $("#SearchForm_GridType").val() + "/GetAutoCompleteData/" + $("#TypeView").val() + "/All"),
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
			});

    $("#SearchForm_Developer").autocomplete(
			resolveUrl("~/" + $("#SearchForm_GridType").val() + "/GetAutoCompleteData/" + $("#TypeView").val() + "/Developer"),
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
			});

    $("#SearchForm_Reviewer").autocomplete(
            resolveUrl("~/" + $("#SearchForm_GridType").val() + "/GetAutoCompleteData/" + $("#TypeView").val() + "/Reviewer"),
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
			});

    $("#SearchForm_Activity").autocomplete(
			resolveUrl("~/" + $("#SearchForm_GridType").val() + "/GetAutoCompleteData/" + $("#TypeView").val() + "/Activity"),
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
			});

    $("#SearchForm_PVobServer").autocomplete(
			resolveUrl("~/" + $("#SearchForm_GridType").val() + "/GetAutoCompleteData/" + $("#TypeView").val() + "/PVobServer"),
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
			});

    $("#SearchForm_PVobName").autocomplete(
			resolveUrl("~/" + $("#SearchForm_GridType").val() + "/GetAutoCompleteData/" + $("#TypeView").val() + "/PVobName"),
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
			});

    $("#SearchForm_Project").autocomplete(
			resolveUrl("~/" + $("#SearchForm_GridType").val() + "/GetAutoCompleteData/" + $("#TypeView").val() + "/Project"),
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
			});

    $("#SearchForm_Name").autocomplete(
			resolveUrl("~/" + $("#SearchForm_GridType").val() + "/GetAutoCompleteData/" + $("#TypeView").val() + "/Name"),
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
			});
}); 