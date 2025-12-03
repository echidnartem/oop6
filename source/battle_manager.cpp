#include "../include/battle_manager.h"
#include "../include/fight_visitor.h"


void start_fight(std::set<std::shared_ptr<NPC>> &set_npc, const int distance) {
    std::set dead_list = simulate_fight(set_npc, distance);

    for (auto &dead_npc : dead_list) {
        set_npc.erase(dead_npc);
    }
}