/*
-- eerom_dump.c
-- Copyright (c) 2017 Shinichiro Nagasato
--
-- This software is released under the MIT License.
--
-- Permission is hereby granted, free of charge, to any person obtaining a copy
-- of this software and associated documentation files (the "Software"), to deal
-- in the Software without restriction, including without limitation the rights
-- to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
-- copies of the Software, and to permit persons to whom the Software is
-- furnished to do so, subject to the following conditions:
--
-- The above copyright notice and this permission notice shall be included in
-- all copies or substantial portions of the Software.
--
-- THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
-- IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
-- FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
-- AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
-- LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
-- OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
-- THE SOFTWARE.
--
*/

#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include<stdlib.h>
#include<string.h>
#include <time.h>

int main(int argc, char **argv) {

	unsigned char rcv_dat[100000];
	unsigned int i,c;
	int f_size;
	unsigned long addr=0;

	FILE *fp;

	fp = fopen(argv[1], "rb");
	if (!fp) {
		return -1;
	}

	f_size = fread( rcv_dat, sizeof( unsigned char ), 100000, fp );

    printf("address  +0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +A +B +C +D +E +F   -- ASCII --\r\n");
    printf("--------------------------------------------------------   ------------\r\n");

	for( i=0 ; i < f_size ; i++ ){
		printf( "%07lx: ",addr );
		for(c=0;c<16;c++){
			printf( "%02X ", rcv_dat[i+c] );
		}
		printf( "  " );

		for(c=0;c<16;c++){
			if(rcv_dat[i+c] < 0x20 || rcv_dat[i+c] >= 0x70){
				rcv_dat[i+c] = '.';
			}
			printf( "%c", rcv_dat[i+c] );
		}

		printf( "\n" );
		addr+=16;
		i+=15;
	}

	fclose(fp);

	return 0;
}
