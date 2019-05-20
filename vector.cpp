// push_back이 필요한 상황에서 vector clear를 간략히 구현한 코드(메모리 할당은 해지되지 않지만 시간이 짧게 걸림)
// Optimize vector for exam

class vector {
public:
  int capacity, sz;
  int *vc;

  vector() {
      capacity = 8;
      sz = 0;
      vc = new int[capacity];
  }
  ~vector() {
      delete[] vc;
  }
  void push_back(int val) {
      if (capacity == sz) {
          capacity *= 2;
          int *tmp = new int[capacity];
          for (register int i = 0; i < sz; i++)
              tmp[i] = vc[i];
          delete[] vc;
          vc = tmp;
      }
      vc[sz++] = val;
  }
  int size() {
      return sz;
  }
  bool empty() {
      return !sz;
  }
  void clear() {
      sz = 0;
  }
  int &operator[](int i) {
      return vc[i];
  }
}


// vector clear를 온전히 구현한 코드(메모리 할당은 해지되나 시간이 오래 걸림)

#include <iostream>

class _vector {
public:
    int sz;
    int capacity;
    int *vc;
    _vector() {
        capacity = 8;
        sz = 0;
        vc = new int[capacity];
    }
    ~_vector() {
        delete[] vc;
    }
    void push_back(int val) {
        if (sz == capacity) {
            int *tmp = new int[capacity];
            for (int i = 0; i < capacity; i++)
                tmp[i] = vc[i];
 
            capacity *= 2;
 
            delete[] vc;
            vc = new int[capacity];
 
            for (int i = 0; i < capacity; i++)
                vc[i] = tmp[i];
        }
        vc[sz++] = val;
    }
 
    void clear() {
        capacity = 8;
        sz = 0;
 
        delete[] vc;
 
        vc = new int[capacity];
    }
 
    int size() {
        return sz;
    }
    bool empty() {
        return !sz;
    }
    int &operator [](int i)  {
        return vc[i];
    }
    /*
        여기서 그냥 int operator [](int i) { return vc[i] };를 하면
        값 참조는 되지만 대입이 되지 않는다.
    */
};
 
int main() {
    _vector vc;
    vc.push_back(1);
    printf("%d", vc[0]);
    vc[0] = 2;
    printf("%d", vc[0]);
    
    return 0;
}




/*
  일반 vector 코드

  This "_vector" class doesn't supply iterator.
  Only use dynamic arrays.
*/
template <typename T>
class _vector {
private:
    int _capacity = 0;
    int _size = 0;
    T *vc;
 
public:
    _vector(int size = 1) {
        _capacity = size;
        vc = new T[size];
    }
    ~_vector() {
        delete[] vc;
    }
    int size() { return _size; }
    bool empty() { return !_size; }
    void resize(int size) {
        _capacity = size;
        T *tVc = new T[size];
        for (int i = 0; i < _size; i++)
            tVc[i] = vc[i];
        delete[] vc;
 
        vc = tVc;
    }
    void clear() {
        delete[] vc;
        _capacity = 1;
        _size = 0;
 
        vc = new T[1];
    }
    void push_back(T val) {
        if (_size == _capacity) {
            _capacity *= 2;
            resize(_capacity);
        }
 
        vc[_size++] = val;
    }
 
    void pop_back() {
        if (_size == 0)
            return;
 
        vc[--_size] = 0;
    }
    
    void reverse() {
        for (int i = 0; i < _size / 2; i++) 
        {
            T tmp = vc[i];
            vc[i] = vc[(_size - 1) - i];
            vc[(_size - 1) - i] = tmp;
        }
    }
    T &operator[](const int &i) const{ return vc[i]; }
    void operator=(const _vector<T> &tVc) {
        _capacity = tVc._capacity;
        _size = tVc._size;
        delete[] vc;
        vc = new T[_capacity];
        for (int i = 0; i < _size; i++)
            vc[i] = tVc[i];
    }
    /*
    If you want use STL std::sort or your own sort
    sort(&vc[0], &vc[vc.size()]);
    */
};

/* 
  위의 내용에서 
  T &operator[](const int &i) const{ return vc[i]; }를 
  T &operator[](const int &i) { return vc[i]; }로 바꾸면 에러가 난다.

  https://msdn.microsoft.com/ko-kr/library/ys0bw32s.aspx
*/