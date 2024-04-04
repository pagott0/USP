import java.util.Scanner;

public class FactorialCalculator1 {

    // Recursive method to calculate factorial
    public static int factorialRecursive(int n) {
        if (n == 0) {
            return 1;
        }
        return n * factorialRecursive(n - 1);
    }

    // Iterative method to calculate factorial
    public static int factorialIterative(int n) {
        int result = 1;
        for (int i = 1; i <= n; i++) {
            result *= i;
        }
        return result;
    }
    // Iterative method to calculate sum of n numbers
    public static int sumIterative(int n) {
        int result = 0;
        for (int i = 1; i <= n; i++) {
            //sum the result with the current number
            result += i;
        }
        return result;
    }

    public static void main(String[] args) {

        Scanner myObj = new Scanner(System.in); // Creates a new object of Scanner class
        System.out.println("input: "); // Asks the user to input a number
        int number = myObj.nextInt(); // Reads an integer from the user
        if (number <= 0) { // Throws an exception if the input is not a positive integer
            throw new IllegalArgumentException("The input must be a positive integer");
        }
        System.out.println("Factorial of " + number + " (Recursive): " + factorialRecursive(number));
        System.out.println("Factorial of " + number + " (Iterative): " + factorialIterative(number));
        System.out.println("Sum of " + number + " (Iterative): " + sumIterative(number)); // Calls the methods to calculate factorial and sum of n numbers
    }
}