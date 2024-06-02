/*File "handlers.h" create by abstarct, (сб, 09-гру-2023 17:28:21 +0200)*/
#ifndef ABSTARCT_HANDLERS_H_SENTURY
#define ABSTARCT_HANDLERS_H_SENTURY


#include "../module/game_module.h"
#include "../graphick/reader.h"
#include "../graphick/graphick.h"
#include "../objects/storage.h"
#include "../player/handlers.h"
#include "../init/init.h"
int game(GameEngine *engine,int mils);
int menu(GameEngine *engine,int mils);
int login(GameEngine *engine,int mils);
//int setting(GameEngine *engine,int mils);
//int autor(GameEngine *engine,int mils);

#endif
