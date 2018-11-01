using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace Hotel
{
	public static class StringExtensions
	{
		public static bool Contains(this String source, String value, StringComparison comparison)
		{
			return source.IndexOf(value, comparison) != -1;
		}
        
		public static bool ContainsCaseInsensitive(this String source, String value)
		{
            if (!String.IsNullOrEmpty(source))
            {
                return Contains(source, value, StringComparison.CurrentCultureIgnoreCase);
            }
            else
            {
                return false;
            }
		}
	}
}
