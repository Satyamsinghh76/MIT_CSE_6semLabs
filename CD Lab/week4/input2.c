#include <stdio.h>
#include <string.h>

int main() {
    char username[] = "admin";     // string initialization
    char password[] = "1234";      // string initialization

    char u[20], p[20];

    printf("Enter username: ");
    scanf("%s", u);

    printf("Enter password: ");
    scanf("%s", p);

    // logical AND (&&) operator
    if (strcmp(u, username) == 0 && strcmp(p, password) == 0) {
        printf("Login successful\n");
    }
    // logical OR (||) operator
    else if (strcmp(u, username) == 0 || strcmp(p, password) == 0) {
        printf("Partial match\n");
    }
    else {
        printf("Login failed\n");
    }

    return 0;
}
