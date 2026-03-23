
void FUN_00825ac0(int param_1,int *param_2)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  char *local_88;
  int local_84;
  int *local_80;
  int *local_7c;
  int local_78;
  int *local_74;
  int local_70;
  char local_6c [8];
  int local_64 [12];
  undefined4 local_34;
  undefined4 local_30;
  int local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_7c = param_2;
  local_74 = (int *)(param_1 + 8);
  local_70 = 0;
  local_80 = (int *)0x0;
  local_78 = *(int *)(*param_2 + 0x88);
  local_84 = *local_74;
  if (local_84 == 0x26) {
    iVar1 = FUN_0068a110();
    if (iVar1 == 1) {
      *(undefined4 *)(local_78 + 0x10c) = 0;
      goto LAB_00825cc0;
    }
    memset(local_6c,0,100);
    strncpy(local_6c,"hdlt_msk",8);
    piVar3 = local_64;
    piVar2 = local_74;
    for (iVar1 = 0xc; piVar2 = piVar2 + 1, iVar1 != 0; iVar1 = iVar1 + -1) {
      *piVar3 = *piVar2;
      piVar3 = piVar3 + 1;
    }
    local_10 = *local_74;
    local_34 = 0x6c6c756e;
    local_30 = 0;
    local_c = 0;
    local_88 = local_6c;
    local_70 = FUN_00824c90(&local_88,0,1,1,1,0);
    if (local_70 == 0) goto LAB_00825cc0;
    FUN_0062cf50(*local_7c,"vhclload");
    *(int *)(local_78 + 0x10c) = local_70;
    *(int *)(local_70 + 0x78) = *local_7c;
    FUN_0077d460(local_70);
    local_80 = (int *)(local_78 + 0x10c);
    FUN_004e3290(local_70,"hdlv_msk.geo",0,4);
  }
  else if (local_84 == 0x28) {
    local_80 = (int *)(local_78 + 0xfc);
  }
  else if (local_84 == 0x2a) {
    *(undefined4 *)(local_78 + 0xf0) = *(undefined4 *)(param_1 + 0x30);
    *(undefined4 *)(local_78 + 0xf4) = *(undefined4 *)(param_1 + 0x34);
    *(undefined4 *)(local_78 + 0xf8) = *(undefined4 *)(param_1 + 0x38);
    goto LAB_00825cc0;
  }
  if (local_70 == 0) {
    local_70 = FUN_00826b40(*local_7c,0);
    if (local_70 == 0) goto LAB_00825cc0;
    FUN_0062b940(local_70,*local_74);
    FUN_00824a30(local_70 + 0x20,local_74 + 1);
  }
  if (local_80 != (int *)0x0) {
    *local_80 = local_70;
  }
LAB_00825cc0:
  FUN_0083e885();
  return;
}

