#include <iostream>
#include <functional>
// для указателя на функцию std::function<return_type(parameters)> name

// вводим число
int enterNum()
{
    int num;
    while (true)
    {
        std::cout << "Num -> ";
        std::cin >> num;

        // проверка
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
        }
        else
        {
            std::cin.ignore(32767, '\n');
            return num;
        }
    }
}

// вводим операцию
char enterOp()
{
    char op;
    while (true)
    {
        std::cout << "Operation (+, -, *, /) -> ";
        std::cin >> op;

        if (std::cin.fail())
            std::cin.clear();
        else if (op == '+' || op == '-'
            || op == '*' || op == '/') {
            std::cin.ignore(32767, '\n');
            return op;
        }

        std::cin.ignore(32767, '\n');
    }
}

// операции
int add(int a, int b)
{
    return a + b;
}

int subtract(int a, int b)
{
    return a - b;
}

int multiply(int a, int b)
{
    return a * b;
}

int divide(int a, int b)
{
    return a / b;
}

// определяем псевдоним для типа
typedef int(*arithmeticFcn)(int, int);

struct arithmeticStruct
{
    char op;
    arithmeticFcn fcn;
};

// массив структуры с операциями
static arithmeticStruct arithmeticArray[]
{
    {'+', add},
    {'-', subtract},
    {'*', multiply},
    {'/', divide}
};

// возвращаем функцию с нужной операцией
arithmeticFcn getArithmeticFcn(char op)
{
    for (auto &i: arithmeticArray)
        if (i.op == op)
            return i.fcn;
    // по умолчанию
    return add;
}

int main()
{
    using namespace std;
    
    int num1 = enterNum();
    char op = enterOp();
    int num2 = enterNum();

    // получаем указатель на функцию
    arithmeticFcn fcn = getArithmeticFcn(op);

    // вызываем функцию по укзаателю (неявно разыменовываем)
    cout << "Result is " << fcn(num1, num2);

    return 0;
}