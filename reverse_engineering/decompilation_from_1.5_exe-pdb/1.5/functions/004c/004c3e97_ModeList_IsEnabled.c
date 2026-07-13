/*
 * Entry: 004c3e97
 * Name: ModeList::IsEnabled
 * Namespace: ModeList
 * Signature: bool IsEnabled(ModeList * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall ModeList::IsEnabled(ModeList *this,int param_1)

{
  return (1 << ((byte)param_1 & 0x1f) & this->enabledMask) != 0;
}
