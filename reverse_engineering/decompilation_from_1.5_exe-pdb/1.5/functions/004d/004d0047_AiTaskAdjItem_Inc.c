/*
 * Entry: 004d0047
 * Name: AiTaskAdjItem::Inc
 * Namespace: AiTaskAdjItem
 * Signature: void Inc(AiTaskAdjItem * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall AiTaskAdjItem::Inc(AiTaskAdjItem *this)

{
  int iVar1;
  float *pfVar2;
  float fVar3;
  
  iVar1 = this->var;
  pfVar2 = aiTaskItems[iVar1].current;
  fVar3 = Clamp(aiTaskItems[iVar1].delta + *pfVar2,aiTaskItems[iVar1].min,aiTaskItems[iVar1].max);
  *pfVar2 = fVar3;
  return;
}
