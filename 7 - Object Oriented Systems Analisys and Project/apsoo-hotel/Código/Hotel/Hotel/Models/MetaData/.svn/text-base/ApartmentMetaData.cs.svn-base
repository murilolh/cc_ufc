using System;

using System.ComponentModel;
using System.ComponentModel.DataAnnotations;
using System.Web.Mvc;

namespace Hotel.Models
{
    [MetadataType(typeof(ApartmentMetaData))]
    public partial class Apartment
    {
        public ApartmentStatus ApartmentStatus
        {
            get { return (ApartmentStatus)this.Status; }
            set { this.Status = (int)value; }
        }

        public int TypeID
        {
            get;
            set;
        }
    }

    public enum ApartmentStatus : int
    {          
        [StringValue("Available")]        
        AVAILABLE = 1,
        [StringValue("Busy")]
        BUSY = 2,
        [StringValue("Maintenance")]
        MAINTENANCE = 3
    }


	public class ApartmentMetaData
	{      
        [DisplayName("ID")]
        public int ID { get; set; }

        [Required(ErrorMessage = "Required.")]
        [DisplayName("Number")]
		public int Number { get; set; }

		[Required(ErrorMessage = "Required.")]
		[DisplayName("Floor")]
		public string Floor { get; set; }

		[Required(ErrorMessage = "Required.")]
		[DisplayName("Status")]
        public ApartmentStatus Status { get; set; }

        [Required(ErrorMessage = "Required.")]
        [DisplayName("Apartment Type")]        
         public ApartmentType ApartmentType { get; set; }
	}
}
