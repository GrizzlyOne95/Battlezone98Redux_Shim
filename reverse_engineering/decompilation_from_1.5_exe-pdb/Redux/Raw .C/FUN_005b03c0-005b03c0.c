
undefined4 * FUN_005b03c0(int param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  undefined4 uVar2;
  int *piVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  undefined4 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084c3b0;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_004f0130(param_1,param_2,param_3);
  local_8 = 0;
  *local_14 = ProducerClass::vftable;
  FUN_00589430(local_14 + 0xe);
  local_8 = CONCAT31(local_8._1_3_,1);
  FUN_00589800(0xdf9ca9e9,0x9fa4327,local_14 + 0x17c,*(undefined4 *)(param_1 + 0x5f0));
  FUN_00589800(0xdf9ca9e9,0x74c3a47c,local_14 + 0x17d,*(undefined4 *)(param_1 + 0x5f4));
  FUN_00589800(0xdf9ca9e9,0xe1bad3b1,local_14 + 0x17e,*(undefined4 *)(param_1 + 0x5f8));
  FUN_00589800(0xdf9ca9e9,0x42756986,local_14 + 0x17f,*(undefined4 *)(param_1 + 0x5fc));
  FUN_00589760(0xdf9ca9e9,0x92a6e0eb,local_14 + 0x180,*(undefined4 *)(param_1 + 0x600));
  FUN_00589760(0xdf9ca9e9,0x8588af8c,local_14 + 0x181,*(undefined4 *)(param_1 + 0x604));
  for (local_1c = 0; local_1c < 9; local_1c = local_1c + 1) {
    uVar5 = 0;
    uVar4 = 0;
    piVar3 = &local_28;
    uVar2 = FUN_00446440(local_1c + 0x31,0xf1915444,piVar3,0,0);
    FUN_00589c20(0xdf9ca9e9,uVar2,piVar3,uVar4,uVar5);
    if (local_28 == 0 && local_24 == 0) {
      local_14[local_1c + 0x182] = 0;
    }
    else {
      uVar2 = FUN_004e0f70(local_28,local_24);
      local_14[local_1c + 0x182] = uVar2;
      if ((local_14[local_1c + 0x182] != 0) && (cVar1 = FUN_00571c40(), cVar1 != '\0')) {
        local_20 = *(int *)(local_14[local_1c + 0x182] + 0x14);
        if (local_20 == 0x42415252) {
          if (DAT_008e8c0e == '\0') {
            local_14[local_1c + 0x182] = 0;
          }
        }
        else if ((local_20 == 0x434f4d4d) && (DAT_008e7733 == '\0')) {
          local_14[local_1c + 0x182] = 0;
        }
      }
    }
  }
  cVar1 = FUN_00589fe0(0xdf9ca9e9,0x18231326,local_14 + 0x18b,0);
  if (cVar1 == '\0') {
    uVar2 = FUN_0044e4c0("prodsmok");
    local_14[0x18b] = uVar2;
  }
  FUN_0047b6c0(0xdf9ca9e9,0x29afb604,local_14 + 0x18c,0);
  FUN_0047b6c0(0xdf9ca9e9,0xa8198ee3,local_14 + 400,0);
  FUN_0047b6c0(0xdf9ca9e9,0xdd64817d,local_14 + 0x194,0);
  local_8 = local_8 & 0xffffff00;
  FUN_00589530();
  ExceptionList = local_10;
  return local_14;
}

