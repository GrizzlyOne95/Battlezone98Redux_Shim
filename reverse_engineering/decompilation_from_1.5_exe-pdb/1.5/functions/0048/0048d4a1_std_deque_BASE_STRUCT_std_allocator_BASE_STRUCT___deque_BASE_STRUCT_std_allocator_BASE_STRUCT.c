/*
 * Entry: 0048d4a1
 * Name: std::deque<BASE_STRUCT,std::allocator<BASE_STRUCT>_>::deque<BASE_STRUCT,std::allocator<BASE_STRUCT>_>
 * Namespace: std::deque<BASE_STRUCT,std::allocator<BASE_STRUCT>_>
 * Signature: deque<BASE_STRUCT,std::allocator<BASE_STRUCT>_> * deque<BASE_STRUCT,std::allocator<BASE_STRUCT>_>(deque<BASE_STRUCT,std::allocator<BASE_STRUCT>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

deque<BASE_STRUCT,std::allocator<BASE_STRUCT>_> * __thiscall
std::deque<BASE_STRUCT,std::allocator<BASE_STRUCT>_>::
deque<BASE_STRUCT,std::allocator<BASE_STRUCT>_>
          (deque<BASE_STRUCT,std::allocator<BASE_STRUCT>_> *this)

{
  _Deque_val<BASE_STRUCT,std::allocator<BASE_STRUCT>_>::
  _Deque_val<BASE_STRUCT,std::allocator<BASE_STRUCT>_>
            ((_Deque_val<BASE_STRUCT,std::allocator<BASE_STRUCT>_> *)this,SUB41(this,0));
  this->_Map = (BASE_STRUCT **)0x0;
  this->_Mapsize = 0;
  this->_Myoff = 0;
  this->_Mysize = 0;
  return this;
}
