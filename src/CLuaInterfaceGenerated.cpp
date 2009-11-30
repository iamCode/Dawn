/*
** Lua binding: CLuaInterface
** Generated automatically by tolua++-1.0.92 on Mon Nov 30 20:54:34 2009.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_CLuaInterface_open (lua_State* tolua_S);

#include "CLuaInterface.h"

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_uint8_t (lua_State* tolua_S)
{
 uint8_t* self = (uint8_t*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_uint16_t (lua_State* tolua_S)
{
 uint16_t* self = (uint16_t*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"CCharacter");
 tolua_usertype(tolua_S,"Item");
 tolua_usertype(tolua_S,"uint8_t");
 tolua_usertype(tolua_S,"CZone");
 tolua_usertype(tolua_S,"uint16_t");
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
   uint16_t tolua_ret = (uint16_t)  self->getStrength();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((uint16_t)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"uint16_t");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(uint16_t));
     tolua_pushusertype(tolua_S,tolua_obj,"uint16_t");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
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
   uint16_t tolua_ret = (uint16_t)  self->getDexterity();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((uint16_t)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"uint16_t");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(uint16_t));
     tolua_pushusertype(tolua_S,tolua_obj,"uint16_t");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
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
   uint16_t tolua_ret = (uint16_t)  self->getVitality();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((uint16_t)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"uint16_t");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(uint16_t));
     tolua_pushusertype(tolua_S,tolua_obj,"uint16_t");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
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
   uint16_t tolua_ret = (uint16_t)  self->getIntellect();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((uint16_t)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"uint16_t");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(uint16_t));
     tolua_pushusertype(tolua_S,tolua_obj,"uint16_t");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
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
   uint16_t tolua_ret = (uint16_t)  self->getWisdom();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((uint16_t)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"uint16_t");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(uint16_t));
     tolua_pushusertype(tolua_S,tolua_obj,"uint16_t");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
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
   uint16_t tolua_ret = (uint16_t)  self->getMaxHealth();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((uint16_t)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"uint16_t");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(uint16_t));
     tolua_pushusertype(tolua_S,tolua_obj,"uint16_t");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
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
   uint16_t tolua_ret = (uint16_t)  self->getMaxMana();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((uint16_t)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"uint16_t");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(uint16_t));
     tolua_pushusertype(tolua_S,tolua_obj,"uint16_t");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
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

/* method: setMoveTexture of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_setMoveTexture00
static int tolua_CLuaInterface_CCharacter_setMoveTexture00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  int direction = ((int)  tolua_tonumber(tolua_S,2,0));
  std::string filename = ((std::string)  tolua_tocppstring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setMoveTexture'", NULL);
#endif
  {
   self->setMoveTexture(direction,filename);
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
   uint16_t tolua_ret = (uint16_t)  self->getWanderRadius();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((uint16_t)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"uint16_t");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(uint16_t));
     tolua_pushusertype(tolua_S,tolua_obj,"uint16_t");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
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
   uint8_t tolua_ret = (uint8_t)  self->getLevel();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((uint8_t)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"uint8_t");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(uint8_t));
     tolua_pushusertype(tolua_S,tolua_obj,"uint8_t");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
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
   uint16_t tolua_ret = (uint16_t)  self->getMinDamage();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((uint16_t)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"uint16_t");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(uint16_t));
     tolua_pushusertype(tolua_S,tolua_obj,"uint16_t");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
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
   uint16_t tolua_ret = (uint16_t)  self->getMaxDamage();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((uint16_t)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"uint16_t");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(uint16_t));
     tolua_pushusertype(tolua_S,tolua_obj,"uint16_t");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
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

/* method: setStrength of class  Item */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_Item_setStrength00
static int tolua_CLuaInterface_Item_setStrength00(lua_State* tolua_S)
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
  int strength = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setStrength'", NULL);
