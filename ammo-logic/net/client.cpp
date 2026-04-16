#include "client.hpp"

#include <fmt/format.h>

#include "token.hpp"

Client Client::singleton;

Client::Client() : m_Client("https://api.artifactsmmo.com") {}

void Client::Initialize(void)
{
    httplib::Headers l_Headers = {
        {        "Accept", "application/json" },
        {  "Content-Type", "application/json" },
        { "Authorization",  "Bearer " + TOKEN }
    };
    m_Client.set_default_headers(l_Headers);
    m_Client.enable_server_certificate_verification(false);
    m_Client.enable_server_hostname_verification(false);

    {
        nlohmann::json details = mt_Get_JSON("/my/details");
        Token::account         = details["data"]["username"];
        printf("Account: '%s'\n", Token::account.c_str());
        exit(0);
    }
}

void Client::Get_Items(std::map<std::string, nlohmann::json>& items)
{
    Get_All_Data("/items", items);
}

void Client::Get_Monsters(std::map<std::string, nlohmann::json>& monsters)
{
    Get_All_Data("/monsters", monsters);
}

void Client::Get_All_Data(const char* path, std::map<std::string, nlohmann::json>& all_data)
{
    const int l_Size = 100;
    int page_count   = 2;
    for (int page = 1; page < page_count; page++)
    {
        std::cout << "page: " << page << '\n';
        httplib::Params l_Params = {
            { "page",   std::to_string(page) },
            { "size", std::to_string(l_Size) },
        };
        auto json = mt_Get_JSON(path, l_Params);
        if (false)
        {
            std::cout << json.dump(4) << '\n';
            std::cout << json["page"] << " / " << json["pages"] << '\n';
        }
        page_count = json["pages"];
        auto data  = json["data"];
        for (auto it = data.begin(); it != data.end(); it++)
        {
            all_data[(*it)["code"]] = *it;
        }
    }
}

void Client::Get_All_Data(const char* path, std::vector<nlohmann::json>& all_data)
{
    const int l_Size = 100;
    int page_count   = 2;
    for (int page = 1; page <= page_count; page++)
    {
        printf("path: '%s' page %d\n", path, page);
        httplib::Params l_Params = {
            { "page",   std::to_string(page) },
            { "size", std::to_string(l_Size) },
        };
        auto json = mt_Get_JSON(path, l_Params);
        if (false)
        {
            std::cout << json.dump(4) << '\n';
            std::cout << json["page"] << " / " << json["pages"] << '\n';
        }
        page_count = json["pages"];
        auto data  = json["data"];
        for (auto it = data.begin(); it != data.end(); it++)
        {
            all_data.push_back(*it);
        }
    }
}

void Client::Get_Resource_Spots(std::vector<nlohmann::json>& spots)
{
    Get_All_Data("/resources", spots);
}

void Client::Get_Maps(std::vector<nlohmann::json>& maps)
{
    Get_All_Data("/maps", maps);
    return;
    const int l_Size = 100;
    int page_count   = 2;
    for (int page = 1; page < page_count; page++)
    {
        std::cout << "page: " << page << '\n';
        httplib::Params l_Params = {
            { "page",   std::to_string(page) },
            { "size", std::to_string(l_Size) },
        };
        auto json = mt_Get_JSON("/maps", l_Params);
        if (false)
        {
            std::cout << json.dump(4) << '\n';
            std::cout << json["page"] << " / " << json["pages"] << '\n';
        }
        page_count = json["pages"];
        auto data  = json["data"];
        for (auto it = data.begin(); it != data.end(); it++)
        {
            maps.push_back(*it);
        }
    }
}

void Client::mt_Get_Characters(std::vector<std::string>& characters)
{
    auto body = mt_Get_JSON("/my/characters");

    characters.clear();

    for (auto it = body["data"].begin(); it != body["data"].end(); it++)
    {
        characters.push_back((*it)["name"]);
    }
}

void Client::mt_Get_Bank_Items(nlohmann::json& items)
{
    std::vector<nlohmann::json> data;
    Get_All_Data("/my/bank/items", data);
    for (auto d: data)
    {
        items["data"].push_back(d);
    }
    if (false)
    {
        printf("items.dump: %s\n", items.dump(4).c_str());
    }
}

void Client::Get_Bank_Detail(nlohmann::json& detail)
{
    detail = mt_Get_JSON("/my/bank");
}

void Client::Get_NPC_Items(std::vector<nlohmann::json>& items)
{
    Get_All_Data("/npcs/items", items);
}

MapCoord Client::mt_Get_Map_With_Content_Code(const char* content_code)
{
    auto json = mt_Get_JSON("/maps", {
                                         { "content_code", content_code }
    });

    return json["data"].begin()->get<MapCoord>();
}

