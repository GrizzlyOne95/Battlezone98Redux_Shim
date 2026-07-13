/*
 * Entry: 004531d0
 * Name: MakeNode
 * Namespace: Global
 * Signature: Strip * MakeNode(float param_1, float param_2, Strip * param_3, Strip * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Strip * __cdecl MakeNode(float param_1,float param_2,Strip *param_3,Strip *param_4)

{
  Strip *unaff_ESI;
  int unaff_EDI;
  
  std::vector<Strip_*,std::allocator<Strip_*>_>::push_back(usedStrips,(Strip **)&stack0xfffffffc);
  unaff_ESI->x = param_1;
  unaff_ESI->z = param_2;
  if (unaff_EDI != 0) {
    unaff_ESI->backward = *(bool *)(unaff_EDI + 0x23);
  }
  return unaff_ESI;
}
