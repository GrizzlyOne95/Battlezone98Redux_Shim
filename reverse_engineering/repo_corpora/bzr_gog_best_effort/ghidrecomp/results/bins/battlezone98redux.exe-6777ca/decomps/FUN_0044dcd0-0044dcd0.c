
undefined4 * __thiscall
FUN_0044dcd0(undefined4 *param_1,int param_2,undefined4 param_3,undefined4 *param_4)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *local_10;
  
  *param_1 = ParticleRender::vftable;
  FUN_0044ea00();
  param_1[6] = param_2;
  *(bool *)(param_1 + 7) = param_4 != (undefined4 *)0x0;
  if (param_4 == (undefined4 *)0x0) {
    local_10 = &DAT_008fe1e0;
  }
  else {
    local_10 = param_4;
  }
  puVar2 = param_1 + 8;
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = *local_10;
    local_10 = local_10 + 1;
    puVar2 = puVar2 + 1;
  }
  param_1[0x1a] = param_3;
  if (param_1[0x1a] != 0) {
    *(undefined4 **)param_1[0x1a] = param_1;
  }
  FUN_0044e420(param_1);
  param_1[0x18] = *(undefined4 *)(param_2 + 0xfc);
  param_1[0x19] = 0x742678f;
  return param_1;
}

