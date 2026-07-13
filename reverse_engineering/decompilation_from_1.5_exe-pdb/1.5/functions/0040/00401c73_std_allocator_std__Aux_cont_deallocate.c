/*
 * Entry: 00401c73
 * Name: std::allocator<std::_Aux_cont>::deallocate
 * Namespace: std::allocator<std::_Aux_cont>
 * Signature: void deallocate(allocator<std::_Aux_cont> * this, _Aux_cont * param_1, uint param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::allocator<std::_Aux_cont>::deallocate
          (allocator<std::_Aux_cont> *this,_Aux_cont *param_1,uint param_2)

{
  operator_delete(param_1);
  return;
}
