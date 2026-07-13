/*
 * Entry: 0048e4c4
 * Name: std::deque<BASE_STRUCT,std::allocator<BASE_STRUCT>_>::push_back
 * Namespace: std::deque<BASE_STRUCT,std::allocator<BASE_STRUCT>_>
 * Signature: void push_back(deque<BASE_STRUCT,std::allocator<BASE_STRUCT>_> * this, BASE_STRUCT * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::deque<BASE_STRUCT,std::allocator<BASE_STRUCT>_>::push_back
          (deque<BASE_STRUCT,std::allocator<BASE_STRUCT>_> *this,BASE_STRUCT *param_1)

{
  uint uVar1;
  BASE_STRUCT *pBVar2;
  uint uVar3;
  
  if (((this->_Myoff + this->_Mysize & 1) == 0) && (this->_Mapsize <= this->_Mysize + 2 >> 1)) {
    _Growmap(this,1);
  }
  uVar3 = this->_Myoff + this->_Mysize;
  uVar1 = uVar3 >> 1;
  if (this->_Mapsize <= uVar1) {
    uVar1 = uVar1 - this->_Mapsize;
  }
  if (this->_Map[uVar1] == (BASE_STRUCT *)0x0) {
    pBVar2 = _Allocate<BASE_STRUCT>(2,(BASE_STRUCT *)0x0);
    this->_Map[uVar1] = pBVar2;
  }
  pBVar2 = this->_Map[uVar1] + (uVar3 & 1);
  if (pBVar2 != (BASE_STRUCT *)0x0) {
    *(undefined4 *)pBVar2 = *(undefined4 *)param_1;
    *(undefined2 *)((int)&pBVar2->dwLocalID + 2) = *(undefined2 *)((int)&param_1->dwLocalID + 2);
  }
  this->_Mysize = this->_Mysize + 1;
  return;
}
