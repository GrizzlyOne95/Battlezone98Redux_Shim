
int * __thiscall FUN_0073aab0(undefined4 *param_1,int *param_2)

{
  int iVar1;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  
  iVar1 = std::ios_base::setf((ios_base *)((int)param_2 + *(int *)(*param_2 + 4)),0x200,0xe00);
  switch(*param_1) {
  case 0:
    FUN_004bc590(param_2,&DAT_0089a004);
    break;
  case 1:
    uVar4 = param_1[3];
    uVar3 = param_1[2];
    pbVar2 = (basic_ostream<char,struct_std::char_traits<char>_> *)
             FUN_004bc590(param_2,&DAT_0089466c);
    std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<
              (pbVar2,CONCAT44(uVar4,uVar3));
    break;
  case 2:
    uVar4 = param_1[3];
    uVar3 = param_1[2];
    pbVar2 = (basic_ostream<char,struct_std::char_traits<char>_> *)
             FUN_004bc590(param_2,&DAT_0089a000);
    std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<
              (pbVar2,CONCAT44(uVar4,uVar3));
    break;
  case 3:
    uVar4 = param_1[3];
    uVar3 = param_1[2];
    pbVar2 = (basic_ostream<char,struct_std::char_traits<char>_> *)
             FUN_004bc590(param_2,&DAT_0089a008);
    std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<
              (pbVar2,CONCAT44(uVar4,uVar3));
    break;
  default:
    FUN_004bc590(param_2,&DAT_0089a004);
  }
  std::ios_base::setf((ios_base *)((int)param_2 + *(int *)(*param_2 + 4)),iVar1,0xe00);
  return param_2;
}

