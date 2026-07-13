
void FUN_0043aac0(undefined4 param_1,undefined4 param_2,char *param_3,int param_4,int param_5,
                 int param_6)

{
  int iVar1;
  int iVar2;
  undefined1 local_34 [20];
  float local_20;
  float local_1c;
  float local_18;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if (DAT_00915594 != 0) {
    FUN_0043a990(local_34);
    local_20 = (float)param_6;
    local_1c = (float)param_4;
    local_18 = (float)param_5;
    iVar1 = FUN_0043af00(0,0,local_34,0);
    if (iVar1 != 0) {
      strncpy((char *)(iVar1 + 4),param_3,0x10);
      *(undefined1 *)(iVar1 + 0x13) = 0;
      *(undefined4 *)(iVar1 + 0x4c) = param_1;
      *(undefined4 *)(iVar1 + 0x54) = param_2;
      *(uint *)(iVar1 + 0x70) = *(uint *)(iVar1 + 0x70) | 0x200;
      iVar2 = FUN_0043b520(DAT_00915594,iVar1,0);
      if (iVar2 == 0) {
        FUN_0043b010(iVar1);
      }
    }
  }
  FUN_0083e885();
  return;
}

