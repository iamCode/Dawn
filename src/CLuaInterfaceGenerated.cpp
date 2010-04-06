/*
** Lua binding: CLuaInterface
** Generated automatically by tolua++-1.0.92 on Tue Apr  6 21:08:49 2010.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_CLuaInterface_open (lua_State* tolua_S);

#include "CLuaInterface.h"

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"LuaCallIndirection");
 tolua_usertype(tolua_S,"ConfigurableSpell");
 tolua_usertype(tolua_S,"TextWindow");
 tolua_usertype(tolua_S,"GeneralHealingSpell");
 tolua_usertype(tolua_S,"CNPC");
 tolua_usertype(tolua_S,"CallIndirection");
 tolua_usertype(tolua_S,"GeneralBoltDamageSpell");
 tolua_usertype(tolua_S,"GeneralRayDamageSpell");
 tolua_usertype(tolua_S,"GeneralBuffSpell");
 tolua_usertype(tolua_S,"CCharacter");
 tolua_usertype(tolua_S,"Item");
 tolua_usertype(tolua_S,"Shop");
 tolua_usertype(tolua_S,"GeneralDamageSpell");
 tolua_usertype(tolua_S,"CSpell");
 tolua_usertype(tolua_S,"Player");
 tolua_usertype(tolua_S,"InteractionPoint");
}

/* method: baseOnType of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_baseOnType00
static int tolua_CLuaInterface_CCharacter_baseOnType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  std::string otherType = ((std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'baseOnType'", NULL);
#endif
  {
   self->baseOnType(otherType);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'baseOnType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setStrength of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_setStrength00
static int tolua_CLuaInterface_CCharacter_setStrength00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  int newStrength = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setStrength'", NULL);
#endif
  {
   self->setStrength(newStrength);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setStrength'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getStrength of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_getStrength00
static int tolua_CLuaInterface_CCharacter_getStrength00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CCharacter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CCharacter* self = (const CCharacter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getStrength'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getStrength();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getStrength'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: modifyStrength of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_modifyStrength00
static int tolua_CLuaInterface_CCharacter_modifyStrength00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  int strengthModifier = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'modifyStrength'", NULL);
#endif
  {
   self->modifyStrength(strengthModifier);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'modifyStrength'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setDexterity of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_setDexterity00
static int tolua_CLuaInterface_CCharacter_setDexterity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  int newDexterity = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDexterity'", NULL);
#endif
  {
   self->setDexterity(newDexterity);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setDexterity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDexterity of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_getDexterity00
static int tolua_CLuaInterface_CCharacter_getDexterity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CCharacter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CCharacter* self = (const CCharacter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDexterity'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getDexterity();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDexterity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: modifyDexterity of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_modifyDexterity00
static int tolua_CLuaInterface_CCharacter_modifyDexterity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  int dexterityModifier = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'modifyDexterity'", NULL);
#endif
  {
   self->modifyDexterity(dexterityModifier);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'modifyDexterity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setVitality of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_setVitality00
static int tolua_CLuaInterface_CCharacter_setVitality00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  int newVitality = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setVitality'", NULL);
#endif
  {
   self->setVitality(newVitality);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setVitality'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getVitality of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_getVitality00
static int tolua_CLuaInterface_CCharacter_getVitality00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CCharacter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CCharacter* self = (const CCharacter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getVitality'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getVitality();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getVitality'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: modifyVitality of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_modifyVitality00
static int tolua_CLuaInterface_CCharacter_modifyVitality00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  int vitalityModifier = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'modifyVitality'", NULL);
#endif
  {
   self->modifyVitality(vitalityModifier);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'modifyVitality'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setIntellect of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_setIntellect00
static int tolua_CLuaInterface_CCharacter_setIntellect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  int newIntellect = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setIntellect'", NULL);
#endif
  {
   self->setIntellect(newIntellect);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setIntellect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getIntellect of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_getIntellect00
static int tolua_CLuaInterface_CCharacter_getIntellect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CCharacter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CCharacter* self = (const CCharacter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getIntellect'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getIntellect();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getIntellect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: modifyIntellect of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_modifyIntellect00
static int tolua_CLuaInterface_CCharacter_modifyIntellect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  int intellectModifier = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'modifyIntellect'", NULL);
#endif
  {
   self->modifyIntellect(intellectModifier);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'modifyIntellect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setWisdom of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_setWisdom00
static int tolua_CLuaInterface_CCharacter_setWisdom00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  int newWisdom = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setWisdom'", NULL);
#endif
  {
   self->setWisdom(newWisdom);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setWisdom'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getWisdom of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_getWisdom00
static int tolua_CLuaInterface_CCharacter_getWisdom00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CCharacter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CCharacter* self = (const CCharacter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getWisdom'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getWisdom();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getWisdom'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: modifyWisdom of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_modifyWisdom00
static int tolua_CLuaInterface_CCharacter_modifyWisdom00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  int wisdomModifier = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'modifyWisdom'", NULL);
#endif
  {
   self->modifyWisdom(wisdomModifier);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'modifyWisdom'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setMaxHealth of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_setMaxHealth00
static int tolua_CLuaInterface_CCharacter_setMaxHealth00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  int newMaxHealth = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setMaxHealth'", NULL);
#endif
  {
   self->setMaxHealth(newMaxHealth);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setMaxHealth'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getMaxHealth of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_getMaxHealth00
static int tolua_CLuaInterface_CCharacter_getMaxHealth00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CCharacter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CCharacter* self = (const CCharacter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMaxHealth'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getMaxHealth();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMaxHealth'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: modifyMaxHealth of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_modifyMaxHealth00
static int tolua_CLuaInterface_CCharacter_modifyMaxHealth00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  int maxHealthModifier = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'modifyMaxHealth'", NULL);
#endif
  {
   self->modifyMaxHealth(maxHealthModifier);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'modifyMaxHealth'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setMaxMana of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_setMaxMana00
static int tolua_CLuaInterface_CCharacter_setMaxMana00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  int newMaxMana = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setMaxMana'", NULL);
#endif
  {
   self->setMaxMana(newMaxMana);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setMaxMana'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getMaxMana of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_getMaxMana00
static int tolua_CLuaInterface_CCharacter_getMaxMana00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CCharacter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CCharacter* self = (const CCharacter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMaxMana'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getMaxMana();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMaxMana'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: modifyMaxMana of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_modifyMaxMana00
static int tolua_CLuaInterface_CCharacter_modifyMaxMana00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  int maxManaModifier = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'modifyMaxMana'", NULL);
#endif
  {
   self->modifyMaxMana(maxManaModifier);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'modifyMaxMana'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setNumMoveTexturesPerDirection of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_setNumMoveTexturesPerDirection00
static int tolua_CLuaInterface_CCharacter_setNumMoveTexturesPerDirection00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  ActivityType::ActivityType activity = ((ActivityType::ActivityType) (int)  tolua_tonumber(tolua_S,2,0));
  int numTextures = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setNumMoveTexturesPerDirection'", NULL);
#endif
  {
   self->setNumMoveTexturesPerDirection(activity,numTextures);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setNumMoveTexturesPerDirection'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setMoveTexture of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_setMoveTexture00
static int tolua_CLuaInterface_CCharacter_setMoveTexture00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  ActivityType::ActivityType activity = ((ActivityType::ActivityType) (int)  tolua_tonumber(tolua_S,2,0));
  int direction = ((int)  tolua_tonumber(tolua_S,3,0));
  int index = ((int)  tolua_tonumber(tolua_S,4,0));
  std::string filename = ((std::string)  tolua_tocppstring(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setMoveTexture'", NULL);
#endif
  {
   self->setMoveTexture(activity,direction,index,filename);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setMoveTexture'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setLifeTexture of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_setLifeTexture00
static int tolua_CLuaInterface_CCharacter_setLifeTexture00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  std::string filename = ((std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setLifeTexture'", NULL);
#endif
  {
   self->setLifeTexture(filename);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setLifeTexture'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setWanderRadius of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_setWanderRadius00
static int tolua_CLuaInterface_CCharacter_setWanderRadius00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  int newWanderRadius = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setWanderRadius'", NULL);
#endif
  {
   self->setWanderRadius(newWanderRadius);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setWanderRadius'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getWanderRadius of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_getWanderRadius00
static int tolua_CLuaInterface_CCharacter_getWanderRadius00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CCharacter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CCharacter* self = (const CCharacter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getWanderRadius'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getWanderRadius();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getWanderRadius'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setName of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_setName00
static int tolua_CLuaInterface_CCharacter_setName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  std::string newName = ((std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setName'", NULL);
#endif
  {
   self->setName(newName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getName of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_getName00
static int tolua_CLuaInterface_CCharacter_getName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CCharacter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CCharacter* self = (const CCharacter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getName'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->getName();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setLevel of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_setLevel00
static int tolua_CLuaInterface_CCharacter_setLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  int newLevel = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setLevel'", NULL);
#endif
  {
   self->setLevel(newLevel);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getLevel of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_getLevel00
static int tolua_CLuaInterface_CCharacter_getLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CCharacter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CCharacter* self = (const CCharacter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getLevel'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getLevel();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setMinDamage of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_setMinDamage00
static int tolua_CLuaInterface_CCharacter_setMinDamage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  int newMinDamage = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setMinDamage'", NULL);
#endif
  {
   self->setMinDamage(newMinDamage);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setMinDamage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getMinDamage of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_getMinDamage00
static int tolua_CLuaInterface_CCharacter_getMinDamage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMinDamage'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getMinDamage();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMinDamage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setMaxDamage of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_setMaxDamage00
static int tolua_CLuaInterface_CCharacter_setMaxDamage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  int newMaxDamage = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setMaxDamage'", NULL);
#endif
  {
   self->setMaxDamage(newMaxDamage);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setMaxDamage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getMaxDamage of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_getMaxDamage00
static int tolua_CLuaInterface_CCharacter_getMaxDamage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMaxDamage'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getMaxDamage();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMaxDamage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setArmor of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_setArmor00
static int tolua_CLuaInterface_CCharacter_setArmor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  int newArmor = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setArmor'", NULL);
#endif
  {
   self->setArmor(newArmor);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setArmor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setDamageModifierPoints of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_setDamageModifierPoints00
static int tolua_CLuaInterface_CCharacter_setDamageModifierPoints00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  int newDamageModifierPoints = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDamageModifierPoints'", NULL);
#endif
  {
   self->setDamageModifierPoints(newDamageModifierPoints);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setDamageModifierPoints'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setHitModifierPoints of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_setHitModifierPoints00
static int tolua_CLuaInterface_CCharacter_setHitModifierPoints00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  int newHitModifierPoints = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setHitModifierPoints'", NULL);
#endif
  {
   self->setHitModifierPoints(newHitModifierPoints);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setHitModifierPoints'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setEvadeModifierPoints of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_setEvadeModifierPoints00
static int tolua_CLuaInterface_CCharacter_setEvadeModifierPoints00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  int newEvadeModifierPoints = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setEvadeModifierPoints'", NULL);
#endif
  {
   self->setEvadeModifierPoints(newEvadeModifierPoints);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setEvadeModifierPoints'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBlockModifierPoints of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_setBlockModifierPoints00
static int tolua_CLuaInterface_CCharacter_setBlockModifierPoints00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  int newBlockModifierPoints = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBlockModifierPoints'", NULL);
#endif
  {
   self->setBlockModifierPoints(newBlockModifierPoints);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setBlockModifierPoints'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setMeleeCriticalModifierPoints of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_setMeleeCriticalModifierPoints00
static int tolua_CLuaInterface_CCharacter_setMeleeCriticalModifierPoints00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  int newMeleeCriticalModifierPoints = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setMeleeCriticalModifierPoints'", NULL);
#endif
  {
   self->setMeleeCriticalModifierPoints(newMeleeCriticalModifierPoints);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setMeleeCriticalModifierPoints'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setResistElementModifierPoints of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_setResistElementModifierPoints00
static int tolua_CLuaInterface_CCharacter_setResistElementModifierPoints00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  ElementType::ElementType elementType = ((ElementType::ElementType) (int)  tolua_tonumber(tolua_S,2,0));
  int newResistElementModifierPoints = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setResistElementModifierPoints'", NULL);
#endif
  {
   self->setResistElementModifierPoints(elementType,newResistElementModifierPoints);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setResistElementModifierPoints'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setResistAllModifierPoints of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_setResistAllModifierPoints00
static int tolua_CLuaInterface_CCharacter_setResistAllModifierPoints00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  int newResistAllModifierPoints = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setResistAllModifierPoints'", NULL);
#endif
  {
   self->setResistAllModifierPoints(newResistAllModifierPoints);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setResistAllModifierPoints'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setSpellEffectElementModifierPoints of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_setSpellEffectElementModifierPoints00
static int tolua_CLuaInterface_CCharacter_setSpellEffectElementModifierPoints00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  ElementType::ElementType elementType = ((ElementType::ElementType) (int)  tolua_tonumber(tolua_S,2,0));
  int newSpellEffectElementModifierPoints = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSpellEffectElementModifierPoints'", NULL);
#endif
  {
   self->setSpellEffectElementModifierPoints(elementType,newSpellEffectElementModifierPoints);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setSpellEffectElementModifierPoints'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setSpellEffectAllModifierPoints of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_setSpellEffectAllModifierPoints00
static int tolua_CLuaInterface_CCharacter_setSpellEffectAllModifierPoints00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  int newSpellEffectAllModifierPoints = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSpellEffectAllModifierPoints'", NULL);
#endif
  {
   self->setSpellEffectAllModifierPoints(newSpellEffectAllModifierPoints);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setSpellEffectAllModifierPoints'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setSpellCriticalModifierPoints of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_setSpellCriticalModifierPoints00
static int tolua_CLuaInterface_CCharacter_setSpellCriticalModifierPoints00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  int newSpellCriticalModifierPoints = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSpellCriticalModifierPoints'", NULL);
#endif
  {
   self->setSpellCriticalModifierPoints(newSpellCriticalModifierPoints);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setSpellCriticalModifierPoints'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBoundingBox of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_setBoundingBox00
static int tolua_CLuaInterface_CCharacter_setBoundingBox00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  int bbx = ((int)  tolua_tonumber(tolua_S,2,0));
  int bby = ((int)  tolua_tonumber(tolua_S,3,0));
  int bbw = ((int)  tolua_tonumber(tolua_S,4,0));
  int bbh = ((int)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBoundingBox'", NULL);
#endif
  {
   self->setBoundingBox(bbx,bby,bbw,bbh);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setBoundingBox'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setUseBoundingBox of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_setUseBoundingBox00
static int tolua_CLuaInterface_CCharacter_setUseBoundingBox00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  bool use = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setUseBoundingBox'", NULL);
#endif
  {
   self->setUseBoundingBox(use);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setUseBoundingBox'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addItemToLootTable of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_addItemToLootTable00
static int tolua_CLuaInterface_CCharacter_addItemToLootTable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Item",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  Item* item = ((Item*)  tolua_tousertype(tolua_S,2,0));
  double dropChance = ((double)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addItemToLootTable'", NULL);
#endif
  {
   self->addItemToLootTable(item,dropChance);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addItemToLootTable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setCoinDrop of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_setCoinDrop00
static int tolua_CLuaInterface_CCharacter_setCoinDrop00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  int minCoinDrop = ((int)  tolua_tonumber(tolua_S,2,0));
  int maxCoinDrop = ((int)  tolua_tonumber(tolua_S,3,0));
  double dropChance = ((double)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setCoinDrop'", NULL);
#endif
  {
   self->setCoinDrop(minCoinDrop,maxCoinDrop,dropChance);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setCoinDrop'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setPosition of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_setPosition00
static int tolua_CLuaInterface_CCharacter_setPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  int xpos = ((int)  tolua_tonumber(tolua_S,2,0));
  int ypos = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPosition'", NULL);
#endif
  {
   self->setPosition(xpos,ypos);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setDescription of class  Item */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_Item_setDescription00
