package LLD.splitwiseLLD.src;
import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.UUID;

public class Expense {
    private String id, title, description,splitType,expenseCreatorId; // for now assume only spendor creates the expense
    private HashMap<String,Integer> userContributionsMap;
    private int totalAmount;

    Expense(String creatorId, String expenseTitle, String splitType, int amount,ArrayList<String>userIds){
        // split the expense equally among all the users
        this.id = UUID.randomUUID().toString();
        this.totalAmount = amount;
        this.splitType = splitType;
        this.title = expenseTitle;
        this.expenseCreatorId = creatorId;

        int splitAmount = amount/userIds.size();

        for(String userId : userIds){
            userContributionsMap.put(userId,-splitAmount);
        }

        userContributionsMap.put(expenseCreatorId, userContributionsMap.get(expenseCreatorId) + amount);
    }

    String getExpenseCreator(){
        return this.expenseCreatorId;
    }

    HashMap<String,Integer> getUserContributionsMap(){
        return userContributionsMap;
    }

}

