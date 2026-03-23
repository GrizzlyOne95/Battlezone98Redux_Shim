
void __fastcall FUN_00679700(int param_1)

{
  char cVar1;
  undefined4 *puVar2;
  
  cVar1 = FUN_0041fc90();
  if (cVar1 != '\0') {
    FUN_006783d0();
  }
  cVar1 = FUN_0041fc90();
  if (cVar1 != '\0') {
    FUN_00678410();
  }
  puVar2 = (undefined4 *)FUN_004200d0(*(undefined4 *)(param_1 + 400));
  *(undefined4 *)(param_1 + 0x1cc) = *puVar2;
  puVar2 = (undefined4 *)FUN_004200d0(*(undefined4 *)(param_1 + 0x194));
  *(undefined4 *)(param_1 + 0x1d0) = *puVar2;
  *(undefined1 *)(param_1 + 0x1dd) = 1;
  return;
}

