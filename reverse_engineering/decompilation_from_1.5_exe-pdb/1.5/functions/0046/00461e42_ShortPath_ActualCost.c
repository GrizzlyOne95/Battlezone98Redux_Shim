/*
 * Entry: 00461e42
 * Name: ShortPath::ActualCost
 * Namespace: ShortPath
 * Signature: float ActualCost(Node * param_1, Node * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl ShortPath::ActualCost(Node *param_1,Node *param_2)

{
  float fVar1;
  
  fVar1 = Dist(&param_1->pos,&param_2->pos);
  return fVar1 * param_2->costFactor;
}
