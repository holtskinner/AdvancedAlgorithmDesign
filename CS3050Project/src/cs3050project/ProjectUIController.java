/*
 * Creators: Justin Hofer, Jonathon Israel, Holt Skinner
 * CS3050 Final Project
 */
package cs3050project;

import java.io.File;
import java.io.FileNotFoundException;
import java.net.URL;
import java.util.ArrayList;
import java.util.NoSuchElementException;
import java.util.ResourceBundle;
import java.util.Scanner;
import javafx.event.ActionEvent;
import javafx.event.Event;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Menu;
import javafx.scene.control.MenuItem;
import javafx.scene.control.TextField;
import javafx.scene.layout.AnchorPane;
import javafx.scene.text.Text;
import javafx.stage.FileChooser;
import javafx.stage.Stage;

public class ProjectUIController implements Initializable {
    
    @FXML
    private AnchorPane anchor;
    
    @FXML
    private TextField tradesText;
    
    @FXML
    private Text infoText;
    
    @FXML
    private Text optimalText;
    
    @FXML
    private Text tradesSolutionText;
    
    @FXML
    private Text fileText;
    
    @FXML
    private Text buyText;
    
    @FXML
    private Text sellText;
    
    @FXML
    private Text days;
    
    @FXML
    private Menu openFileMenu;
    
    private ArrayList<Stock> stocks;
    private Stock currentStock;
        
    @Override
    public void initialize(URL url, ResourceBundle rb) {
       stocks = new ArrayList<>();
       currentStock = null;
    }
    /*
    When a stock is chosen from Opened Files, that stock is set as the current stock,
    the total number of days in the file and the optimal max number of trades is
    set, and the buy, sell, and number of trades fields are cleared.
    */
    private void selectFile(ActionEvent event) {
        MenuItem menuItem = (MenuItem)event.getSource();
        Stock stock = (Stock)menuItem.getUserData();
        currentStock = stock;
        fileText.setText(currentStock.getName());
        infoText.setText("File selected. Input number of trades or choose new file.");
        days.setText(Integer.toString(currentStock.getDays()));
        optimalText.setText(Integer.toString(currentStock.getOptTrades()));
        buyText.setText("");
        sellText.setText("");
        tradesSolutionText.setText("");        
    }
    /*
    grabs all ints from file and constructs a stock. Returns
    false and prints error if error; returns true and passes priceList, file name, and size of 
    list to createStock if successful.
    */
    private boolean openFile (File file){
        infoText.setText("");
        Scanner fileIn;
        ArrayList priceList = new ArrayList<>();
        int itemsIn = 0;
        
        try{
            try{
                fileIn = new Scanner(file); //start scanner
            }catch(FileNotFoundException F){
                throw new Exception("File Not Found");
            }
            int toAdd;
            do{
                try{ //attempt to add line
                    toAdd = Integer.parseInt(fileIn.nextLine()); //get next token as an int
                    if(toAdd <= 0){ //if invalid number, throw Exception
                        throw new Exception("Negative Number or Zero Encountered");
                    }
                    priceList.add(toAdd); //add to arraylist
                    itemsIn++;
                }catch(NumberFormatException NFE){
                    fileIn.close();
                    throw new Exception("Improperly Formatted Line Encountered");

                }
                catch(NoSuchElementException nsee){
                    fileIn.close();
                    throw new Exception("Empty File Encountered");
                }
            }while(fileIn.hasNext()); //do while to check for empty file
            if(itemsIn<2){
                fileIn.close();
                throw new Exception("Not Enough Integers In File");
            }
        }catch(Exception E){
            infoText.setText("Error: "+E.getMessage());
            return false;
        }
        fileIn.close();
        infoText.setText("File successfully opened. Computing optimal number of max trades. Please wait.");
        createStock(file.getName(), priceList, itemsIn);
        return true;
    }
    /*
    Creates new object Stock and links it to menu openFileMenu for selection by user.
    */
    private void createStock(String filename, ArrayList priceList, int itemsIn){
        Stock stock = new Stock(filename, priceList, itemsIn);
        stocks.add(stock);
        MenuItem menuItem = new MenuItem(stock.getName());
        menuItem.setUserData(stock);
        menuItem.setOnAction((ActionEvent event) -> {
            selectFile(event);
        });
        openFileMenu.getItems().add(menuItem);
    }
    /*
    Calls functions to initialize arrays for makeOneLessTrade, sets currentTrades
    equal to optimalTrades, and then calls makeOneLessTrade while the current number
    of trades is more than the number of trades specified by the user.
    */
    private void computeTrades(int trades){
        currentStock.setBuySellValueArrays();
        while(currentStock.getCurrentTrades() > trades){
            currentStock.makeOneLessTrade();
        }
    }
    /*
    Sets buy and sell Strings to empty before filling them with the currently selected
    stock's buy and sell dates, coverting the dates from integers to strings, and finally
    printing them and the solutions number of trades to text fields in the ui.
    */
    private void printSolution(){
        String buyString = "";
        String sellString = "";
        
        for(int i = 0; i < currentStock.getOptTrades(); i++){
            int check = currentStock.getBuyArray()[i];
            if(check != -1) {
                buyString = buyString + Integer.toString(currentStock.getBuyArray()[i]+1) + ", ";
                sellString = sellString + Integer.toString(currentStock.getSellArray()[i]+1) + ", ";
            }
        }
        
        tradesSolutionText.setText(Integer.toString(currentStock.getCurrentTrades()));
        buyText.setText(buyString);
        sellText.setText(sellString);
    }
    /*
    When open is selected from file, opens a new window for selection of file, preventing
    user from using the previous window until the new one is closed. Then passes the file
    to openFile.
    */
    @FXML
    private void handleOpen (Event event) {
        Stage primaryStage = (Stage)anchor.getScene().getWindow();
        FileChooser fileChooser = new FileChooser();
        File file = fileChooser.showOpenDialog(primaryStage);
        if(openFile(file)){
            infoText.setText("Computing complete. Open another file or select an open file to run trades on.");
        }
    }
    /*
    When the run button is pressed, checks for a selected file and the value in the
    text box tradesText. If a file is present and the value in tradesText is a positive
    integer, calls computeTrades and printSolution.
    */
    @FXML
    private void handleRun (ActionEvent event) {
        if (currentStock == null){
            infoText.setText("Please select a file to read from.");
        }else{
            if(tradesText.getText() != null && !tradesText.getText().isEmpty()) {
                try {
                    int numTrades = Integer.parseInt(tradesText.getText());
                    if (numTrades <= 0) {
                        infoText.setText("Number of trades is negative or equal to 0. Please enter a positive integer.");
                    } else {
                        infoText.setText("Computing best solution based on number of trades allowed.");
                        computeTrades(numTrades);
                        printSolution();
                        infoText.setText("Computing complete.");
                    }
                }
                catch (NumberFormatException nfe){
                    infoText.setText("Trades is not an integer. Please enter a positive integer.");   
                }
            }else{
                infoText.setText("No value was entered. Please enter a positive integer.");
            }
        }
    }
}
