/*
 * Entry: 00517837
 * Name: Units_IdToUnitPtr
 * Namespace: Global
 * Signature: tagUNIT * Units_IdToUnitPtr(int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

tagUNIT * __cdecl Units_IdToUnitPtr(int param_1,int param_2)

{
  Attachment **ppAVar1;
  
  ppAVar1 = std::vector<Attachment_*,std::allocator<Attachment_*>_>::operator[]
                      ((vector<Attachment_*,std::allocator<Attachment_*>_> *)(param_1 + 4),
                       attachIndex);
  return (tagUNIT *)(*ppAVar1 + 1);
}
