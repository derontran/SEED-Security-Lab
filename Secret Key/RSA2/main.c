#include <stdio.h>
#include <openssl/bn.h>
#define NBITS 256
void printBN(char *msg, BIGNUM * a)
{
/* Use BN_bn2hex(a) for hex string 
 * Use BN_bn2dec(a) for decimal string */
	char * number_str = BN_bn2hex(a);
	printf("%s %s\n", msg, number_str);
	OPENSSL_free(number_str);
}
int main ()
{
	
	BN_CTX * ctx = BN_CTX_new(); 
	BIGNUM * m = BN_new(); 
	BIGNUM * n = BN_new(); 
	BIGNUM * e = BN_new(); 
	BIGNUM * d = BN_new(); 
	BIGNUM * encrypted_message = BN_new(); 
	BIGNUM * decrypted_message  = BN_new(); 
	BIGNUM * a = BN_new(); 
	// sercet message in hex, and convert it to binary
	BN_hex2bn(&m,"4120746f702073656372657421");

	BN_hex2bn(&n,"DCBFFE3E51F62E09CE7032E2677A78946A849DC4CDDE3A4D0CB81629242FB1A5");
	BN_hex2bn(&e,"010001");
	BN_hex2bn(&d,"74D806F9F3A62BAE331FFE3F0A68AFE35B3D2E4794148AACBC26AA381CD7D30D");
		
	// Encrypt m using m^e mod n
	BN_mod_exp(encrypted_message, m,e,n,ctx);
	printBN("Encrypted Message: ", encrypted_message); 

	// Decrypt using encrypted_message^d mod n 
	BN_mod_exp(decrypted_message,encrypted_message,d, n,ctx);
	printBN("Decrypted Message: ", decrypted_message); 

	return 0; 
	
}
