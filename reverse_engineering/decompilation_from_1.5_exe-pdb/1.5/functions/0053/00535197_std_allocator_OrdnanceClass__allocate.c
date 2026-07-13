/*
 * Entry: 00535197
 * Name: std::allocator<OrdnanceClass_*>::allocate
 * Namespace: std::allocator<OrdnanceClass_*>
 * Signature: OrdnanceClass * * allocate(allocator<OrdnanceClass_*> * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

OrdnanceClass ** __thiscall
std::allocator<OrdnanceClass_*>::allocate(allocator<OrdnanceClass_*> *this,uint param_1)

{
  OrdnanceClass **ppOVar1;
  
  ppOVar1 = _Allocate<OrdnanceClass_*>(param_1,(OrdnanceClass **)0x0);
  return ppOVar1;
}
