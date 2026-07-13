/*
 * Entry: 004cff24
 * Name: TimeAdjItem::Inc
 * Namespace: TimeAdjItem
 * Signature: void Inc(TimeAdjItem * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TimeAdjItem::Inc(TimeAdjItem *this)

{
  int iVar1;
  
  iVar1 = Net_IsNetGame();
  if (iVar1 == 0) {
    TICKS2SEC = TICKS2SEC + 0.0001;
  }
  return;
}
