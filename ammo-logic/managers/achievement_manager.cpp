#include "achievement_manager.hpp"

#include <algorithm>

#include "net/client.hpp"

AchivementManager AchivementManager::singleton;

void AchivementManager::Initialize(void)
{
    // Update_Cache();
}

bool AchivementManager::Is_Completed(const char* achivement_name) const
{
    return std::find_if(m_Achived.begin(), m_Achived.end(), [achivement_name](const std::string& str) { return str == achivement_name; }) !=
           m_Achived.end();
}

void AchivementManager::Update_Cache(void)
{
    std::vector<nlohmann::json> achivements;

    Client::singleton.Get_Account_Achievements(achivements);

    for (std::size_t ii = 0; ii < achivements.size(); ii++)
    {
        if (achivements[ii]["achieved_at"].is_null() == false)
        {
            m_Achived.push_back(achivements[ii]["code"]);
        }
    }
}
