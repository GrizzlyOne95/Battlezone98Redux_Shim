
void FUN_006b1c80(undefined4 *param_1,uint param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,int param_6)

{
  undefined4 uVar1;
  char cVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined1 local_54 [8];
  undefined1 local_4c [8];
  undefined1 local_44 [8];
  int local_3c;
  undefined4 local_38;
  int local_34;
  undefined4 local_30;
  code *local_2c;
  uint local_24 [8];
  
  local_24[7] = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if (((param_2 == 2) || (param_2 == 0x17)) &&
     (local_2c = (code *)FUN_006b1ff0(param_1,param_3), local_2c != (code *)0x0)) {
    local_24[1] = 0;
    local_24[2] = 0;
    local_24[3] = 0;
    local_24[4] = 0;
    local_24[5] = 0;
    local_24[6] = 0;
    local_24[0] = param_2 & 0xffff;
    if (param_2 == 2) {
      local_38 = 0x10;
    }
    else {
      local_38 = 0x1c;
    }
    FUN_006ae950(*param_1,local_24,local_38,param_6 + 0x20);
    iVar3 = FUN_00667170();
    if (iVar3 != 0) {
      FUN_006d8cc0(0x2726,0);
      cVar2 = operator!=<>(param_6 + 0x20,local_4c);
      if (cVar2 != '\0') {
        FUN_006acd90(param_6,0);
        goto LAB_006b1ee7;
      }
    }
    *(undefined1 *)(param_6 + 0x34) = 1;
    FUN_004178a0(param_1);
    FUN_006acd10();
    local_3c = (*local_2c)(*param_1,param_4,param_5,0,0,0,param_6);
    local_34 = WSAGetLastError();
    if ((local_3c == 0) && (local_34 != 0x3e5)) {
      FUN_006ad8c0(param_6,local_34,0);
    }
    else {
      FUN_006ad810(param_6);
    }
    goto LAB_006b1ee7;
  }
  local_30 = FUN_006b1fa0();
  FUN_004178a0(param_1);
  if ((((*(byte *)(param_1 + 1) & 3) == 0) &&
      (cVar2 = FUN_006aeb00(*param_1,param_1 + 1,1,param_6 + 0x20), cVar2 == '\0')) ||
     (iVar3 = FUN_006aec50(*param_1,param_4,param_5,param_6 + 0x20), iVar3 == 0)) {
LAB_006b1ed9:
    FUN_006b0660(param_6,0);
  }
  else {
    FUN_006d8cc0(0x2734,0);
    cVar2 = FUN_006ab920(param_6 + 0x20,local_54);
    if (cVar2 == '\0') {
      FUN_006d8cc0(0x2733,0);
      cVar2 = FUN_006ab920(param_6 + 0x20,local_44);
      if (cVar2 == '\0') goto LAB_006b1ed9;
    }
    puVar4 = (undefined4 *)FUN_004fbb60();
    uVar1 = puVar4[1];
    *(undefined4 *)(param_6 + 0x20) = *puVar4;
    *(undefined4 *)(param_6 + 0x24) = uVar1;
    FUN_006b0ae0(3,*param_1,param_1 + 4,param_6,0,0);
  }
LAB_006b1ee7:
  FUN_0083e885();
  return;
}

