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
			
	function submitForm() {
		//submitAjax();
		//return;
		
		var form = $("#grid").parents("form:first");
		form.submit();
	}
	
	function submitFormWithAjax() {
	
		var form = $("#grid").parents("form:first");
		var formData= form.serialize();
		//alert(formData);

		block();

		$.ajax({
			type: "POST",
			url: "_Grid",
			data: formData,
			success: function(newHtml) {
				//alert(newHtml);
				setTimeout(function() {
								$("#grid").html(newHtml);
		
								initGrid();
								unblock(); }, 500);
			},

			error: function(request, textStatus, errorThrown) {
				alert("AJAX error: " + request.statusText);
				unblock();
			}
		});
	}
	
	function block() {
	    $('#grid #grid-data').block({		    
			message: '<div class="blockUI-message">Processing...</div>',
			css: { border: 'none', width: 'auto' },
			overlayCSS: { backgroundColor: '#C0C0C0' }
		});
		

		//alert("blocked");
	}

	function unblock() {
		$('#grid #grid-data').unblock();

		//alert("unblocked");
	}
	
	function onRowClick(id) {
		document.location = "Edit/" + id;
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


	jQuery(document).ready(function() {

		initGrid();

		$("#grid").parents("form:first").submit(function() {
			//if ($("#GridAction").val() == "AdvancedSearch")
			//	return true;

			//alert("onSubmit " + $("#GridAction").val());
			submitFormWithAjax();
			return false;
		});

		$("#keyword-search-submit").click(function() {
			$("#GridAction").val("KeywordSearch");
		});

		$("#advanced-search-submit").click(function() {
			$("#GridAction").val("AdvancedSearch");
		});


		$("#search-form #advanced-link").click(function() {
			$("#search-form").slideUp("medium", function() {
				$("#search-form #keyword-search").hide();
				$("#search-form #advanced-link").hide();

				$("#search-form #advanced-search").show();
				$("#search-form #keyword-link").show();

				$("#search-form").slideDown("medium");
			}
			);

			$("#SearchForm_IsAdvanced").val("true");
		});


		$("#search-form #keyword-link").click(function() {
			$("#search-form").slideUp("medium", function() {
				$("#search-form #advanced-search").hide();
				$("#search-form #keyword-link").hide();

				$("#search-form #keyword-search").show();
				$("#search-form #advanced-link").show();

				$("#search-form").slideDown("medium");
			}
			);

			$("#SearchForm_IsAdvanced").val("false");
		});


		$("#SearchForm_Keyword").autocomplete(
			resolveUrl("GetKeywordAutoCompleteData"),
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
			}
		);

		$("#SearchForm_Keyword").result(function(event, data, formatted) {
				document.location = resolveUrl("Edit/") + data.ID;
			}
        );

	}); 