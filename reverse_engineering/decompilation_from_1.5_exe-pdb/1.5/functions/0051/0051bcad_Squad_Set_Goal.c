/*
 * Entry: 0051bcad
 * Name: Squad_Set_Goal
 * Namespace: Global
 * Signature: void Squad_Set_Goal(tag_squad * param_1, Goal * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Squad_Set_Goal(tag_squad *param_1,Goal *param_2)

{
  tag_squad *ptVar1;
  
  if ((param_1 != (tag_squad *)0x0) && (param_2 != (Goal *)0x0)) {
    if ((param_1->my_strategic_goal != (Goal *)0x0) &&
       (ptVar1 = param_1->my_strategic_goal->attacking_squad, ptVar1 == param_1)) {
      ptVar1->my_strategic_goal = (Goal *)0x0;
      param_1->my_strategic_goal->attacking_squad = (tag_squad *)0x0;
    }
    param_1->my_strategic_goal = param_2;
    param_2->attacking_squad = param_1;
  }
  return;
}
