/*
 * Entry: 00461466
 * Name: GetRidOfSomeScrap
 * Namespace: Global
 * Signature: void GetRidOfSomeScrap(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl GetRidOfSomeScrap(int param_1)

{
  Scrap **ppSVar1;
  
  while ((uint)param_1 < (uint)((int)Scrap::scrapList._Mylast - (int)Scrap::scrapList._Myfirst >> 2)
        ) {
    ppSVar1 = std::vector<Scrap_*,std::allocator<Scrap_*>_>::front(&Scrap::scrapList);
    (**(code **)((*ppSVar1)->_padding_ + 0x10))();
  }
  return;
}
