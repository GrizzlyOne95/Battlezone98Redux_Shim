
void FUN_0068f6c0(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  int local_5c;
  undefined1 local_58 [80];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  FUN_006a5fd0("AI   About to create team %d\n",param_1);
  uVar1 = FUN_006951d0(DAT_00920f04,param_1,1);
  *(undefined4 *)(DAT_00920f04 + param_1 * 4) = uVar1;
  FUN_006a3aa0(local_58,param_1);
  while( true ) {
    iVar2 = FUN_006a3b60(local_58);
    if (iVar2 == 0) break;
    FUN_0068f630(iVar2);
  }
  FUN_006a3c40(local_58,param_1);
  while( true ) {
    iVar2 = FUN_006a3c70(local_58);
    if (iVar2 == 0) break;
    FUN_0068f690(iVar2);
  }
  for (local_5c = 0; local_5c < 0x10; local_5c = local_5c + 1) {
    if (local_5c != param_1) {
      FUN_006a9040(param_1,local_5c,1);
    }
  }
  FUN_0083e885();
  return;
}

