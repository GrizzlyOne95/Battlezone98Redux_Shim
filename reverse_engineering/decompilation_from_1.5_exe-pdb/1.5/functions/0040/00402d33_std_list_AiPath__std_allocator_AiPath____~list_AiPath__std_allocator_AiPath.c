/*
 * Entry: 00402d33
 * Name: std::list<AiPath_*,std::allocator<AiPath_*>_>::~list<AiPath_*,std::allocator<AiPath_*>_>
 * Namespace: std::list<AiPath_*,std::allocator<AiPath_*>_>
 * Signature: void ~list<AiPath_*,std::allocator<AiPath_*>_>(list<AiPath_*,std::allocator<AiPath_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::list<AiPath_*,std::allocator<AiPath_*>_>::~list<AiPath_*,std::allocator<AiPath_*>_>
          (list<AiPath_*,std::allocator<AiPath_*>_> *this)

{
  _Tidy(this);
  operator_delete((void *)this->_padding_);
  return;
}
