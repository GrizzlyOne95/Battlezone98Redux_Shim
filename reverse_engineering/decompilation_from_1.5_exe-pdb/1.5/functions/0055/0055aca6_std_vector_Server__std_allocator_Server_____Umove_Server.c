/*
 * Entry: 0055aca6
 * Name: std::vector<Server_*,std::allocator<Server_*>_>::_Umove<Server_*_*>
 * Namespace: std::vector<Server_*,std::allocator<Server_*>_>
 * Signature: Server * * _Umove<Server_*_*>(vector<Server_*,std::allocator<Server_*>_> * this, Server * * param_1, Server * * param_2, Server * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Server ** __thiscall
std::vector<Server_*,std::allocator<Server_*>_>::_Umove<Server_*_*>
          (vector<Server_*,std::allocator<Server_*>_> *this,Server **param_1,Server **param_2,
          Server **param_3)

{
  Server **ppSVar1;
  
  ppSVar1 = stdext::unchecked_uninitialized_copy<Server_*_*,Server_*_*,std::allocator<Server_*>_>
                      (param_1,param_2,param_3,(allocator<Server_*> *)&this->_padding_);
  return ppSVar1;
}
