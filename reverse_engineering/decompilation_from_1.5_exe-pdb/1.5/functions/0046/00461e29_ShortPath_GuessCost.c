/*
 * Entry: 00461e29
 * Name: ShortPath::GuessCost
 * Namespace: ShortPath
 * Signature: float GuessCost(Node * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl ShortPath::GuessCost(Node *param_1)

{
  float fVar1;
  
  fVar1 = Dist(&param_1->pos,&goalNode->pos);
  return fVar1;
}
