/*
 * Entry: 0055779d
 * Name: std::allocator<Session_*>::allocate
 * Namespace: std::allocator<Session_*>
 * Signature: Session * * allocate(allocator<Session_*> * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Session ** __thiscall std::allocator<Session_*>::allocate(allocator<Session_*> *this,uint param_1)

{
  Session **ppSVar1;
  
  ppSVar1 = _Allocate<Session_*>(param_1,(Session **)0x0);
  return ppSVar1;
}
