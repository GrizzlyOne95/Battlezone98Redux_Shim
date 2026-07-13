/*
 * Entry: 004a802a
 * Name: std::allocator<PowerPlant_*>::deallocate
 * Namespace: std::allocator<PowerPlant_*>
 * Signature: void deallocate(allocator<PowerPlant_*> * this, PowerPlant * * param_1, uint param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::allocator<PowerPlant_*>::deallocate
          (allocator<PowerPlant_*> *this,PowerPlant **param_1,uint param_2)

{
  operator_delete(param_1);
  return;
}
