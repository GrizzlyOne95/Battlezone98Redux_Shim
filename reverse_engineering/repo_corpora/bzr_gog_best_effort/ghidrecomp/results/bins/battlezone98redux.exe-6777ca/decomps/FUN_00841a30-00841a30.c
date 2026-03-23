
void FUN_00841a30(char *param_1,char *param_2,wchar_t *param_3,wchar_t *param_4,undefined4 *param_5,
                 codecvt<wchar_t,char,int> *param_6)

{
  int *piVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  wchar_t *local_40;
  int local_3c;
  char *local_38;
  char *local_34;
  undefined **local_30 [3];
  int local_24;
  undefined4 local_20;
  undefined1 local_1c;
  undefined4 local_c;
  undefined4 local_8;
  uint local_4;
  
  local_4 = DAT_008e7000 ^ (uint)&local_40;
  local_3c = 0;
  iVar2 = std::codecvt<wchar_t,char,int>::in
                    (param_6,&local_3c,param_1,param_2,&local_34,param_3,param_4,&local_40);
  if (iVar2 != 0) {
    uVar3 = FUN_00843bf0();
    local_38 = "boost::filesystem::path codecvt to wstring";
    std::exception::exception((exception *)local_30,&local_38);
    local_30[0] = boost::system::system_error::vftable;
    local_8 = 0xf;
    local_c = 0;
    local_1c = 0;
    local_24 = iVar2;
    local_20 = uVar3;
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_30,(ThrowInfo *)&DAT_008d7600);
  }
  puVar4 = param_5;
  if (7 < (uint)param_5[5]) {
    puVar4 = (undefined4 *)*param_5;
  }
  piVar1 = param_5 + 4;
  if (7 < (uint)param_5[5]) {
    param_5 = (undefined4 *)*param_5;
  }
  FUN_008412a0(*piVar1 * 2 + (int)param_5,(int)puVar4 + *piVar1 * 2,param_3,local_40);
  FUN_0083e885();
  return;
}

