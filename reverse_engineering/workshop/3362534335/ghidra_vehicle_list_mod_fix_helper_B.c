
void FUN_1000d340(void)

{
  int iVar1;
  code *pcVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  undefined1 auStack_5c [16];
  undefined4 uStack_4c;
  undefined1 auStack_44 [24];
  uint uStack_2c;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  uVar3 = DAT_1002af20;
  pcVar2 = DAT_1002add8;
  local_8 = 0xffffffff;
  puStack_c = &LAB_10021a45;
  local_10 = ExceptionList;
  uStack_2c = DAT_1002a040 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  DAT_1002ac30 = *(int *)(*DAT_1002ad84 + 0x1c8);
  if (-1 < *(int *)(DAT_1002ac30 + 0x38)) {
    iVar1 = *(int *)(DAT_1002ac30 + 0x18);
    puVar4 = *(undefined4 **)
              (*(int *)(iVar1 + 4) +
              (*(int *)(iVar1 + 8) - 1U & *(int *)(iVar1 + 0xc) + *(int *)(DAT_1002ac30 + 0x38)) * 4
              );
    if (puVar4 != (undefined4 *)0x0) {
      uStack_4c = 0x1000d3bd;
      FUN_10018a00(auStack_44,puVar4);
      local_8 = 0;
      puVar4 = puVar4 + 0xf;
      goto LAB_1000d3ff;
    }
  }
  uStack_4c = 0x1000d3ee;
  FUN_10018a00(auStack_44,&DAT_1002a21c);
  local_8 = 1;
  puVar4 = &DAT_1002a204;
LAB_1000d3ff:
  FUN_10018a00(auStack_5c,puVar4);
  local_8 = 0xffffffff;
  (*pcVar2)();
  (*DAT_1002ade4)(uVar3);
  (*DAT_1002addc)();
  ExceptionList = local_10;
  return;
}

