/*
 * Entry: 00453200
 * Name: MakeLinkNode
 * Namespace: Global
 * Signature: Strip * MakeLinkNode(float param_1, float param_2, Strip * param_3, Strip * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Strip * __cdecl MakeLinkNode(float param_1,float param_2,Strip *param_3,Strip *param_4)

{
  vector<Strip_*,std::allocator<Strip_*>_> *this;
  Strip *this_00;
  Strip *unaff_EDI;
  Strip *local_4;
  
  this_00 = AllocStrip(false);
  local_4 = this_00;
  Strip::operator=(this_00,unaff_EDI);
  this_00->visited = false;
  this_00->x = param_1;
  this_00->z = param_2;
  this_00->link = true;
  this_00->seqNo = -1;
  this_00->next = unaff_EDI;
  this = usedStrips;
  this_00->backward = unaff_EDI->backward;
  std::vector<Strip_*,std::allocator<Strip_*>_>::push_back(this,&local_4);
  return this_00;
}
