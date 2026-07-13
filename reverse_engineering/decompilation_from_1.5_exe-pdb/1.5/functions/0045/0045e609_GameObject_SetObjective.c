/*
 * Entry: 0045e609
 * Name: GameObject::SetObjective
 * Namespace: GameObject
 * Signature: void SetObjective(GameObject * this, bool param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall GameObject::SetObjective(GameObject *this,bool param_1)

{
  long lVar1;
  int iVar2;
  
  lVar1 = objectiveCount;
  iVar2 = 0;
  if (param_1) {
    if (this->isObjective == false) {
      objectiveCount = objectiveCount + 1;
      objectiveList[lVar1] = this;
    }
  }
  else if ((this->isObjective != false) && (0 < objectiveCount)) {
    do {
      if (objectiveList[iVar2] == this) {
        objectiveCount = objectiveCount + -1;
        objectiveList[iVar2] = objectiveList[objectiveCount];
        break;
      }
      iVar2 = iVar2 + 1;
    } while (iVar2 < objectiveCount);
  }
  this->isObjective = param_1;
  return;
}
