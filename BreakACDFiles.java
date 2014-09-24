import java.io.File;

import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.io.BufferedReader;
import java.io.FileWriter;
import java.io.BufferedWriter; // because I'm writing many times

import java.io.IOException;

public class BreakACDFiles {
    private String srcPath;
    private String dstPath;
    private File srcDir;
    private File dstDir;	

    // constructor to set up private members and check provided directories exist
    BreakACDFiles(String s, String d) {
	this.srcPath = s;
	this.dstPath = d;
	this.srcDir = new File(s);
	this.dstDir = new File(d);

	if(!srcDir.canRead() || !dstDir.canRead()) {
	    System.out.println("Error: Unable to read source or dest file path");
	    System.exit(0);
	}
    }

    int processTheFiles() {
	int p = 0, fs = 0;
	for(File file: srcDir.listFiles()){
	    if(file.isFile()) {
		//System.out.println(file.getName());
		p += processFile(file);
		fs += 1;
	    }
	}

	System.out.println("Files Processed: " + fs);
	return p;
    }

    int processFile(File f) {
	int r = 0, a = 0, c = 0, d = 0;
	String fileStr = f.getName();
	String aFileStr = dstPath + "A_" + fileStr;
	String cFileStr = dstPath + "C_" + fileStr;
	String dFileStr = dstPath + "D_" + fileStr;	

	try {
	    System.out.println("Opening: " + fileStr);
	    BufferedReader br = new BufferedReader(new InputStreamReader(new FileInputStream(f)));
	    BufferedWriter abr = new BufferedWriter(new FileWriter(aFileStr,true));   
	    BufferedWriter cbr = new BufferedWriter(new FileWriter(cFileStr,true));
    	    BufferedWriter dbr = new BufferedWriter(new FileWriter(dFileStr,true)); 

	    String line = null;
	    while((line = br.readLine()) != null) {
		if(line.charAt(0) == 'A') {
		    //System.out.println(line);
		    abr.write(line);
		    abr.newLine();
		    a += 1;
		} 
		else if(line.charAt(0) == 'C') {
		    //System.out.println(line);
		    cbr.write(line);
		    cbr.newLine();
		    c += 1;
		} 
		else if(line.charAt(0) == 'D') {
		    //System.out.println(line);
		    dbr.write(line);
		    dbr.newLine();
		    d += 1;
		} 
		r += 1;
	    }
	    br.close();
	    abr.close();
	    cbr.close();
	    dbr.close();
	} catch(IOException e) {
	    System.out.println("Exception Reading/Writing Files: " + e);
	} 

	System.out.println("A's Processed: " + a);
	System.out.println("C's Processed: " + c);
	System.out.println("D's Processed: " + d);
	System.out.println("Total Records Processed: " + r);
	
	return r;
    }

    public static void main (String[] args) {
	int p = 0;	
	int len = args.length;  
	if(len != 2) {
	    System.out.println("Error: Input requires a source and destination path: > java BreakACDFiles FilesToProcess/ Output/");
	    System.exit(0);
	}	

	for(String s: args) {
	    System.out.println(s);
	}

	BreakACDFiles b = new BreakACDFiles(args[0],args[1]);
	p = b.processTheFiles();
	System.out.println("Total Records Processed " + p );
    } 
}
