#ifndef _CLIENT_HPP
#define _CLIENT_HPP 1

#include <httplib.h>

#include "types.hpp"

class Client
{
public:
    Client();

    void Initialize(void);

    void Get_Items(std::map<std::string, nlohmann::json>& items);
    void Get_Monsters(std::map<std::string, nlohmann::json>& monsters);
    void Get_Maps(std::vector<nlohmann::json>& maps);
    void Get_Resource_Spots(std::vector<nlohmann::json>& spots);
    void mt_Get_Characters(std::vector<std::string>& characters);
    void mt_Get_Bank_Items(nlohmann::json& items);
    void Get_Bank_Detail(nlohmann::json& detail);
    void Get_NPC_Items(std::vector<nlohmann::json>& items);

    MapCoord mt_Get_Map_With_Content_Code(const char* content_code);

    int mt_Character_Move(const char* character_name, const MapCoord& map_coord, nlohmann::json& character_cache);
    int mt_Character_Fight(const char* character_name, nlohmann::json& character_cache);
    int mt_Character_Rest(const char* character_name, nlohmann::json& character_cache);
    int mt_Character_Craft(const char* character_name, const ItemOrder& craft, nlohmann::json& character_cache);
    int mt_Character_Use_Item(const char* character_name, const ItemOrder& use, nlohmann::json& character_cache);
    int mt_Character_Recycle(const char* character_name, const ItemOrder& recycle, nlohmann::json& character_cache);
    int mt_Character_Task_New(const char* character_name, nlohmann::json& character_cache);
    int mt_Character_Task_Trade(const char* character_name, const ItemOrder& trade, nlohmann::json& character_cache);
    int mt_Character_Task_Complete(const char* character_name, nlohmann::json& character_cache);
    int mt_Character_Unequip_Item(const char* character_name, const char* slot, nlohmann::json& character_cache);
    int mt_Character_Equip_Item(const char* character_name, const char* slot, const char* item_code, nlohmann::json& character_cache);
    int mt_Character_Gather(const char* character_name, nlohmann::json& character_cache);
    int mt_Character_Deposit_Item(const char* character_name, const ItemOrder& deposit, nlohmann::json& character_cache);
    int mt_Character_Withdraw_Item(const char* character_name, const ItemOrder& withdraw, nlohmann::json& character_cache);
    int mt_Character_Deposit_Gold(const char* character_name, int gold_amount, nlohmann::json& character_cache);
    int mt_Character_Withdraw_Gold(const char* character_name, int gold_amount, nlohmann::json& character_cache);
    int mt_Character_Buy_Item(const char* character_name, const ItemOrder& buy, nlohmann::json& character_cache);

    void mt_Get_Character_Cache(const char* character_name, nlohmann::json& character_cache);

private:
    nlohmann::json mt_Get_JSON(const char* path);
    nlohmann::json mt_Get_JSON(const char* path, const httplib::Params& params);

    nlohmann::json mt_Post(const char* path);
    nlohmann::json mt_Post(const char* path, const nlohmann::json& body);

    void Get_All_Data(const char* path, std::map<std::string, nlohmann::json>& all_data);
    void Get_All_Data(const char* path, std::vector<nlohmann::json>& all_data);

    httplib::Client m_Client;
};

#endif  // _CLIENT_HPP
