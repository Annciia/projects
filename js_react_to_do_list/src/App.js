import React from 'react';
import ToDoList from './ToDoList.js';
import NewTask from './NewTask.js';
import Filter from './Filter.js';
import RemoveTasks from './RemoveTasks.js';

export default class App extends React.Component {

    constructor(){
        super(); //zawolanie konstruktora klasy, z ktorej dziedziczy moja klasa
        this.state = {
            tasks: [], //lista zadań, każde zadanie jako struktura w liście wpisywane pod kolejnym id[{ id: ..., nazwa: "...", czy_zrobione: false },{...}]
            iterator: 0, // id zadania
            ukryj: false,
            zaangazowanie: "Dziś mi się nie chce nic robić..."
        };
    }
    
    zmiana_nastawienia() {
        if(this.state.zaangazowanie==='Dziś mi się nie chce nic robić...'){
            this.setState({
                zaangazowanie: "Chętnie wykonam jakieś zadanie! 🐈"
            });
        }
        else if(this.state.zaangazowanie==='Chętnie wykonam jakieś zadanie! 🐈'){
            this.setState({
                zaangazowanie: "Dziś mi się nie chce nic robić..."
            });
        }
    }

    zmiana_stanu_wykonania_zadania(id, czy_zrobione){
        for(let i =0; i<this.state.tasks.length; i++){
            if(this.state.tasks[i].id===id){
                this.state.tasks[i].czy_zrobione=czy_zrobione;
                this.setState({tasks: this.state.tasks})
            }
        }
    }

    dodawanie_nowego_zadania(nazwa_zadania){
        this.state.tasks.push({id: this.state.iterator, nazwa: nazwa_zadania, czy_zrobione: false}); //dopisanie taska do listy
        this.setState({tasks: this.state.tasks}); //uaktualnienie stanu - przypisanie mu całej listy ze state
        this.state.iterator++;
        this.setState({iterator: this.state.iterator});
    }

    ukrywanie_pokazywanie_wykonanych(ukrywanie_pokazywanie){
        this.setState({ukryj: ukrywanie_pokazywanie});
    }

    usuwanie_wykreslonych_zadan() {
        let tasks_nowy = [];
        for(let i=0; i<this.state.tasks.length; i++) {
            if(this.state.tasks[i].czy_zrobione === false) {
                tasks_nowy.push(this.state.tasks[i]);
            }
        }
        this.setState({ tasks: tasks_nowy });
    }
 
    render(){  //każda klasa, która ma być komponentem, musi odzidziczyć z klasy React.Component, a w konsekwencji tego musi mieć metodę render()
        return <div>
                <Filter fun_ukrywanie_pokazywanie={this.ukrywanie_pokazywanie_wykonanych.bind(this)}></Filter> 
                <RemoveTasks usuwanie_zadan={this.usuwanie_wykreslonych_zadan.bind(this)}></RemoveTasks>
                <ToDoList tasks_list = {this.state.tasks} fun_zmien_zrobienie={this.zmiana_stanu_wykonania_zadania.bind(this)} ukryj={this.state.ukryj}></ToDoList> {/*w atrybutach przekazana funkcja lub zmienna z App do komponentu ToDoList*/} 
                <NewTask dodanie_zadania={this.dodawanie_nowego_zadania.bind(this)}></NewTask>
                <div className="zaangazowanie">{this.state.zaangazowanie}</div>
                <div className="nastawienie"><button onClick={this.zmiana_nastawienia.bind(this)}>Zmien nastawienie</button></div>
            </div>;
    }
}
