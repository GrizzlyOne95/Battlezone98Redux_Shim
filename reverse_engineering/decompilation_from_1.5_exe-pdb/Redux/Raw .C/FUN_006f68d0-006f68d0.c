
undefined4 * FUN_006f68d0(undefined4 *param_1,allocator<char> *param_2)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 local_20 [4];
  undefined4 *local_10;
  undefined4 *local_c;
  
  ATL::CManualAccessor::CManualAccessor((CManualAccessor *)local_20);
  local_20[3] = std::allocator<char>::allocator<char>(param_2);
  local_10 = (undefined4 *)std::allocator<char>::allocator<char>(param_2);
  local_c = (undefined4 *)FUN_006ae370();
  for (; local_10 != local_c; local_10 = local_10 + 2) {
    local_20[0] = *local_10;
    local_20[1] = local_10[1];
    iVar1 = FUN_006ae390(local_20);
    if (iVar1 != 0) break;
  }
  puVar2 = local_20;
  puVar3 = param_1;
  for (iVar1 = 7; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  return param_1;
}

