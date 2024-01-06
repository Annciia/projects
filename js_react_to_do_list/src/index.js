import React from 'react';
import ReactDOM from 'react-dom/client';
import App from './App.js';

let div_react = document.getElementById("id_react_to_do");
const root_lista = ReactDOM.createRoot(div_react); //podaję div, gdzie ma być stworzony root; root jest pierwszym obiektem, który woła "render" służący do generowania html
root_lista.render(
    <div>
        <App></App>   {/*tworzenie obiektu klasy App i automatycznie zawołanie w nim metody "render"*/}
    </div>
);
