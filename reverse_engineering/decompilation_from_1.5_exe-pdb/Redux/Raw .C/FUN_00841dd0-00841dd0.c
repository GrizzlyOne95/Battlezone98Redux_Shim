
exception * __thiscall
FUN_00841dd0(exception *param_1,char *param_2,int param_3,undefined4 param_4,undefined4 param_5)

{
  undefined2 *puVar1;
  exception *peVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008659d3;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  if (0xf < *(uint *)(param_2 + 0x14)) {
    param_2 = *(char **)param_2;
  }
  std::exception::exception(param_1,&param_2);
  *(undefined4 *)(param_1 + 0xc) = param_4;
  *(undefined4 *)(param_1 + 0x10) = param_5;
  *(undefined4 *)(param_1 + 0x28) = 0xf;
  *(undefined4 *)(param_1 + 0x24) = 0;
  param_1[0x14] = (exception)0x0;
  *(undefined ***)param_1 = boost::filesystem::filesystem_error::vftable;
  *(undefined4 *)(param_1 + 0x2c) = 0;
  *(undefined4 *)(param_1 + 0x30) = 0;
  local_8 = 2;
  puVar1 = operator_new(0x48);
  if (puVar1 == (undefined2 *)0x0) {
    puVar1 = (undefined2 *)0x0;
  }
  else {
    *(undefined4 *)(puVar1 + 10) = 7;
    *(undefined4 *)(puVar1 + 8) = 0;
    *puVar1 = 0;
    *(undefined4 *)(puVar1 + 0x16) = 7;
    *(undefined4 *)(puVar1 + 0x14) = 0;
    puVar1[0xc] = 0;
    *(undefined4 *)(puVar1 + 0x22) = 0xf;
    *(undefined4 *)(puVar1 + 0x20) = 0;
    *(undefined1 *)(puVar1 + 0x18) = 0;
  }
  FUN_007bd680(puVar1);
  if (*(int *)(param_1 + 0x2c) != param_3) {
    FID_conflict_assign(param_3,0,0xffffffff);
    peVar2 = (exception *)FUN_00841ec8();
    return peVar2;
  }
  ExceptionList = local_10;
  return param_1;
}

