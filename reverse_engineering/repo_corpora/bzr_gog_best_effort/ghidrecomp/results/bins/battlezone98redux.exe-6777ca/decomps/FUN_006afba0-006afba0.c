
/* WARNING: Function: __alloca_probe_16 replaced with injection: alloca_probe */
/* WARNING: Unable to track spacebase fully for stack */

void FUN_006afba0(int param_1,undefined4 *param_2,undefined4 param_3,int param_4,undefined4 param_5,
                 undefined4 *param_6)

{
  int iVar1;
  char cVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  int aiStack_c4 [7];
  undefined1 local_a8 [8];
  undefined1 *local_a0;
  int local_9c;
  undefined4 local_98;
  undefined1 *local_94;
  undefined4 local_90;
  int local_8c;
  undefined2 local_88;
  undefined2 local_86;
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  aiStack_c4[6] = 0x6afbb8;
  FUN_006ae8d0();
  if ((param_1 == 2) || (param_1 == 0x17)) {
    if (param_1 == 2) {
      local_98 = 0x10;
      local_88 = 2;
      local_84 = *param_2;
    }
    else {
      local_98 = 0x1c;
      local_88 = 0x17;
      local_84 = 0;
      local_70 = param_5;
      local_80 = *param_2;
      local_7c = param_2[1];
      local_78 = param_2[2];
      local_74 = param_2[3];
    }
    local_86 = 0;
    local_9c = param_4;
    aiStack_c4[6] = 0x6afc60;
    iVar1 = param_4 * -2;
    local_a0 = local_a8 + iVar1;
    local_94 = local_a8 + iVar1;
    *(undefined4 **)(local_a8 + iVar1 + -4) = param_6;
    *(int **)(local_a8 + iVar1 + -8) = &local_9c;
    *(undefined1 **)(local_a8 + iVar1 + -0xc) = local_94;
    *(undefined4 *)((int)aiStack_c4 + iVar1 + 0xc) = 0;
    *(undefined4 *)((int)aiStack_c4 + iVar1 + 8) = local_98;
    *(undefined2 **)((int)aiStack_c4 + iVar1 + 4) = &local_88;
    puVar5 = (undefined4 *)((int)aiStack_c4 + iVar1);
    *(undefined4 *)((int)aiStack_c4 + iVar1) = 0x6afc9a;
    uVar3 = WSAAddressToStringW();
    puVar5[-1] = uVar3;
    puVar5[-2] = 0x6afca0;
    local_8c = FUN_006d8d90();
    *puVar5 = 0;
    puVar5[-1] = 0;
    puVar5[-2] = param_4;
    puVar5[-3] = param_3;
    puVar5[-4] = 0xffffffff;
    puVar5[-5] = local_94;
    puVar5[-6] = 0;
    puVar5[-7] = 0;
    puVar6 = puVar5 + -8;
    puVar5[-8] = 0x6afcc8;
    WideCharToMultiByte(puVar5[-7],puVar5[-6],(LPCWSTR)puVar5[-5],puVar5[-4],(LPSTR)puVar5[-3],
                        puVar5[-2],(LPCSTR)puVar5[-1],(LPBOOL)*puVar5);
    if (local_8c == -1) {
      *(undefined4 *)((int)puVar6 + -4) = 0x6afcfc;
      cVar2 = FUN_004c85a0();
      if (cVar2 != '\0') {
        *(undefined4 *)((int)puVar6 + -4) = 0x2726;
        *(undefined4 *)((int)puVar6 + -8) = 0x6afd10;
        FUN_006d8cf0();
      }
    }
    else {
      *(undefined4 *)((int)puVar6 + -4) = 0x6afcdc;
      puVar4 = (undefined4 *)FUN_004fbb60();
      uVar3 = puVar4[1];
      *param_6 = *puVar4;
      param_6[1] = uVar3;
    }
    if (local_8c == -1) {
      local_90 = 0;
    }
    else {
      local_90 = param_3;
    }
  }
  else {
    aiStack_c4[6] = 0x273f;
    aiStack_c4[5] = 0x6afbd1;
    FUN_006d8cf0();
  }
  aiStack_c4[6] = 0x6afd44;
  FUN_0083e885();
  return;
}

