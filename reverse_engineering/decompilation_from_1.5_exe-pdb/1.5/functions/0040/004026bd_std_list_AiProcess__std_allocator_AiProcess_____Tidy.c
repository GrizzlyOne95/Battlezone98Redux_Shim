/*
 * Entry: 004026bd
 * Name: std::list<AiProcess_*,std::allocator<AiProcess_*>_>::_Tidy
 * Namespace: std::list<AiProcess_*,std::allocator<AiProcess_*>_>
 * Signature: void _Tidy(list<AiProcess_*,std::allocator<AiProcess_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::list<AiProcess_*,std::allocator<AiProcess_*>_>::_Tidy
          (list<AiProcess_*,std::allocator<AiProcess_*>_> *this)

{
  clear(this);
  operator_delete(this->_Myhead);
  this->_Myhead = (_Node *)0x0;
  return;
}
