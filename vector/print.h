#ifndef _PRINT_H_
#define _PRINT_H_

#include <stdio.h> //采用C风格精细控制输出格式
#include <typeinfo.h>

class UniPrint {
public:
   static void p ( int );
   static void p ( float );
   static void p ( double );
   static void p ( char );
   template <typename T> static void p ( T& ); //向量、列表等支持traverse()遍历操作的线性结构
   
}; //UniPrint

void UniPrint::p ( int e ) { printf ( " %04d", e ); }
void UniPrint::p ( float e ) { printf ( " %4.1f", e ); }
void UniPrint::p ( double e ) { printf ( " %4.1f", e ); }
void UniPrint::p ( char e ) { printf ( " %c", ( 31 < e ) && ( e < 128 ) ? e : '$' ); }


template <typename T> static void print ( T* x ) {	x ? print ( *x ) : printf ( " <NULL>" );  }
template <typename T> static void print ( T& x ) {	UniPrint::p ( x );	}
static void print ( char* x ) {  printf ( " %s", x ? x : "<NULL>" );  } //字符串特别处理
static void print ( const char* x ) {  printf ( " %s", x ? x : "<NULL>" );	} //字符串特别处理

/******************************************************************************************
 * 向量、列表等支持traverse()遍历操作的线性结构
 ******************************************************************************************/
template <typename T> //元素类型
void UniPrint::p ( T& s ) { //引用
   printf ( "%s[%d]*%d:\n", typeid(s).name(), &s, s.size() ); //基本信息
   s.traverse ( print ); //通过print()遍历输出所有元素
   printf ( "\n" );
}

#endif
