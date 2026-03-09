#include <iostream>
#include <sstream>
#include <limits>
#include <iomanip>

using namespace std;

class Time {
private:
    int hours;
    int minutes;
    int seconds;

public:
    Time(int h = 0, int m = 0, int s = 0);

    ~Time();

    bool isValid() const;

    bool operator==(const Time& other) const;

    Time operator+(const Time& other) const;

    friend Time& operator-(const Time& time, const Time& other);

    friend ostream& operator<<(ostream& os, const Time& time);

    friend istream& operator>>(istream& is, Time& time);
};

// Определения функций класса Time

Time::Time(int h, int m, int s) : hours(h), minutes(m), seconds(s) {}

Time::~Time() {}

bool Time::isValid() const {
    return (hours >= 0 && hours < 24 && minutes >= 0 && minutes < 60 && seconds >= 0 && seconds < 60);
}

bool Time::operator==(const Time& other) const {
    return (hours == other.hours && minutes == other.minutes && seconds == other.seconds);
}

Time Time::operator+(const Time& other) const {
    Time result = *this;
    result.seconds += other.seconds;
    result.minutes += result.seconds / 60 + other.minutes;
    result.seconds %= 60;
    result.hours += result.minutes / 60 + other.hours;
    result.minutes %= 60;

    // Проверка и коррекция времени
    if (result.hours >= 24) {
        result.hours %= 24;
    }

    // Преобразуем результат в положительное значение
    if (result.hours < 0) {
        result.hours += 24;
    }
    else if (result.hours >= 24) {
        result.hours %= 24;
    }

    return result;
}

Time& operator-(const Time& time, const Time& other) {
    int thisSeconds = time.hours * 3600 + time.minutes * 60 + time.seconds;
    int otherSeconds = other.hours * 3600 + other.minutes * 60 + other.seconds;
    int diffSeconds = thisSeconds - otherSeconds;

    // Преобразуем результат в положительное значение
    if (diffSeconds < 0) {
        diffSeconds += 24 * 3600;
    }

    Time result;
    result.hours = diffSeconds / 3600;
    result.minutes = (diffSeconds % 3600) / 60;
    result.seconds = diffSeconds % 60;

    return result;
}

ostream& operator<<(ostream& os, const Time& time) {
    int h = time.hours;
    int m = time.minutes;
    int s = time.seconds;

    // Проверка и коррекция времени
    if (h < 0) {
        h += 24;
    }
    else if (h >= 24) {
        h %= 24;
    }

    if (m < 0) {
        m += 60;
        h -= 1;
    }
    else if (m >= 60) {
        m %= 60;
        h += 1;
    }

    if (s < 0) {
        s += 60;
        m -= 1;
    }
    else if (s >= 60) {
        s %= 60;
        m += 1;
    }

    os << setw(2) << setfill('0') << h << ':'
        << setw(2) << setfill('0') << m << ':'
        << setw(2) << setfill('0') << s;
    return os;
}

istream& operator>>(istream& is, Time& time) {
    string input;
    is >> input;

    int h, m, s;
    char delimiter;
    istringstream ss(input);
    ss >> h >> delimiter >> m >> delimiter >> s;

    if (ss.fail() || delimiter != ':' || ss.get() != EOF || h < 0 || m < 0 || s < 0) {
        is.setstate(ios::failbit);
    }
    else {
        // Проверка и коррекция времени
        if (m >= 60) {
            h += m / 60;
            m %= 60;
        }
        if (s >= 60) {
            m += s / 60;
            s %= 60;
        }

        // Проверка и коррекция часов
        if (h >= 24) {
            h %= 24;
        }

        time.hours = h;
        time.minutes = m;
        time.seconds = s;
    }

    return is;
}

int main() {
    system("chcp 1251 > nul");
    system("color 71");

    Time userTime;

    while (true) {
        cout << "Введите время в формате часы:минуты:секунды (от 00:00:00 до 23:59:59): ";
        cin >> userTime;
        if (userTime.isValid() && !cin.fail()) {
            break;
        }
        else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Неправильный формат времени. Повторите ввод." << endl;
        }
    }

    cout << "Что вы хотите сделать?" << endl;
    cout << "1. Добавить время" << endl;
    cout << "2. Вычесть время" << endl;
    int choice;
    cin >> choice;

    Time timeToAddOrSubtract;

    while (true) {
        cout << "Введите время для добавления/вычитания в формате часы:минуты:секунды (от 00:00:00 до 99:99:99): ";
        cin >> timeToAddOrSubtract;
        if (!cin.fail()) {
            break;
        }
        else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Неправильный формат времени. Повторите ввод." << endl;
        }
    }

    Time modifiedTime;

    if (choice == 1) {
        modifiedTime = userTime + timeToAddOrSubtract;
    }
    else if (choice == 2) {
        modifiedTime = userTime - timeToAddOrSubtract;
    }
    else {
        cout << "Неверный выбор." << endl;
        return 1;
    }

    cout << "Результат: " << modifiedTime << endl;

    if (userTime == modifiedTime) {
        cout << "Исходное и измененное время равны." << endl;
    }
    else {
        cout << "Исходное и измененное время не равны." << endl;
    }

    return 0;
}
