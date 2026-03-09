import axios from "axios";

const API_PURCHASES = 'http://localhost:8080/purchases';

class PurchaseService {

    getAll() {
        return axios.get(API_PURCHASES);
    }

    save(purchase) {
        return axios.post(API_PURCHASES, purchase);
    }

    delete(id) {
        return axios.delete(API_PURCHASES + '/' + id);
    }
}

export default new PurchaseService()