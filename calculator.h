//
// Created by Kirill "Raaveinm" on 9/12/25.
//

#ifndef CALCULATOR_H
#define CALCULATOR_H

using Number = double;

class Calculator{
public:
    static bool RunCalculatorCycle();
    static Number GetSavedNumber() { return saved_number; } // Dear reviewer its singleton :3
    static void SetSavedNumber(const Number &value) { saved_number = value;  }
private:
    static bool is_set;
    static Number saved_number;
    bool ReadNumber(const Number& result);
    static bool IsInitialCommandCorrect(Number& currentValue);
};


#endif //CALCULATOR_H
