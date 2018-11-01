using System;

using System.ComponentModel;
using System.ComponentModel.DataAnnotations;
using System.Web.Mvc;

namespace Hotel.Models
{
    [MetadataType(typeof(ApartmentTypeMetaData))]
    public partial class ApartmentType
    {
     
    }

    public class ApartmentTypeMetaData
    {        
        [Required(ErrorMessage = "Required.")]
        [DisplayName("ID")]
        public int ID { get; set; }
        
        [Required(ErrorMessage = "Required.")]
        [DisplayName("Name")]
        public string Name { get; set; }

        [Required(ErrorMessage = "Required.")]
        [Range(0,10,ErrorMessage = "The number of bed must be greater than zero")]
        [DisplayName("Bed")]
        public int Bed { get; set; }

        [Required(ErrorMessage = "Required.")]
        [DisplayName("Description")]
        public string Description{ get; set; }

        [Required(ErrorMessage = "Required.")]
        [Range(0.01, 9999.00)]
        [DisplayName("Price")]
        public double? Price { get; set; }

    }
}
