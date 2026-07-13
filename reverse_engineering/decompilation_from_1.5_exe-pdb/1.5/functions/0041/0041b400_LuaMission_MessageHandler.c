/*
 * Entry: 0041b400
 * Name: LuaMission::MessageHandler
 * Namespace: LuaMission
 * Signature: int MessageHandler(ushort param_1, char * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl LuaMission::MessageHandler(ushort param_1,char *param_2,int param_3)

{
  int iVar1;
  undefined2 in_stack_00000006;
  
  if (*param_2 == '#') {
    iVar1 = (**(code **)(AiMission::current->_padding_ + 0x48))(_param_1,param_2,param_3);
    return iVar1;
  }
  return 0;
}
