
void FUN_00578500(undefined4 param_1,undefined2 param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  undefined2 local_14 [6];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if (DAT_00917f48 != 0) {
    FUN_0056fa50();
    iVar2 = FUN_00577200(param_1);
    if (iVar2 == 0) {
      uVar3 = FUN_0041f870(param_2,param_4);
      uVar3 = FUN_0081cb40("multi_message","player_joined",uVar3);
      FUN_0056fcb0("%s: %s (%ld,%d)",uVar3);
      FUN_00576600(param_1,param_2,param_3,param_4);
      iVar2 = FUN_00822e60();
      DAT_00917f80 = iVar2 + 15000;
      DAT_009180e0 = 0;
      *(undefined4 *)(DAT_00917f48 + 0x42c) = 0;
      *(undefined4 *)(DAT_00917f48 + 0x428) = 0;
      *(undefined4 *)(DAT_00917f48 + 0x430) = 300;
    }
    iVar2 = FUN_00764760();
    if (((iVar2 != 0) && (cVar1 = FUN_00742cf0(), cVar1 != '\0')) && (DAT_00917f4c != '\0')) {
      local_14[0] = 0x5347;
      FUN_00575890(local_14,2,1,0);
    }
  }
  FUN_0083e885();
  return;
}

