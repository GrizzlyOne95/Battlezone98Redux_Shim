/*
 * Entry: 005553b1
 * Name: std::allocator<PortData_*>::deallocate
 * Namespace: std::allocator<PortData_*>
 * Signature: void deallocate(allocator<PortData_*> * this, PortData * * param_1, uint param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::allocator<PortData_*>::deallocate(allocator<PortData_*> *this,PortData **param_1,uint param_2)

{
  operator_delete(param_1);
  return;
}
