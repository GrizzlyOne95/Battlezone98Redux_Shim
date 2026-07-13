/*
 * Entry: 00552308
 * Name: MapList::StopAnim
 * Namespace: MapList
 * Signature: ulong StopAnim(MapList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ulong __thiscall MapList::StopAnim(MapList *this)

{
  ulong uVar1;
  undefined4 local_8;
  
  local_8 = 0;
  uVar1 = 0;
  if (this->vehNameLabel != (TextLabel *)0x0) {
    uVar1 = mciSendCommandA((MCIDEVICEID)(this->mop).lpstrDeviceType,0x804,2,(DWORD_PTR)&local_8);
    if (uVar1 == 0) {
      this->vehNameLabel = (TextLabel *)0x0;
    }
  }
  return uVar1;
}
