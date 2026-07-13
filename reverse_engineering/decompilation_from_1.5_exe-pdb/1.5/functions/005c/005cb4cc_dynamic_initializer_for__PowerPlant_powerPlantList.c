/*
 * Entry: 005cb4cc
 * Name: `dynamic_initializer_for_'PowerPlant::powerPlantList''
 * Namespace: `dynamic_initializer_for_'PowerPlant
 * Signature: void powerPlantList''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl `dynamic_initializer_for_'PowerPlant::powerPlantList__(void)

{
  std::vector<PowerPlant_*,std::allocator<PowerPlant_*>_>::
  vector<PowerPlant_*,std::allocator<PowerPlant_*>_>(&PowerPlant::powerPlantList);
  atexit(`dynamic_atexit_destructor_for_'PowerPlant::powerPlantList__);
  return;
}
