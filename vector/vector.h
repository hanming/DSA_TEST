#ifndef _VECTOR_H_
#define _VECTOR_H_

typedef int Rank; //��
#define DEFAULT_CAPACITY  3 //Ĭ�ϵĳ�ʼ������ʵ��Ӧ���п�����Ϊ����

template <typename T> class Vector { //����ģ����
protected:
   Rank _size; int _capacity;  T* _elem; //��ģ��������������
   void copyFrom ( T const* A, Rank lo, Rank hi ); //������������A[lo, hi)
   void expand(); //�ռ䲻��ʱ����
   
public:
// ���캯��
   Vector ( int c = DEFAULT_CAPACITY, int s = 0, T v = 0 ) //����Ϊc����ģΪs������Ԫ�س�ʼΪv
   	{ //s<=c
   		_elem = new T[_capacity = c]; 
		for ( _size = 0; _size < s; _elem[_size++] = v ); 
	} 
   Vector ( T const* A, Rank n ) { copyFrom ( A, 0, n ); } //�������帴��
   Vector ( T const* A, Rank lo, Rank hi ) { copyFrom ( A, lo, hi ); } //����
   Vector ( Vector<T> const& V ) { copyFrom ( V._elem, 0, V._size ); } //�������帴��
   Vector ( Vector<T> const& V, Rank lo, Rank hi ) { copyFrom ( V._elem, lo, hi ); } //����
// ��������
   ~Vector() { delete [] _elem; } //�ͷ��ڲ��ռ�
// ֻ�����ʽӿ�
   Rank size() const { return _size; } //��ģ

   T& operator[] ( Rank r ) const; //�����±������������������������ʽ���ø�Ԫ��
   Vector<T> & operator= ( Vector<T> const& ); //���ظ�ֵ���������Ա�ֱ�ӿ�¡����
   
   Rank insert ( Rank r, T const& e ); //����Ԫ��
   Rank insert ( T const& e ) { return insert ( _size, e ); } //Ĭ����ΪĩԪ�ز���

// ����
   void traverse ( void (* ) ( T& ) ); //������ʹ�ú���ָ�룬ֻ����ֲ����޸ģ�
   template <typename VST> void traverse ( VST& ); //������ʹ�ú������󣬿�ȫ�����޸ģ�
}; //Vector

template <typename T> //Ԫ������
void Vector<T>::copyFrom ( T const* A, Rank lo, Rank hi ) 
{ //����������A[lo, hi)Ϊ������������
   _elem = new T[_capacity = 2 * ( hi - lo ) ]; _size = 0; //����ռ䣬��ģ����
   while ( lo < hi ) //A[lo, hi)�ڵ�Ԫ����һ
      _elem[_size++] = A[lo++]; //������_elem[0, hi - lo)
}

template <typename T> Vector<T>& Vector<T>::operator= ( Vector<T> const& V ) 
{ //����
   if ( _elem ) delete [] _elem; //�ͷ�ԭ������
   copyFrom ( V._elem, 0, V.size() ); //���帴��
   return *this; //���ص�ǰ��������ã��Ա���ʽ��ֵ
}

template <typename T> T& Vector<T>::operator[] ( Rank r ) const //�����±������
{ return _elem[r]; } // assert: 0 <= r < _size

template <typename T> void Vector<T>::expand() 
{ //�����ռ䲻��ʱ����
   if ( _size < _capacity ) return; //��δ��Աʱ����������
   if ( _capacity < DEFAULT_CAPACITY ) _capacity = DEFAULT_CAPACITY; //��������С����
   T* oldElem = _elem;  _elem = new T[_capacity <<= 1]; //�����ӱ�
   for ( int i = 0; i < _size; i++ )
      _elem[i] = oldElem[i]; //����ԭ�������ݣ�TΪ�������ͣ��������ظ�ֵ������'='��
   /*DSA*/ //printf("\n_ELEM [%x]*%d/%d expanded and shift to [%x]*%d/%d\n", oldElem, _size, _capacity/2, _elem, _size, _capacity);
   delete [] oldElem; //�ͷ�ԭ�ռ�
}

template <typename T> //��e��Ϊ��ΪrԪ�ز���
Rank Vector<T>::insert ( Rank r, T const& e ) 
{ //assert: 0 <= r <= size
   expand(); //���б�Ҫ������
   for ( int i = _size; i > r; i-- ) _elem[i] = _elem[i-1]; //�Ժ���ǰ�����Ԫ��˳�κ���һ����Ԫ
   _elem[r] = e; _size++; //������Ԫ�ز���������
   return r; //������
}

template <typename T> void Vector<T>::traverse ( void ( *visit ) ( T& ) ) //��������ָ�����
{ for ( int i = 0; i < _size; i++ ) visit ( _elem[i] ); } //��������

template <typename T> template <typename VST> //Ԫ�����͡�������
void Vector<T>::traverse ( VST& visit ) //���������������
{ for ( int i = 0; i < _size; i++ ) visit ( _elem[i] ); } //��������

#endif
