import React from "react";
import CarService from "../../services/CarService";

class CarIndex extends React.Component {
    constructor(props) {
        super(props)
        this.state = {
            cars:[]
        }
    }

    componentDidMount() {
        CarService.getAll().then(res => {
            this.setState({cars: res.data})
        });
    }

    delete(id) {
        CarService.delete(id).then(res => {
            this.setState({cars: this.state.cars.filter(d => d.id !== id)})
        });
    }

    render() {
        return (
            <div>
                <h1 className="text-center">Cars</h1>
                <div>
                    <a href="/cars/create" className="btn btn-dark">add</a>
                </div>
                <table className="table table-bordered">
                    <thead>
                        <tr>
                            <td>ID</td>
                            <td>Brand</td>
                            <td>Year</td>
                            <td>Price</td>
                        </tr>
                    </thead>
                    <tbody>
                        {
                            this.state.cars.map(car =>
                                <tr key = {car.id}>
                                    <td>{car.id}</td>
                                    <td>{car.brand}</td>
                                    <td>{car.year}</td>
                                    <td>{car.price}</td>
                                    <td>
                                        <button onClick={() => this.delete(car.id)} className="btn btn-dark">Delete</button>
                                    </td>
                                </tr>
                            )
                        }
                    </tbody>
                </table>
            </div>
        )
    }
}

export default CarIndex;