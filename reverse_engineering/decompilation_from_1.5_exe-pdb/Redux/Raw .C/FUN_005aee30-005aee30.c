
void __thiscall FUN_005aee30(int *param_1,float param_2)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  float10 fVar3;
  undefined1 local_58 [64];
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  param_1[0xc1] = (int)((float)param_1[0xc1] - param_2);
  if (0.0 < (float)param_1[0xc1] || (float)param_1[0xc1] == 0.0) {
    uVar1 = FUN_00472370(param_1[0xc0]);
    FUN_004723b0(uVar1);
    (**(code **)(*param_1 + 0xac))(local_58);
    puVar2 = (undefined4 *)FUN_0049c590();
    local_18 = *puVar2;
    local_14 = puVar2[1];
    local_10 = puVar2[2];
    local_c = puVar2[3];
    FUN_00820180(&local_18,&local_18,1,local_58);
    fVar3 = (float10)FUN_00456080((float)param_1[0xc1] / *(float *)(param_1[0xc0] + 0x54),0x3f800000
                                 );
    FUN_0049c0a0(&local_18,(float)fVar3);
  }
  else {
    (**(code **)(*param_1 + 0xa8))();
  }
  FUN_0083e885();
  return;
}

