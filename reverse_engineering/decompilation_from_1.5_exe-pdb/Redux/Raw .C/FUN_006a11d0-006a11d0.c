
void __fastcall FUN_006a11d0(undefined4 *param_1)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0084fad8;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = UnitAttachment::vftable;
  local_8 = 0;
  if ((DAT_00920f04 != 0) && (-1 < *(char *)(param_1 + 5))) {
    FUN_006a00f0(*(undefined2 *)(param_1[3] + 0x5a),*(undefined1 *)(param_1 + 5),uVar1);
    if (*(char *)(param_1 + 9) == '\0') {
      FUN_0068fc60(param_1 + 1);
    }
    *(int *)(&DAT_02ce9b0c + *(char *)(param_1 + 5) * 0x1e0) =
         *(int *)(&DAT_02ce9b0c + *(char *)(param_1 + 5) * 0x1e0) + -1;
  }
  local_8 = 0xffffffff;
  FUN_004773f0();
  ExceptionList = local_10;
  return;
}

