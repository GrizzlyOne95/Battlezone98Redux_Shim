
undefined4 * FUN_006951d0(int param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  void *pvVar2;
  undefined4 uVar3;
  undefined4 local_10;
  
  puVar1 = malloc(0x59c);
  *puVar1 = param_2;
  puVar1[1] = param_3;
  FUN_0069d210(puVar1 + 2);
  FUN_0069d210(puVar1 + 7);
  FUN_006a8760(puVar1 + 7,"Schedule\\ai_team.cpp",0x15c);
  FUN_0069d210(puVar1 + 0xc);
  puVar1[0x11] = 1000;
  puVar1[0x2c] = 0;
  puVar1[0x18] = 0;
  FUN_00692fe0(puVar1);
  FUN_00694a50(puVar1);
  FUN_00694cf0(puVar1,*(undefined4 *)(param_1 + 0x84),*(undefined4 *)(param_1 + 0x80));
  pvVar2 = operator_new(0xa0);
  if (pvVar2 == (void *)0x0) {
    local_10 = 0;
  }
  else {
    local_10 = FUN_006a7d90(param_1,puVar1);
  }
  puVar1[0x29] = local_10;
  puVar1[0x2a] = 0;
  FUN_00694fc0(puVar1,*(undefined4 *)(param_1 + 0x84),*(undefined4 *)(param_1 + 0x80));
  uVar3 = FUN_0069ee70(0,*(int *)(param_1 + 0x80) + -1,0,*(int *)(param_1 + 0x84) + -1);
  puVar1[0x166] = uVar3;
  return puVar1;
}

