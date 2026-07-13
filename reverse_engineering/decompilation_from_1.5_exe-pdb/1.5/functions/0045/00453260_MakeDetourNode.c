/*
 * Entry: 00453260
 * Name: MakeDetourNode
 * Namespace: Global
 * Signature: Strip * MakeDetourNode(float param_1, float param_2, Strip * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Strip * __cdecl MakeDetourNode(float param_1,float param_2,Strip *param_3)

{
  vector<Strip_*,std::allocator<Strip_*>_> *this;
  Strip *this_00;
  Strip *local_4;
  
  this_00 = AllocStrip(false);
  local_4 = this_00;
  Strip::operator=(this_00,param_3);
  this_00->x = param_1;
  this = usedStrips;
  this_00->z = param_2;
  this_00->detour = true;
  this_00->seqNo = -1;
  std::vector<Strip_*,std::allocator<Strip_*>_>::push_back(this,&local_4);
  return this_00;
}
