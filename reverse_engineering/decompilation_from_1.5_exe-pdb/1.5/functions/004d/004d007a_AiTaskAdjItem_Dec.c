/*
 * Entry: 004d007a
 * Name: AiTaskAdjItem::Dec
 * Namespace: AiTaskAdjItem
 * Signature: void Dec(AiTaskAdjItem * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall AiTaskAdjItem::Dec(AiTaskAdjItem *this)

{
  int iVar1;
  float *pfVar2;
  float fVar3;
  
  iVar1 = this->var;
  pfVar2 = aiTaskItems[iVar1].current;
  fVar3 = Clamp(*pfVar2 - aiTaskItems[iVar1].delta,aiTaskItems[iVar1].min,aiTaskItems[iVar1].max);
  *pfVar2 = fVar3;
  return;
}
