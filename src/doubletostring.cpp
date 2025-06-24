
int pow(int base, int exp) {
    int result = 1;
    for (int i = 0; i < exp; i++) {
        result *= base;
    }
    return result;
}

void reverse(char* str, int length) {
    int start = 0;
    int end = length - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

// Function to convert an integer to a character array
int intToStr(int x, char str[], int d) {
    int i = 0;
    while (x) {
        str[i++] = (x % 10) + '0';
        x = x / 10;
    }
    while (i < d) // Pad with leading zeros if needed
        str[i++] = '0';
    reverse(str, i);
    str[i] = '\0';
    return i;
}

// Function to convert a double to a character array
void doubleToStr(double n, char* res, int afterpoint = 1000000000) {
    long long ipart = (long long)n; // Integer part
    double fpart = n - (double)ipart; // Fractional part

    int i = intToStr(ipart, res, 0); // Convert integer part

    if (afterpoint != 0) {
        res[i] = '.'; // Add decimal point
        fpart = fpart * pow(10, afterpoint); // Scale fractional part
        intToStr((int)fpart, res + i + 1, afterpoint); // Convert fractional part
    }
}