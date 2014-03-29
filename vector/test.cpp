#include <stdio.h>
#include <stdlib.h>

#include "vector.h"
#include "print.h"
/*
	����CRC
*/

//����������Ƽ���CRC
template <typename T> struct Crc { //���������ۼ�T�����������������ܺͣ����Ա�У����󼯺�
   T& c;
   Crc ( T& crc ) : c ( crc ) {}
   virtual void operator() ( T& e ) { c += e; } //����T��ֱ�����
};

template <typename T> void crc ( Vector<T> & V ) { //ͳ������������������Ԫ��֮�ͣ�
   T crc = 0;
#if 0
   //GCC�±��벻��������ʱ�����������й�
   V.traverse ( Crc<T> (crc) ); //��crcΪ�����������б���
#else
   Crc<T> tmp(crc);
   V.traverse ( tmp );
#endif
   printf ( "CRC =" ); print ( crc ); printf ( "\n" ); //���ͳ�Ƶõ�������
} 


// ʹ�ú���ָ����Ƽ���CRC
int sum = 0;
template <typename T> static void crc_callback ( T& x ) 
{	
	sum += x;  
}
template <typename T> void crc_func ( Vector<T> & V ) 
{ 
   V.traverse ( crc_callback ); //��crcΪ�����������б���
   printf ( "CRC =" ); print ( sum ); printf ( "\n" ); //���ͳ�Ƶõ�������
} 


/*
	����Lowpass
*/
template <typename T> struct LP 
{ 
   T& prev;
   LP (T& init): prev ( init ){}
   void operator() ( T& e ) 
   {		
   		prev = (prev + e)/2;
   }
};

template <typename T> void lowpass ( Vector<T> & V ) 
{ 
   T init = V[0];
   LP<T> tmp(init);
   V.traverse ( tmp );
   printf ( "Lowpass:" ); print ( V ); printf ( "\n" ); //���ͳ�Ƶõ�������
} 

#define RAND(r)	(rand()%(r))

int main ( int argc, char *argv[] )
{
	int testID = 0;
	
	Vector<int> vec;
	int testSize = 10;

	printf ( "\n  ==== Test %2d. Generate a random vector\n", testID++ );
	for ( int i = 0; i < testSize; i++ ) 
		vec.insert( i, RAND(testSize*3) );

	printf ( "\n  ==== Test %2d. Print directly\n", testID++ );
	printf ( "%s[%d]*%d:\n", typeid(vec).name(), &vec, vec.size() );
	for ( int i = 0; i < vec.size(); i++ ) 
		printf(" %04d", vec[i]);
	printf ("\n");

	printf ( "\n  ==== Test %2d. Print by traverse method\n", testID++ );
	print(vec);

	printf ( "\n  ==== Test %2d. Calculate CRC by callback function method\n", testID++ );
	crc_func(vec);

	printf ( "\n  ==== Test %2d. Calculate CRC by object method\n", testID++ );
	crc(vec);

	printf ( "\n  ==== Test %2d. Lowpass on by direct traverse\n", testID++ );
	int i = vec.size(); 
	while ( 0 < --i ) 
		{ vec[i-1] += vec[i]; vec[i-1] >>= 1; }   
	print( vec );

	printf ( "\n  ==== Test %2d. Lowpass on by object method traverse\n", testID++ );
	lowpass(vec);

	return 0;
}              

