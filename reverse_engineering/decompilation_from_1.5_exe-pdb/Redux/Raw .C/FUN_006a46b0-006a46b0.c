
bool FUN_006a46b0(int *param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint local_14;
  uint local_c;
  
  FUN_006a2780(*(undefined4 *)(param_2 + 0x44),*(undefined4 *)(param_2 + 0x40),1,0);
  iVar3 = *param_1;
  iVar1 = (*(code *)**(undefined4 **)(iVar3 + 0x18))();
  if (*(int *)(iVar1 + 0x14) == 0x54544e4b) {
    iVar1 = (int)(param_1[5] + (param_1[5] >> 0x1f & 0xfU)) >> 4;
    iVar2 = (int)(param_1[6] + (param_1[6] >> 0x1f & 0xfU)) >> 4;
    if (*(int *)(*(int *)(*(int *)(*(int *)(*(int *)(DAT_00920f04 + (char)param_1[4] * 4) + 0x80) +
                                  iVar2 * 4) + iVar1 * 4) + 4) == 2) {
      if ((iVar1 == *(int *)(param_2 + 0x44)) && (iVar2 == *(int *)(param_2 + 0x40))) {
        return true;
      }
      return false;
    }
    local_14 = 2;
  }
  else {
    local_14 = 1;
  }
  switch(*(undefined4 *)(param_2 + 4)) {
  case 1:
    iVar1 = (*(code *)**(undefined4 **)(iVar3 + 0x18))();
    if ((*(int *)(iVar1 + 0x14) == 0x4d4c5952) ||
       (iVar3 = (*(code *)**(undefined4 **)(iVar3 + 0x18))(), *(int *)(iVar3 + 0x14) == 0x57494e47))
    {
      return true;
    }
    local_c = 2;
    break;
  case 2:
  case 4:
    iVar1 = (*(code *)**(undefined4 **)(iVar3 + 0x18))();
    if (((*(int *)(iVar1 + 0x14) == 0x54544e4b) ||
        (iVar1 = (*(code *)**(undefined4 **)(iVar3 + 0x18))(), *(int *)(iVar1 + 0x14) == 0x54555252)
        ) || (iVar3 = (*(code *)**(undefined4 **)(iVar3 + 0x18))(),
             *(int *)(iVar3 + 0x14) == 0x4857545a)) {
      return false;
    }
    local_c = 1;
    if (((local_14 == 2) &&
        ((int)(param_1[5] + (param_1[5] >> 0x1f & 0xfU)) >> 4 == *(int *)(param_2 + 0x44))) &&
       ((int)(param_1[6] + (param_1[6] >> 0x1f & 0xfU)) >> 4 == *(int *)(param_2 + 0x40))) {
      local_c = 3;
    }
    break;
  default:
    iVar1 = (*(code *)**(undefined4 **)(iVar3 + 0x18))();
    if (((*(int *)(iVar1 + 0x14) == 0x54544e4b) ||
        (iVar1 = (*(code *)**(undefined4 **)(iVar3 + 0x18))(), *(int *)(iVar1 + 0x14) == 0x54555252)
        ) || (iVar3 = (*(code *)**(undefined4 **)(iVar3 + 0x18))(),
             *(int *)(iVar3 + 0x14) == 0x4857545a)) {
      return false;
    }
    local_c = 1;
    break;
  case 5:
    iVar3 = (*(code *)**(undefined4 **)(iVar3 + 0x18))();
    if (*(int *)(iVar3 + 0x14) == 0x4857545a) {
      return false;
    }
    if (*(int *)(param_2 + 0x6c) < 100) {
      local_c = 2;
    }
    else {
      local_c = 1;
    }
    break;
  case 6:
    iVar1 = (*(code *)**(undefined4 **)(iVar3 + 0x18))();
    if ((*(int *)(iVar1 + 0x14) != 0x4d4c5952) &&
       (iVar3 = (*(code *)**(undefined4 **)(iVar3 + 0x18))(), *(int *)(iVar3 + 0x14) != 0x57494e47))
    {
      return false;
    }
    return true;
  }
  return (local_14 & local_c) != 0;
}

