#ifndef _PRINT_H_
#define _PRINT_H_

#include <stdio.h> //����C���ϸ���������ʽ
#include <typeinfo.h>

class UniPrint {
public:
   static void p ( int );
   static void p ( float );
   static void p ( double );
   static void p ( char );
   template <typename T> static void p ( T& ); //�������б��֧��traverse()�������������Խṹ
   
}; //UniPrint

void UniPrint::p ( int e ) { printf ( " %04d", e ); }
void UniPrint::p ( float e ) { printf ( " %4.1f", e ); }
void UniPrint::p ( double e ) { printf ( " %4.1f", e ); }
void UniPrint::p ( char e ) { printf ( " %c", ( 31 < e ) && ( e < 128 ) ? e : '$' ); }


template <typename T> static void print ( T* x ) {	x ? print ( *x ) : printf ( " <NULL>" );  }
template <typename T> static void print ( T& x ) {	UniPrint::p ( x );	}
static void print ( char* x ) {  printf ( " %s", x ? x : "<NULL>" );  } //�ַ����ر���
static void print ( const char* x ) {  printf ( " %s", x ? x : "<NULL>" );	} //�ַ����ر���

/******************************************************************************************
 * �������б��֧��traverse()�������������Խṹ
 ******************************************************************************************/
template <typename T> //Ԫ������
void UniPrint::p ( T& s ) { //����
   printf ( "%s[%d]*%d:\n", typeid(s).name(), &s, s.size() ); //������Ϣ
   s.traverse ( print ); //ͨ��print()�����������Ԫ��
   printf ( "\n" );
}

#endif
