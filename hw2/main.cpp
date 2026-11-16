#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

#include "Errors.hpp"
#include "Fleet.hpp"
#include "Things.hpp"
#include "Transport.hpp"

using namespace std;

void print_help() {
    cout << R"(Доступные команды:

Добавление имущества:
  add scooter id name energy score
      Электросамокат: расход энергии и простота управления.

  add bike id name score
      Обычный велосипед: простота управления.

  add ebike id name energy score
      Электровелосипед: расход энергии и простота управления.

  add cargo id name score capacity
      Грузовой велосипед: простота и грузоподъёмность.

  add helmet id name
      Шлем.

  add dock id name energy
      Док-станция: расход энергии.

Просмотр и отчёты:
  list                     Все позиции, отсортированные по номеру.
  count                    Количество позиций.
  energy                   Общий расход энергии за сутки.
  novice                   Транспорт для новичков.
  can_carry weight         Транспорт для указанного веса груза.

Настройки:
  set_novice_minimum N   Порог для новичков: от 1 до 10.
                           Начальное значение — 6.

Витрина:
  focus id                 Выбрать позицию.
  show_focus               Показать выбор или expired, если его нет.

Другие команды:
  remove id                Удалить позицию.
  help                     Показать эту справку.
  quit                     Завершить программу.

Аргументы:
  id        Уникальный инвентарный номер.
  name      Название без пробелов.
  energy    Расход энергии в кВт·ч за сутки, не меньше 0.
  score     Целая оценка простоты от 1 до 10.
  capacity  Положительная грузоподъёмность в кг.
  weight    Положительный вес груза в кг.

Команды вводятся строчными буквами, каждая на отдельной строке.
В дробных числах используйте точку. Вместимость парка — 100 позиций.
Транспорт с broken в названии не проходит техосмотр.
)";
}

void check(istringstream& in) {
    string check;
    if (in >> check) {
        throw InvalidArgument("Лишние аргументы у команды");
    }
}

template<typename T>
T read_number(istringstream& in) {
    string s;
    if (!(in >> s)) {
        throw InvalidArgument("Не хватает числового аргумента");
    }
    istringstream number_stream(s);
    T val;
    if (!(number_stream >> val)) {
        throw InvalidArgument("Некорректное число");
    }
    char extra;
    if (number_stream >> extra) {
        throw InvalidArgument("Некорректное число");
    }
    return val;
}

unique_ptr<InventoryItem> add_function(istringstream& in) {
    string type, id, name;
    if (!(in >> type >> id >> name)) {
        throw InvalidArgument("Для add нужны тип, инвентарный номер и название");
    }
    unique_ptr<InventoryItem> item;
    if (type == "scooter" || type == "ebike") {
        double energy = read_number<double>(in);
        int score = read_number<int>(in);
        check(in);
        if (type == "scooter") {
            item = make_unique<Scooter>(id, name, energy, score);
        } else {
            item = make_unique<ElectricBike>(id, name, energy, score);
        }
    } else if (type == "bike") {
        int score = read_number<int>(in);
        check(in);
        item = make_unique<Bike>(id, name, score);
    } else if (type == "cargo") {
        int score = read_number<int>(in);
        double capacity = read_number<double>(in);
        check(in);
        item = make_unique<CargoBike>(id, name, score, capacity);
    } else if (type == "helmet") {
        check(in);
        item = make_unique<Helmet>(id, name);
    } else if (type == "dock") {
        double energy = read_number<double>(in);
        check(in);
        item = make_unique<Dock>(id, name, energy);
    } else {
        throw InvalidArgument("Неизвестный тип имущества");
    }
    return item;
}

int main() {
    cout << "Приветствуем вас в парке ФизКат" << '\n';
    cout << "Подсказка по использованию вызывается с помощью функции help" << '\n';
    Fleet park;
    string in;
    while (getline(cin, in)) {
        try {
            istringstream s(in);
            string cmd;
            if (!(s >> cmd)) {
                continue;
            }
            if (cmd == "quit") {
                check(s);
                break;
            } else if (cmd == "list") {
                check(s);
                park.list();
            } else if (cmd == "help") {
                check(s);
                print_help();
            }else if (cmd == "energy") {
                check(s);
                cout << fixed << setprecision(1) << park.total_energy() << '\n';
            } else if (cmd == "count") {
                check(s);
                cout << park.size() << '\n';
            } else if (cmd == "novice") {
                check(s);
                park.novice();
            } else if (cmd == "can_carry") {
                double weight = read_number<double>(s);
                check(s);
                park.can_carry(weight);
            } else if (cmd == "focus") {
                string id;
                if (!(s >> id)) {
                    throw InvalidArgument("Нужно указать инвентарный номер");
                }
                check(s);
                park.focus(id);
            } else if (cmd == "show_focus") {
                check(s);
                park.show_focus();
            } else if (cmd == "remove") {
                string id;
                if (!(s >> id)) {
                    throw InvalidArgument("Нужно указать инвентарный номер");
                }
                check(s);
                park.remove(id);
            } else if (cmd == "add") {
                park.add(add_function(s));
            } else if (cmd == "set_novice_minimum") {
                int minimum = read_number<int>(s);
                check(s);
                park.set_novice_minimum(minimum);
            } else {
                throw InvalidArgument("Неизвестная команда. Введите help для списка команд");
            }
        } catch (const FleetError& error) {
            cout << "error: " << error.what() << '\n';
        }
    }
}
