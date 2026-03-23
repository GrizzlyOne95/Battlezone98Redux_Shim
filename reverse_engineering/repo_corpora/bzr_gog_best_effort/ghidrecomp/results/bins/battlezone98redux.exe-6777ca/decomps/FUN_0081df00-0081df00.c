
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_0081df00(void)

{
  int iVar1;
  int iVar2;
  
  setlocale(0,"English");
  iVar1 = FUN_0081dee0();
  switch(iVar1) {
  case 1:
    DAT_02cc40a4 = 1;
    break;
  case 2:
    DAT_02cc40a4 = 1;
    break;
  case 3:
    DAT_02cc40a4 = 2;
    break;
  case 4:
    DAT_02cc40a4 = 3;
    break;
  default:
    DAT_02cc40a4 = 1;
  }
  PTR_DAT_008fe1b8 = (undefined *)&DAT_008fe1bc;
  iVar2 = DAT_02cc40a4;
  if (DAT_02cc40a4 == 2) {
    PTR_PTR_008fe1c8 = (undefined *)&PTR_s_Escape_Key_008ec4b0;
    setlocale(0,"German");
  }
  else if (DAT_02cc40a4 == 3) {
    PTR_PTR_008fe1c8 = (undefined *)&PTR_s_Escape_Key_008ec2a0;
    setlocale(0,"Spanish");
  }
  else {
    PTR_PTR_008fe1c8 = (undefined *)&PTR_s_Escape_Key_008ec2a0;
    setlocale(0,"English");
  }
  _DAT_02cc40a0 = *(undefined4 *)(PTR_DAT_008fe1b8 + 0x10);
  _DAT_00946728 = *(undefined4 *)(PTR_DAT_008fe1b8 + 0x14);
  *(int *)PTR_DAT_008fe1b8 = DAT_02cc40a4;
  if ((iVar1 < 1) || (7 < iVar1)) {
    FUN_0081e0c0("Game Language Is: **Bad Language**\n",iVar2);
  }
  else {
    FUN_0081e0c0("Game Language Is: %s - %s\n",(&PTR_DAT_008fe178)[iVar1],(&PTR_DAT_008fe198)[iVar1]
                );
  }
  return DAT_02cc40a4;
}

