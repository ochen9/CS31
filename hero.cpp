
#include<iostream>
#include<string>
#include <cassert>
using namespace std;

bool hasCorrectSyntax(string song);
bool isColor (string song, int i);
bool isDigitSlash (string song, int i);
bool isBeat(string song, int&index);
int translateSong(string song, string& instructions, int& badBeat);

int main()
{
	for (;;)
	{
		cout << "Enter song: ";
		string s;
		getline(cin, s);
		string instructions = "";
		int bb = 0;
		if (s == "quit")
			break;
		cout << "hasCorrectSyntax returns ";
		if (hasCorrectSyntax(s))
			cout << "true" << endl;
		else
			cout << "false" << endl;
		cout << translateSong(s, instructions, bb) << endl;
		cout << instructions << endl << bb << endl;
	}
	
}

bool hasCorrectSyntax(string song)
{
	for (int k =0; k!=song.size(); k++)
	{
		if (song[k] == '/') //if slash, then it is a beat and move to next
			k+=0;
		else if (isColor(song, k) && song[k+1]=='/') //color and slash means beat
			k++;
		else if (isColor(song, k) && isDigitSlash(song,k+1)) //color, digit, and then slash
			k+=2;
		else if (isColor(song, k) && isdigit(song[k+1]) && isDigitSlash(song, k+2)) //color, 2 digits, then slash
			k+=3;
		else
			return false;
	}
	return true;
	
}

bool isColor(string song, int i)
{
	switch(song[i])
	{
		case 'G':
		case 'g':
		case 'R':
		case 'r':
		case 'Y':
		case 'y':
		case 'B':
		case 'b':
		case 'O':
		case 'o':
			return true;
		default:
			return false;
	}
}

bool isDigitSlash(string song, int i)
{
	if(isdigit(song[i]) && song[i+1]=='/') //tests whether song[i] is a digit and then if the next character in the string is a slash
		return true;
	else
		return false;
}



int translateSong(string song, string& instructions, int& badBeat){
	
		if (! hasCorrectSyntax(song)) //if song is not syntactically correct
			return 1;
		
		string songInstructions = "";
		char color = 0;
		int k = 0;
		
		while(k!=song.size())
		{
			switch(song[k])
			{
				case '/':
				{
					songInstructions += "x"; //empty beat is translated to x
					k++;
					break;
				}
				case 'G':
				case 'g':
				case 'R':
				case 'r':
				case 'Y':
				case 'y':
				case 'B':
				case 'b':
				case 'O':
				case 'o':
				{
					if (song[k+1] == '/') //if it is one letter followed by slash, then not sustained and thus lowercase
					{
						color = tolower(song[k]);
						
						songInstructions += color;
						k+=2;
					}
					else
						k++;
					
					break;
					
				}
				default: //for digits only
				{
					//cout<<"default\n";
					int lengthSustained;
					if(isdigit(song[k+1])) //if k+1 value is digit then k must also be a digit to be part of default case
						lengthSustained = (song[k] - '0') * 10 + (song[k+1] - '0');
					else
						lengthSustained = song[k] - '0';
					
					
					//when syntax is correct but beat specifies sustained note of less than 2
					if (lengthSustained < 2)
					{
						badBeat = 1;
						for (int i = 0; i != lengthSustained; i++) // will scan string and count how many slashes until song[k]
							if (song[i] == '/')
								badBeat++;
						return 2;
					}
				
					
					//when syntax is correct but while sustained note is in effect, a beat not consisting of only a slash is present
					
					if (isdigit(song[k]))
					{
						for (int i = k + 1; i != k+1+lengthSustained; i++) {
							if (song[i] != '/')
							{
								badBeat = 1;
								for (int j = 0; j != i; j++)
								{
									if (song[j] == '/')
										badBeat++;
								}
								cout<<lengthSustained<<endl;
								return 3;
							}
						}
					}
					
					//when syntax is correct but song ends prematurely
					
					int lastColor = 0;
					for (int i =0; i!=song.size(); i++)
					{
						if(isColor(song, i))
							lastColor = i;
					}
					if(isdigit(song[k+1]))
					{
						if(lastColor == k)
						{
							int numberSlashesSustained= 0;
							for(int i =lastColor; i!=song.size(); i++)
							{
								if (song[i] == '/')
									numberSlashesSustained++;
							}
							
							if(numberSlashesSustained < lengthSustained)
							{
								int totalLengthSustained = 0;
								for (int i=0; i != song.size(); i++)
									if (song[i] == '/')
										totalLengthSustained++;
								badBeat = totalLengthSustained + 1;
								return 4;
							}
						}
					}
					
					
					// translates
					// this way letters and slashes that occur while the note is sustained will be written over as capital letters instead of empty beats x
					char sustainedColor;
					if (isdigit(song[k+1]))
					{
						sustainedColor = song[k-1];
						for (int i = 0; i < lengthSustained; i++)
						{
							songInstructions += toupper(sustainedColor);
							
						}
						k += lengthSustained+1;
					}
					else
					{
						sustainedColor = song[k-1];
						for (int i = 0; i < lengthSustained; i++)
						{
							songInstructions += toupper(sustainedColor);
							
						}
						k += lengthSustained+1;
					}

				
				}
			}
			
		}
		
	

	instructions = songInstructions;
	return 0;
	
}


		   
						 
