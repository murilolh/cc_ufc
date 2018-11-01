using System;

using System.ComponentModel;
using System.ComponentModel.DataAnnotations;
using System.Web.Mvc;

namespace Hotel.Models
{
    [MetadataType(typeof(EmployeeMetaData))]
    public partial class Employee
    {
        public EmployeeType EmployeeType
        {
            get { return (EmployeeType)this.Type; }
            set { this.Type = (int)value; }
        }

        public bool isManager()
        {
            return this.Type == 3;
        }
    }

    public enum EmployeeType : int
    {
        [StringValue("Clerk")]
        CLERK = 1,
        [StringValue("Recepcionist")]
        RECEPCIONIST = 2,
        [StringValue("Manager")]
        MANAGER = 3
    }


    public class EmployeeMetaData
    {
        public int ID { get; set; }

        [Required(ErrorMessage = "Required.")]
        [DisplayName("Name")]
        [StringLength(100, ErrorMessage = "Must be under 50 characters")]
        public string Name { get; set; }

        [Required(ErrorMessage = "Required.")]
        [DisplayName("Login")]
        [StringLength(8, ErrorMessage = "Must be under 8 characters")]
        public string Login { get; set; }

        [Required(ErrorMessage = "Required.")]
        [DisplayName("Password")]
        [StringLength(8, ErrorMessage = "Must be under 8 characters")]
        public string Password { get; set; }

        [Required(ErrorMessage = "Required.")]
        [DisplayName("CPF")]
        [RegularExpression(@"^\d{3}\.?\d{3}\.?\d{3}\-?\d{2}$")]    
        public string CPF { get; set; }

        [Required(ErrorMessage = "Required.")]
        [DisplayName("Type")]
        public EmployeeType Type { get; set; }

        [Required(ErrorMessage = "Required.")]
        [DisplayName("Date of Birth")]        
        public DateTime? DateOfBirth { get; set; }
    }
}
