/*
 * Entry: 00557ab8
 * Name: MapList::Update
 * Namespace: MapList
 * Signature: void Update(MapList * this, char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Function: _alloca_probe_16 replaced with injection: alloca_probe */
/* WARNING: Unable to track spacebase fully for stack */

void __thiscall MapList::Update(MapList *this,char *param_1)

{
  char cVar1;
  TextLabel *this_00;
  int iVar2;
  void *pvVar3;
  TextWindow *this_01;
  undefined4 uStack_28;
  char *pcVar4;
  
  if (this->vehicleList != (VehicleList *)0x0) {
    VehicleList::SetValidVehicles(this->vehicleList,param_1);
  }
  this_01 = this->mapDesc;
  if (this_01 == (TextWindow *)0x0) goto LAB_00557b49;
  if (*param_1 == '\0') {
    pcVar4 = "";
LAB_00557b39:
    TextWindow::SetWindowTextA(this_01,pcVar4);
  }
  else {
    pcVar4 = param_1;
    do {
      cVar1 = *pcVar4;
      pcVar4 = pcVar4 + 1;
    } while (cVar1 != '\0');
    iVar2 = -(int)(pcVar4 + (5 - (int)(param_1 + 1)));
    pcVar4 = &stack0xffffffec + iVar2;
    *(char **)(&stack0xffffffe8 + iVar2) = param_1;
    *(char **)(&stack0xffffffe4 + iVar2) = "%s.des";
    *(undefined1 **)(&stack0xffffffe0 + iVar2) = &stack0xffffffec + iVar2;
    *(undefined4 *)(&stack0xffffffdc + iVar2) = 0x557b19;
    sprintf(*(char **)(&stack0xffffffe0 + iVar2),*(char **)(&stack0xffffffe4 + iVar2));
    *(undefined1 **)(&stack0xffffffdc + iVar2) = &stack0xffffffec + iVar2;
    *(undefined4 *)((int)&uStack_28 + iVar2) = 0x557b1f;
    pvVar3 = UseItem(*(char **)(&stack0xffffffdc + iVar2));
    this_01 = this->mapDesc;
    if (pvVar3 == (void *)0x0) goto LAB_00557b39;
    *(void **)(&stack0xffffffe8 + iVar2) = pvVar3;
    *(undefined4 *)(&stack0xffffffe4 + iVar2) = 0x557b2f;
    TextWindow::SetWindowTextA(this_01,*(char **)(&stack0xffffffe8 + iVar2));
    *(undefined1 **)(&stack0xffffffe8 + iVar2) = &stack0xffffffec + iVar2;
    *(undefined4 *)(&stack0xffffffe4 + iVar2) = 0x557b35;
    UnlockItem(*(char **)(&stack0xffffffe8 + iVar2));
  }
  (**(code **)(this->mapDesc->_padding_ + 4))();
LAB_00557b49:
  if ((this->rect).left != 0) {
    GetSessionDescCRC(Net::dp);
    uStack_28 = 0x557b68;
    sprintf((char *)((this->rect).left + 4),"Mission CRC: %08x");
    this_00 = (TextLabel *)(this->rect).left;
    if (this_00->nTextVisible != 0) {
      TextLabel::DrawLabelText(this_00,(char *)0x0,0);
    }
  }
  SetBitmap(this,param_1);
  StartAnim(this);
  return;
}
