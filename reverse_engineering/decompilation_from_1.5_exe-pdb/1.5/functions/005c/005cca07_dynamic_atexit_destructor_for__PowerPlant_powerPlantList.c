/*
 * Entry: 005cca07
 * Name: `dynamic_atexit_destructor_for_'PowerPlant::powerPlantList''
 * Namespace: `dynamic_atexit_destructor_for_'PowerPlant
 * Signature: void powerPlantList''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl `dynamic_atexit_destructor_for_'PowerPlant::powerPlantList__(void)

{
  std::vector<PowerPlant_*,std::allocator<PowerPlant_*>_>::_Tidy(&PowerPlant::powerPlantList);
  operator_delete((void *)PowerPlant::powerPlantList._padding_);
  return;
}
