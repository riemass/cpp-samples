#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>

using namespace std;

void draw(const int& x, ostream& out, size_t position) {
  out << string(position, ' ') << x << endl;
}

class object_t {
  public:
  object_t(int x) : self_(make_unique<int_model_t>(move(x))) {}
  object_t(const object_t& x) : self_(make_unique<int_model_t>(*x.self_)) {}
  object_t(object_t&& x) : self_(move(x.self_)) {}
  object_t& operator=(const object_t& tmp) {
    return *this = object_t(tmp);
  }
  object_t& operator=(object_t&& tmp) = default;

  friend void draw(const object_t& x, ostream& out, size_t position) {
    x.self_->draw_(out, position);
  }

  private:
  struct int_model_t {
    int_model_t(int x) : data_(move(x)) {}
    void draw_(ostream& out, size_t position) const {
      draw(data_, out, position);
    }
    int data_;
  };
  std::unique_ptr<int_model_t> self_;
};

using document_t = vector<object_t>;

void draw(const document_t& x, ostream& out, size_t position) {
  out << string(position, ' ') << "<document>" << endl;
  for (const auto& e : x) draw(e, out, position + 2);
  out << string(position, ' ') << "</document>" << endl;
}

int main(int argc, char* argv[]) {
  document_t document;
  document.reserve(4);
  document.emplace_back(0);
  document.emplace_back(1);
  document.emplace_back(2);
  document.emplace_back(3);

  reverse(document.begin(), document.end());

  draw(document, cout, 0);

  return 0;
}
