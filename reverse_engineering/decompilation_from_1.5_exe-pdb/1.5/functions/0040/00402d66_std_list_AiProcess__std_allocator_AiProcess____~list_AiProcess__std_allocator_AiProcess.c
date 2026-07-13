/*
 * Entry: 00402d66
 * Name: std::list<AiProcess_*,std::allocator<AiProcess_*>_>::~list<AiProcess_*,std::allocator<AiProcess_*>_>
 * Namespace: std::list<AiProcess_*,std::allocator<AiProcess_*>_>
 * Signature: void ~list<AiProcess_*,std::allocator<AiProcess_*>_>(list<AiProcess_*,std::allocator<AiProcess_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::list<AiProcess_*,std::allocator<AiProcess_*>_>::~list<AiProcess_*,std::allocator<AiProcess_*>_>
          (list<AiProcess_*,std::allocator<AiProcess_*>_> *this)

{
  _Tidy(this);
  operator_delete((void *)this->_padding_);
  return;
}
