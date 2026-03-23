
void __thiscall FUN_005d9990(int *param_1,float param_2)

{
  char cVar1;
  int iVar2;
  float fVar3;
  undefined1 local_e0 [16];
  undefined4 local_d0;
  undefined1 local_b4 [16];
  undefined4 local_a4;
  undefined1 local_88 [16];
  undefined4 local_78;
  undefined1 local_5c [4];
  undefined4 local_58;
  undefined1 local_40 [4];
  undefined4 local_3c;
  undefined1 local_24 [4];
  undefined4 local_20;
  undefined4 local_18;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if ('\0' < *(char *)((int)param_1 + 0xc1)) {
    *(char *)((int)param_1 + 0xc1) = *(char *)((int)param_1 + 0xc1) + -1;
  }
  if ((char)param_1[0x30] == '\0') {
    param_1[0x31] = 0;
    param_1[0x35] = 0;
    param_1[0x2a] = param_1[0x34];
    cVar1 = (**(code **)(*param_1 + 0x34))();
    if (cVar1 != '\0') {
      if ((param_1[0x33] == 0) || (cVar1 = FUN_004b9830(), cVar1 == '\0')) {
        (**(code **)(*param_1 + 0x40))();
      }
      if ((*(char *)(param_1[2] + 0x84) != '\0') &&
         (iVar2 = FUN_0043ac70(param_1[2] + 0x84,param_1[6]), iVar2 != 0)) {
        FUN_0043aaa0(iVar2);
      }
      if (*(char *)(param_1[2] + 0x94) != '\0') {
        FUN_0043a990(local_88);
        local_78 = 0x1000;
        FUN_0043a9e0(local_5c);
        if ((*(uint *)(param_1[6] + 0x14) & 0x10) != 0) {
          local_58 = 0x41;
        }
        FUN_0043aa30(param_1[2] + 0x94,param_1[6],local_88,local_5c);
      }
    }
  }
  else {
    if ((param_1[0x35] < *(int *)(param_1[2] + 0xa4)) &&
       (param_1[0x31] = (int)((float)param_1[0x31] + param_2),
       *(float *)(param_1[2] + 0x80) <= (float)param_1[0x31])) {
      param_1[0x35] = param_1[0x35] + 1;
      param_1[0x2a] = param_1[0x34] + param_1[0x35];
      param_1[0x31] = (int)((float)param_1[0x31] - *(float *)(param_1[2] + 0x80));
      if ((param_1[0x35] == *(int *)(param_1[2] + 0xa4)) &&
         (cVar1 = (**(code **)(*param_1 + 0x34))(), cVar1 == '\0')) {
        (**(code **)(*param_1 + 0x38))();
        if (*(char *)(param_1[2] + 0x58) != '\0') {
          FUN_0043a990(local_b4);
          local_a4 = 0x1000;
          FUN_0043a9e0(local_40);
          if ((*(uint *)(param_1[6] + 0x14) & 0x10) != 0) {
            local_3c = 0x41;
          }
          FUN_0043aa30(param_1[2] + 0x58,param_1[6],local_b4,local_40);
        }
        if (*(char *)(param_1[2] + 0x84) != '\0') {
          FUN_0043a990(local_e0);
          local_d0 = 0x1001;
          FUN_0043a9e0(local_24);
          local_18 = 1;
          if ((*(uint *)(param_1[6] + 0x14) & 0x10) != 0) {
            local_20 = 0x41;
          }
          FUN_0043aa30(param_1[2] + 0x84,param_1[6],local_e0,local_24);
        }
      }
    }
    cVar1 = (**(code **)(*param_1 + 0x34))();
    if (cVar1 != '\0') {
      fVar3 = (float)*(int *)(param_1[2] + 0x34) * param_2 + (float)param_1[0x32];
      iVar2 = (int)fVar3;
      param_1[0x32] = (int)(fVar3 - (float)iVar2);
      (**(code **)(*(int *)param_1[0x33] + 0x18))(-iVar2);
      (**(code **)(*param_1 + 0x3c))(param_2);
    }
  }
  FUN_0083e885();
  return;
}