int Client::mt_Character_Move(const char* character_name, const MapCoord& map_coord, nlohmann::json& character_cache)
{
    std::string l_Path = "/my/";
    l_Path += character_name;
    l_Path += "/action/move";

    nlohmann::json body = mt_Post(l_Path.c_str(), map_coord);

    character_cache = body["data"]["character"];

    return body["data"]["cooldown"]["remaining_seconds"].get<int>();
}

int Client::mt_Character_Fight(const char* character_name, nlohmann::json& character_cache)
{
    std::string l_Path = "/my/";
    l_Path += character_name;
    l_Path += "/action/fight";

    nlohmann::json body = mt_Post(l_Path.c_str());

    character_cache = body["data"]["characters"];

    return body["data"]["cooldown"]["remaining_seconds"].get<int>();
}

int Client::mt_Character_Rest(const char* character_name, nlohmann::json& character_cache)
{
    std::string l_Path = "/my/";
    l_Path += character_name;
    l_Path += "/action/rest";

    nlohmann::json body = mt_Post(l_Path.c_str());

    character_cache = body["data"]["character"];

    return body["data"]["cooldown"]["remaining_seconds"].get<int>();
}

int Client::mt_Character_Craft(const char* character_name, const ItemOrder& craft, nlohmann::json& character_cache)
{
    std::string l_Path = "/my/";
    l_Path += character_name;
    l_Path += "/action/crafting";

    nlohmann::json body = mt_Post(l_Path.c_str(), craft);

    character_cache = body["data"]["character"];

    return body["data"]["cooldown"]["remaining_seconds"].get<int>();
}

int Client::mt_Character_Use_Item(const char* character_name, const ItemOrder& use, nlohmann::json& character_cache)
{
    std::string l_Path = "/my/";
    l_Path += character_name;
    l_Path += "/action/use";

    nlohmann::json body = mt_Post(l_Path.c_str(), use);

    character_cache = body["data"]["character"];

    return body["data"]["cooldown"]["remaining_seconds"].get<int>();
}

int Client::mt_Character_Recycle(const char* character_name, const ItemOrder& recycle, nlohmann::json& character_cache)
{
    std::string l_Path = "/my/";
    l_Path += character_name;
    l_Path += "/action/recycling";

    nlohmann::json body = mt_Post(l_Path.c_str(), recycle);

    character_cache = body["data"]["character"];

    return body["data"]["cooldown"]["remaining_seconds"].get<int>();
}

int Client::mt_Character_Task_New(const char* character_name, nlohmann::json& character_cache)
{
    std::string l_Path = "/my/";
    l_Path += character_name;
    l_Path += "/action/task/new";

    nlohmann::json body = mt_Post(l_Path.c_str());

    character_cache = body["data"]["character"];

    return body["data"]["cooldown"]["remaining_seconds"].get<int>();
}

int Client::mt_Character_Task_Trade(const char* character_name, const ItemOrder& trade, nlohmann::json& character_cache)
{
    std::string l_Path = "/my/";
    l_Path += character_name;
    l_Path += "/action/task/trade";

    nlohmann::json body = mt_Post(l_Path.c_str(), trade);

    character_cache = body["data"]["character"];

    return body["data"]["cooldown"]["remaining_seconds"].get<int>();
}

int Client::mt_Character_Task_Complete(const char* character_name, nlohmann::json& character_cache)
{
    std::string l_Path = "/my/";
    l_Path += character_name;
    l_Path += "/action/task/complete";

    nlohmann::json body = mt_Post(l_Path.c_str());

    character_cache = body["data"]["character"];

    return body["data"]["cooldown"]["remaining_seconds"].get<int>();
}

int Client::mt_Character_Unequip_Item(const char* character_name, const char* slot, nlohmann::json& character_cache)
{
    std::string l_Path = "/my/";
    l_Path += character_name;
    l_Path += "/action/unequip";

    nlohmann::json body = mt_Post(l_Path.c_str(), UnequipOrder { slot, 1 });

    character_cache = body["data"]["character"];

    return body["data"]["cooldown"]["remaining_seconds"].get<int>();
}

int Client::mt_Character_Equip_Item(const char* character_name, const char* slot, const char* item_code, nlohmann::json& character_cache)
{
    std::string l_Path = "/my/";
    l_Path += character_name;
    l_Path += "/action/equip";

    nlohmann::json body = mt_Post(l_Path.c_str(), EquipOrder { item_code, slot, 1 });

    character_cache = body["data"]["character"];

    return body["data"]["cooldown"]["remaining_seconds"].get<int>();
}

int Client::mt_Character_Gather(const char* character_name, nlohmann::json& character_cache)
{
    std::string l_Path = "/my/";
    l_Path += character_name;
    l_Path += "/action/gathering";

    nlohmann::json body = mt_Post(l_Path.c_str());

    character_cache = body["data"]["character"];

    return body["data"]["cooldown"]["remaining_seconds"].get<int>();
}

