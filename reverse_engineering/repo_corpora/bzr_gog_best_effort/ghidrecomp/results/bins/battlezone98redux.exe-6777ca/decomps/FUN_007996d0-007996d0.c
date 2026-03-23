
CCommandManager * __thiscall FUN_007996d0(CCommandManager *param_1,uint param_2)

{
  CCommandManager::ClearAllCmdImages(param_1);
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}

