
undefined2 * __thiscall FUN_00626540(undefined2 *param_1,undefined2 param_2)

{
  int iVar1;
  char *_Source;
  undefined4 *puVar2;
  size_t _Count;
  
  *param_1 = param_2;
  iVar1 = FUN_005771b0();
  if (iVar1 != 0) {
    _Count = 0x21;
    _Source = (char *)FUN_005765e0();
    strncpy((char *)(param_1 + 0x36),_Source,_Count);
    *(undefined1 *)(param_1 + 0x46) = 0;
    *(uint *)(param_1 + 2) = (uint)*(byte *)(iVar1 + 0x68);
    if (*(int *)(param_1 + 2) < 1) {
      param_1[4] = 0x3f;
    }
    else {
      sprintf((char *)(param_1 + 4),"%d");
    }
    FUN_00575510();
    iVar1 = FUN_004bb390();
    if (iVar1 == 4) {
      puVar2 = (undefined4 *)get();
      *(undefined4 *)(param_1 + 0x22) = *puVar2;
    }
    else {
      *(undefined4 *)(param_1 + 0x22) = 0;
    }
    sprintf((char *)(param_1 + 9),"%d");
    FUN_00575510();
    iVar1 = FUN_004bb390();
    if (iVar1 == 4) {
      puVar2 = (undefined4 *)get();
      *(undefined4 *)(param_1 + 0x24) = *puVar2;
    }
    else {
      *(undefined4 *)(param_1 + 0x24) = 0;
    }
    sprintf((char *)(param_1 + 0x2c),"%d");
    FUN_00575510();
    iVar1 = FUN_004bb390();
    if (iVar1 == 4) {
      puVar2 = (undefined4 *)get();
      *(undefined4 *)(param_1 + 0x26) = *puVar2;
    }
    else {
      *(undefined4 *)(param_1 + 0x26) = 0;
    }
    sprintf((char *)(param_1 + 0x31),"%5.2f",(double)*(float *)(param_1 + 0x26));
    FUN_00575510();
    iVar1 = FUN_004bb390();
    if (iVar1 == 4) {
      puVar2 = (undefined4 *)get();
      *(undefined4 *)(param_1 + 0x28) = *puVar2;
    }
    else {
      *(undefined4 *)(param_1 + 0x28) = 0;
    }
    iVar1 = FUN_008445c0();
    FUN_008445c0((double)(iVar1 * 0x3c) + (double)(&DAT_008a2fd0)[-(iVar1 * 0x3c >> 0x1f)]);
    sprintf((char *)(param_1 + 0xe),"%02d:%02d",iVar1);
    FUN_00575510();
    iVar1 = FUN_004bb390();
    if (iVar1 == 4) {
      puVar2 = (undefined4 *)get();
      *(undefined4 *)(param_1 + 0x2a) = *puVar2;
    }
    else {
      *(undefined4 *)(param_1 + 0x2a) = DAT_00917fa4;
    }
    sprintf((char *)(param_1 + 0x1d),"%d");
  }
  FUN_0041fe40();
  return param_1;
}

