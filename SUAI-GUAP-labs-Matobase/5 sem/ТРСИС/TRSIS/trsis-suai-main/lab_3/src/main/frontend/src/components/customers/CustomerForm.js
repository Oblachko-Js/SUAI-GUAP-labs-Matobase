import React from "react";
import CustomerService from "../../services/CustomerService";


class CustomerForm extends React.Component {
    constructor(props) {
        super(props)
        this.state = {
            name: '',
            birthDate: ''
        }
    }

    save = (e) => {
        e.preventDefault();
        let customer = {
            name: this.state.name,
            birthDate: this.state.birthDate
        };
        console.log(customer);
        CustomerService.save(customer).then(res => {
            this.props.history.push('/customers');
        });
    }

    handleName(event) {
        this.setState({ name: event.target.value });
    }

    handleBirthDate(event) {
        this.setState({ birthDate: event.target.value});
    }

    render() {
        return (
            <div className="container">
                <form onSubmit={this.save.bind(this)}>
                    <div className="form-group">
                        <label for="name">Name</label>
                        <input value={this.state.name} onChange={this.handleName.bind(this)} type="text" className="form-control" id="name" />
                    </div>
                    <div className="form-group">
                        <label for="birthDate">BirthDate</label>
                        <input value={this.state.birthDate} onChange={this.handleBirthDate.bind(this)} type="text" className="form-control" id="birthDate" name="birthDate" />
                    </div>
                    <input type="submit" className="btn btn-dark" value="Add" />
                </form>
            </div>
        )
    }
}

export default CustomerForm;