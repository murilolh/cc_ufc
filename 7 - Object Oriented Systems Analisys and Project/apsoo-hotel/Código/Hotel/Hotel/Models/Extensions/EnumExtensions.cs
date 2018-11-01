using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Reflection;

namespace Hotel.Models
{
    public static class EnumExtensions
    {
        public static string GetStringValue(this Enum value)
        {
            try
            {
                Type type = value.GetType();

                FieldInfo fieldInfo = type.GetField(value.ToString());

                StringValueAttribute[] attributes = fieldInfo.GetCustomAttributes(
                    typeof(StringValueAttribute), false) as StringValueAttribute[];

                return attributes[0].StringValue;
            }
            catch
            {
                return string.Empty;
            }
        }

        public static string[] GetStringValue(Type enumType) {
            string[] enumStringValue = null;

            if (!enumType.IsEnum)

                throw new ArgumentException

                ("enumType should be a valid enum");

            
            FieldInfo[] fieldInfo = enumType.GetFields();
            enumStringValue = new string[fieldInfo.Length - 1];
            int j = 0;
            for (int i = 0; i < fieldInfo.Length; i++)
			{
                var attribs =

                fieldInfo[i].GetCustomAttributes(typeof(StringValueAttribute), false)

                as StringValueAttribute[];

                //Get the StringValueAttribute for each enum member

                if (attribs.Length > 0)
                {
                    enumStringValue[j] = attribs[0].StringValue;
                    j++;
                }
            }

            return enumStringValue;
        }

        public static object GetEnumStringValue(this string value, Type enumType, bool ignoreCase)
        {

            object result = null;

            string enumStringValue = null;

            if (!enumType.IsEnum)

                throw new ArgumentException

                ("enumType should be a valid enum");

            foreach (FieldInfo fieldInfo in enumType.GetFields())
            {

                var attribs =

                fieldInfo.GetCustomAttributes(typeof(StringValueAttribute), false)

                as StringValueAttribute[];

                //Get the StringValueAttribute for each enum member

                if (attribs.Length > 0)

                    enumStringValue = attribs[0].StringValue;

                if (string.Compare(enumStringValue, value, ignoreCase) == 0)

                    result = Enum.Parse(enumType, fieldInfo.Name);

            }

            return result;

        }
    }

    public class StringValueAttribute : Attribute
    {
        public string StringValue { get; protected set; }

        public StringValueAttribute(string value)
        {
            this.StringValue = value;
        }
    }
}
