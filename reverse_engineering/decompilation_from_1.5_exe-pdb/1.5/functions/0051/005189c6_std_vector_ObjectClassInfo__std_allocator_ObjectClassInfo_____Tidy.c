/*
 * Entry: 005189c6
 * Name: std::vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::_Tidy
 * Namespace: std::vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>
 * Signature: void _Tidy(vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::_Tidy
          (vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_> *this)

{
  if (this->_Myfirst != (ObjectClassInfo **)0x0) {
    operator_delete(this->_Myfirst);
  }
  this->_Myfirst = (ObjectClassInfo **)0x0;
  this->_Mylast = (ObjectClassInfo **)0x0;
  this->_Myend = (ObjectClassInfo **)0x0;
  return;
}
