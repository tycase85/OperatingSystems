import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.Scanner;

//Created by Robert Tyler Case
public class getHTML {

	public static void main(String [] args) throws IOException{
		String protocol, domain, docPath, portHolder;
		int portNum = 0;
		Scanner scan = new Scanner(System.in);
		
		System.out.println("Input a protocol (default port is http) ");
		if(scan.nextLine().isEmpty()) {
			protocol = "http";
		}
		else {
			protocol = scan.nextLine();
		}
		System.out.println("input a domain: ");
		domain = scan.nextLine();
		System.out.println("Input a document path: ");
		
		docPath = scan.nextLine();
		
		
		
		System.out.println("Input a port number (default port is 80) ");
		if(scan.nextLine().isEmpty()) {
			portNum = 80;
		}
		else {
			portHolder = scan.nextLine();
			portNum = Integer.valueOf(portHolder);
		}
		
		
//		protocol = "http";
//		domain = "wizards.cs.unb.ca";
//		portNum = 80;
//		docPath = "/index.html";
		
		
		URL urlTest = new URL(protocol, domain, portNum, docPath);
		System.out.println(urlTest);
		
	
		    HttpURLConnection myURLConnection = (HttpURLConnection)urlTest.openConnection();
		    myURLConnection.setRequestMethod("GET");
		    myURLConnection.connect();
		    int code = myURLConnection.getResponseCode();
		    System.out.println(code);
		    
		    BufferedReader in = new BufferedReader(new InputStreamReader(myURLConnection.getInputStream()));
		    
		    
		    
		    String[] splitHold = docPath.split("/");
		    String docHolder;
		    if(docPath.equals("")) {
				docHolder = "index.html";
			}
		    else {
		    	docHolder = splitHold[splitHold.length-1];
		    }
		    System.out.println("DocHolder: " + docHolder);
		    File file = new File(docHolder);
		    
		    String inputLine;
		   
		    try (PrintWriter p = new PrintWriter(file)) {
		    	 while ((inputLine = in.readLine()) != null) {
				    	
				    	System.out.println(inputLine);
				    	p.println(inputLine);
				    }
	    		
		    } catch (FileNotFoundException e1) {
		        e1.printStackTrace();
		    }
		    
		    in.close();
		    
		    
		    
		    
	}
	
}
