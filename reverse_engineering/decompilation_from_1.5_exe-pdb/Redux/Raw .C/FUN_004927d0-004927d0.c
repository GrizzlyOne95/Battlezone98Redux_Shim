
void __thiscall FUN_004927d0(int param_1,undefined8 *param_2,float *param_3,char param_4)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  float10 fVar4;
  undefined1 local_bc [64];
  float local_7c;
  float local_78;
  float local_74;
  float local_70;
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  undefined4 local_5c;
  int local_58;
  int local_54;
  int local_50;
  int *local_4c;
  undefined4 local_48 [16];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_50 = param_1;
  if (*(int *)(param_1 + 0x8028) < 0x400) {
    local_4c = (int *)(param_1 + 0x28 + *(int *)(param_1 + 0x8028) * 0x20);
    *(int *)(param_1 + 0x8028) = *(int *)(param_1 + 0x8028) + 1;
    local_54 = FUN_0062ccc0(**(undefined4 **)(param_1 + 0x804c),"fun3d\\ChunkEffect.cpp");
    *(undefined4 *)(local_54 + 0x84) = 0x35;
    if (param_4 == '\0') {
      local_5c = 0;
    }
    else {
      local_5c = 8;
    }
    *(undefined4 *)(local_54 + 0x14) = local_5c;
    fVar4 = (float10)FUN_004464c0(*param_2,param_2[1],param_2[2]);
    local_74 = (float)fVar4;
    fVar4 = (float10)FUN_00492cb0(0x40c90fdb,local_74 * 0.15707964);
    fVar4 = (float10)FUN_004464c0((float)fVar4);
    local_78 = (float)fVar4;
    puVar1 = (undefined4 *)FUN_0081ee70(local_bc,local_78 * 1.5707964);
    puVar3 = local_48;
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar3 = *puVar1;
      puVar1 = puVar1 + 1;
      puVar3 = puVar3 + 1;
    }
    puVar1 = local_48;
    puVar3 = (undefined4 *)(local_54 + 0x20);
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar3 = *puVar1;
      puVar1 = puVar1 + 1;
      puVar3 = puVar3 + 1;
    }
    iVar2 = rand();
    local_58 = *(int *)(*(int *)(local_50 + 0x8050) + (iVar2 % *(int *)(local_50 + 0x8054)) * 4);
    FUN_004e3430(local_58,local_54);
    *(undefined4 *)(local_54 + 0xa0) = *(undefined4 *)(local_58 + 0xa0);
    *(undefined4 *)(local_54 + 0xa4) = *(undefined4 *)(local_58 + 0xa4);
    *(undefined4 *)(local_54 + 0xa8) = *(undefined4 *)(local_58 + 0xa8);
    *(undefined4 *)(local_54 + 0xac) = *(undefined4 *)(local_58 + 0xac);
    *(undefined4 *)(local_54 + 0xb0) = *(undefined4 *)(local_58 + 0xb0);
    *(undefined4 *)(local_54 + 0xb4) = *(undefined4 *)(local_58 + 0xb4);
    *(undefined4 *)(local_54 + 0xb8) = *(undefined4 *)(local_58 + 0xb8);
    *(undefined4 *)(local_54 + 0xbc) = *(undefined4 *)(local_58 + 0xbc);
    *(undefined4 *)(local_54 + 0xc0) = *(undefined4 *)(local_58 + 0xc0);
    *(undefined4 *)(local_54 + 0xc4) = *(undefined4 *)(local_58 + 0xc4);
    *local_4c = local_54;
    local_4c[1] = 0;
    fVar4 = (float10)FUN_004464c0();
    local_60 = (float)fVar4;
    local_4c[2] = (int)(local_60 * 10.0 + *param_3);
    fVar4 = (float10)FUN_004464c0();
    local_6c = (float)fVar4;
    local_4c[3] = (int)(local_6c * 10.0 + param_3[1] + 5.0);
    fVar4 = (float10)FUN_004464c0();
    local_7c = (float)fVar4;
    local_4c[4] = (int)(local_7c * 10.0 + param_3[2]);
    fVar4 = (float10)FUN_004464c0();
    local_64 = (float)fVar4;
    local_4c[5] = (int)(local_64 * 5.0);
    fVar4 = (float10)FUN_004464c0();
    local_68 = (float)fVar4;
    local_4c[6] = (int)(local_68 * 5.0);
    fVar4 = (float10)FUN_004464c0();
    local_70 = (float)fVar4;
    local_4c[7] = (int)(local_70 * 5.0);
  }
  FUN_0083e885();
  return;
}

