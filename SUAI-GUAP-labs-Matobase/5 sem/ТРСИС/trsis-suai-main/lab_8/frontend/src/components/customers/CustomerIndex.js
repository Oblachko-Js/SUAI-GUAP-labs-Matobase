import React from "react";
import CustomerService from "../../services/CustomerService";

class CustomerIndex extends React.Component {
    constructor(props) {
        super(props)
        this.state = {
            customers:[]
        }
    }

    componentDidMount() {
        CustomerService.getAll().then(res => {
            this.setState({customers: res.data})
        });
    }

    delete(id) {
        CustomerService.delete(id).then(res => {
            this.setState({customers: this.state.customers.filter(d => d.id !== id)})
        });
    }

    render() {
        return (
            <div>
                <h1 className="text-center">Customers</h1>
                <div>
                    <a href="/customers/create" className="btn btn-dark">add</a>
                </div>
                <table className="table table-bordered">
                    <thead>
                        <tr>
                            <td>ID</td>
                            <td>Name</td>
                            <td>BirthDate</td>
                        </tr>
                    </thead>
                    <tbody>
                        {
                            this.state.customers.map(customer =>
                                <tr key = {customer.id}>
                                    <td>{customer.id}</td>
                                    <td>{customer.name}</td>
                                    <td>{customer.birthDate}</td>
                                    <td>
                                        <button onClick={() => this.delete(customer.id)} className="btn btn-dark">Delete</button>
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

export default CustomerIndex;