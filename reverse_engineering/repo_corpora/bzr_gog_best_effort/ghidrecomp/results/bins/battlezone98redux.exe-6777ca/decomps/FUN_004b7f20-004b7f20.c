
void __fastcall FUN_004b7f20(int *param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  
  if ((char)param_1[0x1a] != '\x02') {
    if ((char)param_1[0x1a] == '\x01') {
      iVar1 = (**(code **)(*param_1 + 0x30))();
      if ((iVar1 != 0) && (iVar1 = FUN_00479f30(iVar1), iVar1 != 0)) {
        uVar2 = FUN_0045ca50();
        puVar3 = (undefined4 *)FUN_0045bdf0(uVar2);
        if ((puVar3 != (undefined4 *)0x0) && (puVar3 != (undefined4 *)0x0)) {
          (**(code **)*puVar3)(1);
        }
      }
      FUN_004badc0(param_1 + 0x19);
    }
    *(undefined1 *)(param_1 + 0x1a) = 2;
    puVar3 = (undefined4 *)FUN_004bad10(param_1 + 0x19);
    *puVar3 = param_1;
  }
  return;
}

