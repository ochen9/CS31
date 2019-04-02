#include <cstring>
#include <iostream>
#include <fstream>

using namespace std;

int stuff(int lineLength, istream& inf, ostream& outf);
bool findToken(char token[], istream& inf, int& charCount);
bool isPunctuation(char character);
bool isSpace(char character);
bool isTooLong(int length, int lineLength);

int main ()
{
	
		ifstream infile("/Users/oliviachen/Desktop/CS31/project 5/data.txt");
		if ( ! infile )		        // Did opening the file fail?
		{
			cerr << "Error: Cannot open data.txt!" << endl;
		}
		
		
		ofstream outfile("/Users/oliviachen/Desktop/CS31/project 5/results.txt");   // outfile is a name of our choosing.
		if ( ! outfile )		   // Did the creation fail?
		{
			cerr << "Error: Cannot open results.txt!" << endl;
		}
		
		cout << "Enter maximum line length: ";
		int len;
		cin >> len;
		cin.ignore(10000, '\n');
	
		cout << stuff(len, infile, outfile)<<endl;;
		int returnCode = stuff(len, infile, cout);
		cout << "Return code is " << returnCode << endl;
	
}

int stuff(int lineLength, istream& inf, ostream& outf)
{
	if (lineLength<1)
		return 2;
	
	char lastToken[140];
	int charsLastToken = 0;
	int charsLine = 0;
	int charsLongest = 0;
	int numberTokens = 0;
	
	for(;;){
		char token [140]; //maximum input line size
		int numberChars = 0;
		
		if(! (findToken(token, inf, numberChars)))
			break;
		if (strcmp(token, "")==0)
			break;
		if(numberChars > charsLongest) //determines how many characters are in the longest word
			charsLongest = numberChars;
		
		//paragraphs
		if(strcmp(token, "#P#")==0){ //if token is a paragraph break
			outf << '\n' << '\n';
			charsLine = 0;
			
			while (strcmp(token, "#P#") == 0){ //if there are consecutive paragraph breaks
				findToken(token, inf, numberChars);
			}
			
			//print last token that was stored
			int currentChars = 0;
			int i= 0;
			if(numberChars>lineLength){
				while ((numberChars - currentChars)>lineLength){
					i = 0;
					for (int k =currentChars; k<currentChars+lineLength; k++){
						outf <<token[k];
						i++;
					}
					currentChars += i;
					outf<< '\n';
				}
				
				for (int j = currentChars; j<numberChars; j++){
					outf <<token[j];
				}
				charsLine = numberChars - currentChars;
			}
			else{
				outf <<token;
				charsLine += numberChars;
			}
		}
		
		//non-paragraph normal words
		else{
			if((charsLine + numberChars +1 >lineLength) && (strcmp(lastToken, "") !=0)){
				outf << '\n';
				charsLine = 0;
			}
			
			int currentChars = 0; //same name as previous currentChars, but different scope so it's ok
			int i = 0;
			
			if(numberChars >lineLength){
				while((numberChars - currentChars) > lineLength){
					i =0;
					for (int k = currentChars; k<currentChars+lineLength; k++){
						outf <<token[k];
						i++;
					}
					currentChars += i;
					outf << '\n';
				}
				for (int k = currentChars; k<numberChars; k++){
					outf <<token[k];
				}
				charsLine = numberChars - currentChars;
			}
			else{
				if ((charsLastToken !=0) && (lastToken[charsLastToken-1] != '-')
					&& charsLine !=0)//if the end of the last token was the end of the word
				{
					outf<<' ';
					charsLine++;
				}
				if((charsLastToken != 0) && (isPunctuation(lastToken[charsLastToken-1])) && (charsLine != 0))
				{
					outf << '  ';
					charsLine++;
				}
				outf<<token;
				charsLine += numberChars;
			}
		}
		
		strcpy(lastToken, token);
		charsLastToken = numberChars;
		numberTokens++;
	}
	
	if(numberTokens>0)
		outf << '\n'; //output ends with new line character
	if(isTooLong(charsLongest, lineLength)) //if the number of characters exceeds length of line
		return 1;
	else
		return 0;
}

bool findToken(char token[], istream& inf, int& charCount){
	char character;
	if(inf.eof())
		return false;
	charCount = 0;
	strcpy(token, "");
	char next[2];
	
	while(inf.get(character)){ //goes through the spaces
		if(!isSpace(character)){
			next[0] = character;
			next[1] = '\0';
			strcat(token, next);
			charCount++;
			break;
		}
	}
	
	while(inf.get(character)){//reads characters into token until the word is done
		if(isSpace(character))//if character is space- exclusive
			break;
		if (character == '-'){//if character is hyphen- inclusive
			strcat(token, "-"); //adds hyphen to end of token
			charCount++;
			break;
		}
		next[0] = character;
		next[1] = '\0';
		strcat(token, next);
		charCount++;
	}
	
	return true;
}
bool isPunctuation(char character){
	if (character == '.' || character == '?')
		return true;
	else
		return false;
}

bool isSpace(char character){
	if (character == '\n' || character == ' '|| character =='\t')
		return true;
	else
		return false;
}
bool isTooLong(int length, int lineLength){
	if(length > lineLength)
		return true;
	else
		return false;
}


