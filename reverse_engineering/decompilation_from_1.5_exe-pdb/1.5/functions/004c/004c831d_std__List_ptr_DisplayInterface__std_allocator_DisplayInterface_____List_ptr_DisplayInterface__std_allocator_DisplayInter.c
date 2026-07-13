/*
 * Entry: 004c831d
 * Name: std::_List_ptr<DisplayInterface_*,std::allocator<DisplayInterface_*>_>::_List_ptr<DisplayInterface_*,std::allocator<DisplayInterface_*>_>
 * Namespace: std::_List_ptr<DisplayInterface_*,std::allocator<DisplayInterface_*>_>
 * Signature: _List_ptr<DisplayInterface_*,std::allocator<DisplayInterface_*>_> * _List_ptr<DisplayInterface_*,std::allocator<DisplayInterface_*>_>(_List_ptr<DisplayInterface_*,std::allocator<DisplayInterface_*>_> * this, allocator<DisplayInterface_*> param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_List_ptr<DisplayInterface_*,std::allocator<DisplayInterface_*>_> * __thiscall
std::_List_ptr<DisplayInterface_*,std::allocator<DisplayInterface_*>_>::
_List_ptr<DisplayInterface_*,std::allocator<DisplayInterface_*>_>
          (_List_ptr<DisplayInterface_*,std::allocator<DisplayInterface_*>_> *this,
          allocator<DisplayInterface_*> param_1)

{
  _List_nod<DisplayInterface_*,std::allocator<DisplayInterface_*>_>::
  _List_nod<DisplayInterface_*,std::allocator<DisplayInterface_*>_>
            ((_List_nod<DisplayInterface_*,std::allocator<DisplayInterface_*>_> *)this,SUB41(this,0)
            );
  return this;
}
