/*
 * Entry: 0040e75f
 * Name: std::list<AttackerInfo,std::allocator<AttackerInfo>_>::~list<AttackerInfo,std::allocator<AttackerInfo>_>
 * Namespace: std::list<AttackerInfo,std::allocator<AttackerInfo>_>
 * Signature: void ~list<AttackerInfo,std::allocator<AttackerInfo>_>(list<AttackerInfo,std::allocator<AttackerInfo>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::list<AttackerInfo,std::allocator<AttackerInfo>_>::
~list<AttackerInfo,std::allocator<AttackerInfo>_>
          (list<AttackerInfo,std::allocator<AttackerInfo>_> *this)

{
  _Tidy(this);
  operator_delete((void *)this->_padding_);
  return;
}
