// This program only works in a windows pc
// The program is capable of calculating 6 band resistor value
// Written by ←ARROW↔ATOM→
#include <stdio.h>
#include <stdbool.h>
#include <windows.h>
#include <conio.h>

#include "color.c" // include the color.c file

// clrscr() has some limitations
void cls(void) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coordScreen = {0, 0};
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD dwConSize;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    FillConsoleOutputCharacter(hConsole, (TCHAR)' ',
       dwConSize, coordScreen, &cCharsWritten);
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes,
       dwConSize, coordScreen, &cCharsWritten);
    SetConsoleCursorPosition(hConsole, coordScreen);
}

// For reading resistor band
void read_band(int *res_band) {
    printf("Choose from the given values:\n");
    printf(" 4. BAND4 \n 5. BAND5 \n 6. BAND6 \n");
    printf("Enter your choice.\n");
    scanf("%d", res_band);
}

// Validating the resistor band value
void check_res_band(int *res_band) {
    bool check = true;

    while(check) {
        if(*res_band > 6 || *res_band < 4) {
            cls();
            color("YOUR CHOICE IS INCORRECT !!.You should enter only the choices given:\n", RED);
            read_band(res_band);
            check = true;
        } else {
            check = false;
        }
    }
}

// For printing the color code
void print_color_list() {
    color("\n0. Black\t", BLACK);
    color("1. Brown\t", BROWN);
    color("2. Red\t", RED);
    color("3. Orange\t", ORANGE);
    color("4. Yellow\t", YELLOW);
    color("5. Green\t\n", GREEN);
    color("6. Blue\t", BLUE);
    color("7. Violet\t", VIOLET);
    color("8. Grey\t", GREY);
    color("9. White\t", WHITE);
    color("10. Gold\t", GOLD);
    color("11. Silver\t", SILVER);
    printf("12. None\n\n");
}

// Input values according to the band
void input_values(int res_band, int *digit, int *multiplier, int *tolerance, int * temcoef) {
    print_color_list();
    for(int i = 0; i < 6; i++) {
        printf("Enter color no: %d\n", i + 1);
        if(res_band == 4) {
            if(i < 2) {
                scanf("%d", digit + i);
                *(digit + 2) = 0;
            } else if(i == 2) {
                scanf("%d", multiplier);
            } else {
                scanf("%d", tolerance);
                return;
            }
        } else if(res_band == 5) {
            if(i < 3) {
                scanf("%d", digit + i);
            } else if(i == 3) {
                scanf("%d", multiplier);
            } else {
                scanf("%d", tolerance);
                return;
            }
        } else {
            if(i < 3) {
                scanf("%d", digit + i);
            } else if(i == 3) {
                scanf("%d", multiplier);
            } else if(i == 4) {
                scanf("%d", tolerance);
            } else {
                scanf("%d", temcoef);
            }
        }
    }
}

// Exit the program when invalid input is given
void invalid_colorcode() {
    color("Your color code is invalid", RED);
    getch();
    exit(0);
}

void read_digits(int res_band, int *digit, int *multiplier, int *tolerance, int * temcoef) {
    color("\n From left-to-right choose the colors in resistor \n", GREEN);
    input_values(res_band, digit, multiplier, tolerance, temcoef);
}

// returns the the multiplier value
float get_multiplier(int multiplier) {
    switch(multiplier) {
        case(0):
            return 1;
        case(1):
            return 10;
        case(2):
            return 100;
        case(3):
            return 1000;
        case(4):
            return 10000;
        case(5):
            return 100000;
        case(6):
            return 1000000;
        case(7):
            return 10000000;
        case(10):
            return 0.1;
        case(11):
            return 0.01;
        case(8):
        case(9):
        case(12):
            invalid_colorcode();

    }
    return 0;
}

// returns tolerance value
float get_tolerance(int tolerance) {
    switch(tolerance) {
        case(1):
            return 1;
        case(2):
            return 2;
        case(5):
            return 0.5;
        case(6):
            return 0.25;
        case(7):
            return 0.1;
        case(8):
            return 0.05;
        case(10):
            return 5;
        case(11):
            return 10;
        case(12):
            return 20;
        case(0):
        case(3):
        case(4):
        case(9):
            invalid_colorcode();
    }
    return 0;

}


// returns temperature cofficient
int get_temcoef(int temcoef) {
    switch(temcoef) {
        case(1):
            return 100;
        case(2):
            return 50;
        case(3):
            return 15;
        case(4):
            return 25;
        case(6):
            return 10;
        case(7):
            return 5;
        case(5):
        case(8):
        case(9):
        case(10):
        case(11):
        case(12):
            invalid_colorcode();
    }
    return 0;
}

// Print resistance
void calc_resistance(int res_band, int digit[],  int multiplier, int tolerance, int  temcoef) {
    int value;
    float multiplier_, tolerance_;
    for(int i = 0; i < 3; i++) {
        if(digit[i] > 9) {
            invalid_colorcode();
        }
    }

    if(res_band == 4) {
        value = (digit[0]) * 10 + (digit[1]);
        multiplier_ = get_multiplier(multiplier);
        tolerance_ = get_tolerance(tolerance);
        color("\n\nThe Value of resistor:   ", BLUE_1);
        printf("%d * %1.2f ohms +- %1.2f %%", value, multiplier_, tolerance_);
        printf("\n\n\n");
    } else if(res_band == 5) {
        value = (digit[0] * 10 + digit[1]) * 10 + digit[2];
        multiplier_ = get_multiplier(multiplier);
        tolerance_ = get_tolerance(tolerance);
        color("\n\nThe Value of resistor:   ", BLUE_1);
        printf("%d * %1.2f ohms +- %1.2f %%", value, multiplier_, tolerance_);
        printf("\n\n\n");
    } else {
        value = (digit[0] * 10 + digit[1]) * 10 + digit[2];
        multiplier_ = get_multiplier(multiplier);
        tolerance_ = get_tolerance(tolerance);
        color("\n\nThe Value of resistor:   ", BLUE_1);
        printf("%d * %1.2f ohms +- %1.2f %% ( %d ppm/k)", value, multiplier_, tolerance_, get_temcoef(temcoef));
        printf("\n\n\n");
    }
}

int main() {
    int res_band, digit[3], tolerance = 0, temcoef = 0, multiplier = 0;
    int i = 1;
    while(i) {
        printf("Enter the Band:\n");
        read_band(&res_band);
        check_res_band(&res_band);
        read_digits(res_band, &digit[0], &multiplier, &tolerance, &temcoef);
        calc_resistance(res_band, digit, multiplier, tolerance, temcoef);
        printf("Do you want to find more values:\n");
        printf(" 1. Yes\n 0. No\n");
        scanf("%d", &i);
        cls();
    }
}

