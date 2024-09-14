#include <iostream>
#include <string>

int getValue(const char & numeral) {
    if(numeral == 'M') {
        return 1000;
    }
    if(numeral == 'D') {
        return 500;
    }
    if(numeral == 'C') {
        return 100;
    }
    if(numeral == 'L') {
        return 50;
    }
    if(numeral == 'X') {
        return 10;
    }
    if(numeral == 'V') {
        return 5;
    }
    if(numeral == 'I') {
        return 1;
    }
    return -1;
}

bool lengthError(const std::string& numeral) {
    if (numeral.empty() || numeral.length() > 15) {
        std::cout<<"Invalid Length"<<'\n';
        return true;
    }
    return false;
}

bool unexpectedCharacterError(const std::string& numeral) {
    for (int i = 0; i < numeral.length(); ++i) {
        if(getValue(numeral[i]) == -1) {
            std::cout<<"Unexpected Character found"<<'\n';
            return true;
        }
    }
    return false;
}

bool repeatedNumeralError(const std::string& numeral) {
    int repeatedNumeral = 1;
    for (int i = 0; i < numeral.length(); ++i) {
        if (numeral[i] == numeral[i + 1]) {
            // validates that there is not more than 3 {I,X,C,M} in a row
            if (numeral[i] == 'I' || numeral[i] == 'X' || numeral[i] == 'C'|| numeral[i] == 'M' ) {
                repeatedNumeral++;
                if(repeatedNumeral > 3) {
                    std::cout<<"Invalid Format"<<'\n';
                    return true;
                }
            }
            // {V,L,D} cant be in a row
            else if (numeral[i] == 'V' || numeral[i] == 'L' || numeral[i] == 'D') {
                std::cout<<"Invalid Format"<<'\n';
                return true;
            }
        }else {
            repeatedNumeral = 0;
        }
    }
    return false;
}
bool formatError(const std::string& numeral) {
    for (int i = 0; i < numeral.length(); ++i) {
        if(i+1 < numeral.length()) {
            //checks for cases of subtraction for {IV(4),IX(9),XL(40),XC(90),CD(400),CM(900)} by checking current numeral against the next
            if(getValue(numeral[i]) < getValue(numeral[i + 1])) {
                //follows patter of nothing can follow 'I' bar {V,X,I} to make {IV(4), IX(9), II(2)
                if(numeral[i] == 'I' && (numeral[i + 1] != 'V' && numeral[i + 1] != 'X' && numeral[i+1] != 'I')){
                    std::cout<<"Invalid Format"<<'\n';
                    return true;
                }
                if(numeral[i] == 'X' && (numeral[i + 1] != 'L' && numeral[i + 1] != 'C' && numeral[i + 1] != 'X')) {
                    std::cout<<"Invalid Format"<<'\n';
                    return true;
                }
                if(numeral[i] == 'C' && (numeral[i + 1] != 'D' && numeral[i + 1] != 'M' && numeral[i + 1] != 'C')) {
                    std::cout<<"Invalid Format"<<'\n';
                    return true;
                }
                //ignores cases like MLM
                if (numeral[i] == 'V' || numeral[i] == 'L' || numeral[i] == 'D') {
                    std::cout<<"Invalid Format"<<'\n';
                    return true;
                }
            }
            //throws error if a format like IXI is followed where numbers either side the middle are equal to each other and lower than the middle
            else if(i != 0 && getValue(numeral[i]) > getValue(numeral[i + 1]) && getValue(numeral[i -1 ]) == getValue(numeral[i+1])) {
                std::cout<<"Invalid Format"<<'\n';
                return true;
            }
        }
    }
    return false;
}

bool rangeError(const int& total) {
    if(total > 3999 || total < 1) {
        std::cout<<"Roman Numeral is not in the range 1-3999"<<'\n';
        return true;
    }
    return false;
}
//holder for error functions
bool hasErrors(const std::string& numeral) {
    return lengthError(numeral) ||
           unexpectedCharacterError(numeral) ||
               formatError(numeral)||
                   repeatedNumeralError(numeral);
}

int main() {
    bool stop=false;

    while(!stop) {
        std::string willContinue;
        std::string inputNumeral;
        int total=0;

        std::cout << "Enter a valid Roman Numeral in the range 1-3999: ";
        std::getline(std::cin, inputNumeral);

        if(hasErrors(inputNumeral)){
            continue;
        }

        for(int i = 0; i < inputNumeral.length(); i++) {
            if(getValue(inputNumeral[i]) < getValue(inputNumeral[i + 1])) { //looking for smaller number before largest
                total+=getValue(inputNumeral[i+1]) - getValue(inputNumeral[i]); //subtract smaller val from larger to get number
                i++; //skip next iteration
                continue;
            }
            total += getValue(inputNumeral[i]);
        }
        if(rangeError(total)) {
            continue;
        }

        std::cout<<"Value is : "<<total<<'\n';
        std::cout<<"Continue ? Y/N";
        std::cin>>willContinue;

        if(willContinue == "n" || willContinue == "N") {
            stop=true;
            std::cout<<"Good Bye!\n";
        }
        std::cin.ignore(); //reset getline
    }
};
