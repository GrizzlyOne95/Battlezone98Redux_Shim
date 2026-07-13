/*
 * Entry: 00508bc5
 * Name: AI_Parts_SubtractPartFromSquad
 * Namespace: Global
 * Signature: void AI_Parts_SubtractPartFromSquad(tagUNIT * param_1, tag_team * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AI_Parts_SubtractPartFromSquad(tagUNIT *param_1,tag_team *param_2)

{
  tag_squad *ptVar1;
  
  Debug_Assert((int)param_1,0xfa,".\\Schedule\\Ai_parts.cpp","subtract_unit");
  ptVar1 = (param_1->ai).the_squad;
  if (ptVar1 != (tag_squad *)0x0) {
    Squad_Remove_Unit(ptVar1,param_1,param_2);
  }
  return;
}
