/*
 * Entry: 00401b77
 * Name: std::list<AiProcess_*,std::allocator<AiProcess_*>_>::empty
 * Namespace: std::list<AiProcess_*,std::allocator<AiProcess_*>_>
 * Signature: bool empty(list<AiProcess_*,std::allocator<AiProcess_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
std::list<AiProcess_*,std::allocator<AiProcess_*>_>::empty
          (list<AiProcess_*,std::allocator<AiProcess_*>_> *this)

{
  return this->_Mysize == 0;
}
