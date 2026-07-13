/*
 * Entry: 0051bcdd
 * Name: Squad_Detach_Goal
 * Namespace: Global
 * Signature: void Squad_Detach_Goal(tag_squad * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Squad_Detach_Goal(tag_squad *param_1)

{
  Goal *pGVar1;
  
  if (param_1 != (tag_squad *)0x0) {
    pGVar1 = param_1->my_strategic_goal;
    if ((pGVar1 != (Goal *)0x0) && (pGVar1->attacking_squad == param_1)) {
      pGVar1->attacking_squad = (tag_squad *)0x0;
    }
    param_1->my_strategic_goal = (Goal *)0x0;
    param_1->already_committed = 0;
  }
  return;
}
