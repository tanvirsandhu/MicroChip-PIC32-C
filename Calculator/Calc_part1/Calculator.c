/* 
 * File:   Calculator.c
 * Author: Tanvir Sandhu (taksandh@ucsc.edu)
 *
 * Created on January 18, 2021, 4:49 PM
 */

// Standard libraries
#include <stdio.h>
#include <math.h>


//User libraries:
#include "BOARD.h"




// **** Declare function prototypes ****
double Add(double operand1, double operand2);
double Multiply(double operand1, double operand2);
double AbsoluteValue(double operand);
double FahrenheitToCelsius(double operand);
double Tangent(double operand);
//add more prototypes here
double Divide(double operand1, double operand2);
double Subtract(double operand1, double operand2);
double CelsiusToFahrenheit(double operand);
double Average(double operand1, double operand2);



void CalculatorRun(void)
{
    printf("\n\nWelcome to Tanvir's calculator program! Compiled at %s %s\n",__DATE__, __TIME__); 

    while (1) {
        char g;
        printf("\nEnter a mathematical operation to perform (*,/,+,-,m,a,c,f,t,r): ");
        scanf(" %c", &g);
        
        if (g == 'q') { //checks for break command before prompting for operand
            break;
        }
        if (g == '+' || g == '*' || g == '/' || g == '-' || g == 'm' || 
                g == 'a' || g == 'c' || g == 'f' || g == 't' || g == 'r') { 
        //checking if the user operator is valid, if it is, we continue.
            double op1;       //getting operand1
            printf("    Enter the first operand: "); 
            scanf("%lf", &op1);
            
            if (g == '+' || g == '*' || g == '/' || g == '-' || g == 'm') {
            //checking if the operator is binary and needs a second operand
                double op2;       //getting operand2
                printf("    Enter the second operand: "); 
                scanf("%lf", &op2);
      
                //nesting binary functions so op2 is defined
                if (g == '+'){ //if operator is +, will use the add function
                    double result = Add(op1, op2);
                    printf("    Result of (%lf + %lf): %lf", op1, op2, result);
                }
                if (g == '-'){ //if operator is -, will use the subtract function
                    double result = Subtract(op1, op2);
                    printf("    Result of (%lf - %lf): %lf", op1, op2, result);
                }
                if (g == '*'){ //if operator is *, will use the multiply function
                    double result = Multiply(op1, op2);
                    printf("    Result of (%lf * %lf): %lf", op1, op2, result);
                }   
                if (g == '/'){ //if operator is /, will use the divide function
                    if (op2 == 0) {
                        printf("    Divide by Zero Error!");
                    }
                    else{
                        double result = Divide(op1, op2);
                        printf("    Result of (%lf / %lf): %lf", op1, op2, result);
                    }

                }
                if (g == 'm') { //if operator is m, will use the average function
                    double result = Average(op1, op2);
                    printf("    Result of average of %lf and %lf: %lf", op1, op2, result);
                }
            } 
            //the unary functions are listed below because they only need op1
            if (g == 'a'){ //if operator is a, will use the absolute value function
                double result = AbsoluteValue(op1);
                printf("    Result of |%lf|: %lf", op1, result);
            }
            if (g == 'c') { //if operator is c, will use FtoC function
                double result = FahrenheitToCelsius(op1);
                printf("    Result of %lf F to Celsius: %lf C", op1, result);
            }
            if (g == 'f') { //if operator is f, will use CtoF function
                double result = CelsiusToFahrenheit(op1);
                printf("    Result of %lf C to Fahrenheit: %lf F", op1, result);
            }
            if (g == 't') { //if operator is t, will use the tangent function
                double result = Tangent(op1);
                printf("    Result of tan(%lf): %lf ", op1, result);
            }
            
        }
        
        else { //prints invalid operator if user input is not one of the given operators
            printf("    Invalid Operator!");
        }
    }
    
}



/********************************************************************************
 * Define the Add function here.
 ********************************************************************************/
double Add(double operand1, double operand2)
{
    double answer = operand1 + operand2;
    return answer;
}
/********************************************************************************
 * Define the Subtract function here.
 ********************************************************************************/
double Subtract(double operand1, double operand2)
{
	double answer = operand1 - operand2;
    return answer;
}

/********************************************************************************
 * Define the Multiply function here.
 ********************************************************************************/
double Multiply(double operand1, double operand2)
{
    double answer = operand1 * operand2;
    return answer;
}
/********************************************************************************
 * Define the Divide function here.
 ********************************************************************************/
double Divide(double operand1, double operand2)
{
	double answer = operand1/operand2;
    return answer;
}

/********************************************************************************
 * Define the Absolute Value function here.
 ********************************************************************************/
double AbsoluteValue(double operand)
{  
    double answer;
    
    if (operand < 0)
    {   
        answer = (operand * -1);
    }
    else { 
        answer = operand;
    }
    return answer;
}
/*********************************************************************************
 * Define the Fahrenheit to Celsius function here.
 ********************************************************************************/
double FahrenheitToCelsius(double operand)
{
    double answer = (5.0 / 9.0) * (operand - 32.0);
    return answer;
}
    
/*********************************************************************************
 * Define the Celsius to Fahrenheit function here.
 ********************************************************************************/
double CelsiusToFahrenheit(double operand)
{
    double answer = (operand * (9.0 / 5.0)) + 32.0;
    return answer;
}

/********************************************************************************
 * Define the Average function here.
 *******************************************************************************/
double Average(double operand1, double operand2)
{  
    double answer = (operand1 + operand2) / 2.0;
    return answer;
}

/*********************************************************************************
 * Define the Tangent function that takes input in degrees.
 ********************************************************************************/
double Tangent(double operand)
{
    double answer = tan((operand*(3.14159265358979323846264338327950288419/180)));
    return answer;
}
/*********************************************************************************
 * Define the Round function here.
 * In order to receive the extra credit your calculator MUST ALSO CORRECTLY utilize
 * this function.
 ********************************************************************************/
double Round(double operand)
{

}


