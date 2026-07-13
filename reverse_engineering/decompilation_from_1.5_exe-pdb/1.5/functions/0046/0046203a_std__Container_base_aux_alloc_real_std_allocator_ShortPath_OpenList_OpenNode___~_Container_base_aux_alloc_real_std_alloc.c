/*
 * Entry: 0046203a
 * Name: std::_Container_base_aux_alloc_real<std::allocator<ShortPath::OpenList::OpenNode>_>::~_Container_base_aux_alloc_real<std::allocator<ShortPath::OpenList::OpenNode>_>
 * Namespace: std::_Container_base_aux_alloc_real<std::allocator<ShortPath::OpenList::OpenNode>_>
 * Signature: void ~_Container_base_aux_alloc_real<std::allocator<ShortPath::OpenList::OpenNode>_>(_Container_base_aux_alloc_real<std::allocator<ShortPath::OpenList::OpenNode>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::_Container_base_aux_alloc_real<std::allocator<ShortPath::OpenList::OpenNode>_>::
~_Container_base_aux_alloc_real<std::allocator<ShortPath::OpenList::OpenNode>_>
          (_Container_base_aux_alloc_real<std::allocator<ShortPath::OpenList::OpenNode>_> *this)

{
  operator_delete((void *)this->_padding_);
  return;
}
