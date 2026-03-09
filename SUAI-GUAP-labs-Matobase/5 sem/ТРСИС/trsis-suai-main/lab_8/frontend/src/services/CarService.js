import axios from "axios";

const API_CARS = 'http://localhost:8080/cars';

class CarService {

    getAll() {
        return axios.get(API_CARS);
    }

    save(car) {
        return axios.post(API_CARS, car);
    }

    delete(id) {
        return axios.delete(API_CARS + '/' + id);
    }
}

export default new CarService()