#ifndef _ACHIVEMENT_MANAGER_HPP
#define _ACHIVEMENT_MANAGER_HPP 1

#include <string>
#include <vector>

class AchivementManager
{
    AchivementManager() = default;

public:
    static AchivementManager singleton;

    void Initialize(void);

    bool Is_Completed(const char* achivement_name) const;

    void Update_Cache(void);

private:
    std::vector<std::string> m_Achived = {};
};

#endif  // _ACHIVEMENT_MANAGER_HPP
