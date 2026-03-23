
undefined4 * FUN_006b27e0(int param_1)

{
  undefined4 *puVar1;
  undefined4 *extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 extraout_ECX_02;
  undefined4 extraout_ECX_03;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined1 local_c [4];
  undefined4 *local_8;
  
  puVar1 = (undefined4 *)FUN_006c95c0(local_c,param_1);
  FUN_006c98a0(*puVar1);
  puVar1 = extraout_ECX;
  if (param_1 == 3) {
    puVar1 = extraout_ECX;
    FUN_006b2520(1);
    uVar3 = extraout_ECX_00;
    FUN_006b26a0(1);
    uVar2 = extraout_ECX_01;
    FUN_006b25f0(0x578);
    puVar1 = (undefined4 *)FUN_006b26e0(uVar2,uVar3,puVar1);
    *local_8 = *puVar1;
    puVar1 = local_8;
  }
  if (param_1 == 4) {
    FUN_006b2520(0x1f);
    uVar3 = extraout_ECX_02;
    FUN_006b26a0(0xc);
    uVar2 = extraout_ECX_03;
    FUN_006b25f0(9999);
    puVar1 = (undefined4 *)FUN_006b26e0(uVar2,uVar3,puVar1);
    *local_8 = *puVar1;
  }
  return local_8;
}

