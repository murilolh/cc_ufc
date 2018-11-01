using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using Hotel.Models.Repository;

namespace Hotel.Models.Services
{
    public class ClientService
    {
        private List<Client> Clients { 
            get{
                InheritRepository<Client,Person,hotelEntities> cr = new InheritRepository<Client,Person,hotelEntities>();
                return cr.SelectAll().OrderBy(c => c.Name).ToList();
            } 
        }

        public Client GetByID(int clientID)
        {
            return this.Clients.AsQueryable().First(client => client.ID == clientID);
        }


        public IQueryable<Client> GetQueryable()
        {
            return this.Clients.AsQueryable();
        }


        public void Add(Client client)
        {
            /*this.Clients.Add(client);

            try
            {
                //TryUpdateModel(client);

                ClientRepository clientRepo = new ClientRepository();
                clientRepo.Add(client);
                clientRepo.Save();
            }
            catch
            {
            }*/
        }

        public void Update(Client client)
        {

        }

        public void Delete(int clientID)
        {
            /*this.Clients.RemoveAll(client => client.ID == clientID);

            Client aux = this.GetByID(clientID);


            //TryUpdateModel(client);

            ClientRepository clientRepo = new ClientRepository();
            clientRepo.Delete(aux);
            clientRepo.Save();*/
        }


        public ClientCriteria CreateCriteria()
        {
            return new ClientCriteria(this.Clients);
        }


        public int GetTotalItemsCount(ClientCriteria criteria)
        {
            return criteria.GetTotalItemsCount();
        }


        public List<Client> FindByCriteria(ClientCriteria criteria)
        {
            return criteria.Find();
        }


        public List<ClientSuggestion> FindSuggestions(string keyword, int max)
        {
            IQueryable<Client> query = this.GetQueryable();
            query = query.Where(client => client.Name.ToLower().StartsWith(keyword))
                            .Take(max)
                            .OrderBy(client => client.Name)
                            .ThenBy(client => client.CPF);
            

            var list = query.Select(client => new ClientSuggestion
                                                        {
                                                            ID = client.ID,
                                                            Name = client.Name
                                                        })
                            .ToList();

            return list;
        }
    }
}

