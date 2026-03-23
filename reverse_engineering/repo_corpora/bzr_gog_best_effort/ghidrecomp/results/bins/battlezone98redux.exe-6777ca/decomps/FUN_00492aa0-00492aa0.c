
void __thiscall FUN_00492aa0(int param_1,int param_2,float *param_3,char param_4)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  float10 fVar4;
  undefined1 local_ac [64];
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  undefined4 local_54;
  int local_50;
  int *local_4c;
  undefined4 local_48 [16];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_50 = param_1;
  if ((*(int *)(param_2 + 100) == 0) || (0x3ff < *(int *)(param_1 + 0x8028))) {
    FUN_0062d200(param_2,"fun3d\\ChunkEffect.cpp");
  }
  else {
    local_4c = (int *)(param_1 + 0x28 + *(int *)(param_1 + 0x8028) * 0x20);
    *(int *)(param_1 + 0x8028) = *(int *)(param_1 + 0x8028) + 1;
    FUN_0062ba00(param_2);
    *(undefined4 *)(param_2 + 0x84) = 0x35;
    puVar1 = (undefined4 *)FUN_0062e070(local_ac,param_2,0);
    puVar3 = local_48;
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar3 = *puVar1;
      puVar1 = puVar1 + 1;
      puVar3 = puVar3 + 1;
    }
    puVar1 = local_48;
    puVar3 = (undefined4 *)(param_2 + 0x20);
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar3 = *puVar1;
      puVar1 = puVar1 + 1;
      puVar3 = puVar3 + 1;
    }
    if (param_4 == '\0') {
      local_54 = 0;
    }
    else {
      local_54 = 8;
    }
    *(undefined4 *)(param_2 + 0x14) = local_54;
    FUN_0062d4b0(param_2);
    FUN_0062d410(param_2,**(undefined4 **)(local_50 + 0x804c));
    *local_4c = param_2;
    local_4c[1] = 0;
    fVar4 = (float10)FUN_004464c0();
    local_6c = (float)fVar4;
    local_4c[2] = (int)(local_6c * 10.0 + *param_3);
    fVar4 = (float10)FUN_004464c0();
    local_68 = (float)fVar4;
    local_4c[3] = (int)(local_68 * 10.0 + param_3[1] + 5.0);
    fVar4 = (float10)FUN_004464c0();
    local_58 = (float)fVar4;
    local_4c[4] = (int)(local_58 * 10.0 + param_3[2]);
    fVar4 = (float10)FUN_004464c0();
    local_64 = (float)fVar4;
    local_4c[5] = (int)(local_64 * 5.0);
    fVar4 = (float10)FUN_004464c0();
    local_5c = (float)fVar4;
    local_4c[6] = (int)(local_5c * 5.0);
    fVar4 = (float10)FUN_004464c0();
    local_60 = (float)fVar4;
    local_4c[7] = (int)(local_60 * 5.0);
  }
  FUN_0083e885();
  return;
}

