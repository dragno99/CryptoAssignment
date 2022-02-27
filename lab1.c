#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Created by suryansh kumar ( 201951158 - section 2)
 
const int sz = 500;

void convertJtoI(char word[]){
	int len = strlen(word) , i;
	for(i=0;i<len;i++){
		if(word[i] == 'j'){
			word[i] = 'i';
		}
	}
}

int inverse(int x,int m){
	int i = 1;
	for(i=1;i<m;i++){
		if((i * x) % m == 1){
			return i;
		}
	}
	return 0;
}

void adjustWord(char word[] , char delta[]){
	
	int len = strlen(word);

	convertJtoI(word);

	int curr_size = 0 , i = 0 ;
	for(i=0;i+1<len;){
		if(word[i] == word[i + 1] ){
			delta[curr_size++] = word[i];
			delta[curr_size++] = 'x';
			i++;
		}
		else{
			delta[curr_size++] = word[i];
			delta[curr_size++] = word[i + 1];
			i += 2;
		}
	}
	if(i < len){
		delta[curr_size++] = word[i];
		delta[curr_size++] = 'z';
	}
	delta[curr_size] = '\0';

}

void fillPlayFair(char m[5][5] , char key[]){
	int vis[26] = {0};
	vis['j' - 'a'] = 1;
	int keyLen = strlen(key);
	for(int i=0;i<26;i++){
		if(i < keyLen){
			m[i/5][i%5] = key[i];
			vis[key[i] - 'a'] = 1;
		}
		else{
			int j = 0;
			while(i < 26){
				while(j < 26 && vis[j]){
					j++;
				}
				char c = 'a';
				c += j;
				m[i/5][i%5] = c;
				vis[j] = 1;
				i++;
			}
		}
	}
}

void changeForEncryption(char word[] , char key[5][5] , char c1[],int i){
	int x = 0 , y = 0;
	for(x=0;;x++){
		if(key[x/5][x%5] == word[i]){
			break;
		}
	}
	for(y=0;;y++){
		if(key[y/5][y%5] == word[i + 1]){
			break;
		}
	}
	int p = x/5 , q = x % 5;
	int r = y/5 , s = y % 5;
	if(q == s){
		c1[i] = key[(p + 1)%5][q];
		c1[i + 1] = key[(r + 1)%5][s];
	}
	else if(p == r){
		c1[i] = key[p][(q+1)%5];
		c1[i + 1] = key[r][(s+1)%5];
	}
	else{
		c1[i] = key[p][s];
		c1[i+1] = key[r][q];
	}
}

void changeFordecryption(char word[] , char key[5][5] , char c1[],int i){
	int x = 0 , y = 0;
	for(x=0;;x++){
		if(key[x/5][x%5] == word[i]){
			break;
		}
	}
	for(y=0;;y++){
		if(key[y/5][y%5] == word[i + 1]){
			break;
		}
	}
	int p = x/5 , q = x % 5;
	int r = y/5 , s = y % 5;
	if(q == s){
		c1[i] = key[(p - 1 + 5)%5][q];
		c1[i + 1] = key[(r - 1 + 5)%5][s];
	}
	else if(p == r){
		c1[i] = key[p][(q - 1 + 5)%5];
		c1[i + 1] = key[r][(s - 1 + 5)%5];
	}
	else{
		c1[i] = key[p][s];
		c1[i+1] = key[r][q];
	}
}

void encryptPlayfair(char word[] , char key[5][5] , char res[]){
	int len = strlen(word) , i;
	for(i=0;i<len;i+=2){
		changeForEncryption(word , key , res , i);
	}
	res[len] = '\0';
}


void decryptPlayfair(char word[] , char key[5][5] , char res[]){
	int len = strlen(word) , i;
	for(i=0;i<len;i+=2){
		changeFordecryption(word , key , res , i);
	}
	res[len] = '\0';
}

void encryptCeasar(char word[] ,char res[],int key){
	int len = strlen(word) , i = 0;
	for(i=0;i<len;i++){
		int pos = word[i] - 'a';
		pos += key;
		pos %= 26;
		char c = 'a' + pos;
		res[i] = c;
	}
	res[len] = '\0';
}

void decryptCeasar(char word[] ,char res[],int key){
	int len = strlen(word) , i = 0;
	for(i=0;i<len;i++){
		int pos = word[i] - 'a';
		pos = pos - key + 26;
		pos %= 26;
		char c = 'a' + pos;
		res[i] = c;
	}
	res[len] = '\0';
}

void encryptAffine(char word[],char res[],int a,int b){
	int len = strlen(word) , i = 0;
	for(i=0;i<len;i++){
		int x = word[i] - 'a';
		x = (a * x + b) % 26;
		char c = 'a' + x;
		res[i] = c;
	}
	res[len] = '\0';
}

void decryptAffine(char word[],char res[],int a,int b){
	int len = strlen(word) , i = 0;
	int inv = inverse(a , 26);
	for(i=0;i<len;i++){
		int x = word[i] - 'a';
		x = inv * ( x - b ) % 26;
		x = (x + 26) % 26;
		char c = 'a' + x;
		res[i] = c;
	}
	res[len] = '\0';
}



int main(){

	char word[sz] , delta[sz] , k1[sz];
	printf("Enter a word: ");
	scanf("%s" , word);


	adjustWord(word , delta);

	int sz = strlen(delta);

	printf("Delta is: %s\n", delta); // printing delta


	///////////// encryption part

	printf("Enter the key: ");
	scanf("%s" , k1);

	convertJtoI(k1);

	char playFair[5][5];

	fillPlayFair(playFair , k1);

	int i = 0 , j = 0;
	printf("Playfair cipher matrix:\n");
	for(i;i<5;i++){
		for(j=0;j<5;j++){
			printf("%c" , playFair[i][j]);
		}
		printf("\n");
	}

	char c1[sz];
	encryptPlayfair(delta , playFair , c1);

	printf("Encrypted cipher c1: %s\n" , c1);

	char c2[sz];
	int k2 = 3;

	encryptCeasar( c1 , c2 , k2);

	printf("Encrypted cipher C2: %s\n" , c2);

	int k3_a = 7 , k3_b = 5;
	char c3[sz];

	encryptAffine(c2 , c3 , k3_a , k3_b);

	printf("Encrypted cipher c3: %s\n" , c3);

	/////////////////// decryption part

	char decrypted3[sz];
	decryptAffine(c3, decrypted3, k3_a , k3_b);

	printf("Decrypted text d3: %s\n" , decrypted3);

	char decrypted2[sz];
	decryptCeasar(decrypted3 , decrypted2 , k2);
	printf("Decrypted text d2: %s\n" , decrypted2);

	char decrypted1[sz];
	decryptPlayfair(decrypted2 , playFair , decrypted1 );
	printf("Decrypted text d3: %s\n" , decrypted1);

	// now decrypted1 should be equal to delta


	printf("Delta : %s\nFinal Decrypted text : %s\n" , delta , decrypted1);

	printf("Now both Delta and Final Decrypted text are equal means program is working fine......");


	return 0;

}
