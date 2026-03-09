import React from "react";
import PurchaseService from "../../services/PurchaseService";


class PurchaseIndex extends React.Component {
    constructor(props) {
        super(props)
        this.state = {
            purchases:[]
        }
    }

    componentDidMount() {
        PurchaseService.getAll().then(res => {
            this.setState({purchases: res.data})
        });
    }

    delete(id) {
        PurchaseService.delete(id).then(res => {
            this.setState({purchases: this.state.purchases.filter(d => d.id !== id)})
        });
    }

    render() {
        return (
            <div>
                <h1 className="text-center">Purchases</h1>
                <div>
                    <a href="/purchases/create" className="btn btn-dark">add</a>
                </div>
                <table className="table table-bordered">
                    <thead>
                        <tr>
                            <td>ID</td>
                            <td>CarId</td>
                            <td>CustomerId</td>
                            <td>Date</td>
                        </tr>
                    </thead>
                    <tbody>
                        {
                            this.state.purchases.map(purchase =>
                                <tr key = {purchase.id}>
                                    <td>{purchase.id}</td>
                                    <td>{purchase.carId}</td>
                                    <td>{purchase.customerId}</td>
                                    <td>{purchase.date}</td>
                                    <td>
                                        <button onClick={() => this.delete(purchase.id)} className="btn btn-dark">Delete</button>
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

export default PurchaseIndex;