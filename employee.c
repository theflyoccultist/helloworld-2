#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// assign salaries to each department
enum departments { HR, SALES, RESEARCH, SOFTWARE, EXECUTIVE };
const int SALARIES[] = {70000, 60000, 120000, 180000, 100000};
#define SALARY_OVER rand() % 10000 + 1
const char *DEPARTMENT_NAMES[] = {"HR", "Sales", "Research", "Software", "Executive"};

// generate random social security numbers
#define SSN_MAX 999999999
#define SSN_MIN 100000000
#define SSN ((rand() % (SSN_MAX - SSN_MIN + 1)) + SSN_MIN)

// prints the salary and SSN for each department
void process_departments() {
    for (int department = HR; department <= EXECUTIVE; department++) {
      printf("SSN: %d\t", SSN);
      printf("Salary for %s: %d\n", DEPARTMENT_NAMES[department], (SALARIES[department] + SALARY_OVER));
    }
}

// callls the process_departments function twice (for 10 employees)
int main()
  { 
    srand(time(0));
    process_departments();
    printf("\n---- Second Run ----\n\n");
    process_departments();
    return 0;
  }