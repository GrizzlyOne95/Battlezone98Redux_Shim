
void __thiscall FUN_005e94a0(int param_1,undefined4 param_2)

{
  char cVar1;
  int iVar2;
  
  iVar2 = FUN_005c8800(param_2);
  if (iVar2 == 1) {
    cVar1 = FUN_005c8410(param_2,"avmuf");
    if (cVar1 != '\0') {
      *(undefined1 *)(param_1 + 0x54) = 1;
      *(undefined4 *)(param_1 + 0x88) = param_2;
    }
  }
  iVar2 = FUN_005c8800(param_2);
  if (iVar2 == 1) {
    cVar1 = FUN_005c8410(param_2,"avfigh");
    if (cVar1 != '\0') {
      *(undefined1 *)(param_1 + 0x55) = 1;
      *(undefined4 *)(param_1 + 0x90) = param_2;
      FUN_004f6aa0();
      FUN_004f6ab0("tran0401.otf",DAT_009175b0,0x41000000,0);
      FUN_004f6ab0("tran0402.otf",DAT_0091755c,0x41000000,0);
    }
  }
  return;
}

