/*
 * Entry: 004977a1
 * Name: std::vector<Attachment_*,std::allocator<Attachment_*>_>::_Buy
 * Namespace: std::vector<Attachment_*,std::allocator<Attachment_*>_>
 * Signature: bool _Buy(vector<Attachment_*,std::allocator<Attachment_*>_> * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
std::vector<Attachment_*,std::allocator<Attachment_*>_>::_Buy
          (vector<Attachment_*,std::allocator<Attachment_*>_> *this,uint param_1)

{
  bool bVar1;
  Attachment **ppAVar2;
  
  this->_Myfirst = (Attachment **)0x0;
  this->_Mylast = (Attachment **)0x0;
  this->_Myend = (Attachment **)0x0;
  if (param_1 == 0) {
    bVar1 = false;
  }
  else {
    if (param_1 < 0x40000000) {
      ppAVar2 = _Allocate<Attachment_*>(param_1,(Attachment **)0x0);
      this->_Myfirst = ppAVar2;
      this->_Mylast = ppAVar2;
      this->_Myend = ppAVar2 + param_1;
    }
    else {
      _Xlen();
    }
    bVar1 = true;
  }
  return bVar1;
}
