//Conversion from Mealy to Moore machine

#include<iostream>
using namespace std;

int main() {
	int s,i,j,k,flag1=0,flag2=0;
 	cout << "Enter the no. of states: ";  //4
 	cin >> s;
 	int mat[s][5];
	int count=0;
 	int ar[s][2];
 	int asso[s+1];
 
 	cout << "Enter the matrix of states & outputs for different inputs: \n";
 	for(i=0;i<s;i++) { 
 		/* 1 3 0 2 0
 	       2 1 1 4 0
 	       3 2 1 1 1
 	       4 4 1 3 0
 	    */
  		for(j=0;j<5;j++) {
   			cin >> mat[i][j];  
  		}
 	}
 
	cout << "\nThe divisions of the state will be: \n";

 	for(k=1;k<=s;k++) {
  		for(i=1;i<5;i+=2) {
   			for(j=0;j<4;j++) {
				if(mat[j][i]==k && mat[j][i+1]==0) { 
					flag1=1; 
					asso[k]=0; 
				}
			    if(mat[j][i]==k && mat[j][i+1]==1) { 
					flag2=1; 
					asso[k]=1; 
				}
			}
		}      
		if(flag1==1 && flag2==1) {
			ar[k-1][0]=k;
		   	ar[k-1][1]=2;
		} else {
			ar[k-1][0]=k;
		   	ar[k-1][1]=1;
		}
		flag1=0; flag2=0;
 	}

	int sum=0;
 	for(i=0;i<s;i++) {
  		cout << i+1 << " " << ar[i][1] << "\n";
  		sum+=ar[i][1];
 	}
 	cout << "\nTotal new states will be " << sum;
 
  	int mat2[sum][5],l;
 	k=0;
 
	for(i=0;i<sum;i++) {
  		count=ar[mat[k][0]-1][1];
  		while(count) {
   			for(j=0,l=0;j<5;j++,l++) {
    			mat2[i][j]=mat[k][l];
   			}
   			count--;
			if(count==0) { 
    			k++;
			}
   			else 
			   i++;
		}
 	}
	for(i=0;i<sum;i++) {
  		for(j=1;j<5;j+=2) {
   			if(ar[mat2[i][j]-1][1]!=1) {
    			mat2[i][j]=(mat2[i][j]*10)+mat2[i][j+1];
			}
  		}
 	}
 
	for(i=0;i<sum;i++) {
  		if(ar[mat2[i][0]-1][1]!=1) { 
   			mat2[i][0]=mat2[i][0]*10;
   			i++;
   			mat2[i][0]=(mat2[i][0]*10)+1;;
		}
	}

 	cout << "\nThe new table is: \n"; 
 	for(i=0;i<sum;i++) {
	  	cout << "\n";
	  	for(j=0;j<5;j++)
	  		cout << mat2[i][j] << " ";
	}
    int momat[sum][4]; 
 	for(i=0;i<2;i++) {
  		for(j=0;j<sum;j++) {
   			momat[j][i]=mat2[j][i];
  		}
 	}
 	for(i=3,j=0;j<sum;j++) 
 		momat[j][i-1]=mat2[j][i];
 	for(i=3,j=0;j<sum;j++) {
  		if(momat[j][0]>=10)
  			momat[j][i]=momat[j][0]%10;
  		else if(momat[j][0]<10) {
   			momat[j][i]=asso[momat[j][0]];
  		}
 	}

 	cout << "\n\nThe moore table is: \n";
 	if(momat[0][3]==1) { 
		cout << "s ";
	  	for(j=1;j<3;j++)
	  	cout << momat[0][j] << " ";
	  	cout << "0";  
 	}

 	for(i=0;i<sum;i++) {
  		cout << "\n";
  		for(j=0;j<4;j++)
  			cout << momat[i][j] << ' ';
 	}
}
