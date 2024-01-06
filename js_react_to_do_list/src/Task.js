import React from 'react';

export default class Task extends React.Component {

    zmienZrobienie(event) {
        this.props.fun_zmien_zrobienie(this.props.id_zadania, event.target.checked);
    }

    render(){
        //props przechowuje wartości wszystkich atrybutów komponentów
        return (
            <div className="task">
                <input type="checkbox" checked={this.props.czy_zrobione_zadanie} onChange={this.zmienZrobienie.bind(this)}></input> {/*do checked podane, czy zadanie jest obecnie zaznaczone czy nie; na onChange jest przekazane do funkcji, by było wiadomo na co zmienić*/}
                <span className="kot">🐈</span>
                <span>{this.props.nazwa}</span>
            </div>
        );
    }
}