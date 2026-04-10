#include "character_pipeline.hpp"

#include "systems/system.hpp"

CharacterPipeline::CharacterPipeline(Client& client, InventoryManager& bank) : m_Character(client, bank), m_Systems() {}

void CharacterPipeline::Set_Character(const char* character_name)
{
    m_Character.Set_Character(character_name);
}

const char* CharacterPipeline::Get_Character(void) const
{
    return m_Character.Get_Character();
}

void CharacterPipeline::Add_System(System* system)
{
    m_Systems.push_back(system);
}

void CharacterPipeline::Update(float elapsed_time)
{
    m_Character.Update(elapsed_time);
    for (std::size_t jj = 0; jj < m_Systems.size() && (m_Character.Is_Empty() == true); jj++)
    {
        m_Systems[jj]->Fill_Pipeline(m_Character);
        if (m_Character.Is_Empty() == false)
        {
            printf("\t'%s' commanded by '%s'\n", m_Character.Get_Character(), m_Systems[jj]->Name());
        }
    }
}
