#include <iostream>

class Time {
private:
    int hours;
    int minutes;
    int seconds;

public:
    // Конструктор по умолчанию
    Time();

    // Конструктор с параметрами
    Time(int h, int m, int s);

    // Деструктор
    ~Time();

    // Перегрузка оператора '-' для вычитания времени
    Time operator-(const Time& other);

    // Перегрузка оператора '==' для сравнения времени
    bool operator==(const Time& other);

    // Перегрузка оператора '!=' для сравнения времени
    bool operator!=(const Time& other);

    // Функция для вывода времени
    void displayTime();

    // Дружественная функция для перегрузки оператора '+'
    friend Time operator+(const Time& time, int minutesToAdd);
};

// Определение дружественной функции оператора '+'
Time operator+(const Time& time, int minutesToAdd) {
    Time result = time;
    result.minutes += minutesToAdd;

    // Переводим минуты в часы, если количество минут больше или равно 60
    if (result.minutes >= 60) {
        result.hours += result.minutes / 60;
        result.minutes %= 60;
    }

    return result;
}

// Определения функций-членов класса Time

// Конструктор по умолчанию
Time::Time() : hours(0), minutes(0), seconds(0) {}

// Конструктор с параметрами
Time::Time(int h, int m, int s) : hours(h), minutes(m), seconds(s) {}

// Деструктор
Time::~Time() {}

// Перегрузка оператора '-' для вычитания времени
Time Time::operator-(const Time& other) {
    Time result;
    int thisTotalMinutes = hours * 60 + minutes;
    int otherTotalMinutes = other.hours * 60 + other.minutes;
    int differenceMinutes = thisTotalMinutes - otherTotalMinutes;

    if (differenceMinutes < 0) {
        differenceMinutes = 0;
    }

    result.hours = differenceMinutes / 60;
    result.minutes = differenceMinutes % 60;
    return result;
}

// Перегрузка оператора '==' для сравнения времени
bool Time::operator==(const Time& other) {
    return (hours == other.hours && minutes == other.minutes && seconds == other.seconds);
}

// Перегрузка оператора '!=' для сравнения времени
bool Time::operator!=(const Time& other) {
    return !(*this == other);
}

// Функция для вывода времени
void Time::displayTime() {
    std::cout << hours << ":" << minutes << ":" << seconds << std::endl;
}

int main() {
    setlocale(LC_ALL, "");
    int hours1, minutes1, seconds1;
    int hours2, minutes2, seconds2;
    int minutesToAdd;

    std::cout << "Введите время 1 (часы минуты секунды): ";
    std::cin >> hours1 >> minutes1 >> seconds1;

    std::cout << "Введите время 2 (часы минуты секунды): ";
    std::cin >> hours2 >> minutes2 >> seconds2;

    std::cout << "Сколько минут прибавить к Time 1: ";
    std::cin >> minutesToAdd;

    Time time1(hours1, minutes1, seconds1);
    Time time2(hours2, minutes2, seconds2);

    Time result1 = time1 + minutesToAdd;
    Time result2 = time1 - time2;

    std::cout << "Time 1: ";
    time1.displayTime();

    std::cout << "Time 2: ";
    time2.displayTime();

    std::cout << "Time 1 + " << minutesToAdd << " minutes: ";
    result1.displayTime();

    std::cout << "Time 1 - Time 2: ";
    result2.displayTime();

    if (time1 == time2) {
        std::cout << "Time 1 is equal to Time 2." << std::endl;
    }
    else {
        std::cout << "Time 1 is not equal to Time 2." << std::endl;
    }

    return 0;
}
