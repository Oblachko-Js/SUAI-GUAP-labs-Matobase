import React from "react";
import CarService from "../../services/CarService";

class CarForm extends React.Component {
    constructor(props) {
        super(props)
        this.state = {
            brand: '',
            year: '',
            price: ''
        }
    }

    save = (e) => {
        e.preventDefault();
        let car = {
            brand: this.state.brand,
            year: this.state.year,
            price: this.state.price
        };
        console.log(car);
        CarService.save(car).then(res => {
            this.props.history.push('/cars');
        });
    }

    handleBrand(event) {
        this.setState({ brand: event.target.value });
    }

    handleYear(event) {
        this.setState({ year: event.target.value});
    }

    handlePrice(event) {
        this.setState({ price: event.target.value});
    }

    render() {
        return (
            <div className="container">
                <form onSubmit={this.save.bind(this)}>
                    <div className="form-group">
                        <label for="brand">Brand</label>
                        <input value={this.state.brand} onChange={this.handleBrand.bind(this)} type="text" className="form-control" id="brand" />
                    </div>
                    <div className="form-group">
                        <label for="year">Year</label>
                        <input value={this.state.year} onChange={this.handleYear.bind(this)} type="text" className="form-control" id="year" name="year" />
                    </div>
                    <div className="form-group">
                        <label for="price">Price</label>
                        <input value={this.state.price} onChange={this.handlePrice.bind(this)} type="text" className="form-control" id="price" name="price" />
                    </div>
                    <input type="submit" className="btn btn-dark" value="Add" />
                </form>
            </div>
        )
    }
}

export default CarForm;