/*
 * Entry: 004033df
 * Name: std::list<AiPath_*,std::allocator<AiPath_*>_>::empty
 * Namespace: std::list<AiPath_*,std::allocator<AiPath_*>_>
 * Signature: bool empty(list<AiPath_*,std::allocator<AiPath_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
std::list<AiPath_*,std::allocator<AiPath_*>_>::empty(list<AiPath_*,std::allocator<AiPath_*>_> *this)

{
  return this->_Mysize == 0;
}
