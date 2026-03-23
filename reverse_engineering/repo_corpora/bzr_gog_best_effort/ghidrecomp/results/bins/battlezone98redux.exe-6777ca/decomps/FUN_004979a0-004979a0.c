
void __fastcall FUN_004979a0(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = FUN_0068bed0("object.W");
  *(undefined4 *)(param_1 + 8) = uVar1;
  uVar1 = FUN_0068bed0("select.W");
  *(undefined4 *)(param_1 + 0xc) = uVar1;
  uVar1 = FUN_0068bed0("target.W");
  *(undefined4 *)(param_1 + 0x10) = uVar1;
  uVar1 = FUN_0068bed0("caret_u.W");
  *(undefined4 *)(param_1 + 0x14) = uVar1;
  uVar1 = FUN_0068bed0("caret_l.W");
  *(undefined4 *)(param_1 + 0x18) = uVar1;
  uVar1 = FUN_0068bed0("caret_r.W");
  *(undefined4 *)(param_1 + 0x1c) = uVar1;
  uVar1 = FUN_0068bed0("caret_d.W");
  *(undefined4 *)(param_1 + 0x20) = uVar1;
  uVar1 = FUN_0068bed0("grnbar");
  *(undefined4 *)(param_1 + 0x24) = uVar1;
  uVar1 = FUN_0068bed0("yelbar");
  *(undefined4 *)(param_1 + 0x28) = uVar1;
  uVar1 = FUN_0068bed0("redbar");
  *(undefined4 *)(param_1 + 0x2c) = uVar1;
  FUN_0061a140(1);
  return;
}

