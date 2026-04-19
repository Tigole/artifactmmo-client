#include "system.hpp"

#include "managers/inventory_manager.hpp"
#include "managers/item_manager.hpp"

int System::Make_Craft(Character& character, MapCoord workshop_coord, const char* item_code, int item_count) const
{
    const MapCoord bank_coord = InventoryManager::singleton.Get_Bank_Nearest_Coord(character);

    const Recipe* r           = ItemManager::singleton.Get_Recipe(item_code);
    const int bank_item_count = InventoryManager::singleton.Get_Bank_Item_Count(item_code);

    if (r == nullptr)
    {
        SYSTEM_PRINT("no recipe for '%s'", item_code);
        return 0;
    }

    const int character_skill_level = character.Get_Skill_Level(r->skill_name.c_str());
    SYSTEM_PRINT("item '%s' required level: %d current level: %d", item_code, r->skill_level, character_skill_level);
    /// Do we have enough in bank ?
    if ((bank_item_count < item_count) && (r->skill_level <= character_skill_level))
    {
        bool may_craft                         = true;
        int character_inventory_space_required = 0;
        int craft_count                        = 1;
        SYSTEM_PRINT("try to craft '%s'", item_code);

        for (std::size_t jj = 0; jj < r->required_items.size(); jj++)
        {
            const ItemOrder& sub_item     = r->required_items[jj];
            const int bank_sub_item_count = InventoryManager::singleton.Get_Bank_Item_Count(sub_item.code.c_str());
            character_inventory_space_required += sub_item.quantity;

            if (bank_sub_item_count < sub_item.quantity)
            {
                may_craft = false;
                SYSTEM_PRINT("missing '%s' x%d", sub_item.code.c_str(), sub_item.quantity);
            }
        }

        if (may_craft == false)
        {
            return 0;
        }

        if (character.Get_Inventory_Remaining_Space() < character_inventory_space_required)
        {
            SYSTEM_PRINT("has to make space");
            character.Make_Clear_Inventory(this, nullptr);
            return -1;
        }

        if (character.Should_Move(bank_coord))
        {
            character.Add_Move(this, bank_coord);
            return -1;
        }

        if (r->required_items.size() == 1)
        {
            craft_count = character.Get_Inventory_Remaining_Space() / r->required_items[0].quantity;
            craft_count = std::min(craft_count, InventoryManager::singleton.Get_Bank_Item_Count(r->required_items[0].code.c_str()) /
                                                    r->required_items[0].quantity);
            SYSTEM_PRINT(
                "1 required item (character.Get_Inventory_Remaining_Space(): %d r->required_items[0].quantity: %d "
                "InventoryManager::singleton.Get_Bank_Item_Count(r->required_items[0].code.c_str()): %d craft_count: %d)",
                character.Get_Inventory_Remaining_Space(), r->required_items[0].quantity,
                InventoryManager::singleton.Get_Bank_Item_Count(r->required_items[0].code.c_str()), craft_count);
        }

        SYSTEM_PRINT("craft_count: %d item_count: %d bank_item_count: %d item_count - bank_item_count: %d", craft_count, item_count,
                     bank_item_count, item_count - bank_item_count);
        craft_count = std::min(craft_count, item_count - bank_item_count);

        SYSTEM_PRINT("will craft '%s' x%d", item_code, craft_count);

        for (std::size_t jj = 0; jj < r->required_items.size(); jj++)
        {
            const ItemOrder& sub_item = r->required_items[jj];

            character.Add_Withdraw_Item(this, { sub_item.code, sub_item.quantity * craft_count });
        }

        const ItemOrder craft_order = { item_code, craft_count };
        character.Add_Move(this, workshop_coord);
        character.Add_Craft(this, craft_order);
        character.Add_Move(this, InventoryManager::singleton.Get_Bank_Nearest_Coord(workshop_coord));
        character.Make_Clear_Inventory(this, nullptr);
        return craft_count;
    }
    return 0;
}
