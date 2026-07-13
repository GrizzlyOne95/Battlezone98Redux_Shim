/*
 * Entry: 00557734
 * Name: std::allocator<Server_*>::allocate
 * Namespace: std::allocator<Server_*>
 * Signature: Server * * allocate(allocator<Server_*> * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Server ** __thiscall std::allocator<Server_*>::allocate(allocator<Server_*> *this,uint param_1)

{
  Server **ppSVar1;
  
  ppSVar1 = _Allocate<Server_*>(param_1,(Server **)0x0);
  return ppSVar1;
}
