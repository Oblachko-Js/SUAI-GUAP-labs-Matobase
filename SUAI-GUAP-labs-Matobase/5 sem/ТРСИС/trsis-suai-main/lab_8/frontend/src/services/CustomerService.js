import axios from "axios";

const API_CUSTOMERS = 'http://localhost:8080/customers';

class CustomerService {

    getAll() {
        return axios.get(API_CUSTOMERS);
    }

    save(customer) {
        return axios.post(API_CUSTOMERS, customer);
    }

    delete(id) {
        return axios.delete(API_CUSTOMERS + '/' + id);
    }
}

export default new CustomerService()