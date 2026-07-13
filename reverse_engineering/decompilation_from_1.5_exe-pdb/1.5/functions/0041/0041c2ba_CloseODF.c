/*
 * Entry: 0041c2ba
 * Name: CloseODF
 * Namespace: Global
 * Signature: int CloseODF(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl CloseODF(lua_State *param_1)

{
  ParameterDB *this;
  
  this = GetParameterDB(param_1,1);
  if (this != (ParameterDB *)0x0) {
    ParameterDB::~ParameterDB(this);
  }
  return 0;
}