static int tolua_CLuaInterface_Item_setDescription00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Item",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Item* self = (Item*)  tolua_tousertype(tolua_S,1,0);
  std::string description = ((std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDescription'", NULL);
#endif
  {
   self->setDescription(description);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setDescription'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setStats of class  Item */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_Item_setStats00
static int tolua_CLuaInterface_Item_setStats00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Item",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Item* self = (Item*)  tolua_tousertype(tolua_S,1,0);
  StatsType::StatsType statsType = ((StatsType::StatsType) (int)  tolua_tonumber(tolua_S,2,0));
  int amount = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setStats'", NULL);
#endif
  {
   self->setStats(statsType,amount);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setStats'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setResistElementModifierPoints of class  Item */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_Item_setResistElementModifierPoints00
static int tolua_CLuaInterface_Item_setResistElementModifierPoints00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Item",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Item* self = (Item*)  tolua_tousertype(tolua_S,1,0);
  ElementType::ElementType elementType = ((ElementType::ElementType) (int)  tolua_tonumber(tolua_S,2,0));
  int resistModifierPoints = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setResistElementModifierPoints'", NULL);
#endif
  {
   self->setResistElementModifierPoints(elementType,resistModifierPoints);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setResistElementModifierPoints'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setSpellEffectElementModifierPoints of class  Item */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_Item_setSpellEffectElementModifierPoints00
static int tolua_CLuaInterface_Item_setSpellEffectElementModifierPoints00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Item",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Item* self = (Item*)  tolua_tousertype(tolua_S,1,0);
  ElementType::ElementType elementType = ((ElementType::ElementType) (int)  tolua_tonumber(tolua_S,2,0));
  int spellEffectElementModifierPoints = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSpellEffectElementModifierPoints'", NULL);
#endif
  {
   self->setSpellEffectElementModifierPoints(elementType,spellEffectElementModifierPoints);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setSpellEffectElementModifierPoints'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setMinDamage of class  Item */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_Item_setMinDamage00
static int tolua_CLuaInterface_Item_setMinDamage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Item",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Item* self = (Item*)  tolua_tousertype(tolua_S,1,0);
  int minDamage = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setMinDamage'", NULL);
#endif
  {
   self->setMinDamage(minDamage);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setMinDamage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setMaxDamage of class  Item */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_Item_setMaxDamage00
static int tolua_CLuaInterface_Item_setMaxDamage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Item",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Item* self = (Item*)  tolua_tousertype(tolua_S,1,0);
  int maxDamage = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setMaxDamage'", NULL);
#endif
  {
   self->setMaxDamage(maxDamage);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setMaxDamage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setLevelReq of class  Item */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_Item_setLevelReq00
static int tolua_CLuaInterface_Item_setLevelReq00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Item",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Item* self = (Item*)  tolua_tousertype(tolua_S,1,0);
  int levelReq = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setLevelReq'", NULL);
#endif
  {
   self->setLevelReq(levelReq);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setLevelReq'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setValue of class  Item */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_Item_setValue00
static int tolua_CLuaInterface_Item_setValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Item",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Item* self = (Item*)  tolua_tousertype(tolua_S,1,0);
  int newValue = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setValue'", NULL);
#endif
  {
   self->setValue(newValue);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setValue'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setSpellCharges of class  Item */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_Item_setSpellCharges00
static int tolua_CLuaInterface_Item_setSpellCharges00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Item",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Item* self = (Item*)  tolua_tousertype(tolua_S,1,0);
  int newSpellCharges = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSpellCharges'", NULL);
#endif
  {
   self->setSpellCharges(newSpellCharges);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setSpellCharges'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setSpell of class  Item */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_Item_setSpell00
static int tolua_CLuaInterface_Item_setSpell00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Item",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CSpell",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Item* self = (Item*)  tolua_tousertype(tolua_S,1,0);
  CSpell* newSpell = ((CSpell*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSpell'", NULL);
#endif
  {
   self->setSpell(newSpell);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setSpell'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setPosition of class  InteractionPoint */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_InteractionPoint_setPosition00
static int tolua_CLuaInterface_InteractionPoint_setPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"InteractionPoint",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  InteractionPoint* self = (InteractionPoint*)  tolua_tousertype(tolua_S,1,0);
  int posX = ((int)  tolua_tonumber(tolua_S,2,0));
  int posY = ((int)  tolua_tonumber(tolua_S,3,0));
  int width = ((int)  tolua_tonumber(tolua_S,4,0));
  int height = ((int)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPosition'", NULL);
#endif
  {
   self->setPosition(posX,posY,width,height);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setInteractionTexture of class  InteractionPoint */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_InteractionPoint_setInteractionTexture00
static int tolua_CLuaInterface_InteractionPoint_setInteractionTexture00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"InteractionPoint",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  InteractionPoint* self = (InteractionPoint*)  tolua_tousertype(tolua_S,1,0);
  std::string texturename = ((std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setInteractionTexture'", NULL);
#endif
  {
   self->setInteractionTexture(texturename);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setInteractionTexture'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBackgroundTexture of class  InteractionPoint */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_InteractionPoint_setBackgroundTexture00
static int tolua_CLuaInterface_InteractionPoint_setBackgroundTexture00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"InteractionPoint",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  InteractionPoint* self = (InteractionPoint*)  tolua_tousertype(tolua_S,1,0);
  std::string texturename = ((std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBackgroundTexture'", NULL);
#endif
  {
   self->setBackgroundTexture(texturename);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setBackgroundTexture'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setInteractionCode of class  InteractionPoint */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_InteractionPoint_setInteractionCode00
static int tolua_CLuaInterface_InteractionPoint_setInteractionCode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"InteractionPoint",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  InteractionPoint* self = (InteractionPoint*)  tolua_tousertype(tolua_S,1,0);
  std::string interactionCode = ((std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setInteractionCode'", NULL);
#endif
  {
   self->setInteractionCode(interactionCode);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setInteractionCode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setExecuteText of class  LuaCallIndirection */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_LuaCallIndirection_setExecuteText00
static int tolua_CLuaInterface_LuaCallIndirection_setExecuteText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaCallIndirection",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  LuaCallIndirection* self = (LuaCallIndirection*)  tolua_tousertype(tolua_S,1,0);
  std::string text = ((std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setExecuteText'", NULL);
#endif
  {
   self->setExecuteText(text);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setExecuteText'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addOnDieEventHandler of class  CNPC */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CNPC_addOnDieEventHandler00
static int tolua_CLuaInterface_CNPC_addOnDieEventHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CNPC",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CallIndirection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CNPC* self = (CNPC*)  tolua_tousertype(tolua_S,1,0);
  CallIndirection* eventHandler = ((CallIndirection*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addOnDieEventHandler'", NULL);
#endif
  {
   self->addOnDieEventHandler(eventHandler);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addOnDieEventHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAttitude of class  CNPC */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CNPC_setAttitude00
static int tolua_CLuaInterface_CNPC_setAttitude00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CNPC",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CNPC* self = (CNPC*)  tolua_tousertype(tolua_S,1,0);
  Attitude::Attitude attitude = ((Attitude::Attitude) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAttitude'", NULL);
#endif
  {
   self->setAttitude(attitude);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAttitude'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSaveText of class  Player */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_Player_getSaveText00
static int tolua_CLuaInterface_Player_getSaveText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Player",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getSaveText'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->getSaveText();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSaveText'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setText of class  TextWindow */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_TextWindow_setText00
static int tolua_CLuaInterface_TextWindow_setText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TextWindow",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TextWindow* self = (TextWindow*)  tolua_tousertype(tolua_S,1,0);
  std::string text = ((std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setText'", NULL);
#endif
  {
   self->setText(text);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setText'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAutocloseTime of class  TextWindow */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_TextWindow_setAutocloseTime00
static int tolua_CLuaInterface_TextWindow_setAutocloseTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TextWindow",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TextWindow* self = (TextWindow*)  tolua_tousertype(tolua_S,1,0);
  int autocloseTime = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAutocloseTime'", NULL);
#endif
  {
   self->setAutocloseTime(autocloseTime);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAutocloseTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setPosition of class  TextWindow */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_TextWindow_setPosition00
static int tolua_CLuaInterface_TextWindow_setPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TextWindow",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TextWindow* self = (TextWindow*)  tolua_tousertype(tolua_S,1,0);
  PositionType::PositionType tolua_var_1 = ((PositionType::PositionType) (int)  tolua_tonumber(tolua_S,2,0));
  int x = ((int)  tolua_tonumber(tolua_S,3,0));
  int y = ((int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPosition'", NULL);
#endif
  {
   self->setPosition(tolua_var_1,x,y);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setVisible of class  Shop */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_Shop_setVisible00
static int tolua_CLuaInterface_Shop_setVisible00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Shop",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Shop* self = (Shop*)  tolua_tousertype(tolua_S,1,0);
  bool newVisible = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setVisible'", NULL);
#endif
  {
   self->setVisible(newVisible);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setVisible'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addItem of class  Shop */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_Shop_addItem00
static int tolua_CLuaInterface_Shop_addItem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Shop",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Item",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Shop* self = (Shop*)  tolua_tousertype(tolua_S,1,0);
  Item* item = ((Item*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addItem'", NULL);
#endif
  {
   self->addItem(item);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addItem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setCastTime of class  ConfigurableSpell */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_ConfigurableSpell_setCastTime00
static int tolua_CLuaInterface_ConfigurableSpell_setCastTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ConfigurableSpell",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ConfigurableSpell* self = (ConfigurableSpell*)  tolua_tousertype(tolua_S,1,0);
  int newCastTime = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setCastTime'", NULL);
#endif
  {
   self->setCastTime(newCastTime);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setCastTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setCooldown of class  ConfigurableSpell */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_ConfigurableSpell_setCooldown00
static int tolua_CLuaInterface_ConfigurableSpell_setCooldown00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ConfigurableSpell",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ConfigurableSpell* self = (ConfigurableSpell*)  tolua_tousertype(tolua_S,1,0);
  int newCooldown = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setCooldown'", NULL);
#endif
  {
   self->setCooldown(newCooldown);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setCooldown'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setManaCost of class  ConfigurableSpell */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_ConfigurableSpell_setManaCost00
static int tolua_CLuaInterface_ConfigurableSpell_setManaCost00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ConfigurableSpell",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ConfigurableSpell* self = (ConfigurableSpell*)  tolua_tousertype(tolua_S,1,0);
  int newManaCost = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setManaCost'", NULL);
#endif
  {
   self->setManaCost(newManaCost);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setManaCost'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setName of class  ConfigurableSpell */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_ConfigurableSpell_setName00
static int tolua_CLuaInterface_ConfigurableSpell_setName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ConfigurableSpell",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ConfigurableSpell* self = (ConfigurableSpell*)  tolua_tousertype(tolua_S,1,0);
  std::string newName = ((std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setName'", NULL);
#endif
  {
   self->setName(newName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setInfo of class  ConfigurableSpell */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_ConfigurableSpell_setInfo00
static int tolua_CLuaInterface_ConfigurableSpell_setInfo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ConfigurableSpell",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ConfigurableSpell* self = (ConfigurableSpell*)  tolua_tousertype(tolua_S,1,0);
  std::string newInfo = ((std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setInfo'", NULL);
#endif
  {
   self->setInfo(newInfo);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setInfo'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setSpellSymbol of class  ConfigurableSpell */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_ConfigurableSpell_setSpellSymbol00
static int tolua_CLuaInterface_ConfigurableSpell_setSpellSymbol00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ConfigurableSpell",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ConfigurableSpell* self = (ConfigurableSpell*)  tolua_tousertype(tolua_S,1,0);
  std::string symbolFile = ((std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSpellSymbol'", NULL);
#endif
  {
   self->setSpellSymbol(symbolFile);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setSpellSymbol'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setDirectDamage of class  GeneralDamageSpell */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_GeneralDamageSpell_setDirectDamage00
static int tolua_CLuaInterface_GeneralDamageSpell_setDirectDamage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GeneralDamageSpell",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GeneralDamageSpell* self = (GeneralDamageSpell*)  tolua_tousertype(tolua_S,1,0);
  int newMinDirectDamage = ((int)  tolua_tonumber(tolua_S,2,0));
  int newMaxDirectDamage = ((int)  tolua_tonumber(tolua_S,3,0));
  ElementType::ElementType newElementDirect = ((ElementType::ElementType) (int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDirectDamage'", NULL);
#endif
  {
   self->setDirectDamage(newMinDirectDamage,newMaxDirectDamage,newElementDirect);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setDirectDamage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setContinuousDamage of class  GeneralDamageSpell */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_GeneralDamageSpell_setContinuousDamage00
static int tolua_CLuaInterface_GeneralDamageSpell_setContinuousDamage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GeneralDamageSpell",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GeneralDamageSpell* self = (GeneralDamageSpell*)  tolua_tousertype(tolua_S,1,0);
  double newMinContDamagePerSec = ((double)  tolua_tonumber(tolua_S,2,0));
  double newMaxContDamagePerSec = ((double)  tolua_tonumber(tolua_S,3,0));
  int newContDamageTime = ((int)  tolua_tonumber(tolua_S,4,0));
  ElementType::ElementType newContDamageElement = ((ElementType::ElementType) (int)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setContinuousDamage'", NULL);
#endif
  {
   self->setContinuousDamage(newMinContDamagePerSec,newMaxContDamagePerSec,newContDamageTime,newContDamageElement);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setContinuousDamage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setNumAnimations of class  GeneralRayDamageSpell */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_GeneralRayDamageSpell_setNumAnimations00
static int tolua_CLuaInterface_GeneralRayDamageSpell_setNumAnimations00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GeneralRayDamageSpell",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GeneralRayDamageSpell* self = (GeneralRayDamageSpell*)  tolua_tousertype(tolua_S,1,0);
  int count = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setNumAnimations'", NULL);
#endif
  {
   self->setNumAnimations(count);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setNumAnimations'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAnimationTexture of class  GeneralRayDamageSpell */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_GeneralRayDamageSpell_setAnimationTexture00
static int tolua_CLuaInterface_GeneralRayDamageSpell_setAnimationTexture00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GeneralRayDamageSpell",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GeneralRayDamageSpell* self = (GeneralRayDamageSpell*)  tolua_tousertype(tolua_S,1,0);
  int num = ((int)  tolua_tonumber(tolua_S,2,0));
  std::string filename = ((std::string)  tolua_tocppstring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAnimationTexture'", NULL);
#endif
  {
   self->setAnimationTexture(num,filename);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAnimationTexture'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setMoveSpeed of class  GeneralBoltDamageSpell */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_GeneralBoltDamageSpell_setMoveSpeed00
static int tolua_CLuaInterface_GeneralBoltDamageSpell_setMoveSpeed00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GeneralBoltDamageSpell",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GeneralBoltDamageSpell* self = (GeneralBoltDamageSpell*)  tolua_tousertype(tolua_S,1,0);
  int newMoveSpeed = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setMoveSpeed'", NULL);
#endif
  {
   self->setMoveSpeed(newMoveSpeed);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setMoveSpeed'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setExpireTime of class  GeneralBoltDamageSpell */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_GeneralBoltDamageSpell_setExpireTime00
static int tolua_CLuaInterface_GeneralBoltDamageSpell_setExpireTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GeneralBoltDamageSpell",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GeneralBoltDamageSpell* self = (GeneralBoltDamageSpell*)  tolua_tousertype(tolua_S,1,0);
  int newExpireTime = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setExpireTime'", NULL);
#endif
  {
   self->setExpireTime(newExpireTime);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setExpireTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setNumAnimations of class  GeneralBoltDamageSpell */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_GeneralBoltDamageSpell_setNumAnimations00
static int tolua_CLuaInterface_GeneralBoltDamageSpell_setNumAnimations00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GeneralBoltDamageSpell",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GeneralBoltDamageSpell* self = (GeneralBoltDamageSpell*)  tolua_tousertype(tolua_S,1,0);
  int count = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setNumAnimations'", NULL);
#endif
  {
   self->setNumAnimations(count);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setNumAnimations'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAnimationTexture of class  GeneralBoltDamageSpell */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_GeneralBoltDamageSpell_setAnimationTexture00
static int tolua_CLuaInterface_GeneralBoltDamageSpell_setAnimationTexture00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GeneralBoltDamageSpell",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GeneralBoltDamageSpell* self = (GeneralBoltDamageSpell*)  tolua_tousertype(tolua_S,1,0);
  int num = ((int)  tolua_tonumber(tolua_S,2,0));
  std::string filename = ((std::string)  tolua_tocppstring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAnimationTexture'", NULL);
#endif
  {
   self->setAnimationTexture(num,filename);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAnimationTexture'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setEffectType of class  GeneralHealingSpell */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_GeneralHealingSpell_setEffectType00
static int tolua_CLuaInterface_GeneralHealingSpell_setEffectType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GeneralHealingSpell",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GeneralHealingSpell* self = (GeneralHealingSpell*)  tolua_tousertype(tolua_S,1,0);
  EffectType::EffectType newEffectType = ((EffectType::EffectType) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setEffectType'", NULL);
#endif
  {
   self->setEffectType(newEffectType);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setEffectType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setHealEffect of class  GeneralHealingSpell */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_GeneralHealingSpell_setHealEffect00
static int tolua_CLuaInterface_GeneralHealingSpell_setHealEffect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GeneralHealingSpell",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GeneralHealingSpell* self = (GeneralHealingSpell*)  tolua_tousertype(tolua_S,1,0);
  int healEffectMin = ((int)  tolua_tonumber(tolua_S,2,0));
  int healEffectMax = ((int)  tolua_tonumber(tolua_S,3,0));
  ElementType::ElementType healEffectElement = ((ElementType::ElementType) (int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setHealEffect'", NULL);
#endif
  {
   self->setHealEffect(healEffectMin,healEffectMax,healEffectElement);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setHealEffect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setEffectType of class  GeneralBuffSpell */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_GeneralBuffSpell_setEffectType00
static int tolua_CLuaInterface_GeneralBuffSpell_setEffectType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GeneralBuffSpell",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GeneralBuffSpell* self = (GeneralBuffSpell*)  tolua_tousertype(tolua_S,1,0);
  EffectType::EffectType newEffectType = ((EffectType::EffectType) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setEffectType'", NULL);
#endif
  {
   self->setEffectType(newEffectType);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setEffectType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setDuration of class  GeneralBuffSpell */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_GeneralBuffSpell_setDuration00
static int tolua_CLuaInterface_GeneralBuffSpell_setDuration00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GeneralBuffSpell",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GeneralBuffSpell* self = (GeneralBuffSpell*)  tolua_tousertype(tolua_S,1,0);
  int newDuration = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDuration'", NULL);
#endif
  {
   self->setDuration(newDuration);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setDuration'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setStats of class  GeneralBuffSpell */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_GeneralBuffSpell_setStats00
static int tolua_CLuaInterface_GeneralBuffSpell_setStats00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GeneralBuffSpell",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GeneralBuffSpell* self = (GeneralBuffSpell*)  tolua_tousertype(tolua_S,1,0);
  StatsType::StatsType statsType = ((StatsType::StatsType) (int)  tolua_tonumber(tolua_S,2,0));
  int amount = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setStats'", NULL);
#endif
  {
   self->setStats(statsType,amount);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setStats'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setResistElementModifierPoints of class  GeneralBuffSpell */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_GeneralBuffSpell_setResistElementModifierPoints00
static int tolua_CLuaInterface_GeneralBuffSpell_setResistElementModifierPoints00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GeneralBuffSpell",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GeneralBuffSpell* self = (GeneralBuffSpell*)  tolua_tousertype(tolua_S,1,0);
  ElementType::ElementType elementType = ((ElementType::ElementType) (int)  tolua_tonumber(tolua_S,2,0));
  int resistModifierPoints = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setResistElementModifierPoints'", NULL);
#endif
  {
   self->setResistElementModifierPoints(elementType,resistModifierPoints);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setResistElementModifierPoints'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setSpellEffectElementModifierPoints of class  GeneralBuffSpell */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_GeneralBuffSpell_setSpellEffectElementModifierPoints00
static int tolua_CLuaInterface_GeneralBuffSpell_setSpellEffectElementModifierPoints00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GeneralBuffSpell",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GeneralBuffSpell* self = (GeneralBuffSpell*)  tolua_tousertype(tolua_S,1,0);
  ElementType::ElementType elementType = ((ElementType::ElementType) (int)  tolua_tonumber(tolua_S,2,0));
  int spellEffectElementModifierPoints = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSpellEffectElementModifierPoints'", NULL);
#endif
  {
   self->setSpellEffectElementModifierPoints(elementType,spellEffectElementModifierPoints);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setSpellEffectElementModifierPoints'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DawnInterface::createNewMobType */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_DawnInterface_createNewMobType00
static int tolua_CLuaInterface_DawnInterface_createNewMobType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_iscppstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  std::string typeID = ((std::string)  tolua_tocppstring(tolua_S,1,0));
  {
   CCharacter* tolua_ret = (CCharacter*)  DawnInterface::createNewMobType(typeID);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCharacter");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createNewMobType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DawnInterface::createNewItem */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_DawnInterface_createNewItem00
static int tolua_CLuaInterface_DawnInterface_createNewItem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_iscppstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,8,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,9,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,10,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  std::string name = ((std::string)  tolua_tocppstring(tolua_S,1,0));
  int sizeX = ((int)  tolua_tonumber(tolua_S,2,0));
  int sizeY = ((int)  tolua_tonumber(tolua_S,3,0));
  std::string symbolFile = ((std::string)  tolua_tocppstring(tolua_S,4,0));
  ItemQuality::ItemQuality itemQuality = ((ItemQuality::ItemQuality) (int)  tolua_tonumber(tolua_S,5,0));
  EquipPosition::EquipPosition equipPosition = ((EquipPosition::EquipPosition) (int)  tolua_tonumber(tolua_S,6,0));
  ItemType::ItemType itemType = ((ItemType::ItemType) (int)  tolua_tonumber(tolua_S,7,0));
  ArmorType::ArmorType armorType = ((ArmorType::ArmorType) (int)  tolua_tonumber(tolua_S,8,0));
  WeaponType::WeaponType weaponType = ((WeaponType::WeaponType) (int)  tolua_tonumber(tolua_S,9,0));
  {
   Item* tolua_ret = (Item*)  DawnInterface::createNewItem(name,sizeX,sizeY,symbolFile,itemQuality,equipPosition,itemType,armorType,weaponType);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Item");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createNewItem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DawnInterface::giveItemToPlayer */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_DawnInterface_giveItemToPlayer00
static int tolua_CLuaInterface_DawnInterface_giveItemToPlayer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Item",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Item* item = ((Item*)  tolua_tousertype(tolua_S,1,0));
  {
   DawnInterface::giveItemToPlayer(item);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'giveItemToPlayer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DawnInterface::addMobSpawnPoint */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_DawnInterface_addMobSpawnPoint00
static int tolua_CLuaInterface_DawnInterface_addMobSpawnPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_iscppstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  std::string mobID = ((std::string)  tolua_tocppstring(tolua_S,1,0));
  int x_pos = ((int)  tolua_tonumber(tolua_S,2,0));
  int y_pos = ((int)  tolua_tonumber(tolua_S,3,0));
  int respawn_rate = ((int)  tolua_tonumber(tolua_S,4,0));
  int do_respawn = ((int)  tolua_tonumber(tolua_S,5,0));
  {
   CNPC* tolua_ret = (CNPC*)  DawnInterface::addMobSpawnPoint(mobID,x_pos,y_pos,respawn_rate,do_respawn);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CNPC");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addMobSpawnPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DawnInterface::removeMobSpawnPoint */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_DawnInterface_removeMobSpawnPoint00
static int tolua_CLuaInterface_DawnInterface_removeMobSpawnPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CNPC",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CNPC* mobSpawnPoint = ((CNPC*)  tolua_tousertype(tolua_S,1,0));
  {
   DawnInterface::removeMobSpawnPoint(mobSpawnPoint);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeMobSpawnPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DawnInterface::createGeneralRayDamageSpell */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_DawnInterface_createGeneralRayDamageSpell00
static int tolua_CLuaInterface_DawnInterface_createGeneralRayDamageSpell00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   GeneralRayDamageSpell* tolua_ret = (GeneralRayDamageSpell*)  DawnInterface::createGeneralRayDamageSpell();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"GeneralRayDamageSpell");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createGeneralRayDamageSpell'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DawnInterface::createGeneralBoltDamageSpell */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_DawnInterface_createGeneralBoltDamageSpell00
static int tolua_CLuaInterface_DawnInterface_createGeneralBoltDamageSpell00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   GeneralBoltDamageSpell* tolua_ret = (GeneralBoltDamageSpell*)  DawnInterface::createGeneralBoltDamageSpell();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"GeneralBoltDamageSpell");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createGeneralBoltDamageSpell'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DawnInterface::createGeneralHealingSpell */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_DawnInterface_createGeneralHealingSpell00
static int tolua_CLuaInterface_DawnInterface_createGeneralHealingSpell00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   GeneralHealingSpell* tolua_ret = (GeneralHealingSpell*)  DawnInterface::createGeneralHealingSpell();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"GeneralHealingSpell");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createGeneralHealingSpell'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DawnInterface::createGeneralBuffSpell */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_DawnInterface_createGeneralBuffSpell00
static int tolua_CLuaInterface_DawnInterface_createGeneralBuffSpell00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   GeneralBuffSpell* tolua_ret = (GeneralBuffSpell*)  DawnInterface::createGeneralBuffSpell();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"GeneralBuffSpell");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createGeneralBuffSpell'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DawnInterface::inscribeSpellInPlayerSpellbook */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_DawnInterface_inscribeSpellInPlayerSpellbook00
static int tolua_CLuaInterface_DawnInterface_inscribeSpellInPlayerSpellbook00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CSpell",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CSpell* inscribedSpell = ((CSpell*)  tolua_tousertype(tolua_S,1,0));
  {
   DawnInterface::inscribeSpellInPlayerSpellbook(inscribedSpell);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'inscribeSpellInPlayerSpellbook'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DawnInterface::addInteractionPoint */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_DawnInterface_addInteractionPoint00
static int tolua_CLuaInterface_DawnInterface_addInteractionPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   InteractionPoint* tolua_ret = (InteractionPoint*)  DawnInterface::addInteractionPoint();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"InteractionPoint");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addInteractionPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DawnInterface::addCharacterInteractionPoint */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_DawnInterface_addCharacterInteractionPoint00
static int tolua_CLuaInterface_DawnInterface_addCharacterInteractionPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCharacter* character = ((CCharacter*)  tolua_tousertype(tolua_S,1,0));
  {
   InteractionPoint* tolua_ret = (InteractionPoint*)  DawnInterface::addCharacterInteractionPoint(character);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"InteractionPoint");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addCharacterInteractionPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DawnInterface::createTextWindow */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_DawnInterface_createTextWindow00
static int tolua_CLuaInterface_DawnInterface_createTextWindow00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   TextWindow* tolua_ret = (TextWindow*)  DawnInterface::createTextWindow();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"TextWindow");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createTextWindow'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DawnInterface::removeInteractionPoint */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_DawnInterface_removeInteractionPoint00
static int tolua_CLuaInterface_DawnInterface_removeInteractionPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"InteractionPoint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  InteractionPoint* pointToRemove = ((InteractionPoint*)  tolua_tousertype(tolua_S,1,0));
  {
   DawnInterface::removeInteractionPoint(pointToRemove);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeInteractionPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DawnInterface::createEventHandler */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_DawnInterface_createEventHandler00
static int tolua_CLuaInterface_DawnInterface_createEventHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   LuaCallIndirection* tolua_ret = (LuaCallIndirection*)  DawnInterface::createEventHandler();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"LuaCallIndirection");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createEventHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DawnInterface::addQuest */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_DawnInterface_addQuest00
static int tolua_CLuaInterface_DawnInterface_addQuest00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_iscppstring(tolua_S,1,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  std::string questName = ((std::string)  tolua_tocppstring(tolua_S,1,0));
  std::string questDescription = ((std::string)  tolua_tocppstring(tolua_S,2,0));
  {
   DawnInterface::addQuest(questName,questDescription);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addQuest'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DawnInterface::removeQuest */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_DawnInterface_removeQuest00
static int tolua_CLuaInterface_DawnInterface_removeQuest00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_iscppstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  std::string questName = ((std::string)  tolua_tocppstring(tolua_S,1,0));
  {
   DawnInterface::removeQuest(questName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeQuest'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DawnInterface::changeQuestDescription */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_DawnInterface_changeQuestDescription00
static int tolua_CLuaInterface_DawnInterface_changeQuestDescription00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_iscppstring(tolua_S,1,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  std::string questName = ((std::string)  tolua_tocppstring(tolua_S,1,0));
  std::string newDescription = ((std::string)  tolua_tocppstring(tolua_S,2,0));
  {
   DawnInterface::changeQuestDescription(questName,newDescription);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'changeQuestDescription'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DawnInterface::addShop */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_DawnInterface_addShop00
static int tolua_CLuaInterface_DawnInterface_addShop00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Shop* tolua_ret = (Shop*)  DawnInterface::addShop();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Shop");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addShop'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DawnInterface::getPlayer */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_DawnInterface_getPlayer00
static int tolua_CLuaInterface_DawnInterface_getPlayer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Player* tolua_ret = (Player*)  DawnInterface::getPlayer();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Player");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPlayer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DawnInterface::getQuestSaveText */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_DawnInterface_getQuestSaveText00
static int tolua_CLuaInterface_DawnInterface_getQuestSaveText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   std::string tolua_ret = (std::string)  DawnInterface::getQuestSaveText();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getQuestSaveText'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DawnInterface::getInventorySaveText */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_DawnInterface_getInventorySaveText00
static int tolua_CLuaInterface_DawnInterface_getInventorySaveText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   std::string tolua_ret = (std::string)  DawnInterface::getInventorySaveText();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getInventorySaveText'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DawnInterface::restoreItemInBackpack */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_DawnInterface_restoreItemInBackpack00
static int tolua_CLuaInterface_DawnInterface_restoreItemInBackpack00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Item",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Item* item = ((Item*)  tolua_tousertype(tolua_S,1,0));
  int inventoryPosX = ((int)  tolua_tonumber(tolua_S,2,0));
  int inventoryPosY = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   DawnInterface::restoreItemInBackpack(item,inventoryPosX,inventoryPosY);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'restoreItemInBackpack'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DawnInterface::restoreWieldItem */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_DawnInterface_restoreWieldItem00
static int tolua_CLuaInterface_DawnInterface_restoreWieldItem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Item",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int slot = ((int)  tolua_tonumber(tolua_S,1,0));
  Item* item = ((Item*)  tolua_tousertype(tolua_S,2,0));
  {
   DawnInterface::restoreWieldItem(slot,item);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'restoreWieldItem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DawnInterface::restoreGroundLootItem */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_DawnInterface_restoreGroundLootItem00
static int tolua_CLuaInterface_DawnInterface_restoreGroundLootItem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Item",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Item* item = ((Item*)  tolua_tousertype(tolua_S,1,0));
  int xPos = ((int)  tolua_tonumber(tolua_S,2,0));
  int yPos = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   DawnInterface::restoreGroundLootItem(item,xPos,yPos);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'restoreGroundLootItem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DawnInterface::restoreGroundGold */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_DawnInterface_restoreGroundGold00
static int tolua_CLuaInterface_DawnInterface_restoreGroundGold00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int amount = ((int)  tolua_tonumber(tolua_S,1,0));
  int xPos = ((int)  tolua_tonumber(tolua_S,2,0));
  int yPos = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   DawnInterface::restoreGroundGold(amount,xPos,yPos);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'restoreGroundGold'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DawnInterface::setCurrentZone */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_DawnInterface_setCurrentZone00
static int tolua_CLuaInterface_DawnInterface_setCurrentZone00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_iscppstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  std::string zoneName = ((std::string)  tolua_tocppstring(tolua_S,1,0));
  {
   DawnInterface::setCurrentZone(zoneName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setCurrentZone'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DawnInterface::getAllZonesSaveText */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_DawnInterface_getAllZonesSaveText00
static int tolua_CLuaInterface_DawnInterface_getAllZonesSaveText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   std::string tolua_ret = (std::string)  DawnInterface::getAllZonesSaveText();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAllZonesSaveText'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DawnInterface::getItemReferenceRestore */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_DawnInterface_getItemReferenceRestore00
static int tolua_CLuaInterface_DawnInterface_getItemReferenceRestore00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCharacter* character = ((CCharacter*)  tolua_tousertype(tolua_S,1,0));
  {
   std::string tolua_ret = (std::string)  DawnInterface::getItemReferenceRestore(character);
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getItemReferenceRestore'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DawnInterface::getItemReferenceRestore */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_DawnInterface_getItemReferenceRestore01
static int tolua_CLuaInterface_DawnInterface_getItemReferenceRestore01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"InteractionPoint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  InteractionPoint* interactionPoint = ((InteractionPoint*)  tolua_tousertype(tolua_S,1,0));
  {
   std::string tolua_ret = (std::string)  DawnInterface::getItemReferenceRestore(interactionPoint);
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_CLuaInterface_DawnInterface_getItemReferenceRestore00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: DawnInterface::getItemReferenceRestore */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_DawnInterface_getItemReferenceRestore02
static int tolua_CLuaInterface_DawnInterface_getItemReferenceRestore02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Shop",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  Shop* shop = ((Shop*)  tolua_tousertype(tolua_S,1,0));
  {
   std::string tolua_ret = (std::string)  DawnInterface::getItemReferenceRestore(shop);
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_CLuaInterface_DawnInterface_getItemReferenceRestore01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: DawnInterface::getItemReferenceRestore */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_DawnInterface_getItemReferenceRestore03
static int tolua_CLuaInterface_DawnInterface_getItemReferenceRestore03(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CallIndirection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CallIndirection* eventHandler = ((CallIndirection*)  tolua_tousertype(tolua_S,1,0));
  {
   std::string tolua_ret = (std::string)  DawnInterface::getItemReferenceRestore(eventHandler);
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_CLuaInterface_DawnInterface_getItemReferenceRestore02(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: DawnInterface::getItemReferenceRestore */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_DawnInterface_getItemReferenceRestore04
static int tolua_CLuaInterface_DawnInterface_getItemReferenceRestore04(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TextWindow",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  TextWindow* textWindow = ((TextWindow*)  tolua_tousertype(tolua_S,1,0));
  {
   std::string tolua_ret = (std::string)  DawnInterface::getItemReferenceRestore(textWindow);
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_CLuaInterface_DawnInterface_getItemReferenceRestore03(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: DawnInterface::restoreCharacterReference */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_DawnInterface_restoreCharacterReference00
static int tolua_CLuaInterface_DawnInterface_restoreCharacterReference00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_iscppstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  std::string zoneName = ((std::string)  tolua_tocppstring(tolua_S,1,0));
  int posInArray = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   CCharacter* tolua_ret = (CCharacter*)  DawnInterface::restoreCharacterReference(zoneName,posInArray);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCharacter");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'restoreCharacterReference'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DawnInterface::restoreInteractionPointReference */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_DawnInterface_restoreInteractionPointReference00
static int tolua_CLuaInterface_DawnInterface_restoreInteractionPointReference00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_iscppstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  std::string zoneName = ((std::string)  tolua_tocppstring(tolua_S,1,0));
  int posInArray = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   InteractionPoint* tolua_ret = (InteractionPoint*)  DawnInterface::restoreInteractionPointReference(zoneName,posInArray);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"InteractionPoint");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'restoreInteractionPointReference'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DawnInterface::restoreEventHandlerReference */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_DawnInterface_restoreEventHandlerReference00
static int tolua_CLuaInterface_DawnInterface_restoreEventHandlerReference00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_iscppstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  std::string zoneName = ((std::string)  tolua_tocppstring(tolua_S,1,0));
  int posInArray = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   CallIndirection* tolua_ret = (CallIndirection*)  DawnInterface::restoreEventHandlerReference(zoneName,posInArray);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CallIndirection");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'restoreEventHandlerReference'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_CLuaInterface_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_constant(tolua_S,"STOP",STOP);
  tolua_constant(tolua_S,"N",N);
  tolua_constant(tolua_S,"NE",NE);
  tolua_constant(tolua_S,"E",E);
  tolua_constant(tolua_S,"SE",SE);
  tolua_constant(tolua_S,"S",S);
  tolua_constant(tolua_S,"SW",SW);
  tolua_constant(tolua_S,"W",W);
  tolua_constant(tolua_S,"NW",NW);
  tolua_module(tolua_S,"ActivityType",0);
  tolua_beginmodule(tolua_S,"ActivityType");
   tolua_constant(tolua_S,"Walking",ActivityType::Walking);
   tolua_constant(tolua_S,"Casting",ActivityType::Casting);
   tolua_constant(tolua_S,"Attacking",ActivityType::Attacking);
   tolua_constant(tolua_S,"Count",ActivityType::Count);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"Attitude",0);
  tolua_beginmodule(tolua_S,"Attitude");
   tolua_constant(tolua_S,"FRIENDLY",Attitude::FRIENDLY);
   tolua_constant(tolua_S,"NEUTRAL",Attitude::NEUTRAL);
   tolua_constant(tolua_S,"HOSTILE",Attitude::HOSTILE);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCharacter","CCharacter","",NULL);
  tolua_beginmodule(tolua_S,"CCharacter");
   tolua_function(tolua_S,"baseOnType",tolua_CLuaInterface_CCharacter_baseOnType00);
   tolua_function(tolua_S,"setStrength",tolua_CLuaInterface_CCharacter_setStrength00);
   tolua_function(tolua_S,"getStrength",tolua_CLuaInterface_CCharacter_getStrength00);
   tolua_function(tolua_S,"modifyStrength",tolua_CLuaInterface_CCharacter_modifyStrength00);
   tolua_function(tolua_S,"setDexterity",tolua_CLuaInterface_CCharacter_setDexterity00);
   tolua_function(tolua_S,"getDexterity",tolua_CLuaInterface_CCharacter_getDexterity00);
   tolua_function(tolua_S,"modifyDexterity",tolua_CLuaInterface_CCharacter_modifyDexterity00);
   tolua_function(tolua_S,"setVitality",tolua_CLuaInterface_CCharacter_setVitality00);
   tolua_function(tolua_S,"getVitality",tolua_CLuaInterface_CCharacter_getVitality00);
   tolua_function(tolua_S,"modifyVitality",tolua_CLuaInterface_CCharacter_modifyVitality00);
   tolua_function(tolua_S,"setIntellect",tolua_CLuaInterface_CCharacter_setIntellect00);
   tolua_function(tolua_S,"getIntellect",tolua_CLuaInterface_CCharacter_getIntellect00);
   tolua_function(tolua_S,"modifyIntellect",tolua_CLuaInterface_CCharacter_modifyIntellect00);
   tolua_function(tolua_S,"setWisdom",tolua_CLuaInterface_CCharacter_setWisdom00);
   tolua_function(tolua_S,"getWisdom",tolua_CLuaInterface_CCharacter_getWisdom00);
   tolua_function(tolua_S,"modifyWisdom",tolua_CLuaInterface_CCharacter_modifyWisdom00);
   tolua_function(tolua_S,"setMaxHealth",tolua_CLuaInterface_CCharacter_setMaxHealth00);
   tolua_function(tolua_S,"getMaxHealth",tolua_CLuaInterface_CCharacter_getMaxHealth00);
   tolua_function(tolua_S,"modifyMaxHealth",tolua_CLuaInterface_CCharacter_modifyMaxHealth00);
   tolua_function(tolua_S,"setMaxMana",tolua_CLuaInterface_CCharacter_setMaxMana00);
   tolua_function(tolua_S,"getMaxMana",tolua_CLuaInterface_CCharacter_getMaxMana00);
   tolua_function(tolua_S,"modifyMaxMana",tolua_CLuaInterface_CCharacter_modifyMaxMana00);
   tolua_function(tolua_S,"setNumMoveTexturesPerDirection",tolua_CLuaInterface_CCharacter_setNumMoveTexturesPerDirection00);
   tolua_function(tolua_S,"setMoveTexture",tolua_CLuaInterface_CCharacter_setMoveTexture00);
   tolua_function(tolua_S,"setLifeTexture",tolua_CLuaInterface_CCharacter_setLifeTexture00);
   tolua_function(tolua_S,"setWanderRadius",tolua_CLuaInterface_CCharacter_setWanderRadius00);
   tolua_function(tolua_S,"getWanderRadius",tolua_CLuaInterface_CCharacter_getWanderRadius00);
   tolua_function(tolua_S,"setName",tolua_CLuaInterface_CCharacter_setName00);
   tolua_function(tolua_S,"getName",tolua_CLuaInterface_CCharacter_getName00);
   tolua_function(tolua_S,"setLevel",tolua_CLuaInterface_CCharacter_setLevel00);
   tolua_function(tolua_S,"getLevel",tolua_CLuaInterface_CCharacter_getLevel00);
   tolua_function(tolua_S,"setMinDamage",tolua_CLuaInterface_CCharacter_setMinDamage00);
   tolua_function(tolua_S,"getMinDamage",tolua_CLuaInterface_CCharacter_getMinDamage00);
   tolua_function(tolua_S,"setMaxDamage",tolua_CLuaInterface_CCharacter_setMaxDamage00);
   tolua_function(tolua_S,"getMaxDamage",tolua_CLuaInterface_CCharacter_getMaxDamage00);
   tolua_function(tolua_S,"setArmor",tolua_CLuaInterface_CCharacter_setArmor00);
   tolua_function(tolua_S,"setDamageModifierPoints",tolua_CLuaInterface_CCharacter_setDamageModifierPoints00);
   tolua_function(tolua_S,"setHitModifierPoints",tolua_CLuaInterface_CCharacter_setHitModifierPoints00);
   tolua_function(tolua_S,"setEvadeModifierPoints",tolua_CLuaInterface_CCharacter_setEvadeModifierPoints00);
   tolua_function(tolua_S,"setBlockModifierPoints",tolua_CLuaInterface_CCharacter_setBlockModifierPoints00);
   tolua_function(tolua_S,"setMeleeCriticalModifierPoints",tolua_CLuaInterface_CCharacter_setMeleeCriticalModifierPoints00);
   tolua_function(tolua_S,"setResistElementModifierPoints",tolua_CLuaInterface_CCharacter_setResistElementModifierPoints00);
   tolua_function(tolua_S,"setResistAllModifierPoints",tolua_CLuaInterface_CCharacter_setResistAllModifierPoints00);
   tolua_function(tolua_S,"setSpellEffectElementModifierPoints",tolua_CLuaInterface_CCharacter_setSpellEffectElementModifierPoints00);
   tolua_function(tolua_S,"setSpellEffectAllModifierPoints",tolua_CLuaInterface_CCharacter_setSpellEffectAllModifierPoints00);
   tolua_function(tolua_S,"setSpellCriticalModifierPoints",tolua_CLuaInterface_CCharacter_setSpellCriticalModifierPoints00);
   tolua_function(tolua_S,"setBoundingBox",tolua_CLuaInterface_CCharacter_setBoundingBox00);
   tolua_function(tolua_S,"setUseBoundingBox",tolua_CLuaInterface_CCharacter_setUseBoundingBox00);
   tolua_function(tolua_S,"addItemToLootTable",tolua_CLuaInterface_CCharacter_addItemToLootTable00);
   tolua_function(tolua_S,"setCoinDrop",tolua_CLuaInterface_CCharacter_setCoinDrop00);
   tolua_function(tolua_S,"setPosition",tolua_CLuaInterface_CCharacter_setPosition00);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"StatsType",0);
  tolua_beginmodule(tolua_S,"StatsType");
   tolua_constant(tolua_S,"Dexterity",StatsType::Dexterity);
   tolua_constant(tolua_S,"Intellect",StatsType::Intellect);
   tolua_constant(tolua_S,"Strength",StatsType::Strength);
   tolua_constant(tolua_S,"Vitality",StatsType::Vitality);
   tolua_constant(tolua_S,"Wisdom",StatsType::Wisdom);
   tolua_constant(tolua_S,"Health",StatsType::Health);
   tolua_constant(tolua_S,"Mana",StatsType::Mana);
   tolua_constant(tolua_S,"Armor",StatsType::Armor);
   tolua_constant(tolua_S,"DamageModifier",StatsType::DamageModifier);
   tolua_constant(tolua_S,"HitModifier",StatsType::HitModifier);
   tolua_constant(tolua_S,"EvadeModifier",StatsType::EvadeModifier);
   tolua_constant(tolua_S,"BlockModifier",StatsType::BlockModifier);
   tolua_constant(tolua_S,"MeleeCritical",StatsType::MeleeCritical);
   tolua_constant(tolua_S,"SpellCritical",StatsType::SpellCritical);
   tolua_constant(tolua_S,"ResistAll",StatsType::ResistAll);
   tolua_constant(tolua_S,"SpellEffectAll",StatsType::SpellEffectAll);
   tolua_constant(tolua_S,"Count",StatsType::Count);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"ElementType",0);
  tolua_beginmodule(tolua_S,"ElementType");
   tolua_constant(tolua_S,"Fire",ElementType::Fire);
   tolua_constant(tolua_S,"Water",ElementType::Water);
   tolua_constant(tolua_S,"Air",ElementType::Air);
   tolua_constant(tolua_S,"Earth",ElementType::Earth);
   tolua_constant(tolua_S,"Light",ElementType::Light);
   tolua_constant(tolua_S,"Dark",ElementType::Dark);
   tolua_constant(tolua_S,"Count",ElementType::Count);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"EffectType",0);
  tolua_beginmodule(tolua_S,"EffectType");
   tolua_constant(tolua_S,"SingleTargetSpell",EffectType::SingleTargetSpell);
   tolua_constant(tolua_S,"SelfAffectingSpell",EffectType::SelfAffectingSpell);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"PositionType",0);
  tolua_beginmodule(tolua_S,"PositionType");
   tolua_constant(tolua_S,"BOTTOMLEFT",PositionType::BOTTOMLEFT);
   tolua_constant(tolua_S,"BOTTOMCENTER",PositionType::BOTTOMCENTER);
   tolua_constant(tolua_S,"LEFTCENTER",PositionType::LEFTCENTER);
   tolua_constant(tolua_S,"CENTER",PositionType::CENTER);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"ItemQuality",0);
  tolua_beginmodule(tolua_S,"ItemQuality");
   tolua_constant(tolua_S,"POOR",ItemQuality::POOR);
   tolua_constant(tolua_S,"NORMAL",ItemQuality::NORMAL);
   tolua_constant(tolua_S,"ENHANCED",ItemQuality::ENHANCED);
   tolua_constant(tolua_S,"RARE",ItemQuality::RARE);
   tolua_constant(tolua_S,"LORE",ItemQuality::LORE);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"ItemSlot",0);
  tolua_beginmodule(tolua_S,"ItemSlot");
   tolua_constant(tolua_S,"HEAD",ItemSlot::HEAD);
   tolua_constant(tolua_S,"AMULET",ItemSlot::AMULET);
   tolua_constant(tolua_S,"MAIN_HAND",ItemSlot::MAIN_HAND);
   tolua_constant(tolua_S,"OFF_HAND",ItemSlot::OFF_HAND);
   tolua_constant(tolua_S,"BELT",ItemSlot::BELT);
   tolua_constant(tolua_S,"LEGS",ItemSlot::LEGS);
   tolua_constant(tolua_S,"SHOULDER",ItemSlot::SHOULDER);
   tolua_constant(tolua_S,"CHEST",ItemSlot::CHEST);
   tolua_constant(tolua_S,"GLOVES",ItemSlot::GLOVES);
   tolua_constant(tolua_S,"CLOAK",ItemSlot::CLOAK);
   tolua_constant(tolua_S,"BOOTS",ItemSlot::BOOTS);
   tolua_constant(tolua_S,"RING_ONE",ItemSlot::RING_ONE);
   tolua_constant(tolua_S,"RING_TWO",ItemSlot::RING_TWO);
   tolua_constant(tolua_S,"COUNT",ItemSlot::COUNT);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"EquipPosition",0);
  tolua_beginmodule(tolua_S,"EquipPosition");
   tolua_constant(tolua_S,"MAIN_HAND",EquipPosition::MAIN_HAND);
   tolua_constant(tolua_S,"OFF_HAND",EquipPosition::OFF_HAND);
   tolua_constant(tolua_S,"CHEST",EquipPosition::CHEST);
   tolua_constant(tolua_S,"LEGS",EquipPosition::LEGS);
   tolua_constant(tolua_S,"BELT",EquipPosition::BELT);
   tolua_constant(tolua_S,"BOOTS",EquipPosition::BOOTS);
   tolua_constant(tolua_S,"RING",EquipPosition::RING);
   tolua_constant(tolua_S,"GLOVES",EquipPosition::GLOVES);
   tolua_constant(tolua_S,"HEAD",EquipPosition::HEAD);
   tolua_constant(tolua_S,"CLOAK",EquipPosition::CLOAK);
   tolua_constant(tolua_S,"AMULET",EquipPosition::AMULET);
   tolua_constant(tolua_S,"SHOULDER",EquipPosition::SHOULDER);
   tolua_constant(tolua_S,"NONE",EquipPosition::NONE);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"ItemType",0);
  tolua_beginmodule(tolua_S,"ItemType");
   tolua_constant(tolua_S,"QUESTITEM",ItemType::QUESTITEM);
   tolua_constant(tolua_S,"MISCELLANEOUS",ItemType::MISCELLANEOUS);
   tolua_constant(tolua_S,"ARMOR",ItemType::ARMOR);
   tolua_constant(tolua_S,"WEAPON",ItemType::WEAPON);
   tolua_constant(tolua_S,"JEWELRY",ItemType::JEWELRY);
   tolua_constant(tolua_S,"SCROLL",ItemType::SCROLL);
   tolua_constant(tolua_S,"POTION",ItemType::POTION);
   tolua_constant(tolua_S,"FOOD",ItemType::FOOD);
   tolua_constant(tolua_S,"DRINK",ItemType::DRINK);
   tolua_constant(tolua_S,"NEWSPELL",ItemType::NEWSPELL);
   tolua_constant(tolua_S,"COUNT",ItemType::COUNT);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"ArmorType",0);
  tolua_beginmodule(tolua_S,"ArmorType");
   tolua_constant(tolua_S,"NO_ARMOR",ArmorType::NO_ARMOR);
   tolua_constant(tolua_S,"CLOTH",ArmorType::CLOTH);
   tolua_constant(tolua_S,"LEATHER",ArmorType::LEATHER);
   tolua_constant(tolua_S,"MAIL",ArmorType::MAIL);
   tolua_constant(tolua_S,"PLATE",ArmorType::PLATE);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"WeaponType",0);
  tolua_beginmodule(tolua_S,"WeaponType");
   tolua_constant(tolua_S,"NO_WEAPON",WeaponType::NO_WEAPON);
   tolua_constant(tolua_S,"ONEHAND_SWORD",WeaponType::ONEHAND_SWORD);
   tolua_constant(tolua_S,"TWOHAND_SWORD",WeaponType::TWOHAND_SWORD);
   tolua_constant(tolua_S,"DAGGER",WeaponType::DAGGER);
   tolua_constant(tolua_S,"STAFF",WeaponType::STAFF);
   tolua_constant(tolua_S,"ONEHAND_CLUB",WeaponType::ONEHAND_CLUB);
   tolua_constant(tolua_S,"TWOHAND_CLUB",WeaponType::TWOHAND_CLUB);
   tolua_constant(tolua_S,"WAND",WeaponType::WAND);
   tolua_constant(tolua_S,"SPELLBOOK",WeaponType::SPELLBOOK);
   tolua_constant(tolua_S,"ONEHAND_MACE",WeaponType::ONEHAND_MACE);
   tolua_constant(tolua_S,"TWOHAND_MACE",WeaponType::TWOHAND_MACE);
   tolua_constant(tolua_S,"ONEHAND_AXE",WeaponType::ONEHAND_AXE);
   tolua_constant(tolua_S,"TWOHAND_AXE",WeaponType::TWOHAND_AXE);
   tolua_constant(tolua_S,"BOW",WeaponType::BOW);
   tolua_constant(tolua_S,"SLINGSHOT",WeaponType::SLINGSHOT);
   tolua_constant(tolua_S,"CROSSBOW",WeaponType::CROSSBOW);
   tolua_constant(tolua_S,"SHIELD",WeaponType::SHIELD);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"Item","Item","",NULL);
  tolua_beginmodule(tolua_S,"Item");
   tolua_function(tolua_S,"setDescription",tolua_CLuaInterface_Item_setDescription00);
   tolua_function(tolua_S,"setStats",tolua_CLuaInterface_Item_setStats00);
   tolua_function(tolua_S,"setResistElementModifierPoints",tolua_CLuaInterface_Item_setResistElementModifierPoints00);
   tolua_function(tolua_S,"setSpellEffectElementModifierPoints",tolua_CLuaInterface_Item_setSpellEffectElementModifierPoints00);
   tolua_function(tolua_S,"setMinDamage",tolua_CLuaInterface_Item_setMinDamage00);
   tolua_function(tolua_S,"setMaxDamage",tolua_CLuaInterface_Item_setMaxDamage00);
   tolua_function(tolua_S,"setLevelReq",tolua_CLuaInterface_Item_setLevelReq00);
   tolua_function(tolua_S,"setValue",tolua_CLuaInterface_Item_setValue00);
   tolua_function(tolua_S,"setSpellCharges",tolua_CLuaInterface_Item_setSpellCharges00);
   tolua_function(tolua_S,"setSpell",tolua_CLuaInterface_Item_setSpell00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"InteractionPoint","InteractionPoint","",NULL);
  tolua_beginmodule(tolua_S,"InteractionPoint");
   tolua_function(tolua_S,"setPosition",tolua_CLuaInterface_InteractionPoint_setPosition00);
   tolua_function(tolua_S,"setInteractionTexture",tolua_CLuaInterface_InteractionPoint_setInteractionTexture00);
   tolua_function(tolua_S,"setBackgroundTexture",tolua_CLuaInterface_InteractionPoint_setBackgroundTexture00);
   tolua_function(tolua_S,"setInteractionCode",tolua_CLuaInterface_InteractionPoint_setInteractionCode00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CallIndirection","CallIndirection","",NULL);
  tolua_beginmodule(tolua_S,"CallIndirection");
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"LuaCallIndirection","LuaCallIndirection","CallIndirection",NULL);
  tolua_beginmodule(tolua_S,"LuaCallIndirection");
   tolua_function(tolua_S,"setExecuteText",tolua_CLuaInterface_LuaCallIndirection_setExecuteText00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CNPC","CNPC","CCharacter",NULL);
  tolua_beginmodule(tolua_S,"CNPC");
   tolua_function(tolua_S,"addOnDieEventHandler",tolua_CLuaInterface_CNPC_addOnDieEventHandler00);
   tolua_function(tolua_S,"setAttitude",tolua_CLuaInterface_CNPC_setAttitude00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"Player","Player","CCharacter",NULL);
  tolua_beginmodule(tolua_S,"Player");
   tolua_function(tolua_S,"getSaveText",tolua_CLuaInterface_Player_getSaveText00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"TextWindow","TextWindow","",NULL);
  tolua_beginmodule(tolua_S,"TextWindow");
   tolua_function(tolua_S,"setText",tolua_CLuaInterface_TextWindow_setText00);
   tolua_function(tolua_S,"setAutocloseTime",tolua_CLuaInterface_TextWindow_setAutocloseTime00);
   tolua_function(tolua_S,"setPosition",tolua_CLuaInterface_TextWindow_setPosition00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"Shop","Shop","",NULL);
  tolua_beginmodule(tolua_S,"Shop");
   tolua_function(tolua_S,"setVisible",tolua_CLuaInterface_Shop_setVisible00);
   tolua_function(tolua_S,"addItem",tolua_CLuaInterface_Shop_addItem00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"ConfigurableSpell","ConfigurableSpell","CSpell",NULL);
  tolua_beginmodule(tolua_S,"ConfigurableSpell");
   tolua_function(tolua_S,"setCastTime",tolua_CLuaInterface_ConfigurableSpell_setCastTime00);
   tolua_function(tolua_S,"setCooldown",tolua_CLuaInterface_ConfigurableSpell_setCooldown00);
   tolua_function(tolua_S,"setManaCost",tolua_CLuaInterface_ConfigurableSpell_setManaCost00);
   tolua_function(tolua_S,"setName",tolua_CLuaInterface_ConfigurableSpell_setName00);
   tolua_function(tolua_S,"setInfo",tolua_CLuaInterface_ConfigurableSpell_setInfo00);
   tolua_function(tolua_S,"setSpellSymbol",tolua_CLuaInterface_ConfigurableSpell_setSpellSymbol00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"GeneralDamageSpell","GeneralDamageSpell","ConfigurableSpell",NULL);
  tolua_beginmodule(tolua_S,"GeneralDamageSpell");
   tolua_function(tolua_S,"setDirectDamage",tolua_CLuaInterface_GeneralDamageSpell_setDirectDamage00);
   tolua_function(tolua_S,"setContinuousDamage",tolua_CLuaInterface_GeneralDamageSpell_setContinuousDamage00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"GeneralRayDamageSpell","GeneralRayDamageSpell","GeneralDamageSpell",NULL);
  tolua_beginmodule(tolua_S,"GeneralRayDamageSpell");
   tolua_function(tolua_S,"setNumAnimations",tolua_CLuaInterface_GeneralRayDamageSpell_setNumAnimations00);
   tolua_function(tolua_S,"setAnimationTexture",tolua_CLuaInterface_GeneralRayDamageSpell_setAnimationTexture00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"GeneralBoltDamageSpell","GeneralBoltDamageSpell","GeneralDamageSpell",NULL);
  tolua_beginmodule(tolua_S,"GeneralBoltDamageSpell");
   tolua_function(tolua_S,"setMoveSpeed",tolua_CLuaInterface_GeneralBoltDamageSpell_setMoveSpeed00);
   tolua_function(tolua_S,"setExpireTime",tolua_CLuaInterface_GeneralBoltDamageSpell_setExpireTime00);
   tolua_function(tolua_S,"setNumAnimations",tolua_CLuaInterface_GeneralBoltDamageSpell_setNumAnimations00);
   tolua_function(tolua_S,"setAnimationTexture",tolua_CLuaInterface_GeneralBoltDamageSpell_setAnimationTexture00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"GeneralHealingSpell","GeneralHealingSpell","ConfigurableSpell",NULL);
  tolua_beginmodule(tolua_S,"GeneralHealingSpell");
   tolua_function(tolua_S,"setEffectType",tolua_CLuaInterface_GeneralHealingSpell_setEffectType00);
   tolua_function(tolua_S,"setHealEffect",tolua_CLuaInterface_GeneralHealingSpell_setHealEffect00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"GeneralBuffSpell","GeneralBuffSpell","ConfigurableSpell",NULL);
  tolua_beginmodule(tolua_S,"GeneralBuffSpell");
   tolua_function(tolua_S,"setEffectType",tolua_CLuaInterface_GeneralBuffSpell_setEffectType00);
   tolua_function(tolua_S,"setDuration",tolua_CLuaInterface_GeneralBuffSpell_setDuration00);
   tolua_function(tolua_S,"setStats",tolua_CLuaInterface_GeneralBuffSpell_setStats00);
   tolua_function(tolua_S,"setResistElementModifierPoints",tolua_CLuaInterface_GeneralBuffSpell_setResistElementModifierPoints00);
   tolua_function(tolua_S,"setSpellEffectElementModifierPoints",tolua_CLuaInterface_GeneralBuffSpell_setSpellEffectElementModifierPoints00);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"DawnInterface",0);
  tolua_beginmodule(tolua_S,"DawnInterface");
   tolua_function(tolua_S,"createNewMobType",tolua_CLuaInterface_DawnInterface_createNewMobType00);
   tolua_function(tolua_S,"createNewItem",tolua_CLuaInterface_DawnInterface_createNewItem00);
   tolua_function(tolua_S,"giveItemToPlayer",tolua_CLuaInterface_DawnInterface_giveItemToPlayer00);
   tolua_function(tolua_S,"addMobSpawnPoint",tolua_CLuaInterface_DawnInterface_addMobSpawnPoint00);
   tolua_function(tolua_S,"removeMobSpawnPoint",tolua_CLuaInterface_DawnInterface_removeMobSpawnPoint00);
   tolua_function(tolua_S,"createGeneralRayDamageSpell",tolua_CLuaInterface_DawnInterface_createGeneralRayDamageSpell00);
   tolua_function(tolua_S,"createGeneralBoltDamageSpell",tolua_CLuaInterface_DawnInterface_createGeneralBoltDamageSpell00);
   tolua_function(tolua_S,"createGeneralHealingSpell",tolua_CLuaInterface_DawnInterface_createGeneralHealingSpell00);
   tolua_function(tolua_S,"createGeneralBuffSpell",tolua_CLuaInterface_DawnInterface_createGeneralBuffSpell00);
   tolua_function(tolua_S,"inscribeSpellInPlayerSpellbook",tolua_CLuaInterface_DawnInterface_inscribeSpellInPlayerSpellbook00);
   tolua_function(tolua_S,"addInteractionPoint",tolua_CLuaInterface_DawnInterface_addInteractionPoint00);
   tolua_function(tolua_S,"addCharacterInteractionPoint",tolua_CLuaInterface_DawnInterface_addCharacterInteractionPoint00);
   tolua_function(tolua_S,"createTextWindow",tolua_CLuaInterface_DawnInterface_createTextWindow00);
   tolua_function(tolua_S,"removeInteractionPoint",tolua_CLuaInterface_DawnInterface_removeInteractionPoint00);
   tolua_function(tolua_S,"createEventHandler",tolua_CLuaInterface_DawnInterface_createEventHandler00);
   tolua_function(tolua_S,"addQuest",tolua_CLuaInterface_DawnInterface_addQuest00);
   tolua_function(tolua_S,"removeQuest",tolua_CLuaInterface_DawnInterface_removeQuest00);
   tolua_function(tolua_S,"changeQuestDescription",tolua_CLuaInterface_DawnInterface_changeQuestDescription00);
   tolua_function(tolua_S,"addShop",tolua_CLuaInterface_DawnInterface_addShop00);
   tolua_function(tolua_S,"getPlayer",tolua_CLuaInterface_DawnInterface_getPlayer00);
   tolua_function(tolua_S,"getQuestSaveText",tolua_CLuaInterface_DawnInterface_getQuestSaveText00);
   tolua_function(tolua_S,"getInventorySaveText",tolua_CLuaInterface_DawnInterface_getInventorySaveText00);
   tolua_function(tolua_S,"restoreItemInBackpack",tolua_CLuaInterface_DawnInterface_restoreItemInBackpack00);
   tolua_function(tolua_S,"restoreWieldItem",tolua_CLuaInterface_DawnInterface_restoreWieldItem00);
   tolua_function(tolua_S,"restoreGroundLootItem",tolua_CLuaInterface_DawnInterface_restoreGroundLootItem00);
   tolua_function(tolua_S,"restoreGroundGold",tolua_CLuaInterface_DawnInterface_restoreGroundGold00);
   tolua_function(tolua_S,"setCurrentZone",tolua_CLuaInterface_DawnInterface_setCurrentZone00);
   tolua_function(tolua_S,"getAllZonesSaveText",tolua_CLuaInterface_DawnInterface_getAllZonesSaveText00);
   tolua_function(tolua_S,"getItemReferenceRestore",tolua_CLuaInterface_DawnInterface_getItemReferenceRestore00);
   tolua_function(tolua_S,"getItemReferenceRestore",tolua_CLuaInterface_DawnInterface_getItemReferenceRestore01);
   tolua_function(tolua_S,"getItemReferenceRestore",tolua_CLuaInterface_DawnInterface_getItemReferenceRestore02);
   tolua_function(tolua_S,"getItemReferenceRestore",tolua_CLuaInterface_DawnInterface_getItemReferenceRestore03);
   tolua_function(tolua_S,"getItemReferenceRestore",tolua_CLuaInterface_DawnInterface_getItemReferenceRestore04);
   tolua_function(tolua_S,"restoreCharacterReference",tolua_CLuaInterface_DawnInterface_restoreCharacterReference00);
   tolua_function(tolua_S,"restoreInteractionPointReference",tolua_CLuaInterface_DawnInterface_restoreInteractionPointReference00);
   tolua_function(tolua_S,"restoreEventHandlerReference",tolua_CLuaInterface_DawnInterface_restoreEventHandlerReference00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_CLuaInterface (lua_State* tolua_S) {
 return tolua_CLuaInterface_open(tolua_S);
};
#endif

