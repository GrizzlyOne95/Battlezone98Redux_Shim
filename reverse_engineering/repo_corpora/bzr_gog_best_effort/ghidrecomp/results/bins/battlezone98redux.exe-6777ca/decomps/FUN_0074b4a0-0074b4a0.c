
void __fastcall FUN_0074b4a0(undefined4 *param_1)

{
  uint uVar1;
  int iVar2;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  puStack_c = &LAB_0085bc16;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = BZRNetLobby::vftable;
  local_8 = 1;
  iVar2 = get(uVar1);
  if (*(undefined4 **)(iVar2 + 0xc38) == param_1) {
    iVar2 = get(uVar1);
    *(undefined4 *)(iVar2 + 0xc38) = 0;
  }
  local_8 = local_8 & 0xffffff00;
  FUN_006676c0();
  local_8 = 0xffffffff;
  FUN_0073d510();
  ExceptionList = local_10;
  return;
}

