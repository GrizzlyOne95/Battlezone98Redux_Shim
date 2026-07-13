
void __fastcall FUN_00459880(undefined4 *param_1)

{
  int iVar1;
  uint uVar2;
  int *piVar3;
  undefined4 *puVar4;
  uint local_18;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  puStack_c = &LAB_00846fe6;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = TwirlTrailRender::vftable;
  local_8 = 1;
  uVar2 = get(uVar2);
  for (local_18 = 0; local_18 < uVar2; local_18 = local_18 + 1) {
    piVar3 = (int *)FUN_0045bb80(local_18);
    iVar1 = *piVar3;
    if (iVar1 != 0) {
      FUN_0045b9c0();
      if (iVar1 != 0) {
        FUN_00459990(1);
      }
      puVar4 = (undefined4 *)FUN_0045bb80(local_18);
      *puVar4 = 0;
    }
  }
  FUN_0045b9c0();
  local_8 = local_8 & 0xffffff00;
  FUN_0045b800();
  local_8 = 0xffffffff;
  FUN_0044ddc0();
  ExceptionList = local_10;
  return;
}

