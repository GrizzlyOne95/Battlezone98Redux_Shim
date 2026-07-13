
void __fastcall FUN_004b8460(int *param_1)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  undefined1 local_18 [8];
  undefined4 local_10;
  int local_c;
  int *local_8;
  
  if ((char)param_1[0x1a] != '\x01') {
    local_8 = param_1;
    if ((char)param_1[0x1a] == '\x02') {
      FUN_004badc0(param_1 + 0x19);
      *(undefined1 *)(local_8 + 0x1a) = 1;
      if (0xffff < (uint)local_8[0x19]) {
        local_10 = FUN_004b75f0(local_8);
        uVar1 = make_pair<>(local_18,(int)local_8 + 0x62,&local_10);
        FUN_004baf80(uVar1);
        *(undefined2 *)((int)local_8 + 0x62) = DAT_009175bc;
      }
      local_c = (**(code **)(*local_8 + 0x30))();
      if ((local_c != 0) && ((*(uint *)(local_c + 0x14) & 0x80) != 0)) {
        *(undefined1 *)(local_8 + 0x1a) = 0;
        *(undefined2 *)((int)local_8 + 0x62) = 0;
        return;
      }
      FUN_004b7d70();
    }
    else {
      *(undefined1 *)(param_1 + 0x1a) = 1;
      *(undefined2 *)((int)param_1 + 0x62) = DAT_009175bc;
      param_1[0x19] = (uint)DAT_009180d4 * 0x10000 + DAT_008e80b0;
      DAT_008e80b0 = DAT_008e80b0 + 1;
    }
    puVar2 = (undefined4 *)FUN_004bad10(local_8 + 0x19);
    *puVar2 = local_8;
    FUN_004b8000();
  }
  return;
}

