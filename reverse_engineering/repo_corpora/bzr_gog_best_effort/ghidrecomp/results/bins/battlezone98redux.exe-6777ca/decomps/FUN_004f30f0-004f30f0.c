
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_004f30f0(int param_1)

{
  undefined4 local_c;
  
  _DAT_008e8688 = FUN_00787ac0("Config","InfoWidth",0xb4,"lang.ini");
  _DAT_008e8684 = FUN_00787ac0("Config","InfoHeight",100,"lang.ini");
  if (DAT_00915567 == '\0') {
    local_c = 0x14;
  }
  else {
    local_c = 0x96;
  }
  _DAT_008e868c = FUN_00787ac0("Config","InfoRightOffset",local_c,"lang.ini");
  *(undefined4 *)(param_1 + 0xfc) = 0;
  *(undefined1 *)(param_1 + 0x11c) = 0;
  *(undefined4 *)(param_1 + 0x120) = 0;
  return;
}

