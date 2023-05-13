package LLD.splitwiseLLD.src;
import java.util.Scanner;

import LLD.splitwiseLLD.Splitwise;

// Press ⇧ twice to open the Search Everywhere dialog and type `show whitespaces`,
// then press Enter. You can now see whitespace characters in your code.
public class Main {
    public static void main(String[] args) {

        Splitwise sw = new Splitwise();

        Scanner sc = new Scanner(System.in);
        int cmd = 1;

        while(cmd != 0){

            System.out.println("************Enter The Operation To Perform**********");

            System.out.println("1. Add User     2. Add Group     3.Add User To Group");

            System.out.println("4. List group members");

            System.out.println("5.Add Expense To Group      6.Print Balance sheet of User \n 7.print total balance sheet");

            System.out.println("0.Exit");
            cmd = sc.nextInt();

            if(cmd == 1){
                System.out.println("Enter User Name");
                String uname = sc.next();
                sw.createUser(uname);
            }else if(cmd == 2){
                System.out.println("Enter Group Name");
                String gname = sc.next();
                sw.createGroup(gname);
            }else if(cmd == 3){
                System.out.println("Enter Group Name");
                String gname = sc.next();
                System.out.println("Enter User Name");
                String uname = sc.next();
                sw.addUserToGroup(gname,uname);
            }else if(cmd == 4) {

                System.out.println("Enter Group Name");
                String gname = sc.next();
                sw.printGroupMembers(gname);

            }else if(cmd == 5){

            }


        }


    }
}