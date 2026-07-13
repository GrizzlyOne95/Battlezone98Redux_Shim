/*
 * Entry: 00402629
 * Name: std::list<AiPath_*,std::allocator<AiPath_*>_>::_Tidy
 * Namespace: std::list<AiPath_*,std::allocator<AiPath_*>_>
 * Signature: void _Tidy(list<AiPath_*,std::allocator<AiPath_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::list<AiPath_*,std::allocator<AiPath_*>_>::_Tidy(list<AiPath_*,std::allocator<AiPath_*>_> *this)

{
  clear(this);
  operator_delete(this->_Myhead);
  this->_Myhead = (_Node *)0x0;
  return;
}
