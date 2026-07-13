/*
 * Entry: 00461a88
 * Name: ShortPath::Neighbors::AssignCost
 * Namespace: ShortPath::Neighbors
 * Signature: void AssignCost(Node * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ShortPath::Neighbors::AssignCost(Node *param_1)

{
  float fVar1;
  
  fVar1 = HeightChange(curNode,param_1);
  if (3.0 <= fVar1) {
    if (fVar1 <= 20.0) {
      if (7.0 <= fVar1) {
        fVar1 = 5.0;
      }
      else {
        fVar1 = 2.0;
      }
    }
    else {
      fVar1 = 1000.0;
    }
  }
  else {
    fVar1 = 1.0;
  }
  param_1->costFactor = fVar1;
  return;
}
