
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_0077b000(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  void *pvVar6;
  int iVar7;
  undefined4 local_428;
  float local_424;
  int local_420;
  int local_41c;
  char local_414 [1024];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085e57f;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *(undefined1 *)(param_1 + 0x85) = 1;
  if ((*(int *)(param_1 + 0x44) == 0) && (iVar5 = FUN_00684ca0(0,local_14), iVar5 != 0)) {
    iVar5 = FUN_00822e60();
    *(undefined4 *)(param_1 + 0x5c) = 0;
    *(float *)(param_1 + 0x50) = *(float *)(param_1 + 0x50) - _DAT_025f8e4c;
    *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) - _DAT_025f8e54;
    FUN_007c9cd0(0x3e19999a);
    pvVar6 = calloc((int)*(float *)(param_1 + 0x48) * (int)*(float *)(param_1 + 0x4c),4);
    *(void **)(param_1 + 0x44) = pvVar6;
    if (*(int *)(param_1 + 0x44) != 0) {
      local_424 = 0.15;
      fVar1 = *(float *)(param_1 + 0x48);
      fVar2 = *(float *)(param_1 + 0x4c);
      for (local_41c = 0; local_41c < (int)*(float *)(param_1 + 0x48); local_41c = local_41c + 1) {
        fVar3 = *(float *)(param_1 + 0x50);
        for (local_420 = 0; local_420 < (int)*(float *)(param_1 + 0x4c); local_420 = local_420 + 1)
        {
          fVar4 = *(float *)(param_1 + 0x54);
          pvVar6 = operator_new(0x3b4);
          local_8 = 0;
          if (pvVar6 == (void *)0x0) {
            local_428 = 0;
          }
          else {
            local_428 = FUN_007778b0(local_41c,local_420,(float)local_41c * 1280.0 + fVar3,
                                     fVar4 - (float)local_420 * 1280.0,0);
          }
          local_8 = 0xffffffff;
          *(undefined4 *)
           (*(int *)(param_1 + 0x44) + ((int)*(float *)(param_1 + 0x4c) * local_41c + local_420) * 4
           ) = local_428;
          local_424 = local_424 + 0.1 / (fVar1 * fVar2);
          FUN_007c9cf0(local_424);
        }
      }
    }
    iVar7 = FUN_00822e60();
    *(int *)(param_1 + 0x58) = iVar7 - iVar5;
    _snprintf(local_414,0x400,
              "total duration %d ms\n\ttotal tangent duration %d ms\n\tvertex generation duration %d ms\n"
              ,*(undefined4 *)(param_1 + 0x58),*(undefined4 *)(param_1 + 0x5c),
              *(int *)(param_1 + 0x58) - *(int *)(param_1 + 0x5c));
    FUN_007d6a70(local_414);
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

