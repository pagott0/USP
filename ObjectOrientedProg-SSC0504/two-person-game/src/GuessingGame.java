import java.util.Random;
import java.util.Scanner;
public class GuessingGame {
    private int targetNumber;
    private int numberGuesses;
    private boolean hasGuessedRight;

    //Constructor: initialize the attributes of the game. Target number is a random number between 1 and 100, number of guesses 0 and the user have not guessed right yet.
    public GuessingGame() {
        Random rand = new Random();
        targetNumber = rand.nextInt(100) + 1;
        numberGuesses = 0;
        hasGuessedRight = false;
    }

    //basically it is the same thing of the constructor, but it prints the message of the game.
    //i'm using this method to initialize the game again if the user wants to play another time.
    public void setup() {
        Random rand = new Random();
        targetNumber = rand.nextInt(100) + 1;
        numberGuesses = 0;
        hasGuessedRight = false;
        System.out.println("GUESSING GAME: The computer is thinking about a number between 1 and 100, if you guess it right, you win.");
    }

    //method to accept the user guess and check if it is right. if it is, change the hasGuessedRight to true
    //always sum one to the number of guesses
    //returns the feedback to the user in every play
    //checks if the guess is in the right range (1 ... 100)
    public void acceptGuess(int guess) {
        if(guess > 100 || guess < 1) {
            System.out.println("Your guess should be between 1 and 100, try again.");
            return;
        }
        if(guess == targetNumber) {
            hasGuessedRight = true;
        }
        numberGuesses++;
        String feedback = feedback(guess);
        System.out.println(feedback);
    }

    //returns the number of guesses, used when the user win.
    public int countGuess() {
        return numberGuesses;
    }

    //method to return the feedback of the current guess.
    public String feedback(int guess) {
        if(guess == targetNumber) {
            return "Correct! You won! Number of guesses: " + countGuess();
        } else if (guess > targetNumber) {
            return "Hmmm... Try a lower number.";
        } else {
            return "Nop, you should try a higher number";
        }
    }
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        GuessingGame game = new GuessingGame();
        System.out.println("GUESSING GAME: The computer is thinking about a number between 1 and 100, if you guess it right, you win.");
        while(!game.hasGuessedRight) {
            System.out.println("Enter you guess!");
            int userGuess = scanner.nextInt();
            scanner.nextLine(); // Consume the newline character (clean the buffer)
            game.acceptGuess(userGuess);
            //once the user guessed right, check if wants to play again. If wants, call the setup and restarts. Else, show thanks message and ends the while.
            if(game.hasGuessedRight) {
                System.out.println("Do you want to play again? (y/n)");
                String wantsToPlayAgain = scanner.nextLine();
                if(wantsToPlayAgain.equals("y")) {
                    game.setup();
                } else {
                    System.out.println("Thanks for playing.");
                }
            }
        }
    }
}
