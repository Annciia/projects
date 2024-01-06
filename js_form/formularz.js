
let lista_bledow = [];

function validate(formularz){
    lista_bledow = [];
    var p =  true;
    p = checkString(formularz.elements["f_imie"], "Podaj imie!") && p;
    p = checkString(formularz.elements["f_nazwisko"], "Podaj nazwisko!") && p;
    p = checkEmail(formularz.elements["f_email"], "Nieprawidłowy e-mail!") && p;
    p = checkData(formularz.elements["f_data"], "Nieprawidłowa data!") && p;
    p = checkHaslo(formularz.elements["f_haslo"], "Nieprawidłowe hasło!") && p;
    p = checkPowtorzHaslo(formularz.elements["f_powtorzhaslo"], formularz.elements["f_haslo"], "Powtórzone hasło nie zgadza się!") && p;
    p = checkOpis(formularz.elements["f_opis"], "Maksymalna długość opisu to 20 znaków!") && p;

    let div_bledy = document.getElementById("bledy");
    if(lista_bledow.length == 0) {
        div_bledy.style.visibility = "hidden";
    } else {
        div_bledy.style.visibility = "visible";
    }
    let str = "<ul>";
    for(let i=0; i<lista_bledow.length; i++) {
        str += "<li>" + lista_bledow[i] + "</li>";
    }
    str += "</ul>";
    div_bledy.innerHTML = str;

    return p;
}

function areOnlyWhiteSpace(str) {
    var ws = "\t\n\r ";
    for (var i = 0; i < str.length; i++) {
        var c = str.charAt(i);
        if (ws.indexOf(c) == -1) {
            return false;
        }
    }
    return true;
}

function gwiazdkowanie(obj, p){  //p=true - włączone  gwaizdkowanie; p=false - wyłącozne
    let name = "err_"+obj.name.substring(2, obj.name.length);
    let el_gwiazdka= document.getElementById(name);
    if(p == true) {
        el_gwiazdka.textContent = "*";
        obj.classList.add("blad_ramka");
    } else {
        el_gwiazdka.textContent = "";
        obj.classList.remove("blad_ramka")
    }
}

function checkEmail(obj, komunikat) {
    let str=obj.value;
    if (areOnlyWhiteSpace(str)) {
        gwiazdkowanie(obj, true);
        if(komunikat != undefined) { lista_bledow.push(komunikat); }
        return false;
    }
    else {
        var at = str.indexOf("@");
        if (at < 1) {
            gwiazdkowanie(obj, true);
            if(komunikat != undefined) { lista_bledow.push(komunikat); }
            return false;
        }
        else {
            var l = -1;
            for (var i = 0; i < str.length; i++) {
                var c = str.charAt(i);
                if (c == ".") {
                    l = i;
                }
            }
            if ((l < (at + 2)) || (l == str.length - 1)) {
                gwiazdkowanie(obj, true);
                if(komunikat != undefined) { lista_bledow.push(komunikat); }
                return false;
            }
        }
        gwiazdkowanie(obj, false);
        return true;
    }
}

function checkString(obj, komunikat) {
    let p=areOnlyWhiteSpace(obj.value); //niewypełnione pole p=true
    gwiazdkowanie(obj, p);
    if(p==true) {
        if(komunikat != undefined) { lista_bledow.push(komunikat); }
    }
    return !p;
}

function checkData(obj, komunikat){
    let p = true;
    let str=obj.value;
    if(areOnlyWhiteSpace(str)) {
        gwiazdkowanie(obj, true);
        if(komunikat != undefined) { lista_bledow.push(komunikat); }
        return false; 
    }
    let dateReg = /^\d{2}[./-]\d{2}[./-]\d{4}$/ ;
    p = dateReg.test(str); //zwraca true jak się zgadza
    if (p == false){
        gwiazdkowanie(obj, true);
        if(komunikat != undefined) { lista_bledow.push(komunikat); }
        return p;
    }
    else{
        gwiazdkowanie(obj, false);
        return p;
    }
}

function checkOpis(obj, komunikat){
    let str = obj.value;
    if(str.length>20){
        obj.value=str.substring(0,20);
    }
    return true;
}

function checkHaslo(obj, komunikat){
    let str = obj.value;
    if(str.length<8){
        gwiazdkowanie(obj, true);
        if(komunikat != undefined) { lista_bledow.push(komunikat); }
        return false;
    }
    if(/\d+/.test(str)==false){  //gdy string nie zawiera cyfry
        gwiazdkowanie(obj, true);
        if(komunikat != undefined) { lista_bledow.push(komunikat); }
        return false;
    }
    gwiazdkowanie(obj, false);
    return true;
}

function checkPowtorzHaslo(obj, obj2, komunikat) {
    if(obj.value != obj2.value) {
        gwiazdkowanie(obj, true);
        if(komunikat != undefined) { lista_bledow.push(komunikat); }
        return false;
    } else {
        gwiazdkowanie(obj, false);
        return true;
    }
}