/*
 * Entry: 004a345a
 * Name: ParameterDB::Get
 * Namespace: ParameterDB
 * Signature: bool Get(ParameterDB * this, uint param_1, uint param_2, long64 * param_3, long64 param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
ParameterDB::Get(ParameterDB *this,uint param_1,uint param_2,long64 *param_3,long64 param_4)

{
  bool bVar1;
  char *_Source;
  undefined4 in_stack_00000010;
  
  _Source = Get(this,param_1,param_2);
  if (_Source == (char *)0x0) {
    if (param_3 != (long64 *)0x0) {
      *(undefined4 *)param_3 = in_stack_00000010;
      *(undefined4 *)((int)param_3 + 4) = (undefined4)param_4;
    }
    bVar1 = false;
  }
  else {
    if (param_3 != (long64 *)0x0) {
      in_stack_00000010 = 0;
      param_4._0_4_ = 0;
      strncpy((char *)&stack0x00000010,_Source,8);
      *(undefined4 *)param_3 = in_stack_00000010;
      *(undefined4 *)((int)param_3 + 4) = (undefined4)param_4;
    }
    bVar1 = true;
  }
  return bVar1;
}
