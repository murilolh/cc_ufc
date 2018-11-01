using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using Hotel.Models.Repository;

namespace Hotel.Models.Services
{
    public class CheckService
    {
        private List<Check> Checks { 
            get{
                CheckRepository<Check,hotelEntities> chr = new CheckRepository<Check,hotelEntities>();
                return chr.SelectAll().OrderBy(r => r.Client.Name).ToList();
            } 
        }

        public Check GetByID(int checkID)
        {
            return this.Checks.AsQueryable().First(check => check.ID == checkID);
        }


        public IQueryable<Check> GetQueryable()
        {
            return this.Checks.AsQueryable();
        }

        public void Update(Check check)
        {

        }


        public CheckCriteria CreateCriteria()
        {
            return new CheckCriteria(this.Checks);
        }

        public CheckCriteria CreateCriteria(string id)
        {
            List<Check> checks = this.Checks;
            if (id == "Checkout")
            {   
                checks.RemoveAll(c => c.Status == (int)CheckStatus.FINALIZED || c.Status == (int)CheckStatus.RESERVATION_REQUEST || c.Status == (int)CheckStatus.CANCELLED);
            }
            else if (id == "Checkin")
            {

                checks.RemoveAll(c => c.Status == (int)CheckStatus.EFFECTED || c.Status == (int)CheckStatus.RESERVATION_EFFECTED || c.Status == (int)CheckStatus.CANCELLED || c.Status == (int)CheckStatus.FINALIZED);
            }
            return new CheckCriteria(checks);
        }


        public int GetTotalItemsCount(CheckCriteria criteria)
        {
            return criteria.GetTotalItemsCount();
        }


        public List<Check> FindByCriteria(CheckCriteria criteria)
        {
            return criteria.Find();
        }


        public List<CheckSuggestion> FindSuggestions(string keyword, int max)
        {
            IQueryable<Check> query = this.GetQueryable();
            query = query.Where(check => check.DateBegin.ToString().ToLower().StartsWith(keyword))
                            .Take(max)
                            .OrderBy(check => check.DateBegin);

            var list = query.Select(check => new CheckSuggestion
                                                        {
                                                            ID = check.ID,
                                                            DateBegin = check.DateBegin
                                                        })
                            .ToList();

            return list;
        }
    }
}

