#include "../include/bandit.h"
#include "../include/fight_visitor.h"


std::string Bandit::info() const {
    return "Bandit(" + std::to_string(this->x) + ' ' + std::to_string(this->y) + ')' + '<' + this->unique_name + '>';
}
bool Bandit::accept(std::shared_ptr<NPC> npc_ptr) const {
    VisitorFightBandit visitor_fight_bandit;
    return visitor_fight_bandit.fight(npc_ptr);
}