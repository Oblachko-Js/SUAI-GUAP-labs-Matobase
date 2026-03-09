#include <iostream>
#include <cmath>
using namespace std;

void calculate_z1_and_z2(double a, double& z1, double& z2);
double get_number(char var_name);


int main()
{
    double a = get_number('a');

    double z1 = 0, z2 = 0;
    calculate_z1_and_z2(a, z1, z2);

    if (z1 != 0 && z2 != 0) {
        cout << endl << "z1 = " << z1 << endl << "z2 = " << z2 << endl;
    }
    else {
        cout << "Cannot calculate z1 and z2 for the given value of a." << endl;
    }

    system("pause");
    return 0;
}


double get_number(char var_name) {
    double arg;
    cout << "Enter " << var_name << ": ";

    while (!(cin >> arg)) {
        cin.clear();
        //cin.ignore(100, '\n');
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "You entered not a number!\n" << "Enter " << var_name << ": ";;
    }
    return arg;
}


void calculate_z1_and_z2(double a, double& z1, double& z2)
{
    if (a <= 0)
        return;

    else {
        if ((a - 2 * sqrt(a)) <= 0)
            return;

        else {
            z1 = ((a - 2) / pow(a, 2)) + (sqrt(pow(a, 2) - 4 * a * sqrt(a) + 4 * a)) /
                (sqrt(a - 2 * sqrt(a)));
            z2 = (static_cast<double>(1) / a) - (2 / pow(a, 2)) + sqrt(a - 2 *
                sqrt(a));
        }
    }
}
