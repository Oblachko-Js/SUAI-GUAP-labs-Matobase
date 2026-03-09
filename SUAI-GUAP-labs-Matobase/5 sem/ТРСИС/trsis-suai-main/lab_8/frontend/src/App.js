import logo from './logo.svg';
import './App.css';
import { Route } from 'react-router';
import { BrowserRouter } from 'react-router-dom';

import CarIndex from './components/cars/CarIndex';
import CarForm from './components/cars/CarForm';
import Index from './components/Index';
import CustomerIndex from './components/customers/CustomerIndex';
import CustomerForm from './components/customers/CustomerForm';
import PurchaseIndex from './components/purchases/PurchaseIndex';
import PurchaseForm from './components/purchases/PurchaseForm';


function App() {
  return (
    <BrowserRouter>
      <div className="app-wrapper">
        <Index />
      </div>
      <div className='app-wrapper-content'>
        <Route path='/cars' exact component={CarIndex} />
        <Route path='/cars/create' component={CarForm} />

        <Route path='/customers' exact component={CustomerIndex} />
        <Route path='/customers/create' component={CustomerForm} />

        <Route path='/purchases' exact component={PurchaseIndex} />
        <Route path='/purchases/create' component={PurchaseForm} />
      </div>
    </BrowserRouter>

  );
}

export default App;
