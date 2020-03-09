import java.util.Arrays;
import java.util.Scanner;
import java.util.concurrent.SynchronousQueue;
//FOR GITHUB!!
public class ConnectFour {
    public static void main (String[] args){
        Scanner input = new Scanner (System.in);
        int height;
        int length;
        //DISPLAY INITIAL QUESTION
        System.out.print("What would you like the height of the board to be? ");
        height = input.nextInt();
        System.out.print("What would you like the length of the board to be? ");
        length = input.nextInt();
        char[][] charArr = new char[height][length];
        //INITIALIZE AND PRINT BOARD
        initializeBoard(charArr);
        printBoard(charArr);

        System.out.println();
        //DISPLAY PLAYER ROLE
        System.out.println("Player 1: x");
        System.out.println("Player 2: o");

        System.out.println();

        boolean playerWin = false;
        //LOOP FOR GAME
        while (playerWin == false){
            int check1 = 0;
            int p1Col;
            System.out.print("Player 1: Which column would you like to choose? ");
            p1Col = (input.nextInt());
            int p1Row = insertChip(charArr, p1Col, 'x');
            printBoard(charArr);
            System.out.println();
            if (checkIfWinner(charArr, p1Col, p1Row, 'x') == true){
                System.out.println("Player 1 won the game!");
                playerWin = true;
                break;
            }
            int p2Col;
            System.out.print("Player 2: Which column would you like to choose? ");
            p2Col = (input.nextInt()) ;
            int p2Row = insertChip(charArr, p2Col, 'o');
            printBoard(charArr);
            System.out.println();
            if (checkIfWinner(charArr, p2Col, p2Row, 'o') == true){
                System.out.println("Player 2 won the game!");
                playerWin = true;
                break;
            }
            //FOR TIE
            for (int i = charArr.length - 1; i>= 0;i--){
                for (int j = 0 ; j<charArr[0].length; j++) {
                    if (charArr[i][j] != '-'){
                        check1++;
                    }
                }
            }
            if (check1 == height*length)
            {
                System.out.println("Draw. Nobody wins.");
                playerWin = true;
            }
        }
    }
    //PRINTS BOARD
    public static void printBoard(char[][] array){
        for (int i = array.length - 1; i>=0; i--){
            for(int j = 0; j<array[0].length; j++){
                System.out.print(array[i][j] + " ");

            }
            System.out.println();
        }
    }
    //INITIALIZES BOARD
    public static void initializeBoard(char[][] array){
        for (int i = 0; i < array.length; i++) {
            for (int j = 0; j < array[0].length; j++ ){
                array[i][j] = '-';
            }
        }
    }
    //PUTS CHIP IN COLUMN AND RETURNS ROW
    public static int insertChip(char[][] array, int col, char chipType){
        int k;
        for (k = 0; k < array.length;){
            if (array[k][col] == 'x' || array[k][col] == 'o'){
            k++;
            }
           else {
                array[k][col] = chipType;
                break;
            }
        }
        return k ;
    }
    //CHECKS WINNER
   public static boolean checkIfWinner(char[][] array, int col, int row, char chipType) {
        boolean pWin = false;
       int n = 0;
       for (int i = 0; i<array.length; i++){
           if(array[i][col] == chipType) {
               n++;

               if (n == 4) {
                   pWin = true;
                   return pWin;
               }
           }
           else
               n = 0;
       }
       for (int j = 0; j < (array[0].length); j++) {
           if (array[row][j] == chipType) {
                   n++;

                   if (n == 4) {
                       pWin = true;
                       return pWin;
                   }
               }
           else
               n = 0;

           }


       return pWin;
   }

}
