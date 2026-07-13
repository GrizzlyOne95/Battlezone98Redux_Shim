/*
 * Entry: 0051897d
 * Name: std::vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::_Buy
 * Namespace: std::vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>
 * Signature: bool _Buy(vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_> * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
std::vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::_Buy
          (vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_> *this,uint param_1)

{
  bool bVar1;
  ObjectClassInfo **ppOVar2;
  
  this->_Myfirst = (ObjectClassInfo **)0x0;
  this->_Mylast = (ObjectClassInfo **)0x0;
  this->_Myend = (ObjectClassInfo **)0x0;
  if (param_1 == 0) {
    bVar1 = false;
  }
  else {
    if (param_1 < 0x40000000) {
      ppOVar2 = _Allocate<ObjectClassInfo_*>(param_1,(ObjectClassInfo **)0x0);
      this->_Myfirst = ppOVar2;
      this->_Mylast = ppOVar2;
      this->_Myend = ppOVar2 + param_1;
    }
    else {
      _Xlen();
    }
    bVar1 = true;
  }
  return bVar1;
}
