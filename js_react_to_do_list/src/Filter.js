import React from 'react';

export default class Filter extends React.Component {
    zmienUkrycie(event) {
        this.props.fun_ukrywanie_pokazywanie(event.target.checked);
        if(event.target.checked) {
            event.target.parentElement.classList.add("ukryj");
        } else {
            event.target.parentElement.classList.remove("ukryj");
        }
    }
    render(){
        return (
            <div className="filtr">
                <input type="checkbox" onChange={this.zmienUkrycie.bind(this)}></input>
                
                <span className="ukryj">ukryj wykonane zadania</span>
                <span className="pokaz">pokaż wykonane zadania</span>
                
                <span className="kot">🐈</span>
            </div>
        );
    }
}