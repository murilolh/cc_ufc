using System.Web.Mvc;

namespace Hotel.ViewModels.Shared
{
	public interface IGrid
	{
		Pager Pager { get; set; }
		Sorter Sorter { get; set; }
		GridAction GridAction { get; set; }
		bool IsEmpty { get; }
		SelectList PageSizeSelectList();
		string PageNavActionLink(string linkText, int page);
		string SortActionLink(string linkText, string sortField);
	}
}