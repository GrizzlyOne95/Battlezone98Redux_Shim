/*
 * Entry: 004cff40
 * Name: TimeAdjItem::Dec
 * Namespace: TimeAdjItem
 * Signature: void Dec(TimeAdjItem * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TimeAdjItem::Dec(TimeAdjItem *this)

{
  int iVar1;
  
  iVar1 = Net_IsNetGame();
  if (iVar1 == 0) {
    TICKS2SEC = TICKS2SEC - 0.0001;
  }
  if (TICKS2SEC < 0.0001) {
    TICKS2SEC = 0.0001;
    return;
  }
  return;
}
