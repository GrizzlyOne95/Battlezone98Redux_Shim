
void __fastcall FUN_0041af80(undefined4 *param_1)

{
  char cVar1;
  uint uVar2;
  int *piVar3;
  undefined4 *puVar4;
  undefined1 local_2c [4];
  undefined4 local_28;
  undefined1 local_24 [4];
  int *local_20;
  uint local_1c;
  undefined4 local_18;
  undefined4 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  puStack_c = &LAB_00844c86;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = TouchInputMasterButton::vftable;
  local_8 = 1;
  local_14 = param_1;
  FID_conflict_begin(&local_18);
  FID_conflict_end(local_24);
  do {
    cVar1 = FID_conflict_operator__(local_24);
    if (cVar1 == '\0') {
LAB_0041b01a:
      local_1c = 0;
      while( true ) {
        uVar2 = size();
        if (uVar2 <= local_1c) break;
        puVar4 = (undefined4 *)FUN_004200d0(local_1c);
        local_20 = (int *)*puVar4;
        (**(code **)(*local_20 + 0x28))(local_14);
        local_1c = local_1c + 1;
      }
      local_8 = local_8 & 0xffffff00;
      FUN_0041fe20();
      local_8 = 0xffffffff;
      FUN_0041abe0();
      ExceptionList = local_10;
      return;
    }
    piVar3 = (int *)FUN_00421ec0(uVar2);
    if ((undefined4 *)*piVar3 == local_14) {
      local_28 = local_18;
      FUN_004200f0(local_2c,local_18);
      goto LAB_0041b01a;
    }
    FUN_00421ee0();
  } while( true );
}

