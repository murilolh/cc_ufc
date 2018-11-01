package main;

import java.io.*;
	
public class Textfile{

	public FileInputStream inputFile;
	public BufferedReader input;
	public FileOutputStream outputFile;
	public PrintStream output;
	public String buffer = "";
	public String openMode = "";
	public String caminho = "";

	public void open(String pFileName, String pOpenMode) throws Exception//FileNotFoundException
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
	
	public String readAll() throws Exception
	{
		String aux = input.readLine();
		while(aux != null)
		{			
			buffer = buffer + "\n" + aux ;
			aux = input.readLine();
		}
		return(buffer);		
	}

	public void write(String pBuffer) throws Exception
	{
		output.println(pBuffer);							
	}
	
	public InputStream getFile() throws Exception
	{
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
				
		while(true)
		{
			System.out.println("Digite o caminho do arquivo:");
			caminho = br.readLine(); 
			try
			{
				this.open(caminho,"INPUT");
				break;
			}
			catch(FileNotFoundException e)
			{
				System.out.println("Caminho de arquivo inválido!");
			}
		}
		
		return new ByteArrayInputStream(this.readAll().getBytes("UTF-8"));
	}
	
	public InputStream getFile(String cam) throws Exception
	{
		try
		{
			this.open(cam,"INPUT");
		}
		catch(FileNotFoundException e)
		{
			System.out.println("Caminho de arquivo inválido!");
		}
		
		return new ByteArrayInputStream(this.readAll().getBytes("UTF-8"));
	}	
}