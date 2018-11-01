package multi;

import java.io.*;

public class TextFile {

        FileInputStream inputFile;
	BufferedReader input;
	FileOutputStream outputFile;
	PrintStream output;
	String buffer = "";
	String openMode = "";

	public void open(String pFileName, String pOpenMode) throws FileNotFoundException
	{
		openMode = pOpenMode.toUpperCase();

		if(openMode.equals("INPUT")){
			inputFile = new FileInputStream(pFileName);
			input = new BufferedReader(new InputStreamReader(inputFile));
		}

		if(openMode.equals("OUTPUT")){
			outputFile = new FileOutputStream(pFileName, false);
			output = new PrintStream(outputFile);
		}

		if(openMode.equals("APPEND")){
			outputFile = new FileOutputStream(pFileName, true);
			output = new PrintStream(outputFile);
		}

	}

	public void close() throws Exception
	{
		if(openMode.equals("INPUT")){
			input.close();
			inputFile.close();
		}

		else{
			output.close();
			outputFile.close();
		}

	}

	public String read() throws Exception
	{
		buffer = input.readLine();
		return(buffer);
	}

	public void write(String pBuffer) throws Exception
	{
		output.print(pBuffer);
	}

}
