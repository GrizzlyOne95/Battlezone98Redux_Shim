/*
 * Entry: 00408edc
 * Name: std::_Vector_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::_Vector_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>
 * Namespace: std::_Vector_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>
 * Signature: _Vector_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> * _Vector_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>(_Vector_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> * this, SpawnPoint * * param_1, _Container_base_aux * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> * __thiscall
std::_Vector_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::
_Vector_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>
          (_Vector_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> *this,SpawnPoint **param_1,
          _Container_base_aux *param_2)

{
  _Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::
  _Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>
            ((_Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> *)this,param_1,
             param_2);
  return this;
}
