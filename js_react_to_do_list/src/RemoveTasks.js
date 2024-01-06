import React from 'react';

export default class RemoveTasks extends React.Component {

    usuwanie() {
        this.props.usuwanie_zadan();
    }

    render() {
        return (
            <div className="usuwanie_zadan">
                <button onClick={this.usuwanie.bind(this)}>🐈 Usuń</button>
            </div>
        );
    }
}