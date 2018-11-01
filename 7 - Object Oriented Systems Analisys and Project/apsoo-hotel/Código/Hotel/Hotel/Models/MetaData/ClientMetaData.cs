using System;

using System.ComponentModel;
using System.ComponentModel.DataAnnotations;

namespace Hotel.Models
{
    [MetadataType(typeof(ClientMetaData))]
    public partial class Client
    {
    }

	public class ClientMetaData
	{		
		public int ID { get; set; }

		[Required(ErrorMessage = "Required."), DisplayName("Name"),
        StringLength(100, ErrorMessage = "Must be under 50 characters")]
		public string Name { get; set; }

		[Required(ErrorMessage = "Required.")]
		[DisplayName("Login")]
        [StringLength(8, ErrorMessage = "Must be under 8 characters")]
		public string Login { get; set; }

        [DisplayName("Password") ]       
        [StringLength(8, ErrorMessage = "Must be under 8 characters")]
		public string Password { get; set; }

		[DisplayName("CPF")]
        [RegularExpression(@"^\d{3}\.?\d{3}\.?\d{3}\-?\d{2}$")]
		public string CPF { get; set; }

		[DisplayName("Date of Birth")]
		public DateTime? DateOfBirth { get; set; }
	}
}
