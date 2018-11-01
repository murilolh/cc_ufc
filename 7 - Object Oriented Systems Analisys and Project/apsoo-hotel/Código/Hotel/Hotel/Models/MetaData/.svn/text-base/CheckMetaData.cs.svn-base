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
    [MetadataType(typeof(CheckMetaData))]
    public partial class Check
    {
        public CheckStatus CheckStatus
        {
            get { return (CheckStatus)this.Status; }
            set {this.Status = (int)value;}
        }

        public int ClientID {
            get ;
            set ;
        }

        public int ApartmentID
        {
            get;
            set;
        }

        public List<Expense> Expenses
        {
            get;
            set;
        }

        public string Name{
            get { return this.Client.Name; }
            set { this.Client.Name = value; }
        }

        public int ApartmentNumber
        {
            get { return this.Apartment.Number; }
            set { this.Apartment.Number = value; }
        }
    }

    public enum CheckStatus : int
    {   
        [StringValue("Reservation Request")]
        RESERVATION_REQUEST = 1,
        [StringValue("Reservation Effected")]
        RESERVATION_EFFECTED = 2,
        [StringValue("Effected")]
        EFFECTED = 3,
        [StringValue("Finalized")]
        FINALIZED = 4,
        [StringValue("Cancelled")]
        CANCELLED = 5
    }
   

    public class CheckMetaData
    {
        public int ID { get; set; }

        [Required(ErrorMessage = "Required.")]
        [DisplayName("Client")]
        public Client Client { get; set; }

        [Required(ErrorMessage = "Required.")]
        [DisplayName("Apartment")]
        public Apartment Apartment { get; set; }

        [Required(ErrorMessage = "Required.")]
        [DisplayName("Status")]
        public CheckStatus Status { get; set; }

        [Required(ErrorMessage = "Required.")]
        [DisplayName("Initial Date")]
        public DateTime? DateBegin { get; set; }

        [Required(ErrorMessage = "Required.")]
        [DisplayName("Final Date")]
        public DateTime? DateEnd { get; set; }

        [Required(ErrorMessage = "Required.")]
        [Range(0.00, 9999.00)]
        [DisplayName("Value")]
        public Double? Value { get; set; }
    }    

}
