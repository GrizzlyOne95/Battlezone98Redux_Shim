/*
 * Entry: 00507f5b
 * Name: AI_SquadMove
 * Namespace: Global
 * Signature: void AI_SquadMove(tagUNIT * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AI_SquadMove(tagUNIT *param_1)

{
  tag_squad *ptVar1;
  int iVar2;
  tag_squad *unaff_EDI;
  
  Debug_Assert((int)param_1,0x793,".\\Schedule\\Ai.cpp","u");
  ptVar1 = (param_1->ai).the_squad;
  if (ptVar1 != (tag_squad *)0x0) {
    (param_1->ai).transit_processed = 1;
    iVar2 = (param_1->ai).transit_time;
    if (ptVar1->max_transit_time < iVar2) {
      ptVar1->max_transit_time = iVar2;
    }
    ptVar1->units_calculated = ptVar1->units_calculated + 1;
    if (ptVar1->units_calculated == (ptVar1->my_units).count) {
      AI_SquadCalculateWaits(unaff_EDI);
    }
  }
  return;
}
