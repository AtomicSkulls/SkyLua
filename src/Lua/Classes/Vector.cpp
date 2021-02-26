#include "Vector.h"


namespace SkyLua 
{
    namespace Classes
    {
        namespace Vector 
        {
            int lua_destructor(lua_State* l)
            {
                LuaVector* obj = Util::lua_checkudata<LuaVector>(l, 1, "lua_vector");
                delete obj;

                return 0;
            }

            int lua_constructor(lua_State* l)
            {
                float x = luaL_checknumber(l, 1);
                float y = luaL_checknumber(l, 2);
                float z = luaL_checknumber(l, 3);

                LuaVector** udata = (LuaVector**)lua_newuserdata(l, sizeof(LuaVector*));
                *udata = new LuaVector(x, y, z);

                luaL_getmetatable(l, "lua_vector");

            
                lua_pushnumber(l, x);
                lua_setfield(l, -2, "x");
             
                lua_pushnumber(l, y);
                lua_setfield(l, -2, "y");

                lua_pushnumber(l, z);
                lua_setfield(l, -2, "z");

            
                /*
                     5| metatable "lua_vector"           |-1
                     4| userdata                         |-2
                     3| number(z)                        |-3
                     2| number(y)                        |-4
                     1| number (x)                       |-5
                */
            
                lua_setmetatable(l, -2);

                // We return 1 so Lua callsite will get the user data and 
                // Lua will clean the stack after that.

                return 1;
            }

            int lua_registerclass(lua_State* l)
            {
                luaL_newmetatable(l, "lua_vector");

                luaL_setfuncs(l, regs, 0);

                lua_pushvalue(l, -1);

                lua_setfield(l, -1, "__index");


                lua_setglobal(l, "Vector");
                // example: x = Vector( 2, 4, 8 ) 
            
                return 0;
            }
        }
    }
}

