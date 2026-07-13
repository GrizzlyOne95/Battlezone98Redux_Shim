/*
 * Entry: 004a83b9
 * Name: std::allocator<PowerPlant_*>::allocate
 * Namespace: std::allocator<PowerPlant_*>
 * Signature: PowerPlant * * allocate(allocator<PowerPlant_*> * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

PowerPlant ** __thiscall
std::allocator<PowerPlant_*>::allocate(allocator<PowerPlant_*> *this,uint param_1)

{
  PowerPlant **ppPVar1;
  
  ppPVar1 = _Allocate<PowerPlant_*>(param_1,(PowerPlant **)0x0);
  return ppPVar1;
}
