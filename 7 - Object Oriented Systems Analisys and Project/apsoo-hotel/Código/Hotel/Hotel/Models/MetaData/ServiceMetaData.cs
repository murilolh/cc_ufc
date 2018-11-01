using System;

using System.ComponentModel;
using System.ComponentModel.DataAnnotations;

namespace Hotel.Models
{
    [MetadataType(typeof(ServiceMetaData))]
    public partial class Service
    {
    }

	public class ServiceMetaData
	{		
		public int ID { get; set; }

		[Required(ErrorMessage = "Required."), DisplayName("Name"), StringLength(100, ErrorMessage = "Must be under 100 characters")]        
		public string Name { get; set; }

		public string Description { get; set; }
        
        [Required(ErrorMessage = "Required.")]
        [Range(0.00, 9999.00)]
        public double? Price { get; set; }
	}
}
