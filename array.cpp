#include <iostream>
#include <string>
#include <cassert>

using namespace std;

int tally(const string a[], int n, string target);
int findMatch(const string a[], int n, string target);
bool findRun(const string a[], int n, string target, int& begin, int& end);
int positionOfMin(const string a[], int n);
int moveToEnd(string a[], int n, int pos);
int moveToBeginning(string a[], int n, int pos);
int findDifference(const string a1[], int n1, const string a2[], int n2);
int eliminateDups(string a[], int n);
bool subsequence(const string a1[], int n1, const string a2[], int n2);
bool isNondecreasingOrder(const string a[], int n);
int makeMerger(const string a1[], int n1, const string a2[], int n2,
			   string result[], int max);
int separate(string a[], int n, string separator);



int main()
{
	string h[7] = { "romanoff", "thor", "rogers", "banner", "", "parker", "rogers" };
	assert(tally(h, 7, "rogers") == 2);
	assert(tally(h, 7, "") == 1);
	assert(tally(h, 7, "rhodes") == 0);
	assert(tally(h, 0, "rogers") == 0);
	assert(findMatch(h, 7, "rogers") == 2);
	assert(findMatch(h, 2, "rogers") == -1);
	int bg;
	int en;
	assert(findRun(h, 7, "banner", bg, en) && bg == 3 && en == 3);
	
	string g[4] = { "romanoff", "thor", "banner", "parker" };
	assert(positionOfMin(g, 4) == 2);
	assert(findDifference(h, 4, g, 4) == 2);
	assert(subsequence(h, 7, g, 4));
	assert(moveToEnd(g, 4, 1) == 1 && g[1] == "banner" && g[3] == "thor");
	
	string f[4] = { "parker", "banner", "thor", "rogers" };
	assert(moveToBeginning(f, 4, 2) == 2 && f[0] == "thor" && f[2] == "banner");
	
	string e[5] = { "parker", "parker", "parker", "thor", "thor" };
	assert(eliminateDups(e, 5) == 2 && e[1] == "thor");
	
	string x[4] = { "rhodes", "rhodes", "tchalla", "thor" };
	string y[4] = { "banner", "parker", "rhodes", "rogers" };
	string z[10];
	assert(makeMerger(x, 4, y, 4, z, 10) == 8 && z[5] == "rogers");

	assert(separate(h, 7, "rogers") == 3);
	
	cout << "All tests succeeded" << endl;
}

int tally(const string a[], int n, string target)
{
	if (n<0)
		return -1;
	
	int count = 0;
	for(int i =0; i!=n; i++)
	{
		if(a[i]==target)
			count++;
	}
	return count;
}
		

int findMatch(const string a[], int n, string target)
{
	if(n<0)
		return -1;
	for (int i=0; i!=n; i++)
	{
		if (a[i] == target)
		{
			return i;
			break;
		}
	}
		return -1;
}

bool findRun(const string a[], int n, string target, int& begin, int& end)
{
	int b=0;
	int e=0;
	
	if(n<0)
		return false;
	if (findMatch(a, n, target) == -1) //means that string is not in array
		return false;
	
	for(int i=0; i!=n; i++){
		if(a[i] ==target){
			b = i;
			break;
			
			}
		}
	for(int j=b; j!=n; j++)
	{
		if(a[j]==target)
			e = j;
		else
			break;
	}
	begin = b;
	end = e;
	return true;

}

int positionOfMin(const string a[], int n)
{
	if(n<=0)
		return -1;
	
	string min=a[0];
	int position = 0;
	
	for (int i=1; i!=n; i++){
		if(a[i]<min){
			min=a[i];
			position = i;
		}
		
	}
	return position;
}

int moveToEnd(string a[], int n, int pos)
{
	if(n<0)
		return -1;
	if(pos<0 || pos>=n)
		return -1;
	string position = a[pos];
	for(int i=pos; i!=n; i++){
		a[i]=a[i+1];
	}
	a[n-1] = position;
	return pos;
}

int moveToBeginning(string a[], int n, int pos)
{
	if(n<0)
		return -1;
	if(pos<0 || pos>=n)
		return -1;
	string position = a[pos];
	for(int i=pos; i>=0; i--){
		a[i]=a[i-1];
	}
	a[0] = position;
	return pos;
}

