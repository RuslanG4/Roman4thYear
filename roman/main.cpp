#include <iostream>
#include <string>

int getValue(char t_numeral) {
    if(t_numeral == 'M' || t_numeral == 'm') {
        return 1000;
    }
    if(t_numeral == 'D' || t_numeral == 'd') {
        return 500;
    }
    if(t_numeral == 'C' || t_numeral == 'c') {
        return 100;
    }
    if(t_numeral == 'L' || t_numeral == 'l') {
        return 50;
    }
    if(t_numeral == 'X' || t_numeral == 'x') {
        return 10;
    }
    if(t_numeral == 'V' || t_numeral == 'v') {
        return 5;
    }
    if(t_numeral == 'I' || t_numeral == 'i') {
        return 1;
    }
    else {
        return -1;
    }
}

int main() {
    bool stop=false;

    while(!stop) {
        std::string willContinue;
        std::string inputNumeral;
        int total=0;
        bool error=false;

        std::cout << "Enter a valid Roman Numeral in the range 1-3999: ";
        std::getline(std::cin, inputNumeral);

        if(inputNumeral.length() > 15 || inputNumeral.length() < 0) {
            inputNumeral="";
            std::cout<<"Invalid Length"<<'\n';
            continue;
        }

        for(int i = 0; i < inputNumeral.length(); i++) {
            if(getValue(inputNumeral[i]) == -1) {
                std::cout<<"Unexpected Character found"<<'\n';
                error=true;
                break;
            }
            if(getValue(inputNumeral[i]) < getValue(inputNumeral[i + 1])) { //looking for smaller number before largest
                total+=getValue(inputNumeral[i+1]) - getValue(inputNumeral[i]); //subtract smaller val from larger to get number
                i++; //skip next iteration
                continue;
            }
            total += getValue(inputNumeral[i]);
            if(total >3999 || total < 1) {
                std::cout<<"Roman Numeral is not in the range 1-3999"<<'\n';
                error=true;
                break;
            }
        }
        if(error) {
            continue;
        }

        std::cout<<"Value is : "<<total<<'\n';

        std::cout<<"Continue ? Y/N";
        std::cin>>willContinue;
        if(willContinue == "n" || willContinue == "N") {
            stop=true;
            std::cout<<"Good Bye!\n";
        }
        std::cin.get(); //reset getline
    }
};
