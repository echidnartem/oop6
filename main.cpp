#include "include/battle_manager.h"
#include "include/factory.h"
#include "include/observer.h"


int main() {
    std::ofstream log_file("../log.txt", std::ios::out);
    if (!log_file.is_open()) {
        std::cerr << "Failed to open log.txt\n";
        return 1;
    }

    auto bandit_ptr = FactoryNPC::create_npc(TypeNPC::bandit, "Shadow", 10, 20);
    auto bear_ptr = FactoryNPC::create_npc(TypeNPC::bear, "Grizzly", 11, 21);
    auto elf_ptr = FactoryNPC::create_npc(TypeNPC::elf, "Lira", 12, 22);

    std::cout << "Test print NPC:\n";
    bandit_ptr->print(std::cout) << '\n';
    bear_ptr->print(std::cout) << '\n';
    elf_ptr->print(std::cout) << "\n\n";

    std::ifstream in("../input.txt");
    if (!in.is_open()) {
        std::cerr << "Warning: input.txt not found. Skipping file load.\n";
    } else {
        auto bandit_file = FactoryNPC::create_npc_from_file(TypeNPC::bandit, in);
        auto bear_file = FactoryNPC::create_npc_from_file(TypeNPC::bear, in);
        auto elf_file = FactoryNPC::create_npc_from_file(TypeNPC::elf, in);

        std::cout << "Test print NPC from file:\n";
        if (bandit_file) std::cout << bandit_file->info() << '\n';
        if (bear_file) std::cout << bear_file->info() << '\n';
        if (elf_file) std::cout << elf_file->info() << "\n\n";

        std::ofstream out("../output.txt");
        if (bandit_file) bandit_file->save(out) << '\n';
        if (bear_file) bear_file->save(out) << '\n';
        if (elf_file) elf_file->save(out) << '\n';
        out.close();
        std::cout << "NPC saved to 'output.txt'\n\n";
    }

    std::cout << "Test fight:\n";
    // Bear атакует Elf => должен убить
    bool bear_kills_elf = bear_ptr->accept(elf_ptr);
    std::cout << "Bear attacked Elf and " 
              << (bear_kills_elf ? "killed" : "did NOT kill") << " him.\n";

    // Elf атакует Bandit => должен убить
    bool elf_kills_bandit = elf_ptr->accept(bandit_ptr);
    std::cout << "Elf attacked Bandit and " 
              << (elf_kills_bandit ? "killed" : "did NOT kill") << " him.\n";

    // Bandit атакует Bandit => должен убить
    bool bandit_kills_bandit = bandit_ptr->accept(bandit_ptr);
    std::cout << "Bandit attacked Bandit and " 
              << (bandit_kills_bandit ? "killed" : "did NOT kill") << " him.\n\n";

    // Наблюдатели
    auto console_observer = std::make_shared<ConsoleObserver>();
    auto file_observer = std::make_shared<FileObserver>();

    // Привязываем наблюдателей к NPC (для уведомлений при убийствах)
    bear_ptr->attach(console_observer);
    bear_ptr->attach(file_observer);
    elf_ptr->attach(console_observer);
    elf_ptr->attach(file_observer);
    bandit_ptr->attach(console_observer);
    bandit_ptr->attach(file_observer);

    std::cout << "Test notify (Bear kills Elf):\n";
    bear_ptr->notify(*elf_ptr);

    std::cout << "\n";

    std::set<std::shared_ptr<NPC>> set_npc;
    set_npc.insert(bear_ptr);
    set_npc.insert(elf_ptr);
    set_npc.insert(bandit_ptr);

    auto bandit2 = FactoryNPC::create_npc(TypeNPC::bandit, "Rogue", 10, 21);
    bandit2->attach(console_observer);
    bandit2->attach(file_observer);
    set_npc.insert(bandit2);

    std::cout << "All NPCs before fight:\n";
    print_all_npc(std::cout, set_npc);
    std::cout << "\n";

    // Запускаем симуляцию боя (в радиусе distance = 1)
    start_fight(set_npc, 1);

    std::cout << "All NPCs after fight:\n";
    print_all_npc(std::cout, set_npc);
    std::cout << "\n";

    log_file.close();
    return 0;
}