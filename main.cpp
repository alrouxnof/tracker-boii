#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
// #include "toml++/toml.h"
#include "json.hpp"

/// 1. Questions
/// 2. Yes/No or Rating(1-5)
/// 3. Store
/// 4. graph

// Todo operations (Completed/Not):
// 1. Add todo
// 2. Edit todo
// 3. Complete todo
// 4. Clear list
// 5. Show graph

// Emotion operations (Rating 1-5):
// 1. Add emotion question, and its options.
// 2. Edit emotion question, and its options.
// 3. Ask daily these questions.
// 4. Show graph

// How u feeling (Sad-1, High-5)?
// 1. Option1: 2
// 2. Option2: 5
// 3. Option3: 1

typedef std::pair<std::string, bool> Todo;
typedef std::vector<Todo> TodoList;
static TodoList todos = {
  {"Shit", true},
  {"Assignment", false},
};

typedef std::pair<std::string, std::unordered_map<std::string, std::uint8_t>> EmotionQuestion;
typedef std::vector<EmotionQuestion> EmotionQuestionsList;
static EmotionQuestionsList emotions = {
  { "How u feelin?", {{ "Sad", 0 }, { "Amgry", 0 }, { "Calm", 0 }, { "Depressed", 0 }} },
  { "How u fuckin?", {{ "Breakin da bed", 0 }, { "KCPD", 0 }, { "TADE", 0 }} }
};

static std::vector<std::string> operations = {
  "Show todos 📝",
  "Add todo ➕",
  "Edit todo ✏️",
  "Complete todo ✅",
  "Clear todos ⛔",
  "Show performance graph 🚀",
  "Show emotion questions",
  "Add emotion question",
  "Edit emotion question",
  "Fill emotions",
  "Show emotion graph",
  "Quit 🟥"
};

void show_operations(const std::vector<std::string>& operations);
uint8_t get_selected_operation(const std::vector<std::string>& operations);
void give_dumbass_feedback();

void show_todos(const TodoList& todos);
void add_todo(TodoList& todos, const std::string& new_todo);
void edit_todo(TodoList& todos, const unsigned int& todo_index, const std::string& updated_todo);
void complete_todo(TodoList& todos, const unsigned int& todo_index);
void clear_todos(TodoList& todos);
void show_todos_performance(const TodoList& todos);

void show_emotion_questions(const EmotionQuestionsList& questions);
void add_emotion_question(EmotionQuestionsList& questions, const EmotionQuestion& new_question);
void edit_emotion_question(EmotionQuestionsList& questions, const unsigned int& question_index, const EmotionQuestion& updated_question);
void show_emotions_graph(const EmotionQuestionsList& questions);

using json = nlohmann::json;

