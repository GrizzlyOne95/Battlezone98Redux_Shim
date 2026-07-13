
void FUN_005d4a60(undefined4 param_1,int param_2)

{
  undefined1 uVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  char *local_2c;
  undefined1 local_20 [24];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  iVar2 = FUN_00434160();
  if ((iVar2 != 9) && (DAT_00918132 == '\0')) {
    DAT_00918132 = 1;
    FUN_00434600();
    iVar2 = FUN_00572a70();
    if (iVar2 == 0) {
      FUN_00822a70();
    }
    FUN_0043a570();
    FUN_00623ff0();
    basic_string<>(param_1);
    FUN_00787f90(local_20,param_2 != 0);
    ~basic_string<>();
    if (DAT_00918320 == (int *)0x0) {
      FUN_0081e820("Starting alert in game UI wrapper\n");
      uVar3 = FUN_0081e660();
      FUN_004bc590(uVar3);
      DAT_00918328 = 0x1d;
      DAT_009455df = '\0';
      while (((DAT_00918328 != 0 && (DAT_009455de == '\0')) && (DAT_009455df == '\0'))) {
        FUN_005d5150(DAT_00918328);
      }
      if (DAT_00918320 != (int *)0x0) {
        if (DAT_00918320 != (int *)0x0) {
          (**(code **)(*DAT_00918320 + 0xc))(1);
        }
        DAT_00918320 = (int *)0x0;
      }
      DAT_00918328 = 0;
      if (DAT_00918320 == (int *)0x0) {
        local_2c = "\n";
      }
      else {
        local_2c = " (parent still set)\n";
      }
      FUN_0081e820("Ending alert in game UI wrapper",local_2c);
      uVar3 = FUN_0081e660();
      uVar3 = FUN_004bc590(uVar3);
      FUN_004bc590(uVar3);
    }
    else {
      iVar2 = DAT_00918320[9];
      iVar4 = DAT_00918320[10];
      uVar1 = *(undefined1 *)((int)DAT_00918320 + 0x26);
      FUN_0056f820();
      uVar3 = FUN_0056f820(DAT_00918320);
      FUN_00787de0(uVar3);
      *(undefined1 *)((int)DAT_00918320 + 0x26) = 0;
      FUN_007c76d0();
      *(char *)(DAT_00918320 + 10) = (char)iVar4;
      *(undefined1 *)((int)DAT_00918320 + 0x26) = uVar1;
      iVar4 = FUN_00434160();
      if (iVar4 != 9) {
        *(char *)(DAT_00918320 + 9) = (char)iVar2;
      }
    }
    iVar2 = FUN_00434160();
    if (iVar2 == 9) {
      DAT_009454e0 = 1;
    }
    FUN_0043a910(0xffffffff,0xffffffff,0xffffffff);
    iVar2 = FUN_00434160();
    if (iVar2 == 5) {
      FUN_0043a5f0();
    }
    iVar2 = FUN_00572a70();
    if (iVar2 == 0) {
      FUN_00822ab0();
    }
    FUN_00434600();
    FUN_00623eb0();
    DAT_00918132 = '\0';
  }
  FUN_0083e885();
  return;
}

