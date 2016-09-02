/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cs3050project;

import java.util.ArrayList;

public class Stock {

    private String name;
    
    private ArrayList<Integer> pricesArray;
    private int[] masterBuyArray;
    private int[] masterSellArray;
    private int[] masterValuesArray;
    private int[] buyArray;
    private int[] sellArray;
    private int[] valuesArray;
    
    private int itemsIn;
    private int optimalTrades;
    private int currentTrades;
    private int totalValue;
    private int tradeValue;
    private int value;
    private int days;
    

    public Stock(){};
    
    public Stock(String filename, ArrayList priceList ,int days){
        this.pricesArray = priceList;
        this.masterBuyArray = new int[priceList.size()/2];
        this.masterSellArray = new int[priceList.size()/2];
        this.masterValuesArray = new int[priceList.size()/2];
        this.optimalTrades = 0;
        this.tradeValue = 0;
        this.totalValue = 0;
        this.name = filename;
        this.days = days;
        computeOptimalTrades();
        this.currentTrades = this.optimalTrades;
    }
    
    public String getName(){
        return name;
    }
    
    public void makeOneLessTrade(){
        int j = 0;
        while(this.valuesArray[j] == -1){//if artifact trade is found in first position, moves starting position forward until normal value found.
            j++;
        }
        
        int currentValue = this.valuesArray[j], position = j, offset = 1, savedOffset = 1; //current value holds the value of total ammount of money lost buy reducing number of trades by one
        boolean merge = false; //true for merging 2 trades, false for deleteing 1 trade
        //check all values for lowest
        for(int i = j+1; i < optimalTrades; i++){
            if((this.valuesArray[i] < currentValue || currentValue == -1) && this.valuesArray[i] != -1){ //checks for lowest value while accounting for artifact trades
               currentValue = this.valuesArray[i]; //reset lowest ammount lost
               position = i; //position of trade to be deleted              
            }
        }
        //check combinations of trades for lowest loss
        for(int i = j+1; i < optimalTrades; i++){
            if(this.sellArray[i] == -1){
                offset++; //keeps track of artifact trades between 2 trades
            }
            else {
                int previousTotal = this.valuesArray[i] + this.valuesArray[i-offset]; //combined value of 2 trades before merging
                int ammountRegained = pricesArray.get(this.sellArray[i]) - pricesArray.get(this.buyArray[i-offset]); //ammount of money recovered by merging trades
                int toCheck =  previousTotal - ammountRegained; //total ammount of money lost by merging trades
                if(toCheck < currentValue){
                    currentValue = toCheck; //assign new lowest loss
                    position = i; //save positon
                    savedOffset = offset; //account for artifact trades 
                    merge = true; //trade reduction is a merge
                }
                offset = 1; //reset offset
            }
        }
        //adjust for missing trade
        if(merge == false){ //if deleteing one trade
            this.buyArray[position] = -1;
            this.sellArray[position] = -1;
            this.value = this.value - this.valuesArray[position];
            this.valuesArray[position] = -1;
        }
        if(merge == true){ //if mergeing 2 trades
            this.value = this.value - this.valuesArray[position] + this.valuesArray[position-savedOffset]; //reduce value by removing the 2 trades to be merged
            this.value = this.value + pricesArray.get(this.sellArray[position]) - pricesArray.get(this.buyArray[position-savedOffset]); //increase value by ammount gained by makeing the new trade
            this.valuesArray[position-savedOffset] = pricesArray.get(this.sellArray[position]) - pricesArray.get(this.buyArray[position-savedOffset]); //1st trade become new trade. Set new value
            this.buyArray[position] = -1; //2nd trade becomes an artifact
            this.sellArray[position-savedOffset] = this.sellArray[position]; //set new sell date for first trade
            this.sellArray[position] = -1; //2nd trade becomes an artifact
            this.valuesArray[position] = -1; //2nd trade becomes an artifact
        }
        this.currentTrades = this.currentTrades-1; //keep track of number of trades
    }
    
    /**
     * used by constructor to find optimal solution given any number of trades
     * @param pricesArray int array of prices by day
     */
    private void computeOptimalTrades(){
        int i = 0; //hold location in price array
        boolean buy = true; //true for buy, false for sell
        while(i < pricesArray.size()-1){
            if((int)pricesArray.get(i) < (int)pricesArray.get(i+1) && buy){ //if today has a lower price than tommorrow, and program is set to buy
                this.masterBuyArray[this.optimalTrades] = i; //set buy day
                buy = false; //set program to sell
            }
            if((int)pricesArray.get(i) > (int)pricesArray.get(i+1) && !buy){ //if today has a high price than tommorrow, and program is set to sell
                this.masterSellArray[this.optimalTrades] = i; //set sell day
                buy = true; //set program to sell
                this.tradeValue = pricesArray.get(this.masterSellArray[this.optimalTrades]) - pricesArray.get(this.masterBuyArray[this.optimalTrades]); //sets tradeValue for trade
                this.totalValue = this.totalValue + this.tradeValue; //sets totalValue by ammount gained by trade
                this.masterValuesArray[this.optimalTrades] = this.tradeValue; //sets value for trade in array;
                this.optimalTrades = optimalTrades + 1; //increase number of trades by 1
            }
            i++; //go to next day
        }
        if(!buy){ //if it is last day, and program is set to sell
            this.masterSellArray[this.optimalTrades] = i; //sell stock
            this.tradeValue = pricesArray.get(this.masterSellArray[this.optimalTrades]) - pricesArray.get(this.masterBuyArray[this.optimalTrades]);
            this.totalValue = this.totalValue + this.tradeValue;
            this.masterValuesArray[this.optimalTrades] = this.tradeValue;
            this.optimalTrades = this.optimalTrades + 1; //increase number of trades by 1
        }
    }
    
    /*
        creates new arrays based on the master array to run in makeOneLessTrade, in order to
        allow multiple runs of different numbers of trades on the same file.
    */ 
    public void setBuySellValueArrays(){
        this.value = this.totalValue;
        this.currentTrades = optimalTrades;
        this.buyArray = new int[this.optimalTrades]; //create new array of correct size for all arrays
        this.sellArray = new int[this.optimalTrades];
        this.valuesArray = new int[this.optimalTrades];
        for(int i = 0; i < this.optimalTrades; i++){
            this.buyArray[i] = this.masterBuyArray[i]; //set new array
            this.sellArray[i] = this.masterSellArray[i];
            this.valuesArray[i] = this.masterValuesArray[i];
        }
    }
            
    public int[] getBuyArray() {
        return buyArray;
    }
    
    public int[] getSellArray() {
        return sellArray;
    }
    
    public int getCurrentTrades() {
        return currentTrades;
    }
    
    public int getOptTrades(){
        return optimalTrades;
    }
    
    public int getDays(){
        return this.days;
    }
    
}
