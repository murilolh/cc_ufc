using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using Hotel.Models.Repository;

namespace Hotel.Models.Services
{
    public class ExpenseService
    {
        private List<Expense> Expenses { 
            get{
                ExpenseRepository<Expense,hotelEntities> er = new ExpenseRepository<Expense,hotelEntities>();
                return er.SelectAll().OrderBy(r => r.Service.Name).ToList();
            } 
        }

        public Expense GetByID(int expenseID)
        {
            return this.Expenses.AsQueryable().First(expense => expense.ID == expenseID);
        }


        public IQueryable<Expense> GetQueryable()
        {
            return this.Expenses.AsQueryable();
        }

        public void Update(Expense expense)
        {

        }


        public ExpenseCriteria CreateCriteria()
        {
            return new ExpenseCriteria(this.Expenses);
        }


        public int GetTotalItemsCount(ExpenseCriteria criteria)
        {
            return criteria.GetTotalItemsCount();
        }


        public List<Expense> FindByCriteria(ExpenseCriteria criteria)
        {
            return criteria.Find();
        }


        public List<ExpenseSuggestion> FindSuggestions(string keyword, int max)
        {
            IQueryable<Expense> query = this.GetQueryable();
            query = query.Where(expense => expense.Date.ToString().ToLower().StartsWith(keyword))
                            .Take(max)
                            .OrderBy(expense => expense.Date);

            var list = query.Select(expense => new ExpenseSuggestion
                                                        {
                                                            ID = expense.ID,
                                                            Date = expense.Date
                                                        })
                            .ToList();

            return list;
        }
    }
}

