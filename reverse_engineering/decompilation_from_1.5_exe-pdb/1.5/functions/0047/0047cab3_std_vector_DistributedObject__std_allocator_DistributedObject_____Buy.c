/*
 * Entry: 0047cab3
 * Name: std::vector<DistributedObject_*,std::allocator<DistributedObject_*>_>::_Buy
 * Namespace: std::vector<DistributedObject_*,std::allocator<DistributedObject_*>_>
 * Signature: bool _Buy(vector<DistributedObject_*,std::allocator<DistributedObject_*>_> * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
std::vector<DistributedObject_*,std::allocator<DistributedObject_*>_>::_Buy
          (vector<DistributedObject_*,std::allocator<DistributedObject_*>_> *this,uint param_1)

{
  bool bVar1;
  DistributedObject **ppDVar2;
  
  this->_Myfirst = (DistributedObject **)0x0;
  this->_Mylast = (DistributedObject **)0x0;
  this->_Myend = (DistributedObject **)0x0;
  if (param_1 == 0) {
    bVar1 = false;
  }
  else {
    if (param_1 < 0x40000000) {
      ppDVar2 = _Allocate<DistributedObject_*>(param_1,(DistributedObject **)0x0);
      this->_Myfirst = ppDVar2;
      this->_Mylast = ppDVar2;
      this->_Myend = ppDVar2 + param_1;
    }
    else {
      _Xlen();
    }
    bVar1 = true;
  }
  return bVar1;
}