int Client::mt_Character_Deposit_Item(const char* character_name, const ItemOrder& deposit, nlohmann::json& character_cache)
{
    std::string l_Path = "/my/";
    l_Path += character_name;
    l_Path += "/action/bank/deposit/item";

    nlohmann::json body = mt_Post(l_Path.c_str(), nlohmann::json({ deposit }));

    character_cache = body["data"]["character"];

    return body["data"]["cooldown"]["remaining_seconds"].get<int>();
}

int Client::mt_Character_Withdraw_Item(const char* character_name, const ItemOrder& withdraw, nlohmann::json& character_cache)
{
    std::string l_Path = "/my/";
    l_Path += character_name;
    l_Path += "/action/bank/withdraw/item";

    nlohmann::json body = mt_Post(l_Path.c_str(), nlohmann::json({ withdraw }));

    character_cache = body["data"]["character"];

    return body["data"]["cooldown"]["remaining_seconds"].get<int>();
}

int Client::mt_Character_Deposit_Gold(const char* character_name, int gold_amount, nlohmann::json& character_cache)
{
    std::string l_Path = "/my/";
    l_Path += character_name;
    l_Path += "/action/bank/deposit/gold";
    nlohmann::json body;

    body["quantity"] = gold_amount;

    body = mt_Post(l_Path.c_str(), body);

    character_cache = body["data"]["character"];

    return body["data"]["cooldown"]["remaining_seconds"].get<int>();
}

int Client::mt_Character_Withdraw_Gold(const char* character_name, int gold_amount, nlohmann::json& character_cache)
{
    std::string l_Path = "/my/";
    l_Path += character_name;
    l_Path += "/action/bank/withdraw/gold";

    nlohmann::json body = mt_Post(l_Path.c_str(), { "quantity", gold_amount });

    character_cache = body["data"]["character"];

    return body["data"]["cooldown"]["remaining_seconds"].get<int>();
}

int Client::mt_Character_Buy_Item(const char* character_name, const ItemOrder& buy, nlohmann::json& character_cache)
{
    std::string l_Path = "/my/";
    l_Path += character_name;
    l_Path += "/action/npc/buy";

    nlohmann::json body = mt_Post(l_Path.c_str(), buy);

    character_cache = body["data"]["character"];

    return body["data"]["cooldown"]["remaining_seconds"].get<int>();
}

void Client::mt_Get_Character_Cache(const char* character_name, nlohmann::json& character_cache)
{
    std::string l_Path = "/characters/";
    l_Path += character_name;

    character_cache = mt_Get_JSON(l_Path.c_str())["data"];
}

nlohmann::json Client::mt_Get_JSON(const char* path)
{
    return mt_Get_JSON(path, httplib::Params());
}

nlohmann::json Client::mt_Get_JSON(const char* path, const httplib::Params& params)
{
    printf("GET - path: '%s'\n", path);
    auto res = m_Client.Get(path, params, httplib::Headers());

    if (res == nullptr)
    {
        throw std::runtime_error(httplib::to_string(res.error()));
    }
    if (res->status != 200)
    {
        throw std::runtime_error(fmt::format("path: '{}' status: '{}' message: '{}'", path, res->status, res->body));
    }

    auto body = nlohmann::json::parse(res->body);

    return body;
}

nlohmann::json Client::mt_Post(const char* path)
{
    nlohmann::json json;

    for (int ii = 0; ii < 10; ii++)
    {
        printf("POST[try %d] - path: '%s'\n", ii, path);
        auto res = m_Client.Post(path);

        if (res == nullptr)
        {
            printf("???\n");
            throw std::runtime_error(httplib::to_string(res.error()));
        }
        if (res->status != 200)
        {
            if (res->status == 499)
            {
                printf("499 : %s\n", res->body.c_str());
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                continue;
            }
            throw std::runtime_error(fmt::format("path: '{}' status: '{}' message: '{}'", path, res->status, res->body));
        }

        json = nlohmann::json::parse(res->body);
        break;

        if (false)
        {
            printf("%s\n", json.dump().c_str());
        }
    }

    return json;
}

nlohmann::json Client::mt_Post(const char* path, const nlohmann::json& body)
{
    nlohmann::json json;

    for (int ii = 0; ii < 10; ii++)
    {
        printf("POST[try %d] - path: '%s'\n", ii, path);
        auto res = m_Client.Post(path, httplib::Headers(), to_string(body), "application/json");

        if (res == nullptr)
        {
            throw std::runtime_error(httplib::to_string(res.error()));
        }
        if (res->status != 200)
        {
            if (res->status == 499)
            {
                printf("499 : %s\n", res->body.c_str());
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                continue;
            }
            std::cout << body.dump(4) << '\n';
            throw std::runtime_error(fmt::format("path: '{}' status: '{}' message: '{}'", path, res->status, res->body));
        }

        json = nlohmann::json::parse(res->body);
        break;
    }
    // printf("%s\n", json.dump().c_str());

    return json;
}
