#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define LINE_SIZE 100
#define FILE_SIZE 100000000


int main(int argc, char argv[]){
	
	// Input output file pointers
	FILE * fp_in;
	FILE * fp_out;

	

	// Open files	
	fp_in = fopen( "something.gc" , "r" );
	fp_out = fopen( "decomp.gene" , "w" );
	
	// Compression characters
	int b[4];
	int s;

	uint64_t fcount=1;	
	int count;
		
	while(fcount < FILE_SIZE){
		for(count=0; count<(LINE_SIZE/4); count++){

			// pull char into s
			s = fgetc(fp_in);
			
			// split
			b[0]=((s & 0x03)<<1)|0x41;
			b[1]=((s & 0x0c)>>1)|0x41;
			b[2]=((s & 0x30)>>3)|0x41;
			b[3]=((s & 0xc0)>>5)|0x41;

			// write chars
			fputc(b[3],fp_out);
			fputc(b[2],fp_out);
			fputc(b[1],fp_out);
			fputc(b[0],fp_out);

			fcount=fcount+1;	

		}
		fputc('\n',fp_out);
	}

	fputc(EOF, fp_out);
	fclose(fp_in);
	fclose(fp_out);
}
