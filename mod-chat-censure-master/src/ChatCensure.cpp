#include "PrecompiledHeaders/ScriptPCH.h"
#include "Channel.h"
#include "ScriptMgr.h"
#include "Player.h"
#include "Configuration/Config.h"
#include "Chat.h"

class System_Censure : public PlayerScript
{
    public:
        System_Censure() : PlayerScript("System_Censure") {}

        void OnChat(Player* player, uint32 /*type*/, uint32 lang, std::string& msg)
        {
            CheckMessage(player, msg, lang, NULL, NULL, NULL, NULL);
        }

        void OnChat(Player* player, uint32 /*type*/, uint32 lang, std::string& msg, Player* receiver)
        {
            CheckMessage(player, msg, lang, receiver, NULL, NULL, NULL);
        }

        void OnChat(Player* player, uint32 /*type*/, uint32 lang, std::string& msg, Group* group)
        {
            CheckMessage(player, msg, lang, NULL, group, NULL, NULL);
        }

        void OnChat(Player* player, uint32 /*type*/, uint32 lang, std::string& msg, Guild* guild)
        {
            CheckMessage(player, msg, lang, NULL, NULL, guild, NULL);
        }

        void OnChat(Player* player, uint32 /*type*/, uint32 lang, std::string& msg, Channel* channel)
        {
            CheckMessage(player, msg, lang, NULL, NULL, NULL, channel);
        }

    void CheckMessage(Player* player, std::string& msg, uint32 lang, Player* /*receiver*/, Group* /*group*/, Guild* /*guild*/, Channel* channel)
    {
        if (player->IsGameMaster() || lang == LANG_ADDON)
            return;

        // transform to lowercase (for simpler checking)
        std::string lower = msg;
        std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);

        const uint8 cheksSize = 38;
        std::string checks[cheksSize];
        checks[0] ="http://";
        checks[1] =".com";
        checks[2] =".www";
        checks[3] =".net";
        checks[4] =".org";
        checks[5] =".ru";
        checks[6] ="www.";
        checks[7] ="wow-";
        checks[8] ="qlia";
        checks[9] ="chuto";
        checks[10] ="ql";
        checks[11] ="pichula";
        checks[12] ="pixula";
        checks[13] ="guatonkl";
        checks[14] ="guatonculiao";
        checks[15] ="pajaronql";
        checks[16] ="azeroth-project";
        checks[17] ="xetumare";
        checks[18] ="pierdo";
        checks[19] ="spierd";
        checks[20] ="guatonql";
        checks[21] ="maraca";
        checks[22] ="gmputo";
        checks[23] ="nepe";
        checks[24] ="pene";
        checks[25] ="piko";
        checks[26] ="zorractm";
        checks[27] ="perroctm";
        checks[28] ="gmql";
        checks[29] ="gmsculiaos";
        checks[30] ="ctm";
        checks[31] ="CTM";
        checks[32] ="puto";
        checks[33] ="bitch";
        checks[34] ="paoql";
        checks[35] ="woweter";
        checks[36] ="culiao";
        checks[37] ="pico";

        for (int i = 0; i < cheksSize; ++i)
             if (lower.find(checks[i]) != std::string::npos)
             {
                 msg = "";
                 ChatHandler(player->GetSession()).PSendSysMessage("You can't send this kind of message !!");
                 return;
             }
    }
};

void AddMyChatCensureScripts()
{
    new System_Censure();
}
