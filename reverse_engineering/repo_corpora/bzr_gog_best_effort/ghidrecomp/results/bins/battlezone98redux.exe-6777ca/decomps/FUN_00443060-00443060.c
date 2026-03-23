
void FUN_00443060(int *param_1,int *param_2)

{
  int iVar1;
  undefined4 *puVar2;
  float10 fVar3;
  undefined1 local_178 [24];
  undefined1 local_160 [24];
  undefined1 local_148 [4];
  float local_144;
  undefined4 local_140;
  int local_13c;
  float local_138;
  undefined4 local_134;
  int local_130;
  undefined4 local_e4;
  undefined4 local_bc;
  int local_b8;
  undefined4 local_6c;
  undefined1 local_44 [12];
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_140 = 0;
  iVar1 = FUN_00442f40(param_1,param_2);
  if (iVar1 != 0) {
    fVar3 = (float10)FUN_00822d60();
    local_138 = (float)fVar3;
    local_144 = (float)param_1[5] + (float)param_2[5];
    puVar2 = (undefined4 *)FUN_00444b00(local_178,param_1);
    local_20 = *puVar2;
    local_1c = puVar2[1];
    local_18 = puVar2[2];
    local_14 = puVar2[3];
    local_10 = puVar2[4];
    local_c = puVar2[5];
    puVar2 = (undefined4 *)FUN_00444b00(local_160,param_2);
    local_38 = *puVar2;
    local_34 = puVar2[1];
    local_30 = puVar2[2];
    local_2c = puVar2[3];
    local_28 = puVar2[4];
    local_24 = puVar2[5];
    local_13c = 0;
    iVar1 = FUN_00443370(local_20,local_1c,local_18,local_14,local_10,local_c,local_38,local_34,
                         local_30,local_2c,local_28,local_24,local_144,local_138,local_148,local_44)
    ;
    if (iVar1 != 0) {
      local_140 = 1;
      local_bc = 0;
      local_134 = 0;
      local_6c = 0x7f7fffff;
      local_e4 = 0x7f7fffff;
      if (param_1[9] == 1) {
        local_13c = FUN_004405e0(param_1,param_2,local_138,&local_134,&local_bc);
      }
      else if (param_2[9] == 1) {
        local_13c = FUN_004405e0(param_2,param_1,local_138,&local_bc,&local_134);
      }
      else if (*(int *)(*param_1 + 0x84) == 6) {
        local_13c = FUN_004405e0(param_1,param_2,local_138,&local_134,&local_bc);
      }
      else if (*(int *)(*param_2 + 0x84) == 6) {
        local_13c = FUN_004405e0(param_2,param_1,local_138,&local_bc,&local_134);
      }
    }
    if (local_13c != 0) {
      local_b8 = *param_1;
      local_130 = *param_2;
      iVar1 = FUN_0062c000(local_b8,local_130,&local_134,&local_bc);
      if (iVar1 != 0) {
        FUN_004436c0(&local_134,&local_bc);
      }
    }
  }
  FUN_0083e885();
  return;
}

