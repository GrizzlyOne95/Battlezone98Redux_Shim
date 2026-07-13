/*
 * Entry: 00556753
 * Name: VehicleList::SetValidVehicles
 * Namespace: VehicleList
 * Signature: void SetValidVehicles(VehicleList * this, char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: _alloca_probe_16 replaced with injection: alloca_probe */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Unable to track spacebase fully for stack */

void __thiscall VehicleList::SetValidVehicles(VehicleList *this,char *param_1)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  long lVar4;
  void *pvVar5;
  undefined1 *puVar6;
  undefined4 uStack_30;
  undefined4 auStack_2c [2];
  long alStack_24 [2];
  size_t sStack_1c;
  
  pcVar3 = param_1;
  do {
    cVar1 = *pcVar3;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  sStack_1c = 0x55677e;
  iVar2 = -(int)(pcVar3 + (5 - (int)(param_1 + 1)));
  *(char **)((int)&sStack_1c + iVar2) = param_1;
  *(char **)((int)alStack_24 + iVar2 + 4) = "%s.vxt";
  *(undefined1 **)((int)alStack_24 + iVar2) = &stack0xffffffe8 + iVar2;
  *(undefined4 *)((int)auStack_2c + iVar2 + 4) = 0x55678f;
  sprintf(*(char **)((int)alStack_24 + iVar2),*(char **)((int)alStack_24 + iVar2 + 4));
  *(char **)((int)auStack_2c + iVar2 + 4) = this->validVehicles;
  *(undefined4 *)((int)auStack_2c + iVar2) = 0x556798;
  free(*(void **)((int)auStack_2c + iVar2 + 4));
  this->validVehicles = (char *)0x0;
  *(undefined1 **)((int)auStack_2c + iVar2) = &stack0xffffffe8 + iVar2;
  *(undefined4 *)((int)&uStack_30 + iVar2) = 0x5567a2;
  lVar4 = GetItemSize(*(char **)((int)auStack_2c + iVar2));
  puVar6 = &stack0xffffffe8 + iVar2;
  if (0 < lVar4) {
    *(undefined1 **)((int)&sStack_1c + iVar2) = &stack0xffffffe8 + iVar2;
    *(undefined4 *)((int)alStack_24 + iVar2 + 4) = 0x5567b1;
    pvVar5 = UseItem(*(char **)((int)&sStack_1c + iVar2));
    puVar6 = &stack0xffffffe8 + iVar2;
    if (pvVar5 != (void *)0x0) {
      *(long *)((int)&sStack_1c + iVar2) = lVar4 + 1;
      *(undefined4 *)((int)alStack_24 + iVar2 + 4) = 0x5567c3;
      pcVar3 = malloc(*(size_t *)((int)&sStack_1c + iVar2));
      *(long *)((int)alStack_24 + iVar2 + 4) = lVar4;
      *(void **)((int)alStack_24 + iVar2) = pvVar5;
      this->validVehicles = pcVar3;
      *(char **)((int)auStack_2c + iVar2 + 4) = pcVar3;
      *(undefined4 *)((int)auStack_2c + iVar2) = 0x5567d0;
      memcpy();
      pcVar3 = this->validVehicles;
      *(undefined1 **)((int)auStack_2c + iVar2) = &stack0xffffffe8 + iVar2;
      pcVar3[lVar4] = '\0';
      *(undefined4 *)((int)&uStack_30 + iVar2) = 0x5567dd;
      UnlockItem(*(char **)((int)auStack_2c + iVar2));
      puVar6 = &stack0xffffffe8 + iVar2;
    }
  }
  validVehicles = this->validVehicles;
  *(undefined4 *)(puVar6 + -4) = 0x5567ef;
  MoveForward(this);
  *(undefined4 *)(puVar6 + -4) = 0x5567f6;
  SetCurrentSelection(this);
  return;
}
