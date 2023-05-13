package LLD.splitwiseLLD.src;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.UUID;

public class Group{

    private String id, name;
    private ArrayList<User> listOfUsers;
    private ArrayList<Expense> listOfExpenses;
    Group(){
        id = UUID.randomUUID().toString();
        listOfExpenses = new ArrayList<>();
        listOfUsers = new ArrayList<>();
    }
    Group(String n){
        id = UUID.randomUUID().toString();
        name = n;
        listOfUsers = new ArrayList<>();
        listOfExpenses = new ArrayList<>();
    }

    String getName(){
        return name;
    }
    void addUser(User newUser){
        if(!checkIfUserPresent(newUser)) {
            listOfUsers.add(newUser);
        }
    }

    User getByName(String targetName){
        for(User u : listOfUsers){
            if(u.getName() == targetName){
                return u;
            }
        }
        return listOfUsers.get(0);
    }
    User getById(String targetId){
        for(User u : listOfUsers){
            if(u.getId() == targetId){
                return u;
            }
        }
        return listOfUsers.get(0);
    }

    boolean checkIfUserPresent(User user){
        for(User u : listOfUsers){
            if(u.getName() == user.getName()){
                return true;
            }
        }
        return false;
    }

    void printAllUserNames(){
        System.out.print("\n"+  name+" group members are : ");
        for(User u : listOfUsers){
            System.out.print(u.getName() + " ");
        }
        System.out.println();
    }

    void addExpense(Expense newExpense){
            listOfExpenses.add(newExpense);

            String expenseCreator = newExpense.getExpenseCreator();
            HashMap<String,Integer> contributions = newExpense.getUserContributionsMap();

            User u1 = getById(expenseCreator);

            for(Map.Entry<String, Integer> c : contributions.entrySet()){
                //   u1 is paying for the expense so u2 owes u1
                User u2 = getById(c.getKey());
                addExpenseSplit(u1, u2, c.getValue());
            }
    }

    //   u2  owes u1 here
    void addExpenseSplit(User u1, User u2, int amount){
        u1.adjustAmount(u2.getId(), -1 * amount);
        u2.adjustAmount(u1.getId(), amount);
    }
}


class AllGroups{
    HashMap<String, Group> groupsMapByName;

    AllGroups(){
        groupsMapByName = new HashMap<>();
    }
    Group getOrCreateGroupByName(String groupName){
          if(groupsMapByName.containsKey(groupName)){
              return groupsMapByName.get(groupName);
          }
          Group g = new Group(groupName);
          groupsMapByName.put(groupName,g);
          return g;
    }

}