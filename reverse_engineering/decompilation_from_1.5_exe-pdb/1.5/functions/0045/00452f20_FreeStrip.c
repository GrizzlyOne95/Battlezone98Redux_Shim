/*
 * Entry: 00452f20
 * Name: FreeStrip
 * Namespace: Global
 * Signature: void FreeStrip(Strip * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl FreeStrip(Strip *param_1)

{
  vector<Strip_*,std::allocator<Strip_*>_> *this;
  
  this = freeStrips;
  param_1->seqNo = 0;
  std::vector<Strip_*,std::allocator<Strip_*>_>::push_back(this,&param_1);
  return;
}
