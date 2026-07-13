
undefined4 __thiscall FUN_006f09f0(undefined4 *param_1,undefined4 param_2)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00854e98;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 0;
  FUN_006f4460(*param_1,param_1[1],&stack0x00000008);
  local_8 = 0xffffffff;
  std::function<void___cdecl(void)>::~function<void___cdecl(void)>
            ((function<void___cdecl(void)> *)&stack0x00000008);
  ExceptionList = local_10;
  return param_2;
}

