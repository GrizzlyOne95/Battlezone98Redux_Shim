/*
 * Entry: 00556a71
 * Name: MapList::StartAnim
 * Namespace: MapList
 * Signature: void StartAnim(MapList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall MapList::StartAnim(MapList *this)

{
  byte bVar1;
  byte bVar2;
  VehicleList *this_00;
  HWND__ *pHVar3;
  char *pcVar4;
  TextLabel *pTVar5;
  int iVar6;
  ulong uVar7;
  MCIERROR MVar8;
  TextLabel *pTVar9;
  bool bVar10;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 uStack_8;
  
  local_10 = 0;
  this_00 = this->vehicleList;
  (this->mdpp).rc.left = 0;
  local_c = 0;
  uStack_8 = 0;
  pHVar3 = this->hDlg;
  (this->mop).lpstrElementName = "AVIVideo";
  (this->mop).hWndParent = (HWND__ *)0x48000000;
  (this->mdpp).dwCallback = (ulong)pHVar3;
  (this->mdwp).nCmdShow = (uint)pHVar3;
  (this->mdpp).rc.top = 0x150;
  (this->mdpp).rc.right = 0x3f;
  (this->mdpp).rc.bottom = 0x96;
  (this->mdwp).dwCallback = 0x78;
  if (this_00 == (VehicleList *)0x0) {
    pcVar4 = "";
  }
  else {
    pcVar4 = VehicleList::GetAvi(this_00);
  }
  if ((TextLabel *)pcVar4 != (TextLabel *)0x0) {
    pTVar9 = this->vehNameLabel;
    (this->mop).lpstrAlias = pcVar4;
    pTVar5 = (TextLabel *)pcVar4;
    if (pTVar9 != (TextLabel *)0x0) {
      do {
        bVar1 = *(byte *)&pTVar5->hParentHwnd;
        bVar10 = bVar1 < *(byte *)&pTVar9->hParentHwnd;
        if (bVar1 != *(byte *)&pTVar9->hParentHwnd) {
LAB_00556b05:
          iVar6 = (1 - (uint)bVar10) - (uint)(bVar10 != 0);
          goto LAB_00556b0a;
        }
        if (bVar1 == 0) break;
        bVar1 = *(byte *)((int)&pTVar5->hParentHwnd + 1);
        bVar2 = *(byte *)((int)&pTVar9->hParentHwnd + 1);
        bVar10 = bVar1 < bVar2;
        if (bVar1 != bVar2) goto LAB_00556b05;
        pTVar9 = (TextLabel *)((int)&pTVar9->hParentHwnd + 2);
        pTVar5 = (TextLabel *)((int)&pTVar5->hParentHwnd + 2);
      } while (bVar1 != 0);
      iVar6 = 0;
LAB_00556b0a:
      if (iVar6 == 0) {
        return;
      }
    }
    uVar7 = StopAnim(this);
    if ((((uVar7 == 0) &&
         (MVar8 = mciSendCommandA(0,0x803,0x132200,(DWORD_PTR)&(this->mop).wDeviceID), MVar8 == 0))
        && (MVar8 = mciSendCommandA((MCIDEVICEID)(this->mop).lpstrDeviceType,0x842,0x610000,
                                    (DWORD_PTR)&(this->mdpp).rc), MVar8 == 0)) &&
       (MVar8 = mciSendCommandA((MCIDEVICEID)(this->mop).lpstrDeviceType,0x806,0x10000,
                                (DWORD_PTR)&local_10), MVar8 == 0)) {
      this->vehNameLabel = (TextLabel *)pcVar4;
    }
  }
  return;
}
