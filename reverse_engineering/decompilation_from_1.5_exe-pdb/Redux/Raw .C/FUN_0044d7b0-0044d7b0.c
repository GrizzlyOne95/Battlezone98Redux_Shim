
void __thiscall FUN_0044d7b0(undefined4 *param_1,int param_2,undefined4 param_3)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  int local_5c;
  char local_54 [64];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008467b0;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  FUN_0044dec0(param_2,param_3);
  local_8 = 0;
  *param_1 = MultiRenderClass::vftable;
  if (param_2 == 0) {
    param_1[0x41] = 0;
    param_1[0x42] = 0;
  }
  else {
    uVar2 = FUN_00446460(param_1 + 0x15,0x811c9dc5,uVar1);
    FUN_00589430(param_1 + 0x25);
    local_8 = CONCAT31(local_8._1_3_,1);
    FUN_005896c0(uVar2,0x8c8e76ec,param_1 + 0x42,*(undefined4 *)(param_2 + 0x108));
    uVar3 = FUN_0083d92c(-(uint)((int)((ulonglong)(uint)param_1[0x42] * 4 >> 0x20) != 0) |
                         (uint)((ulonglong)(uint)param_1[0x42] * 4));
    param_1[0x41] = uVar3;
    for (local_5c = 0; local_5c < (int)param_1[0x42]; local_5c = local_5c + 1) {
      sprintf(local_54,"renderName%d",local_5c + 1);
      if (*(int *)(param_2 + 0x104) == 0) {
        *(undefined4 *)(param_1[0x41] + local_5c * 4) = 0;
      }
      else {
        *(undefined4 *)(param_1[0x41] + local_5c * 4) =
             *(undefined4 *)(*(int *)(param_2 + 0x104) + local_5c * 4);
      }
      uVar3 = *(undefined4 *)(param_1[0x41] + local_5c * 4);
      iVar5 = param_1[0x41] + local_5c * 4;
      uVar4 = FUN_00446460(local_54,0x811c9dc5,iVar5,uVar3);
      FUN_00589fe0(uVar2,uVar4,iVar5,uVar3);
    }
    local_8 = local_8 & 0xffffff00;
    FUN_00589530();
  }
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