int main() {
  // Loading config
  std::string config_path = "db.toml";
  std::ifstream config("db.json");
  json parsed_config = json::parse(config);

  TodoList todos2;
  parsed_config["todos"].get_to(todos2);
  show_todos(todos2);
  // std::cout << parsed_config["todos"].is_array() << "\n";
  // auto todos1 = parsed_config["todos"].array();
  // std::cout << "size: " << todos1.size() << "\n";
  // for (auto it = todos1.begin(); it != todos1.end(); it++) {
  //   std::cout << it.key() << ": " << it.value() << "\n";
  // }

  // toml::table parsed_config;
  // try
  // {
  //   parsed_config = toml::parse_file(config_path);
  //   std::cout << "Loading config...\n";
  // }
  // catch(const toml::parse_error& error)
  // {
  //   std::cout << "Error while parsing config: " << error.description() << "\n";
  //   return 1;
  // }

  // std::cout << "Todos array of tables: " << parsed_config["todos"].is_array_of_tables() << "\n";
  // toml::array* todo_array = parsed_config.as_array();
  // todo_array->for_each([](auto&& todo)
  //       {
  //         if constexpr (toml::is_table<decltype>(todo)) {

  //         }
  //         else {
  //           (*todo)++;
  //         }
  //           // if constexpr (toml::is_number<decltype(todo)>)
  //           //     (*el)++;
  //           // else if constexpr (toml::is_string<decltype(todo)>)
  //           //     el = "five"sv;
  //       });

  std::cout << "\\\\\\\\\\\\ Tracker Boi //////\n";
  
  int operation_value = 0;
  bool quit = false;

  while (!quit) {
    operation_value = get_selected_operation(operations);

    switch(operation_value) {
      case 1: {
        show_todos(todos);
        break;
      }
      case 2: {
        /// input todo, add it to list
        std::string new_todo;
        std::cout << "New Todo: ";
        std::cin >> new_todo;
        add_todo(todos, new_todo);
        break;
      }
      case 3: {
        /// get which todo to edit, enter new string, then update it in list
        int todo_value = 0;
        std::cout << "Todo number to update: ";
        std::cin >> todo_value;
        while (todo_value < 1 || todo_value > todos.size()) {
          std::cout << "You dumbass! See those todo numbers!!\n";
          std::cout << "Todo number to update: ";
          std::cin >> todo_value;
        }
        std::string updated_todo;
        std::cout << "Updated Todo: ";
        std::cin >> updated_todo;
        edit_todo(todos, todo_value-1, updated_todo);
        break;
      }
      case 4: {
        /// get which todo to complete, update it in list
        int todo_value = 0;
        std::cout << "Todo number to complete ✅: ";
        std::cin >> todo_value;
        while (todo_value < 1 || todo_value > todos.size()) {
          std::cout << "You dumbass! See those todo numbers!!\n";
          std::cout << "Todo number to complete ✅: ";
          std::cin >> todo_value;
        }
        complete_todo(todos, todo_value-1);
        break;
      }
      case 5: {
        /// ask for confirmation
        std::cout << "Do you really want to clear all todos? (y/n)";
        char option;
        std::cin >> option;
        if (option == 'n') {
          break;
        }
        else {
          /// clear all todos in list
          clear_todos(todos);
        }
        break;
      }
      case 6: {
        /// show some kind of performance graph
        show_todos_performance(todos);
        break;
      }
      case 7: {
        /// show all emotion questions, with their options
        break;
      }
      case 8: {
        /// input emotion question
        /// input first emotion option
        /// ask for next option?
        /// input next emotion option, so on ...
        /// save these in list
        break;
      }
      case 9: {
        /// input which emotion question
        /// edit question or answer?
        /// if option which option?
        /// get input, and update it in list
        break;
      }
      case 10: {
        /// Ask all questions, one by one
        /// store those reponses in the list
        break;
      }
      case 11: {
        /// Show some kind of performance graph
        break;
      }
      default: {
        quit = true;
        break;
      };
    }
  }

  return 0;
}

/// ✏️📝

void show_operations(const std::vector<std::string>& operations) {
  std::cout << "\n🔗 Operations:\n";
  for (unsigned long i=0; i<operations.size(); i++) {
    std::cout << " " << i+1 << ". " << operations[i] << "\n";
  }
}

uint8_t get_selected_operation(const std::vector<std::string>& ) {
  show_operations(operations);

  int operation_value = 0;
  std::cout << "\n ➡️  ";
  std::cin >> operation_value;
  while (operation_value < 1 || operation_value > operations.size()) {
    give_dumbass_feedback();
    std::cout << "\n ➡️  ";
    std::cin >> operation_value;
  }

  return operation_value;
}

void give_dumbass_feedback() {
  std::cout << "You dumbass! See those operation values!!\n";
}

void show_todos(const TodoList& todos) {
  std::cout << "\n🏅 Todos:\n";
  for (unsigned long i=0; i<todos.size(); i++) {
    std::cout << " " << i+1 << ". " << todos[i].first << (todos[i].second ? " ✅": "") << "\n";
  }
}

void add_todo(TodoList& todos, const std::string& new_todo) {
  todos.push_back({new_todo, false});
}

void edit_todo(TodoList& todos, const unsigned int& todo_index, const std::string& updated_todo) {
  todos[todo_index].first = updated_todo;
}

void complete_todo(TodoList& todos, const unsigned int& todo_index) {
  todos[todo_index].second = true;
}

void clear_todos(TodoList& todos) {
  todos.clear();
}

void show_todos_performance(const TodoList& todos) {
  /// TODO: Implement some kind of graph.
}

void show_emotion_questions(const EmotionQuestionsList& questions);
void add_emotion_question(EmotionQuestionsList& questions, const EmotionQuestion& new_question);
void edit_emotion_question(EmotionQuestionsList& questions, const unsigned int& question_index, const EmotionQuestion& updated_question);
void show_emotions_graph(const EmotionQuestionsList& questions);