#endif
  {
   self->setStrength(strength);
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

/* method: setDexterity of class  Item */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_Item_setDexterity00
static int tolua_CLuaInterface_Item_setDexterity00(lua_State* tolua_S)
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
  int dexterity = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDexterity'", NULL);
#endif
  {
   self->setDexterity(dexterity);
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

/* method: setIntellect of class  Item */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_Item_setIntellect00
static int tolua_CLuaInterface_Item_setIntellect00(lua_State* tolua_S)
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
  int intellect = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setIntellect'", NULL);
#endif
  {
   self->setIntellect(intellect);
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

/* method: setVitality of class  Item */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_Item_setVitality00
static int tolua_CLuaInterface_Item_setVitality00(lua_State* tolua_S)
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
  int vitality = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setVitality'", NULL);
#endif
  {
   self->setVitality(vitality);
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

/* method: setWisdom of class  Item */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_Item_setWisdom00
static int tolua_CLuaInterface_Item_setWisdom00(lua_State* tolua_S)
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
  int wisdom = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setWisdom'", NULL);
#endif
  {
   self->setWisdom(wisdom);
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

/* method: setHealth of class  Item */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_Item_setHealth00
static int tolua_CLuaInterface_Item_setHealth00(lua_State* tolua_S)
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
  int health = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setHealth'", NULL);
#endif
  {
   self->setHealth(health);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setHealth'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setMana of class  Item */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_Item_setMana00
static int tolua_CLuaInterface_Item_setMana00(lua_State* tolua_S)
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
  int mana = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setMana'", NULL);
#endif
  {
   self->setMana(mana);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setMana'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setArmor of class  Item */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_Item_setArmor00
static int tolua_CLuaInterface_Item_setArmor00(lua_State* tolua_S)
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
  int armor = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setArmor'", NULL);
#endif
  {
   self->setArmor(armor);
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

/* method: setDamageModifierPoints of class  Item */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_Item_setDamageModifierPoints00
static int tolua_CLuaInterface_Item_setDamageModifierPoints00(lua_State* tolua_S)
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
  int damageModifierPoints = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDamageModifierPoints'", NULL);
#endif
  {
   self->setDamageModifierPoints(damageModifierPoints);
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

/* method: setHitModifierPoints of class  Item */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_Item_setHitModifierPoints00
static int tolua_CLuaInterface_Item_setHitModifierPoints00(lua_State* tolua_S)
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
  int hitModifierPoints = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setHitModifierPoints'", NULL);
#endif
  {
   self->setHitModifierPoints(hitModifierPoints);
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

/* method: setEvadeModifierPoints of class  Item */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_Item_setEvadeModifierPoints00
static int tolua_CLuaInterface_Item_setEvadeModifierPoints00(lua_State* tolua_S)
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
  int evadeModifierPoints = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setEvadeModifierPoints'", NULL);
#endif
  {
   self->setEvadeModifierPoints(evadeModifierPoints);
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

/* method: setBlockModifierPoints of class  Item */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_Item_setBlockModifierPoints00
static int tolua_CLuaInterface_Item_setBlockModifierPoints00(lua_State* tolua_S)
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
  int blockModifierPoints = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBlockModifierPoints'", NULL);
#endif
  {
   self->setBlockModifierPoints(blockModifierPoints);
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

/* method: setMeleeCriticalModifierPoints of class  Item */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_Item_setMeleeCriticalModifierPoints00
static int tolua_CLuaInterface_Item_setMeleeCriticalModifierPoints00(lua_State* tolua_S)
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
  int meleeCriticalModifierPoints = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setMeleeCriticalModifierPoints'", NULL);
#endif
  {
   self->setMeleeCriticalModifierPoints(meleeCriticalModifierPoints);
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

/* method: setResistAllModifierPoints of class  Item */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_Item_setResistAllModifierPoints00
static int tolua_CLuaInterface_Item_setResistAllModifierPoints00(lua_State* tolua_S)
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
  int resistAllModifierPoints = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setResistAllModifierPoints'", NULL);
#endif
  {
   self->setResistAllModifierPoints(resistAllModifierPoints);
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

/* method: setSpellEffectAllModifierPoints of class  Item */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_Item_setSpellEffectAllModifierPoints00
static int tolua_CLuaInterface_Item_setSpellEffectAllModifierPoints00(lua_State* tolua_S)
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
  int spellEffectAllModifierPoints = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSpellEffectAllModifierPoints'", NULL);
#endif
  {
   self->setSpellEffectAllModifierPoints(spellEffectAllModifierPoints);
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

/* method: setSpellCriticalModifierPoints of class  Item */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_Item_setSpellCriticalModifierPoints00
static int tolua_CLuaInterface_Item_setSpellCriticalModifierPoints00(lua_State* tolua_S)
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
  int spellCriticalModifierPoints = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSpellCriticalModifierPoints'", NULL);
#endif
  {
   self->setSpellCriticalModifierPoints(spellCriticalModifierPoints);
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

/* function: DawnInterface::getCurrentZone */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_DawnInterface_getCurrentZone00
static int tolua_CLuaInterface_DawnInterface_getCurrentZone00(lua_State* tolua_S)
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
   CZone* tolua_ret = (CZone*)  DawnInterface::getCurrentZone();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CZone");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCurrentZone'.",&tolua_err);
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
     !tolua_isusertype(tolua_S,6,"CZone",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
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
  CZone* zone = ((CZone*)  tolua_tousertype(tolua_S,6,0));
  {
   DawnInterface::addMobSpawnPoint(mobID,x_pos,y_pos,respawn_rate,do_respawn,zone);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addMobSpawnPoint'.",&tolua_err);
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
   tolua_function(tolua_S,"setBoundingBox",tolua_CLuaInterface_CCharacter_setBoundingBox00);
   tolua_function(tolua_S,"setUseBoundingBox",tolua_CLuaInterface_CCharacter_setUseBoundingBox00);
   tolua_function(tolua_S,"addItemToLootTable",tolua_CLuaInterface_CCharacter_addItemToLootTable00);
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
   tolua_function(tolua_S,"setStrength",tolua_CLuaInterface_Item_setStrength00);
   tolua_function(tolua_S,"setDexterity",tolua_CLuaInterface_Item_setDexterity00);
   tolua_function(tolua_S,"setIntellect",tolua_CLuaInterface_Item_setIntellect00);
   tolua_function(tolua_S,"setVitality",tolua_CLuaInterface_Item_setVitality00);
   tolua_function(tolua_S,"setWisdom",tolua_CLuaInterface_Item_setWisdom00);
   tolua_function(tolua_S,"setHealth",tolua_CLuaInterface_Item_setHealth00);
   tolua_function(tolua_S,"setMana",tolua_CLuaInterface_Item_setMana00);
   tolua_function(tolua_S,"setArmor",tolua_CLuaInterface_Item_setArmor00);
   tolua_function(tolua_S,"setDamageModifierPoints",tolua_CLuaInterface_Item_setDamageModifierPoints00);
   tolua_function(tolua_S,"setHitModifierPoints",tolua_CLuaInterface_Item_setHitModifierPoints00);
   tolua_function(tolua_S,"setEvadeModifierPoints",tolua_CLuaInterface_Item_setEvadeModifierPoints00);
   tolua_function(tolua_S,"setBlockModifierPoints",tolua_CLuaInterface_Item_setBlockModifierPoints00);
   tolua_function(tolua_S,"setMeleeCriticalModifierPoints",tolua_CLuaInterface_Item_setMeleeCriticalModifierPoints00);
   tolua_function(tolua_S,"setResistElementModifierPoints",tolua_CLuaInterface_Item_setResistElementModifierPoints00);
   tolua_function(tolua_S,"setResistAllModifierPoints",tolua_CLuaInterface_Item_setResistAllModifierPoints00);
   tolua_function(tolua_S,"setSpellEffectElementModifierPoints",tolua_CLuaInterface_Item_setSpellEffectElementModifierPoints00);
   tolua_function(tolua_S,"setSpellEffectAllModifierPoints",tolua_CLuaInterface_Item_setSpellEffectAllModifierPoints00);
   tolua_function(tolua_S,"setSpellCriticalModifierPoints",tolua_CLuaInterface_Item_setSpellCriticalModifierPoints00);
   tolua_function(tolua_S,"setMinDamage",tolua_CLuaInterface_Item_setMinDamage00);
   tolua_function(tolua_S,"setMaxDamage",tolua_CLuaInterface_Item_setMaxDamage00);
   tolua_function(tolua_S,"setLevelReq",tolua_CLuaInterface_Item_setLevelReq00);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"DawnInterface",0);
  tolua_beginmodule(tolua_S,"DawnInterface");
   tolua_function(tolua_S,"createNewMobType",tolua_CLuaInterface_DawnInterface_createNewMobType00);
   tolua_function(tolua_S,"createNewItem",tolua_CLuaInterface_DawnInterface_createNewItem00);
   tolua_function(tolua_S,"giveItemToPlayer",tolua_CLuaInterface_DawnInterface_giveItemToPlayer00);
   tolua_function(tolua_S,"getCurrentZone",tolua_CLuaInterface_DawnInterface_getCurrentZone00);
   tolua_function(tolua_S,"addMobSpawnPoint",tolua_CLuaInterface_DawnInterface_addMobSpawnPoint00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_CLuaInterface (lua_State* tolua_S) {
 return tolua_CLuaInterface_open(tolua_S);
};
#endif

