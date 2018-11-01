using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace Hotel
{
	public static class StringFormatter
	{
		public static string FormatDate(DateTime? dateTime)
		{
			if (dateTime == null)
				return "";

			return dateTime.Value.ToString("MMM d, yyyy");
		}


		public static string FormatInputDate(DateTime? dateTime)
		{
			if (dateTime == null)
				return "";

			return dateTime.Value.ToString("dd/MM/yyyy");
		}

        public static string FormatInputDateTime(DateTime? dateTime)
        {
            if (dateTime == null)
                return "";

            return dateTime.Value.ToString("dd/MM/yyyy HH:mm");
        }


		public static string FormatPhone(String phone)
		{
			if (phone == null)
				return "";

			string result;
			if (phone.Length == 10)
			{
				result = phone.Substring(0, 10);
				result = "(" + result.Substring(0, 3) + ") " + result.Substring(3, 3) + "-" + result.Substring(6, 4);
			}
			else
			{
				result = phone;
			}

			return result;

		}


		public static string FormatCurrency(decimal? amount)
		{
			if (amount == null)
				return "";

			return amount.Value.ToString("C");
		}

        public static string FormatCurrency(double? amount)
        {
            if (amount == null)
                return "";

            return amount.Value.ToString("C");
        }
	}
}
