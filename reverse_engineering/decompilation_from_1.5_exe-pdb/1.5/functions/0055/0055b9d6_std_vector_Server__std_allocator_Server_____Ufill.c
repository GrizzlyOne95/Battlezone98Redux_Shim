/*
 * Entry: 0055b9d6
 * Name: std::vector<Server_*,std::allocator<Server_*>_>::_Ufill
 * Namespace: std::vector<Server_*,std::allocator<Server_*>_>
 * Signature: Server * * _Ufill(vector<Server_*,std::allocator<Server_*>_> * this, Server * * param_1, uint param_2, Server * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Server ** __thiscall
std::vector<Server_*,std::allocator<Server_*>_>::_Ufill
          (vector<Server_*,std::allocator<Server_*>_> *this,Server **param_1,uint param_2,
          Server **param_3)

{
  stdext::unchecked_fill_n<Server_*_*,unsigned_int,Server_*>(param_1,param_2,param_3);
  return param_1 + param_2;
}
