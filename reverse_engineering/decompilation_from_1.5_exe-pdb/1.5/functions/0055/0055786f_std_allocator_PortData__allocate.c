/*
 * Entry: 0055786f
 * Name: std::allocator<PortData_*>::allocate
 * Namespace: std::allocator<PortData_*>
 * Signature: PortData * * allocate(allocator<PortData_*> * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

PortData ** __thiscall
std::allocator<PortData_*>::allocate(allocator<PortData_*> *this,uint param_1)

{
  PortData **ppPVar1;
  
  ppPVar1 = _Allocate<PortData_*>(param_1,(PortData **)0x0);
  return ppPVar1;
}
