
void FUN_00466790(char *param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined8 local_5c;
  int *local_54;
  int local_50;
  int local_4c;
  undefined4 local_48 [16];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_5c = 0;
  strncpy((char *)&local_5c,param_1,8);
  local_50 = FUN_004e0f70((undefined4)local_5c,local_5c._4_4_);
  if (local_50 != 0) {
    puVar3 = &DAT_008fe1e0;
    puVar4 = local_48;
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar4 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar4 = puVar4 + 1;
    }
    FUN_00462160(local_48,param_3);
    local_4c = FUN_004e1190(local_48,param_2,0,0xffffffff,0);
    if (local_4c != 0) {
      if (*(int *)(local_50 + 0x1c) == 3) {
        *(uint *)(*(int *)(local_4c + 0x228) + 0x114) =
             *(uint *)(*(int *)(local_4c + 0x228) + 0x114) | 0xc;
      }
      cVar1 = FUN_00571c30();
      if (cVar1 != '\0') {
        FUN_004b8460();
      }
      local_54 = (int *)FUN_0045ca50();
      (**(code **)(*local_54 + 0x1c))(local_4c);
    }
  }
  FUN_0083e885();
  return;
}

