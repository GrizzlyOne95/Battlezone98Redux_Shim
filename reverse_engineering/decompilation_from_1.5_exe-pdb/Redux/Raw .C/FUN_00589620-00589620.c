
undefined4 __fastcall FUN_00589620(int *param_1)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  undefined1 *puVar4;
  undefined1 *puVar5;
  undefined1 local_1c [4];
  undefined1 local_18 [4];
  int *local_14;
  undefined1 local_10 [4];
  int local_c;
  undefined1 local_8 [4];
  
  local_c = *param_1 + 0x18;
  local_14 = param_1;
  FUN_0058a2c0(local_8,&stack0x00000004);
  uVar2 = FUN_0044ef90(local_18);
  cVar1 = FUN_00420f10(uVar2);
  if (cVar1 != '\0') {
    puVar5 = &stack0x00000008;
    puVar4 = local_10;
    FUN_004305e0(puVar4,puVar5);
    FUN_0058a2c0(puVar4,puVar5);
    puVar5 = local_1c;
    FUN_004305e0(puVar5);
    uVar2 = FUN_0044ef90(puVar5);
    cVar1 = FUN_00420f10(uVar2);
    if (cVar1 != '\0') {
      iVar3 = FUN_004305e0();
      return *(undefined4 *)(iVar3 + 4);
    }
  }
  return 0;
}

