/*
 * Entry: 0048bab8
 * Name: std::deque<BASE_STRUCT,std::allocator<BASE_STRUCT>_>::_Tidy
 * Namespace: std::deque<BASE_STRUCT,std::allocator<BASE_STRUCT>_>
 * Signature: void _Tidy(deque<BASE_STRUCT,std::allocator<BASE_STRUCT>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::deque<BASE_STRUCT,std::allocator<BASE_STRUCT>_>::_Tidy
          (deque<BASE_STRUCT,std::allocator<BASE_STRUCT>_> *this)

{
  BASE_STRUCT **ppBVar1;
  uint uVar2;
  
  while (this->_Mysize != 0) {
    if ((this->_Mysize != 0) && (uVar2 = this->_Mysize - 1, this->_Mysize = uVar2, uVar2 == 0)) {
      this->_Myoff = 0;
    }
  }
  uVar2 = this->_Mapsize;
  while (ppBVar1 = this->_Map, uVar2 != 0) {
    uVar2 = uVar2 - 1;
    if (ppBVar1[uVar2] != (BASE_STRUCT *)0x0) {
      operator_delete(ppBVar1[uVar2]);
    }
  }
  if (ppBVar1 != (BASE_STRUCT **)0x0) {
    operator_delete(ppBVar1);
  }
  this->_Mapsize = 0;
  this->_Map = (BASE_STRUCT **)0x0;
  return;
}
