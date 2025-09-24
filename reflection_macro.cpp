#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

// ---------- Step 1: Define a macro to expose members ----------
#define REFLECTABLE(...)                                                       \
  auto reflect() { return std::tie(__VA_ARGS__); }                             \
  auto reflect() const { return std::tie(__VA_ARGS__); }

// ---------- Step 2: Example class ----------
struct Person {
  std::string name;
  int age;
  bool is_student;

  REFLECTABLE(name, age, is_student)
};

struct Organization {
  std::string org_name;
  int established_year;
  std::vector<Person> members;
  REFLECTABLE(org_name, established_year, members)
};

// ---------- Step 3: Serialization ----------
template <typename T> std::string serialize(const T &obj) {
  std::ostringstream oss;
  auto members = obj.reflect();
  std::apply(
      [&oss](auto &&...elems) {
        ((oss << elems << '|'), ...); // Serialize members with a separator
      },
      members);
  return oss.str();
}

// ---------- Step 4: Deserialization ----------
template <typename T> T deserialize(const std::string &data) {
  T obj{};
  auto members = obj.reflect();
  std::istringstream iss(data);

  std::apply(
      [&](auto &&...elems) {
        // Lambda to unpack members
        ((iss >> elems, iss.ignore(1, '|')), ...);
      },
      members);
  return obj;
}

// ---------- Step 5: Demo ----------
int main() {
  Person p{"Alice", 30, true};
  Person q{"Bob", 25, false};
  Person r{"Charlie", 28, true};
  Person s{"Diana", 22, false};
  Organization org{"OpenAI", 2015, {p, q, r, s}};

  // Serialize
  std::string serialized = serialize(p);
  std::cout << "Serialized: " << serialized << "\n";

  decltype(auto) serialized_org = serialize(org);
  std::cout << "Serialized Organization: " << serialized_org << "\n";

  // Deserialize
  Person t = deserialize<Person>(serialized);
  std::cout << "Deserialized: name=" << q.name << ", age=" << q.age
            << ", is_student=" << std::boolalpha << q.is_student << "\n";

  decltype(auto) deserialized_org = deserialize<Organization>(serialized_org);
  std::cout << "Deserialized Organization: org_name="
            << deserialized_org.org_name
            << ", established_year=" << deserialized_org.established_year
            << ", members_count=" << deserialized_org.members.size() << "\n";
}
