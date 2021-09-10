#include <stdio.h>
#include <openssl/bn.h>

void printBN(char*msg, BIGNUM*a){
	// Convert the BIGNUM to number string
	char*number_str = BN_bn2hex(a);
	// Print out the number string
	printf("%s %s\n", msg, number_str);
	// Free the dynamically allocated memory
	OPENSSL_free(number_str);
}
int main(){

	BN_CTX * ctx = BN_CTX_new();
	BIGNUM *p = BN_new();
	BIGNUM *q = BN_new();
	BIGNUM *e = BN_new();
	BIGNUM *one = BN_new();
	BIGNUM *temp1 = BN_new();
	BIGNUM *temp2 = BN_new();
	BIGNUM *phi = BN_new();
	BIGNUM *private_key = BN_new();
	
	BN_hex2bn(&p, "F7E75FDC469067FFDC4E847C51F452DF");
	BN_hex2bn(&q, "E85CED54AF57E53E092113E62F436F4F");
	BN_hex2bn(&e, "0D88C3");

	BN_dec2bn(&one,"1");
	
	// Generate phi of n(pxq)  
	BN_sub(temp1,p,one);
	BN_sub(temp2,q,one);
	BN_mul(phi,temp1,temp2,ctx);


	// e*private_key mod phi =1 
	BN_mod_inverse(private_key,e,phi,ctx); 
	printBN("Private Key = ", private_key);

	return 0; 
}
