/**
 * @file   List.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
/////////////////////////////////
//  List.h                     //
//  Simple Template Container  //
//            Taiga.Noumi      //
/////////////////////////////////

////
/* 機能を最小限に絞ったコンテナクラス．
/* ・assertが有効ならば[]演算子に範囲外チェックが入る
/* ・データの追加は末尾のみ対応，データの削除は任意位置に対して可能
/* ・適合する最初の要素を削除するremove,適合する全要素を削除するremoveAllを用意
/* ・データ参照と追加はO(1)，オブジェクトを引数に取った削除はO(n)
/* ・イテレータのインターフェースはC++標準コンテナとほぼ同一
/*
/*  //sample
/*  datatype::Quaternion q1(1,0,0,0);
/*  datatype::Quaternion q2(0,1,0,0);
/*  datatype::List<datatype::Quaternion> list;
/*  list.add(q1);
/*  list.add(q2);
/*  list.add(q3);
/*
/*  //イテレータを使って要素にアクセス
/*  datatype::List<datatype::Quaternion>::iterator it = list.begin();
/*  while(it != list.end()){
/*      std::cout << (*it).conjugate();//*itを使って要素にアクセス
/*      ++it;                          //後置インクリメントもサポートするが，前置のほうが一時オブジェクトを作らず高速
/*  }
/*  for(it = list.begin(); it != list.end(); ++it){
/*      std::cout << (*it).conjugate();//上と同じことをfor文で
/*  }
/*  for(int i = 0; i < list.size(); i++){
/*      std::cout << list[i].conjugate();//イテレータを使わない場合
/*  }
/*
/*/
////

#ifndef stf_datatype_List_h
#define stf_datatype_List_h
#include<assert.h>

namespace stf { 
namespace datatype {

template<class T>
class List {
public:
	explicit List() : size_(0),capacity_(3){ data_ = new T*[capacity_];};
	~List(){};
	// inner class
	class _iterator{
	private:
		T *point_;//現在の要素
		const List<T> *list_;//リスト
		int index_;
	public:
		_iterator(const _iterator &rhs): point_(rhs.point_), list_(rhs.list_), index_(rhs.index_){};
		_iterator(): point_(0), list_(0), index_(0) {};
		_iterator(const List<T>* container, int index=0): point_((*container).data_[index]), list_(container), index_(index) {};
		~_iterator(){};
		int index() const { return index_; } //getter
        T& operator *(){return *point_;}
        bool operator==(const _iterator &rhs){
			if(point_ == rhs.point_)  //指しているオブジェクトが同一で
              if(index_ == rhs.index_)//インデックスも一緒の場合
                return true;
			return false;
		}
		bool operator!=(const _iterator &rhs){return !(*this == rhs);}
		//前置インクリメント
		_iterator &operator++(){ 
			index_++;
			point_ = list_->data_[index_];
			return *this;
		}
		//後置インクリメント
		_iterator operator++(int dummy){		
			return (*this)++;
		}
		//前置デクリメント        
        _iterator &operator--(){
            index--;
            point_ = list_->data_[index_];
            return *this;
        }
		//後置デクリメント 
        _iterator &operator--(int dummy){
            return (*this)--;
        }
	};
	typedef typename List<T>::_iterator iterator;
	// public methods
	T& operator [](int index){assert(index < size_ && index >= 0); return *(data_[index]);}
	const T& operator [](int index) const {assert(index < size_ && index >= 0); return *(data_[index]);}
	_iterator begin() const{return _iterator(this,0);}
	_iterator end() const{return _iterator(this,size_);}
	int size() const{return size_;}
	int capacity() const{return capacity_;}
	void clear(){
		delete [] data_;
		data_ = new T*[3];
		size_ = 0;
		capacity_ = 3;
	}
	void add(T& data){
        size_++;
        //常に1個以上の空きスロットが出来るようにcapacity_を確保する
		if(size_ < capacity_){
			data_[size_-1] = &data;
            data_[size_] = 0;//最後のポインタをNULLで埋める
		}else{
			T** tempdata = new T*[2 * capacity_];
			for(int i = 0; i < capacity_; i++)
				tempdata[i] = data_[i];//ポインタをコピー
			delete [] data_;
			data_ = tempdata;
			data_[size_-1] = &data;
            data_[size_] = 0;//最後のポインタをNULLで埋める
			capacity_ *= 2;
		}
	}
    void push_back(T& data){//std::vectorと互換性を持たせるための関数
        add(data);
    }
    void remove(T& data){
        int i = 0;
        while(i < size_){
            if(data_[i] == &data){
                removeat_(i);
                return;
            }
            i++;
        }
    }
    void removeAll(T& data){
        int i = 0;
        while(i < size_){
          if(data_[i] == &data) removeat_(i);
          else i++;
        }
    }
	List(const List<T>& rhs){}//コピーコンストラクタ，実行されない
private:
	T** data_;
	int capacity_;//現在確保されている配列サイズ
	int size_;//使用されている配列サイズ
    T& operator =(const List<T>& rhs){}//コピー，実行されない
    //i番目の要素を削除
    void removeat_(int index){
        assert(size_ != 0);
        size_ --;
        for(int i = index; i < size_; i++)
          data_[i] = data_[i+1];
        data_[size_] = 0;
        if(size_ * 3 < capacity_){
            capacity_ /= 2;
			T** tempdata = new T*[capacity_];
			for(int i = 0; i < size_; i++)
			  tempdata[i] = data_[i];//ポインタをコピー
			delete [] data_;
			data_ = tempdata;
            data_[size_] = 0;//最後のポインタをNULLで埋める
        }
    }
};

} /* End of namespace stf::datatype */
} /* End of namespace stf */

#endif // stf_datatype_List_h
