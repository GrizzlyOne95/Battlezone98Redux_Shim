/*
 * Entry: 00403fbe
 * Name: std::list<AiTask_*,std::allocator<AiTask_*>_>::empty
 * Namespace: std::list<AiTask_*,std::allocator<AiTask_*>_>
 * Signature: bool empty(list<AiTask_*,std::allocator<AiTask_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
std::list<AiTask_*,std::allocator<AiTask_*>_>::empty(list<AiTask_*,std::allocator<AiTask_*>_> *this)

{
  return this->_Mysize == 0;
}
