#include "Configuration/Config.h"
#include "ScriptMgr.h"
#include "Player.h"
#include "Chat.h"
#include <time.h>

bool Enabled;
uint32 xpAmount;
time_t t = time(NULL);
tm *now = localtime(&t);

class DoubleXpWeekend : public PlayerScript
{
public:
    DoubleXpWeekend() : PlayerScript("DoubleXpWeekend") {}

        void OnLogin(Player* player) override
        {
            // Announce to the player that the XP weekend is happeneing.
            if (!Enabled)
                return;

            if (now->tm_wday == 5 /*Friday*/ || now->tm_wday == 6 /*Satureday*/ || now->tm_wday == 0/*Sunday*/ || now->tm_wday == 1/*Monday*/ || now->tm_wday == 2/*Tuesday*/ || now->tm_wday == 3/*Wednesday*/ || now->tm_wday == 4/*Thursday*/)
                ChatHandler(player->GetSession()).PSendSysMessage("Welcome to Wowtorn your XP multiplier has been set to: %u", xpAmount);
            
        }

        void OnGiveXP(Player* /*p*/, uint32& amount, Unit* /*victim*/) override
        {
            if (!Enabled)
                return;

            if (now->tm_wday == 5 /*Friday*/ || now->tm_wday == 6 /*Satureday*/ || now->tm_wday == 0/*Sunday*/ || now->tm_wday == 1/*Monday*/ || now->tm_wday == 2/*Tuesday*/ || now->tm_wday == 3/*Wednesday*/ || now->tm_wday == 4/*Thursday*/)
                amount *= xpAmount;
        }
};

class DoubleXpWeekendConf : public WorldScript
{
public:
    DoubleXpWeekendConf() : WorldScript("DoubleXpConf") {}

    void OnBeforeConfigLoad(bool reload) override
    {
        if (!reload) {
            std::string conf_path = _CONF_DIR;
            std::string cfg_file = conf_path + "/mod-double-xp-weekend.conf";

            std::string cfg_def_file = cfg_file + ".dist";
            sConfigMgr->LoadMore(cfg_def_file.c_str());
            sConfigMgr->LoadMore(cfg_file.c_str());

            Enabled = sConfigMgr->GetBoolDefault("XPWeekend.Enabled", true);
            xpAmount = sConfigMgr->GetIntDefault("XPWeekend.xpAmount", 3);

        }
    }
};


void AdddoublexpScripts()
{
    new DoubleXpWeekendConf();
    new DoubleXpWeekend();
}
