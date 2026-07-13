
undefined4 * FUN_006f6950(undefined4 *param_1,allocator<char> *param_2)

{
  int iVar1;
  CManualAccessor *pCVar2;
  undefined4 *puVar3;
  CManualAccessor local_28 [12];
  undefined4 local_1c;
  undefined4 *local_18;
  undefined4 *local_14;
  int local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  ATL::CManualAccessor::CManualAccessor(local_28);
  local_1c = std::allocator<char>::allocator<char>(param_2);
  local_18 = (undefined4 *)std::allocator<char>::allocator<char>(param_2);
  local_14 = (undefined4 *)FUN_006ae370();
  for (; local_18 != local_14; local_18 = local_18 + 2) {
    local_c = *local_18;
    local_8 = local_18[1];
    iVar1 = FUN_006ae390(&local_c);
    local_10 = iVar1 + local_10;
  }
  pCVar2 = local_28;
  puVar3 = param_1;
  for (iVar1 = 7; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *(undefined4 *)pCVar2;
    pCVar2 = pCVar2 + 4;
    puVar3 = puVar3 + 1;
  }
  return param_1;
}

