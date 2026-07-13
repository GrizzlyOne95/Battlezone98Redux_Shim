/*
 * Entry: 004e6700
 * Name: std::vector<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::_Umove<SpawnPoint_*_*>
 * Namespace: std::vector<SpawnPoint_*,std::allocator<SpawnPoint_*>_>
 * Signature: SpawnPoint * * _Umove<SpawnPoint_*_*>(vector<SpawnPoint_*,std::allocator<SpawnPoint_*>_> * this, SpawnPoint * * param_1, SpawnPoint * * param_2, SpawnPoint * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SpawnPoint ** __thiscall
std::vector<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::_Umove<SpawnPoint_*_*>
          (vector<SpawnPoint_*,std::allocator<SpawnPoint_*>_> *this,SpawnPoint **param_1,
          SpawnPoint **param_2,SpawnPoint **param_3)

{
  SpawnPoint **ppSVar1;
  
  ppSVar1 = stdext::
            unchecked_uninitialized_copy<SpawnPoint_*_*,SpawnPoint_*_*,std::allocator<SpawnPoint_*>_>
                      (param_1,param_2,param_3,(allocator<SpawnPoint_*> *)&this->_padding_);
  return ppSVar1;
}