int findDifference(const string a1[], int n1, const string a2[], int n2)
{
	if(n1<0 || n2<0)
		return -1;
	int smaller =0;
	int difference = 0;
	
	if(n1<=n2)
		smaller =n1;
	else
		smaller = n2;
	
	while(difference<smaller){
		if(a1[difference]==a2[difference])
		   difference++;
		else
		   break;
	}
	
	return difference;
	
}

int eliminateDups(string a[], int n)
{
	if (n<0)
		return -1;
	int first = 0;
	int last = 0;
	int number = n;
	
	for(int i=0; i!=number; i++)
	{
		for (int j = i; j < number; j++)
			if (a[j] == a[i])
			{
				first = j;
				break;
			}
		for (int k = first; k < number; k++)
		{
			if (a[k] == a[i])
				last = k;
			else
				break;
		}
		
		for(int m=first; m<last; m++){
			moveToEnd(a,n,m);
			number--;
			last--;
			m--;
		}
		
	}
	return number;
}

bool subsequence(const string a1[], int n1, const string a2[], int n2)
{
	if (n1 < 0 || n2 < 0 || n2 > n1)
		return false;
	if (n2 == 0)
		return true;
	
	int numberOfStrings = 0;
	int lastString = 0;
	for (int i = 0; i < n2; i++)
	{
		for (int k = lastString; k < n1; k++) // makes sure a2 is in range of a1
		{
			if (a1[k] == a2[i])
			{
				lastString = k;
				numberOfStrings++;
				break;
			}
		}
	}
	
	if (numberOfStrings !=n2)
		return false;
	else
		return true;
}

bool isNondecreasingOrder(const string a[], int n)
{
	for(int i=0; i!=n; i++){
		if(a[i]>a[i+1])
			return false;
	}
	return true;
}

int makeMerger(const string a1[], int n1, const string a2[], int n2,
			   string result[], int max)
{
	if(n1<0 || n2<0)
		return -1;
	if(n1+n2>max)
		return -1;
	
	if (n1==0){
		for(int i=0; i!=n2; i++)
			result[i]=a2[i];
		return n2;
	}
	if (n2==0){
		for(int i=0; i!=n1; i++)
			result[i]=a1[i];
		return n1;
	}
	
	if (isNondecreasingOrder(a1, n1) && isNondecreasingOrder(a2, n2)){
		int i = 0;
		int j = 0;//counting a1
		int k = 0;//counting a2
		
		while (i < (n1 + n2))
		{
			if (a1[j] <= a2[k]) // takes smallest value between a1[j] and a2[k] and adds to result
			{
				result[i] = a1[j];
				j++;
				i++;
			}
			else if(a2[k] < a1[j])
			{
				result[i] = a2[k];
				k++;
				i++;
			}
			
			
			else if (j == n1) // if all elements of a1 are used
			{
				while (k < n2){
					result[i] = a2[k];
					k++;
					i++;
				}
				break;
			}
			else if (k == n2) // if all elements of a2 are used
			{
				while (j < n1){
					result[i] = a1[j];
					j++;
					i++;
				}
				break;
			}
			
			
		}
		return n1 + n2;
	}
	else
		return -1;
}

int separate(string a[], int n, string separator)
{
	if (n<0)
		return -1;
	
	string equalToSeparator[1000];
	string lessThanSeparator[1000];
	string greaterThanSeparator[1000];
	
	int numberEqual = 0;
	int numberLessThan = 0;
	int numberGreaterThan = 0;
	
	int j = 0; //counts number of elements less than separator
	int k = 0; //counts number of elements equal to separator
	int m = 0; //counts number of elements greater than separator
	
	for (int i = 0; i!=n; i++){
		if (a[i]<separator){
			lessThanSeparator[j] = a[i];
			j++;
			numberLessThan++;
		}
		if(a[i]==separator){
			equalToSeparator[k] = a[i];
			k++;
			numberEqual++;
		}
		if (a[i]>separator){
			greaterThanSeparator[m] = a[i];
			m++;
			numberGreaterThan++;
		}
	}
		int count = 0;
		k = 0;
		m = 0; //resets k and m to 0 so that they can be used as counters again
		for (count = 0; count < numberLessThan; count++)
			a[count] = lessThanSeparator[count];
		for (count = count; k < numberEqual; count++)
		{
			a[count] = equalToSeparator[k];
			k++;
		}
		for (count = count; m < numberGreaterThan; count++)
		{
			a[count] = greaterThanSeparator[m];
			m++;
		}
		
		if (numberLessThan == n)
			return n;
		else
			return numberLessThan;
	
}

