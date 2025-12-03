#pragma once


#include <set>
#include "npc.h"
#include "bandit.h"
#include "bear.h"
#include "elf.h"


bool validate_fight(const std::shared_ptr<NPC> &npc_1, const std::shared_ptr<NPC> &npc_2, const int distance);
std::set<std::shared_ptr<NPC>> simulate_fight(const std::set<std::shared_ptr<NPC> > &set_npc, const int distance);


class IVisitorFight {
public:
    virtual bool fight(std::shared_ptr <NPC> defender) = 0;

    virtual ~IVisitorFight() = default;
};

struct VisitorFightBandit final : IVisitorFight  { bool fight(std::shared_ptr<NPC> defender) override; };
struct VisitorFightBear final : IVisitorFight { bool fight(std::shared_ptr<NPC> defender) override; };
struct VisitorFightElf final : IVisitorFight { bool fight(std::shared_ptr<NPC> defender) override; };