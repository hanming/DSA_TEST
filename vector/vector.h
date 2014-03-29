#ifndef _VECTOR_H_
#define _VECTOR_H_

typedef int Rank; //秩
#define DEFAULT_CAPACITY  3 //默认的初始容量（实际应用中可设置为更大）

template <typename T> class Vector { //向量模板类
protected:
   Rank _size; int _capacity;  T* _elem; //规模、容量、数据区
   void copyFrom ( T const* A, Rank lo, Rank hi ); //复制数组区间A[lo, hi)
   void expand(); //空间不足时扩容
   
public:
// 构造函数
   Vector ( int c = DEFAULT_CAPACITY, int s = 0, T v = 0 ) //容量为c、规模为s、所有元素初始为v
   	{ //s<=c
   		_elem = new T[_capacity = c]; 
		for ( _size = 0; _size < s; _elem[_size++] = v ); 
	} 
   Vector ( T const* A, Rank n ) { copyFrom ( A, 0, n ); } //数组整体复制
   Vector ( T const* A, Rank lo, Rank hi ) { copyFrom ( A, lo, hi ); } //区间
   Vector ( Vector<T> const& V ) { copyFrom ( V._elem, 0, V._size ); } //向量整体复制
   Vector ( Vector<T> const& V, Rank lo, Rank hi ) { copyFrom ( V._elem, lo, hi ); } //区间
// 析构函数
   ~Vector() { delete [] _elem; } //释放内部空间
// 只读访问接口
   Rank size() const { return _size; } //规模

   T& operator[] ( Rank r ) const; //重载下标操作符，可以类似于数组形式引用各元素
   Vector<T> & operator= ( Vector<T> const& ); //重载赋值操作符，以便直接克隆向量
   
   Rank insert ( Rank r, T const& e ); //插入元素
   Rank insert ( T const& e ) { return insert ( _size, e ); } //默认作为末元素插入

// 遍历
   void traverse ( void (* ) ( T& ) ); //遍历（使用函数指针，只读或局部性修改）
   template <typename VST> void traverse ( VST& ); //遍历（使用函数对象，可全局性修改）
}; //Vector

template <typename T> //元素类型
void Vector<T>::copyFrom ( T const* A, Rank lo, Rank hi ) 
{ //以数组区间A[lo, hi)为蓝本复制向量
   _elem = new T[_capacity = 2 * ( hi - lo ) ]; _size = 0; //分配空间，规模清零
   while ( lo < hi ) //A[lo, hi)内的元素逐一
      _elem[_size++] = A[lo++]; //复制至_elem[0, hi - lo)
}

template <typename T> Vector<T>& Vector<T>::operator= ( Vector<T> const& V ) 
{ //重载
   if ( _elem ) delete [] _elem; //释放原有内容
   copyFrom ( V._elem, 0, V.size() ); //整体复制
   return *this; //返回当前对象的引用，以便链式赋值
}

template <typename T> T& Vector<T>::operator[] ( Rank r ) const //重载下标操作符
{ return _elem[r]; } // assert: 0 <= r < _size

template <typename T> void Vector<T>::expand() 
{ //向量空间不足时扩容
   if ( _size < _capacity ) return; //尚未满员时，不必扩容
   if ( _capacity < DEFAULT_CAPACITY ) _capacity = DEFAULT_CAPACITY; //不低于最小容量
   T* oldElem = _elem;  _elem = new T[_capacity <<= 1]; //容量加倍
   for ( int i = 0; i < _size; i++ )
      _elem[i] = oldElem[i]; //复制原向量内容（T为基本类型，或已重载赋值操作符'='）
   /*DSA*/ //printf("\n_ELEM [%x]*%d/%d expanded and shift to [%x]*%d/%d\n", oldElem, _size, _capacity/2, _elem, _size, _capacity);
   delete [] oldElem; //释放原空间
}

template <typename T> //将e作为秩为r元素插入
Rank Vector<T>::insert ( Rank r, T const& e ) 
{ //assert: 0 <= r <= size
   expand(); //若有必要，扩容
   for ( int i = _size; i > r; i-- ) _elem[i] = _elem[i-1]; //自后向前，后继元素顺次后移一个单元
   _elem[r] = e; _size++; //置入新元素并更新容量
   return r; //返回秩
}

template <typename T> void Vector<T>::traverse ( void ( *visit ) ( T& ) ) //借助函数指针机制
{ for ( int i = 0; i < _size; i++ ) visit ( _elem[i] ); } //遍历向量

template <typename T> template <typename VST> //元素类型、操作器
void Vector<T>::traverse ( VST& visit ) //借助函数对象机制
{ for ( int i = 0; i < _size; i++ ) visit ( _elem[i] ); } //遍历向量

#endif
