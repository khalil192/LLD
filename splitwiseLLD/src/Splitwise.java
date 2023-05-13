package LLD.splitwiseLLD.src;
import java.util.ArrayList;
import java.util.HashMap;

public class Splitwise {

    private AllGroups GroupDb;
    private AllUsers userDb;
    Splitwise(){
        userDb = new AllUsers();
        GroupDb = new AllGroups();
    }

    void createGroup(String groupName){
        Group group = GroupDb.getOrCreateGroupByName(groupName);
        System.out.println(groupName + " group is created");
    }
    void createUser(String uname){
        User u  = userDb.getOrCreateUserByName(uname);
        System.out.println(uname + " user is created");
    }

    void addUserToGroup(String groupName, String userName){
        User user = userDb.getOrCreateUserByName(userName);
        Group group = GroupDb.getOrCreateGroupByName(groupName);

        group.addUser(user);

        System.out.println(user.getName() + " is added to "+ group.getName());

    }

    void createExpense(String groupName, Expense expense){
        Group group = GroupDb.getOrCreateGroupByName(groupName);
        group.addExpense(expense);
        System.out.println( " expense is added ");

    }

    void printBalanceSheetOfUser(String uName){
         userDb.printBalanceSheetOfUser(uName);
    }

    void printTotalBalanceSheet(){
        userDb.printTotalBalanceSheet();
    }

    void printGroupMembers(String gname){
         GroupDb.getOrCreateGroupByName(gname).printAllUserNames();
    }
}
