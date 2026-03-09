import React from "react";
import PurchaseService from "../../services/PurchaseService";

class PurchaseForm extends React.Component {
    constructor(props) {
        super(props)
        this.state = {
            carId: '',
            customerId: '',
            date: ''
        }
    }

    save = (e) => {
        e.preventDefault();
        let purchase = {
            carId: this.state.carId,
            customerId: this.state.customerId,
            date: this.state.date
        };
        console.log(purchase);
        PurchaseService.save(purchase).then(res => {
            this.props.history.push('/purchases');
        });
    }

    handleCarId(event) {
        this.setState({ carId: event.target.value });
    }

    handleCustomerId(event) {
        this.setState({ customerId: event.target.value});
    }

    handleDate(event) {
        this.setState({ date: event.target.value});
    }

    render() {
        return (
            <div className="container">
                <form onSubmit={this.save.bind(this)}>
                    <div className="form-group">
                        <label for="carId">CarId</label>
                        <input value={this.state.carId} onChange={this.handleCarId.bind(this)} type="text" className="form-control" id="carId" />
                    </div>
                    <div className="form-group">
                        <label for="customerId">CustomerId</label>
                        <input value={this.state.customerId} onChange={this.handleCustomerId.bind(this)} type="text" className="form-control" id="customerId" name="customerId" />
                    </div>
                    <div className="form-group">
                        <label for="date">Date</label>
                        <input value={this.state.date} onChange={this.handleDate.bind(this)} type="text" className="form-control" id="date" name="date" />
                    </div>
                    <input type="submit" className="btn btn-dark" value="Add" />
                </form>
            </div>
        )
    }
}

export default PurchaseForm;