
void FUN_00773d80(undefined4 param_1,char param_2)

{
  int *piVar1;
  uint uVar2;
  uint *puVar3;
  longlong *plVar4;
  undefined8 uVar5;
  longlong lVar6;
  undefined4 uVar7;
  uint uStack_64;
  undefined4 local_1c;
  undefined1 local_15;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0085e260;
  local_10 = ExceptionList;
  uStack_64 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_14 = (undefined1 *)&uStack_64;
  ExceptionList = &local_10;
  local_8 = 0;
  local_1c = FUN_007739d0(param_1,0,10);
  piVar1 = (int *)FUN_00773a50();
  uVar7 = 0;
  uVar2 = (**(code **)(*piVar1 + 0xe8))(local_1c,0);
  local_15 = (uVar2 & 0x28) == 0;
  if (((uVar2 & 0x10) == 0) && (param_2 != '\0')) {
    puVar3 = (uint *)FUN_00774340(&local_1c);
    uVar5 = FUN_00822ea0();
    uVar2 = (uint)((ulonglong)uVar5 >> 0x20);
    if ((puVar3[1] <= uVar2) && ((puVar3[1] < uVar2 || (*puVar3 < (uint)uVar5)))) {
      piVar1 = (int *)FUN_00773a50();
      (**(code **)(*piVar1 + 0xf4))(local_1c,0,1);
      plVar4 = (longlong *)FUN_00774340(&local_1c);
      lVar6 = FUN_00822ea0();
      *plVar4 = lVar6 + 300000;
    }
  }
  FUN_00773ee2(uVar7);
  return;
}

