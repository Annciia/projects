import React from 'react';

export default class NewTask extends React.Component {
    constructor(props) {
        super(props);
        this.state = {
            tresc_zadania: ""
        };
    }

    dodajZadanie() {
        this.props.dodanie_zadania(this.state.tresc_zadania); //przez props. dosteję się do funkcji/(albo zmiennej), która była przekazana z App w atrybucie komponenentu NewTask o tej nazwie dodanie_zadania
        this.setState({ tresc_zadania: "" });
    }

    zmianaTresciZadania = (event) => {
        this.setState({ tresc_zadania: event.target.value });
        event.target.style.color= "purple";
    }
    zatwierdzZadanie = (event) => {
        if (event.key === 'Enter') {
            this.dodajZadanie();
        }
    }

    render() {
        return (
            <div className="wysokosc_tekstu">
                <input type="text" id="tresc_zadania" value= {this.state.tresc_zadania} onChange={this.zmianaTresciZadania} onKeyDown={this.zatwierdzZadanie}/> {/*wszystko co wprowadzam do input text-> na OnChange wartość wpisana w pole tekstowe przechowywana w event.target.value jest zapisywana w stanie (SetState)*/}
                <button onClick={this.dodajZadanie.bind(this)}>🐈 Dodaj</button>
            </div>
        );
    }
}
