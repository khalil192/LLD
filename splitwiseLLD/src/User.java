package LLD.splitwiseLLD.src;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.UUID;

public class User {

    private String id,name;
    private int totalAmountSpent;
    private HashMap<String, Integer> balance; //
    User(){
        id = UUID.randomUUID().toString();
        name = "NA";
        balance = new HashMap<>();
    }

    User(String n){
        id = UUID.randomUUID().toString();
        name = n;
    }

    String getName(){
        return name;
    }
    String getId(){
        return id;
    }

    void adjustAmount(String friendId, int amount){
        balance.put(friendId, balance.get(friendId) + amount);
    }

    HashMap<String, Integer> getBalanceSheet(){
        return balance;
    }
}

class AllUsers{
    HashMap<String, User> usersMapByName;
    HashMap<String, User> usersMapById;

    AllUsers(){
        usersMapByName = new HashMap<>();
        usersMapById = new HashMap<>();
    }
    User getOrCreateUserByName(String name){
        if(usersMapByName.containsKey(name)){
            return usersMapByName.get(name);
        }
        System.out.println("user not found, creating one" + name);
        User newUser = new User(name);
        usersMapByName.put(name,newUser);
        usersMapById.put(newUser.getId(),newUser);
        return newUser;
    }

    User getById(String userId){
         if(usersMapById.containsKey(userId)){
             return usersMapById.get(userId);
         }
        return null;
    }

    String getName(String id){
        if(usersMapById.containsKey(id)){
            return usersMapById.get(id).getName();
        }
        return "dummy";
    }

    void printBalanceSheetOfUser(String uname){
        User u = getOrCreateUserByName(uname);
        HashMap<String,Integer> balanceSheet = u.getBalanceSheet();
        System.out.println("printing balance sheet of " + uname);

        for(Map.Entry<String, Integer> e : balanceSheet.entrySet()){
            String eName = this.getName(e.getKey());
            System.out.println("------" + eName + " : " +  e.getValue());
        }
    }

    void printTotalBalanceSheet(){
        for(Map.Entry<String, User> e : usersMapByName.entrySet()){
            printBalanceSheetOfUser(e.getValue().getName());
        }
    }

}
