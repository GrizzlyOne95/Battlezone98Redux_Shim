
undefined1 __thiscall FUN_005b1270(int param_1,undefined4 param_2)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  bool bVar5;
  undefined1 local_18;
  
  bVar5 = true;
  if ((DAT_00917b20 < 0x40e) || (DAT_009173b7 != '\0')) {
    iVar2 = FUN_00572a70();
    if (iVar2 == 0) {
      iVar2 = *(int *)(param_1 + 0xf8);
      iVar4 = rand();
      *(float *)(param_1 + 0x240) = ((float)iVar4 * *(float *)(iVar2 + 0x16c)) / 32767.0;
    }
    else {
      iVar2 = *(int *)(param_1 + 0xf8);
      uVar3 = FUN_004b9a90();
      *(float *)(param_1 + 0x240) =
           (((float)(uVar3 & 0xf) + 0.0) * *(float *)(iVar2 + 0x16c)) / 15.0;
    }
  }
  else {
    cVar1 = FUN_004ceb10(param_2,param_1 + 0x240,4);
    bVar5 = cVar1 != '\0';
  }
  if ((bVar5) && (cVar1 = FUN_00511550(param_2), cVar1 != '\0')) {
    local_18 = 1;
  }
  else {
    local_18 = 0;
  }
  return local_18;
}

