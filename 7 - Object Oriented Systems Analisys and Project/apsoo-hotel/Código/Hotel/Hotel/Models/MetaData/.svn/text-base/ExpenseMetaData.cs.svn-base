using System;

using System.Collections.Generic;
using System.ComponentModel;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Text;
using System.Web.Mvc;
using Hotel.Models.Repository;

namespace Hotel.Models
{
    [MetadataType(typeof(ExpenseMetaData))]
    public partial class Expense
    {
        IRepository<Service, hotelEntities> cr;
        CheckRepository<Check, hotelEntities> ar;        

        public int ServiceID {
            get ;
            set ;
        }

        public int CheckID
        {
            get;
            set;
        }
    }  

    public class ExpenseMetaData
    {
        public int ID { get; set; }

        [Required(ErrorMessage = "Required.")]
        [DisplayName("Service")]
        public Service Service { get; set; }

        [Required(ErrorMessage = "Required.")]
        [DisplayName("Check")]
        public Check Check { get; set; }

        [Required(ErrorMessage = "Required.")]
        [DisplayName("Date")]
        public DateTime? Date { get; set; }

        [Required(ErrorMessage = "Required.")]
        [DisplayName("Amount")]
        [Range(1, 9999)]
        public int Amount { get; set; }

        [Required(ErrorMessage = "Required.")]
        [Range(0.00, 9999.00)]
        [DisplayName("Value")]
        public Double? Value { get; set; }
    }    

}
