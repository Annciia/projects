import React from 'react';
import Task from './Task.js';

export default class ToDoList extends React.Component {

    render(){
        let pusta= true;
        return (
            <div>
                {
                    this.props.tasks_list.map((zadanie, i) => 
                    {
                        if (this.props.ukryj===false || (this.props.ukryj===true && zadanie.czy_zrobione === false)){
                            //bierze z listy po kolei zadania i wkłada je do kolejnych Tasków
                            pusta = false;
                            return <Task key={i} id_zadania={zadanie.id} nazwa={zadanie.nazwa} fun_zmien_zrobienie={this.props.fun_zmien_zrobienie } czy_zrobione_zadanie={zadanie.czy_zrobione} ></Task>
                        }
                        else{return (null);}
                    })
                }
                {
                    (pusta===true) ? (<div className="nic">LISTA PUSTA!</div>) : (null)
                }
            </div>
        );
    }
}