
void __fastcall FUN_00661570(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = FUN_005c7fb0(0);
  *(undefined4 *)(param_1 + 0x60) = uVar1;
  if (*(char *)(param_1 + 0x54) == '\0') {
    FUN_005cadd0(1,8);
    FUN_005cacb0(1,10);
    *(undefined1 *)(param_1 + 0x54) = 1;
    uVar1 = FUN_005c8250("cvfigh",2,"spawn_nav_beacon",0,0);
    *(undefined4 *)(param_1 + 0x68) = uVar1;
    FUN_005cd6f0(*(undefined4 *)(param_1 + 0x68));
    uVar1 = FUN_005c8080("bvfigh",1,*(undefined4 *)(param_1 + 0x60),0);
    FUN_005cb820(uVar1,*(undefined4 *)(param_1 + 0x68),1);
  }
  return;
}

