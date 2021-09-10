#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <openssl/evp.h>

unsigned char outbuf[1024];
char word[17];
FILE *dict;
FILE *out;
const unsigned char *plaintext = "This is a top secret";
const unsigned char *ciphertext = "764aa26b55a4da654df6b19e4bce00f4ed05e09346fb0e762583cb7da2ac93a2";
const unsigned char *iv = "aabbccddeeff00998877665544332211";

int outlen, tmplen;
void hexToDec(const unsigned char*hexdec,char*result){

    int i =0; 
    while (hexdec[i]!='\0') {
        switch (hexdec[i]) {
        case '0':
            strcat(result,"0000");
            break;
        case '1':
            strcat(result,"0001");
            break;
        case '2':
            strcat(result,"0010");
            break;
        case '3':
            strcat(result,"0011");
            break;
        case '4':
            strcat(result,"0100");
            break;
        case '5':
            strcat(result,"0101");
            break;
        case '6':
            strcat(result,"0110");
            break;
        case '7':
            strcat(result,"0111");
            break;
        case '8':
            strcat(result,"1000");
            break;
        case '9':
            strcat(result,"1001");
            break;
        case 'A':
        case 'a':
            strcat(result,"1010");
            break;
        case 'B':
        case 'b':
            strcat(result,"1011");
            break;
        case 'C':
        case 'c':
            strcat(result,"1100");
            break;
        case 'D':
        case 'd':
            strcat(result,"1101");
            break;
        case 'E':
        case 'e':
            strcat(result,"1110");
            break;
        case 'F':
        case 'f':
            strcat(result,"1111");
            break;
        default:
            printf("\nInvalid hexadecimal digit %c",
                   hexdec[i]);
        }
        i++;
    }
}


void word_processing(char *word, int len)
{
    int numWordAdd = 16-len;
    while (numWordAdd--)
    {
        word[len++] = '#';
    }
    word[len] = '\0';
    int i; 
    for (i = 0; word[i]; i++)
    {
        word[i] = tolower(word[i]);
    }
}
int main()
{
    EVP_CIPHER_CTX ctx;
    //EVP_CIPHER_CTX_init(&ctx);
    EVP_CIPHER_CTX_init(&ctx);
    ssize_t word_size= 0; 
    dict = fopen("words.txt", "r");
    out = fopen("out.txt", "wb");
	   while (fgets(word,sizeof(word),dict)){
	 // while(1) {
	        word[strlen(word) - 1] = '\0';
		word_processing(word, strlen(word));
		//strcat("%s%d\n",word,sizeof(word)); 
		EVP_EncryptInit_ex(&ctx, EVP_aes_128_cbc(), NULL, word, iv);
		if (!EVP_EncryptUpdate(&ctx, outbuf, &outlen, plaintext, strlen(plaintext)))
		{
		    /* Error */
		    strcat("%s","error");
		    return 0;
		}
		/* Buffer passed to EVP_EncryptFinal() must be after data just
		 * encrypted to avoid overwriting it.
		 */
		if (!EVP_EncryptFinal_ex(&ctx, outbuf + outlen, &tmplen))
		{
		    /* Error */
		    strcat("%s","error");
		    return 0;
		}
		outlen += tmplen;
		EVP_CIPHER_CTX_cleanup(&ctx);
		/* Need binary mode for fopen because encrypted data is
		 * binary data. Also cannot use strlen() on it because
		 * it wont be null terminated and may contain embedded
		 * nulls.
		 */

		char* hexindecimal =(char*) malloc(2*outlen+1); 
		strcpy(hexindecimal,"");
		hexToDec(ciphertext,hexindecimal); 
		//printf("%d\n",strlen(ciphertext )); 	
		//if(strlen(ciphertext) == strlen(outbuf))
		//{
		//	printf("%s","found");
		//}		
		//if(strcmp(hexindecimal,ciphertext) ==0)
		//{
		//	printf("%s","found");
		//}		
		fwrite(outbuf, 1, outlen, out);
		free(hexindecimal);
	    }
	fclose(out);
	fclose(dict); 
	return 0;
}
